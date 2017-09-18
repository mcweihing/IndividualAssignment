#include "MyFunctions.h"

using namespace std;

bool isInt(char token) {
	int ascii = (int)token;
	return ((ascii > 47) && (ascii < 58));
}

string getCost(string input, int start) {
	string cost;
	if (input[start - 1] != ' ') throw BadInput();
	//using index now because I don't have a set length to pull from (ie 0.99 or 100.99)
	int index = start;
	char token = input[index];
	//pull digits before decimal
	while (token != '.') {
		if (isInt(token)) {
			cost += token;
		}
		else throw BadInput();
		token = input[++index];
	}
	//token is now a decimal point
	cost += token;
	++index;
	//now just need two more digits aftrer decimal
	for (int i = index; i < index + 2; ++i) {
		token = input[i];
		if (isInt(token)) {
			cost += token;
		}
		else throw BadInput();
	}
	return cost;
}
string getDepartmentCode(string input, int start) {
	string departmentCode;
	if (input[start - 1] != ' ') throw BadInput();
	//gets the next 4 char's ensuring each is a capital letter
	for (int i = start; i < (start + 4); ++i) {
		char token = input[i];
		int ascii = (int)token;
		if ((ascii > 64) && (ascii < 91)) {
			departmentCode += token;
		}
		else {
			throw BadInput();
		}
	}
	return departmentCode;
}
string getNumber(string input, int start, int length) {
	string number;
	if (input[start - 1] != ' ') throw BadInput();
	//takes the next 'length' digits 0-9
	for (int i = start; i < start + length; ++i) {
		char token = input[i];
		if (isInt(token)) {
			number += token;
		}
		else {
			throw BadInput();
		}
	}
	return number;
}
string getName(string input, int start) {
	if (input[start - 1] != ' ') throw BadInput();
	//takes the rest of the input line
	string name = input.substr(start, input.size() - start);
	return name;
}
string getDate(string input, int start) {
	string date;
	if (input[start - 1] != ' ') throw BadInput();
	string month = input.substr(start, 2);
	//month string parsed into an int for easy comparisons
	int monthInt = atoi(month.c_str());
	//indicates an invalid month
	if ((monthInt < 1) || (monthInt > 12)) throw BadInput();
	date += month;

	int index = start + 2;
	//only accepts '/' to separate month and year
	if (input[index++] != '/') throw BadInput();
	date += '/';
	//take the year, ensure each digit is between 0-9
	for (index; index < start + 7; ++index) {
		char token = input[index];
		if (isInt(token)) {
			date += token;
		}
		else throw BadInput();
	}
	return date;
}

bool costExists(book* currentBook) {
	//checks to see if any of the costs have been defined for given book
	cost costs = currentBook->Cost;
	string costNew = costs.costNew;
	string costUsed = costs.costUsed;
	string costRent = costs.costRent;
	string costElectronic = costs.costElectronic;
	bool noneExist = ((costNew == "") && (costUsed == "") && (costRent == "") && (costElectronic == ""));
	return !noneExist;
}
double compareCost(book* currentBook, string compare) {
	vector<double> existingCosts;
	cost costs = currentBook->Cost;
	//pulls all costs that have been defined
	if (costs.costNew != "") {
		double costNew = atof((costs.costNew).c_str());
		existingCosts.push_back(costNew);
	}
	if (costs.costUsed != "") {
		double costUsed = atof((costs.costUsed).c_str());
		existingCosts.push_back(costUsed);
	}
	if (costs.costRent != "") {
		double costRent = atof((costs.costRent).c_str());
		existingCosts.push_back(costRent);
	}
	if (costs.costElectronic != "") {
		double costElectronic = atof((costs.costElectronic).c_str());
		existingCosts.push_back(costElectronic);
	}
	//find minimum value
	if (compare == "min") {
		double min = existingCosts[0];
		for (int i = 0; i < existingCosts.size(); ++i) {
			double temp = existingCosts[i];
			if (temp < min) min = temp;
		}
		return min;
	}
	//find maximum value
	if (compare == "max") {
		double max = existingCosts[0];
		for (int i = 0; i < existingCosts.size(); ++i) {
			double temp = existingCosts[i];
			if (temp > max) max = temp;
		}
		return max;
	}
}
double average(vector<double> vec) {
	//standard arithmetic average
	double avg;
	if (vec.size() > 0) {
		double sum = 0;
		for (int i = 0; i < vec.size(); ++i) {
			sum += vec[i];
		}
		avg = sum / vec.size();
	}
	else {
		avg = 0;
	}
	return avg;
}

bool keyExists(vector<string> list, string key) {
	//checks to see if key exists in given vector of keys
	for (int i = 0; i < list.size(); ++i) {
		if (list[i] == key) return true;
	}
	return false;
}
