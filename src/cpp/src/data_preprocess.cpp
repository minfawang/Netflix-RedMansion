#define  _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <sys/stat.h>
#include "includes.hpp"


using namespace std;


void test_data() {
	struct stat results;
	ifstream main;

	record rcd;
	char *data_name = "qual_data.data";

	int size;
	
	main.open(data_name, ios::binary | ios::in);

	if (stat(data_name, &results) == 0) {

	} else {
		cout << "Stat Error" << endl;
		system("pause");
		exit(-1);
	}

	size = results.st_size;
	cout << size << endl;

	system("pause");

	if (!main.is_open()) {
		cout << "Cannot open file" << endl;
		system("pause");
		exit(-1);
	}


	
	
	record *data = new record[size / sizeof(record)];
	main.read((char *)data, size);

	cout << data[0] << endl;

	delete data;
}

void preprocess() {
	ifstream all_data, all_index;
	ofstream main, prob, qual;

	int cnt = 0;
	
	all_data.open("all.dta");
	all_index.open("all.idx");

	main.open("main_data.data", ios::binary | ios::out);
	prob.open("prob_data.data", ios::binary | ios::out);
	qual.open("qual_data.data", ios::binary | ios::out);

	if (!all_data.is_open() || !all_index.is_open()) {
		cout << "Cannot open file" << endl;
		system("pause");
		exit(-1);
	}

	while (all_data.good()) {
		record rcd;
		unsigned int user, movie, date;
		float score;
		int mark;

		all_data >> user >> movie >> date >> score;
		all_index >> mark;

		rcd.user = user;
		rcd.movie = movie;
		rcd.date = date;
		rcd.score = score;

		if (mark == 1 || mark == 2 || mark == 3) {
			main.write((char *)&rcd, sizeof(rcd));
		} else if (mark == 4) {
			prob.write((char *)&rcd, sizeof(rcd));
		} else {
			qual.write((char *)&rcd, sizeof(rcd));
		}

		cnt++;

		if (cnt % 10000 == 0) {
			cout << cnt << endl;
		}
	}


	
}

int main(int argc, char * argv[]) {
	preprocess();
	test_data();
	system("pause");
}