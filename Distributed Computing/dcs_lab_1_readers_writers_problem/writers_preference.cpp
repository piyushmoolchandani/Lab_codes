#include<iostream>
#include<pthread.h>
#include<fstream>
#include<semaphore.h>

using namespace std;

sem_t reader_lock, writer_lock, reader_writer_lock, resource_lock;
int reader_count = 0, writer_count = 0;

void * reader(void * args){
	
	sem_wait(&reader_writer_lock);
	sem_wait(&reader_lock);
	reader_count++;
	if (reader_count == 1)
		sem_wait(&resource_lock);
	sem_post(&reader_lock);
	sem_post(&reader_writer_lock);
	
	cout << "Reader" << endl;
	
	sem_wait(&reader_lock);
	reader_count--;
	if (reader_count == 0)
		sem_post(&resource_lock);
	sem_post(&reader_lock);
	return NULL;
}

void * writer(void * args){

	sem_wait(&writer_lock);
	writer_count++;
	if (writer_count == 1)
		sem_post(&reader_writer_lock);
	sem_post(&writer_lock);
	
	sem_wait(&resource_lock);
	cout << "Writers" << endl;
	sem_post(&resource_lock);

	sem_wait(&writer_lock);
	writer_count--;
	if (writer_count == 0)
		sem_wait(&reader_writer_lock);
	sem_post(&writer_lock);
	return NULL;
}

int main(){

	cout << "Enter number of readers and writers respectively: ";
	int rc, wc;
	cin >> rc >> wc;
	
	sem_init(&reader_writer_lock, 0, 1);
	sem_init(&reader_lock, 0, 1);
	sem_init(&writer_lock, 0, 1);
	sem_init(&resource_lock, 0, 1);
	pthread_t writers[wc];
	pthread_t readers[rc];
	
	for (int i = 0; i < rc; i++){
		pthread_create(&writers[i], NULL, writer, NULL);
		pthread_create(&readers[i], NULL, reader, NULL);
	}
	
	for (int i = 0; i < rc; i++){
		pthread_join(readers[i], NULL);
	}
	for (int i = 0; i < wc; i++){
		pthread_join(writers[i], NULL);
	}
	return 0;

}
