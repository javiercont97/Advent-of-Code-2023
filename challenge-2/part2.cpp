#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int parseInt(string s);
string intToString(int);
vector<string> split(string s, char separator);

struct Roll {
	int red;
	int green;
	int blue;
};

struct Game {
	int id;
	vector<Roll> rolls;
};

Game parseGame(string game);
vector<Roll> parseRolls(string gameRolls);

string printRolls(Game game) {
	string out = "\n[\n";
	for (Roll g : game.rolls) {
		out += "\t{ red: ";
		out += intToString(g.red);
		out += ", green: ";
		out += intToString(g.green);
		out += ", blue: ";
		out += intToString(g.blue);
		out += "}\n";
	}
	out += "]\n";
	return out;
}

int main() {
	ifstream data;
	data.open("input.txt");
	string line;

	int total = 0;
	if (data.is_open()) {
		int idsSum = 0;

		while (std::getline(data, line)) {
			Game game = parseGame(line);
			Roll maxCubes = {
				red : INT32_MIN,
				green : INT32_MIN,
				blue : INT32_MIN
			};

			for (Roll g : game.rolls) {
				if (g.red > maxCubes.red) maxCubes.red = g.red;
				if (g.green > maxCubes.green) maxCubes.green = g.green;
				if (g.blue > maxCubes.blue) maxCubes.blue = g.blue;
			}

			int power = maxCubes.red * maxCubes.green * maxCubes.blue;
            total += power;
			printf("%d [%d]: %s\n", game.id, power, printRolls(game).c_str());
		}

		printf("Total power sum = %d\n", total);
	}
	return 0;
}

Game parseGame(string gameString) {
	Game game = {
		id : parseInt(gameString.substr(5, gameString.find(':') - 5)),
		rolls : parseRolls(
			gameString.substr(gameString.find(':') + 1, gameString.length()))
	};
	return game;
}

vector<Roll> parseRolls(string gameRolls) {
	vector<Roll> out = {};
	vector<string> sets = split(gameRolls, ';');
	for (string set : sets) {
		vector<string> roll = split(set, ',');
		Roll currentRoll{red : 0, green : 0, blue : 0};
		for (string color : roll) {
			int redColor = color.find("red");
			int greenColor = color.find("green");
			int blueColor = color.find("blue");
			if (redColor >= 0) {
				currentRoll.red = parseInt(color.substr(1, redColor - 2));
			} else if (greenColor >= 0) {
				currentRoll.green = parseInt(color.substr(1, greenColor - 2));
			} else if (blueColor >= 0) {
				currentRoll.blue = parseInt(color.substr(1, blueColor - 2));
			}
		}
		out.push_back(currentRoll);
	}
	return out;
}

int parseInt(string s) {
	int n = 0;
	int factor = 1;
	for (int i = 1; i <= s.length(); i++) {
		n += (s.at(s.length() - i) - '0') * factor;
		factor *= 10;
	}
	return n;
}

string intToString(int n) {
	map<int, string> digitToStringMap = {{0, "0"}, {1, "1"}, {2, "2"}, {3, "3"},
										 {4, "4"}, {5, "5"}, {6, "6"}, {7, "7"},
										 {8, "8"}, {9, "9"}};

	string out = "";
	do {
		int lastDigit = n % 10;
		n /= 10;
		out = digitToStringMap[lastDigit] + out;
	} while (n != 0);

	return out;
}

vector<string> split(string s, char separator) {
	vector<string> out = {};
	string subs = "";
	for (char c : s) {
		if (c == separator) {
			out.push_back(subs);
			subs = "";
			continue;
		}
		subs += c;
	}
	out.push_back(subs);
	return out;
}