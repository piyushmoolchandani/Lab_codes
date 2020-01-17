#include<iostream>
#include<thread>
#include<fstream>
#include<semaphore>

using namespace std;

sem_t reader_writer_lock;
sem_t reader_reader_lock;
int reader_count = 0;
int temp = 0;

void reader();
void writer();

int main(){
	
	cout << "Readers preference problem." << endl;
	cout << "Please enter number of readers: " << endl;
	int reader_count;
	cin >> reader_count;
	
	semaphore s;
}

void reader(){
	/*
	ifstream fin;
	fin.open("text_data.txt");
	char temp;
	if (!fin.eof())
		fin.read(temp);
	*/
	sem_wait(&reader_reader_lock);
	reader_count += 1;
	if (reader_count == 1){
		sem_wait(&reader_writer_lock);
	}
	cout << temp << endl;
	sem_post(&reader_reader_lock)
	
	sem_wait(&reader_reader_lock);
	reader_count--;
	if (reader_count == 0)
		sem_post(&reader_writer_lock);
	}
	
	
		
}

void writer(){
	sem_wait(&reader_writer_lock);
	temp = 7;
	puts(temp);
	sem_post(&reader_writer_lock);
}
