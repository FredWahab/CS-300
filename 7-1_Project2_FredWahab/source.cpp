//============================================================================
// Name        : source.cpp
// Author      : Fred Wahab
// Version     : 1.0
// Description : a command-line program written in C++ that prompts the user 
// to ask for the file name that contains the course data and read that file 
// into course objects that are stored in a data structure. 
//============================================================================

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//initialize global objects and variables
struct Course {
	string courseNumber;
	string courseName;
	vector<string> coursePrereqs;
};
vector<Course> courses;

//LOAD DATA STRUCTURE
void LoadDataStructure() {
	//local variables
	string fileName;

	//get filename
	cout << "Please enter name of file: ";
	cin >> fileName;
	cout << endl;

	//open file
	ifstream infile;
	infile.open(fileName);

	//insert data into courses
	if (infile.is_open()) {
		string line;

		//read file line by line
		while (getline(infile, line)) {
			vector <string> tokens;
			string token;
			stringstream ss(line);

			//tokenize at ','
			while (getline(ss, token, ',')) {
				tokens.push_back(token);
			}

			//create new course and add data from file
			Course newCourse = Course();
			newCourse.courseNumber = tokens[0];
			newCourse.courseName = tokens[1];
			//if prereqs exist add to course
			if (tokens.size() > 2) {
				for (int i = 2; i < tokens.size(); i++) {
					newCourse.coursePrereqs.push_back(tokens[i]);
				}
			}

			//add new course to courses
			courses.push_back(newCourse);
		}

		cout << "Data Structure successfully loaded!" << endl;
	}
	else {
		cout << "Error: Filename not found." << endl;
	}

	system("PAUSE");
	infile.close();
}

//PRINT COURSE LIST
void PrintCourseList() {

	//validate data loaded from file
	if (courses.size() > 0) {

		//sort courses alphanumerically
		for (int i = 0; i < courses.size() - 1; i++) {
			for (int j = 0; j < courses.size() - i - 1; j++) {
				if (courses[j].courseNumber > courses[j + 1].courseNumber) {
					swap(courses[j + 1], courses[j]);
				}
			}
		}

		//loop and print courses number and name
		cout << "---------------------------------------------" << endl;
		cout << "Courses List" << endl;
		cout << "---------------------------------------------" << endl;
		for (int i = 0; i < courses.size(); i++) {
			cout << courses[i].courseNumber << ", ";
			cout << courses[i].courseName << endl;
		}
		cout << "---------------------------------------------" << endl;
	}
	else {
		cout << "Error: Load Data Structure first." << endl;
		system("PAUSE");
	}
}

//PRINT COURSE
void PrintCourse() {

	//validate data loaded from file
	if (courses.size() > 0) {
		string courseInput;
		int courseFound = 0;

		cout << "What course do you want to know about? ";
		cin >> courseInput;
		cout << endl;

		//loop through courses to find courseInput match
		for (int i = 0; i < courses.size(); i++) {
			if (courses[i].courseNumber == courseInput) {
				cout << "---------------------------------------------" << endl;
				cout << "Course Information" << endl;
				cout << "---------------------------------------------" << endl;
				cout << courses[i].courseNumber << ", ";
				cout << courses[i].courseName << endl;
				cout << "Prerequisites: ";
				if (courses[i].coursePrereqs.size() > 0) {
					int prereqSize = courses[i].coursePrereqs.size();

					//loop through course prereqs
					for (int j = 0; j < prereqSize - 1; j++) {
						cout << courses[i].coursePrereqs[j] << ", ";
					}
					//eliminate comma from last entry
					cout << courses[i].coursePrereqs[prereqSize - 1];

					courseFound = 1;
				}
				else {
					cout << "None";
				}
				cout << endl;
				cout << "---------------------------------------------" << endl;
			}
		}

		//course input validation
		if (courseFound == 0) {
			cout << "Error: Invalid Course" << endl;
			system("PAUSE");
		}

	}
	else {
		cout << "Error: Load Data Structure first." << endl;
		system("PAUSE");
	}
}

//MAIN
int main() {
	bool quit = false;

	cout << endl;
	cout << "Welcome to the course planner." << endl;

	do {
		string input;

		//menu
		cout << endl;
		cout << "  1. Load Data Structure" << endl;
		cout << "  2. Print Course List" << endl;
		cout << "  3. Print Course" << endl;
		cout << "  9. Exit" << endl;
		cout << endl;
		cout << "What would you like to do? ";
		cin >> input;
		cout << endl;

		//input validation
		while ((input != "1") && (input != "2") && (input != "3") && (input != "9")) {
			cout << "Error: " << input << " is not a valid option." << endl;
			system("PAUSE");
			cout << endl;
			cout << "  1. Load Data Structure" << endl;
			cout << "  2. Print Course List" << endl;
			cout << "  3. Print Course" << endl;
			cout << "  9. Exit" << endl;
			cout << endl;
			cout << "What would you like to do? ";
			cin >> input;
			cout << endl;
		}

		//navigation
		if (input == "1") {
			LoadDataStructure();
		}
		if (input == "2") {
			PrintCourseList();
		}
		if (input == "3") {
			PrintCourse();
		}
		if (input == "9") {
			cout << endl;
			cout << "Thank you for using the course planner!" << endl;
			exit(quit);
		}
	} while (!quit);

	return 0;
}