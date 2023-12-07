#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
	ifstream data;
	data.open("input.txt");
	string line;

	if (data.is_open()) {
		
		while (std::getline(data, line)) {

		}
	}

	return 0;
}