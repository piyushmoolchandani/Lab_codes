#include<iostream>
#include<queue>
#include<vector>
#include<time.h>
#include<string.h>
#include<thread>
#include<mutex>
#include<unistd.h>
#include<utility>
#include<string>

#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
using namespace std;

#define N 3
#define REQUEST 1
#define REPLY 2

#define message_type_idx 0
#define timestamp_idx 1
#define request_id_idx 11
#define reply_id_idx 1

#define size_request_buffer 12
#define size_reply_buffer 2
#define max_message_size 12


mutex array_lock, queue_lock;

int my_id;
int port;
time_t timestamp;
time_t current_time;
std::queue < pair<int, struct sockaddr_in> > pending_requests;
bool * reply_received = new bool[N];
bool cse_query_live = true;
std::vector < pair<int, int> > dependent_nodes;

int sockfd;
struct sockaddr_in servaddr;

void check_and_act(){

	cout << "Thread check and act activated." << endl;
	while(1){
		// acquire lock for array
		array_lock.lock();
		
		bool done = true;
		for (int i = 0; i < N; i++){
			if (i == my_id)
				continue;
			if (reply_received[i] != 1){
				done = false;
				break;
			}
		}
		
		if (not done){
			// release lock for array
			array_lock.unlock();
		}
		else{
			
			// acquire lock for queue;
			queue_lock.lock();
			
			time(&current_time);
			cout << current_time;
			cout << ": critical section entry time" << endl;
			
			cout << "Entered critical section for requested generated with timestamp: " << timestamp << endl;
			
			for (int i = 0; i < N; i++)
				reply_received[i] = false;
				
			// send reply to all nodes in queue
			while(not pending_requests.empty()){
			
				pair <int, struct sockaddr_in> temp = pending_requests.front();
				pending_requests.pop();
				string reply_str = to_string(REPLY * 10 + my_id);
				char * reply = new char[size_reply_buffer + 1];
				reply_str.copy(reply, size_reply_buffer, 0);
				
				sendto(sockfd, (const char *)reply, strlen(reply), MSG_CONFIRM, (const struct sockaddr *) &(temp.second), sizeof(temp.second));
			}	
			
			time(&current_time);
			cout << current_time << ": critical section exit time" << endl;
			cse_query_live = false;
			
			// release lock for queue;
			queue_lock.unlock();
			
			// release lock for array
			array_lock.unlock();
			
			// wait for some time
			sleep(1);
			
			// new critical section entry 
			time(&timestamp);
			
			// send timestamp, my_id and request to all dependent nodes
			for (int i = 0; i < N - 1; i++){
				pair <int, int> temp = dependent_nodes[i];
				struct sockaddr_in dependent_addr;
				memset(&dependent_addr, 0, sizeof(dependent_addr));
				
				dependent_addr.sin_family = AF_INET;
				dependent_addr.sin_port = htons(temp.second);
				dependent_addr.sin_addr.s_addr = INADDR_ANY;
				
				char * request = new char[size_request_buffer + 1];
				string request_str = to_string(REQUEST);
				request_str.append(to_string(timestamp));
				request_str.append(to_string(my_id));
				request_str.copy(request, size_request_buffer, 0);
				
				sendto(sockfd, (const char *)request, strlen(request), MSG_CONFIRM, (const struct sockaddr *) &dependent_addr, sizeof(dependent_addr));
			}
		}
	}
}
			
void message_handler(){
	
	cout << "Thread message handler activated." << endl;
	
	struct sockaddr_in sender_addr;
	memset(&sender_addr, 0, sizeof(sender_addr));
	char buffer[max_message_size];
	
	while (true){
		int message;
		int n;
		
		n = recvfrom(sockfd, (char *)buffer, max_message_size, MSG_WAITALL, (struct sockaddr *)&sender_addr, sizeof(sender_addr));
		
		if (message == REQUEST){
			
			time_t foreign_timestamp;
			int foreign_id;
			
			// retrieve timestamp and id
			
			if (foreign_timestamp > timestamp){
				
				// acquire lock for queue
				queue_lock.lock();
				
				//pending_requests.push(foreign_id);
				
				// release lock for queue
				queue_lock.unlock();
			}
		}
		
		else if (message == REPLY){
			
			int foreign_id;
			// retrieve id
			
			// acquire lock for array
			array_lock.lock();
			
			reply_received[foreign_id] = 1;
			
			// release lock for array
			array_lock.unlock();
		}
	}
}

int main(int argc, char ** argv){
	
	/* 
		argv:
		1: id
		2: port number 1
		3: port number 2
		4: port number 3
	*/
	my_id = atoi(argv[1]);
	port = atoi(argv[my_id + 2]);
	
	cout << "Node: " << my_id << endl;
	
	for (int i = 0; i < N; i++){
		if (i != my_id)
			dependent_nodes.push_back(make_pair(i, atoi(argv[i + 2])));
		reply_received[i] = false;
	}
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		cout << "Socket creating failed" << endl;
		exit(0);
	}
	
	cout << "Socket successfully created" << endl;
	
	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(port);
	
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
		cout << "Bind failed"  << endl;
		exit(0);
	}
	
	cout << "Bind successful" << endl;
	
	thread t_message_handler(&message_handler);
	thread t_check_and_act(&check_and_act);
	
	t_message_handler.join();
	t_check_and_act.join();
	
	return 0;
}
