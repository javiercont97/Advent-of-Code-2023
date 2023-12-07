#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string rowSeparator(int colSize) {
	string separator = "+";
	for (int i = 0; i < colSize + 2; i++) {
		separator += "-";
	}
	return separator;
}

void printRowSeparator() {
	printf("%s%s%s+\n", rowSeparator(50).c_str(), rowSeparator(60).c_str(),
		   rowSeparator(5).c_str());
}

string converLiteralToNumeric(string line) {
	string newLine = "";
	map<string, string> matchingLiterals = {
		{"0", "0"}, {"1", "1"}, {"2", "2"}, {"3", "3"}, {"4", "4"},
		{"5", "5"}, {"6", "6"}, {"7", "7"}, {"8", "8"}, {"9", "9"}};

	vector<string> tokens = {};

	for (int i = 0; i < line.length(); i++) {
		int min = 100000;
		string key = "";
		for (auto digit : matchingLiterals) {
			int n = line.find(digit.first, i);
			if (n >= 0) {
				if (n < min) {
					min = n;
					key = digit.second;
				}
			}
		}
		newLine += key;
	}
	return newLine;
}

int pickFirstAndLastDigit(string line) {
	if (line.empty()) return 0;
	return 10 * ((int)line.at(0) - '0') + (int)line.at(line.length() - 1) - '0';
}

int main() {
	ifstream data;
	data.open("input.txt");
	string line;

	int total = 0;
	if (data.is_open()) {
		printRowSeparator();
		while (std::getline(data, line)) {
			string parsedStr = converLiteralToNumeric(line);
			int sum = pickFirstAndLastDigit(parsedStr);
			printf("| %-50s | %-60s | %5d |\n", line.c_str(), parsedStr.c_str(),
				   sum);
			printRowSeparator();

			converLiteralToNumeric(line).c_str();

			total += sum;
		}

		cout << total << endl;
	}

	return 0;
}