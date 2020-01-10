#include<iostream>
#include<thread>
#include<fstream>
semaphore s;


using namespace std;

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
	ifstream fin;
	fin.open("text_data.txt");
	char temp;
	if (!fin.eof())
		fin.read(temp);
