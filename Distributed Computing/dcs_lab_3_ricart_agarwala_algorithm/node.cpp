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
#define request 1
#define reply 2

#define message_type_idx 0
#define timestamp_idx 1
#define request_id_idx 11
#define reply_id_idx 1

#define size_request_buffer 12
#define size_reply_buffer 2


mutex array_lock, queue_lock;

int my_id;
int port;
time_t timestamp;
time_t current_time;
std::queue < pair<int, int> > pending_requests;
bool * reply_received = new bool[N];
bool cse_query_live = true;
std::vector < pair<int, int> > dependent_nodes;

void check_and_act(int sockfd){

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
				reply_received[i] = 0;
				
			// send reply to all nodes in queue
			
			// give some wait or sleep time
			
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
			
			// send timestamp, my_id and request to all dependent nodes
		}
	}
}
			
void message_handler(int sockfd){
	
	cout << "Thread message handler activated." << endl;
	int message;
	
	// receive message and convert to int
	
	if (message == request){
		
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
	
	else if (message == reply){
		
		int foreign_id;
		// retrieve id
		
		// acquire lock for array
		array_lock.lock();
		
		reply_received[foreign_id] = 1;
		
		// release lock for array
		array_lock.unlock();
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
	}
	
	// Work going on below
	
	int sockfd;
	struct sockaddr_in servaddr;
	
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
	
	thread t_message_handler(&message_handler, sockfd);
	thread t_check_and_act(&check_and_act, sockfd);
	
	t_message_handler.join();
	t_check_and_act.join();
	
	return 0;
}
