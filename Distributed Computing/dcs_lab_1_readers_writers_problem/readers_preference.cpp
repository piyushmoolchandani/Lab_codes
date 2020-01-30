#include<iostream>
#include<pthread.h>
#include<fstream>
#include<semaphore.h>
#include<time.h>
#include<unistd.h>

using namespace std;

sem_t reader_writer_lock;
sem_t reader_reader_lock;
int reader_count;
int char_generator = 100;

void *reader(void * args);
void *writer(void * args);

int main(){
	
	cout << "Enter number of readers and writers respectively: ";
	int rc, wc;
	cin >> rc >> wc;
	
	sem_init(&reader_writer_lock, 0, 1);
	sem_init(&reader_reader_lock, 0, 1);
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

void *reader(void * args){
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
	
	sleep(.1);
	cout << "\nReader";
	ifstream fi;
	string line;
	fi.open("data.txt", ios :: in);
	while(fi){
		getline(fi, line);
		cout << line << endl;
	}
	fi.close();
	
	sem_wait(&reader_reader_lock);
	reader_count--;
	if (reader_count == 0){
		sem_post(&reader_writer_lock);
	}
	sem_post(&reader_reader_lock);
	return NULL;
}

void *writer(void * args){
	sem_wait(&reader_writer_lock);
	
	sleep(.1);
	cout << "\nWriter";
	ofstream fo;
	fo.open("data.txt", ios :: out);
	if (fo) {
		char_generator += 1;
		char temp_c = char_generator;
		fo << temp_c << " ";
	}
	fo.close();
	
	sem_post(&reader_writer_lock);
	return NULL;
}
