#include<iostream>
#include<thread>
#include<fstream>
#include<semaphore.h>

using namespace std;

sem_t reader_writer_lock;
sem_t reader_reader_lock;
int reader_count;
int temp = 900;

void * reader();
void * writer();

int main(){
	
	cout << "Readers preference problem." << endl;
	cout << "Please enter number of readers: " << endl;
	cin >> reader_count;
	
	sem_init(&reader_writer_lock, 0, 1);
	sem_init(&reader_reader_lock, 0, 1);
	pthread_t writer;
	pthread_t readers[reader_count];
	
	pthread_create(&writer, NULL, writer, NULL);
	for (int i = 0; i < reader_count; i++){
		pthread_create(&readers[i], NULL, reader, NULL);
	}
	pthread_join(writer, NULL);
	for (int i = 0; i < reader_count; i++){
		pthread_join(readers[i], NULL);
	}
	return 0;
}

void * reader(){
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
	sem_post(&reader_reader_lock);
	
	cout << temp << endl;
	
	sem_wait(&reader_reader_lock);
	reader_count--;
	if (reader_count == 0){
		sem_post(&reader_writer_lock);
	}
	sem_wait(&reader_reader_lock);
}

void * writer(){
	sem_wait(&reader_writer_lock);
	temp -= 1;
	puts(temp);
	sem_post(&reader_writer_lock);
}
