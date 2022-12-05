#pragma once
#include<iostream>
#include<regex>
#include <string>
using namespace std;

class Event{

private:

	char* name = nullptr;
	string time = "10:00";
	string date = "10/10/2010";

	static int NO_EVENTS;

public:

	const static int MIN_NAME_SIZE=3;

	char* getName() {
		char* nameCopy = this->copyArray(this->name);
		return nameCopy;
	}
	void setName(const char* name) {
		if (strlen(name) < Event::MIN_NAME_SIZE) {
			throw "Wrong name";
		}
		if (this->name != nullptr) {
			delete[] this->name;
		}
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	string getTime() {
		return this->time;
	}
	void setTime(string time) {
		regex pattern("([01]?[0-9]|2[0-3]):[0-5][0-9]");
		smatch x;
		regex_search(time, x, pattern);
		if (x[0].matched == false)
			cout << endl << "Wrong time";
		else this->time = time;
	}
	string getDate() {
		return this->date;
	}
	void setDate(string date) {
		regex pattern("^(1[0-2]|0[1-9])/(3[01]|[12][0-9]|0[1-9])/[0-9]{4}$");
		smatch x;
		regex_search(date, x, pattern);
		if (x[0].matched == false)
			cout << endl << "Wrong date";
		else this->date = date;
	}
	~Event() {
		cout << endl << "Event destructor";
		this->deleteEvent();
		Event::NO_EVENTS--;
	}
	void deleteEvent(){
		if (this->name != nullptr) {
			delete[]this->name;
			this->name = nullptr;
		}
	}
	Event() {
		this->setName("Event");
		cout << endl << "Calling event default constructor";
		Event::NO_EVENTS ++;
	}
	Event(const char* name, string date, string time) {
		this->setName(name);
		this->setDate(date);
		this->setTime(time);

		Event::NO_EVENTS++;
	}
	Event(const Event& event) {
		cout << endl << "Copy constructor";
		this->setName(event.name);
		this->setDate(event.date);
		this->setTime(event.time);
		Event::NO_EVENTS++;
	}
	void print() {
		cout << endl << "Event date: " << this->date;
		cout << endl << "Event time: " << this->time;
		if(this->name!=nullptr)
			cout << endl << "Event name: " << this->name;
	}
	char* capitalizeFirstLetter(const char* text) {
		char* newText = new char[strlen(text) + 1];
		strcpy(newText, text);
		for (int x = 0; x<strlen(text); x++) {
			if (x == 0) {
				newText[x] = toupper(text[x]);
			}
			else if (text[x - 1] == ' ') {
				newText[x] = toupper(text[x]);
			}
		}
		return newText;
	}
	static int getNoEvents() {
		return NO_EVENTS;
	}
	void operator=(const Event& event) {
		if (this == &event) {
			return;
		}
		this->date = event.date;
		this->time = event.time;
		if (this->name) {
			delete[]this->name;
			this->name = nullptr;
		}
		if (event.name != nullptr) {
			this->name = new char[strlen(event.name) + 1];
			memcpy(this->name, event.name, strlen(event.name) + 1);
		}
		else this->name = nullptr;
	}
	bool operator!=(Event event) {
		if (this->date != event.date) return true;
		else return false;
	}
	bool operator==(Event event) {
		if (this->date == event.date && this->time == event.time) return true;
		else return false;
	}
	friend void operator<< (ostream& out, Event& event);
	friend void operator>> (istream& in, Event& event);

	private:
		static char* copyArray(const char* array) {
			char* copy = new char[strlen(array) + 1];
			for (int i = 0; i < strlen(array) + 1; i++) {
				copy[i] = array[i];
			}
			copy[strlen(array) + 1] = '\0';
			return copy;
		}
};

int Event::NO_EVENTS = 0;

//https://www.oreilly.com/library/view/regular-expressions-cookbook/9781449327453/ch04s04.html

	bool validDate(string date) {
	regex pattern("^(1[0-2]|0[1-9])/(3[01]|[12][0-9]|0[1-9])/[0-9]{4}$");
	smatch x;
	regex_search(date, x, pattern);
	if (x[0].matched == true) return true;
	else return false;
}
	bool validTime(string time) {
	regex pattern("([01]?[0-9]|2[0-3]):[0-5][0-9]");
	smatch x;
	regex_search(time, x, pattern);
	if (x[0].matched == true) return true;
	else return false;
}
	bool validName(const char* name) {
	if (strlen(name) < Event::MIN_NAME_SIZE)
		return false;
	else return true;
}

	void operator>>(istream& in, Event& event) {
	cout << endl << "Event date: ";
	in >> event.date;
	if (validDate(event.date) == false)
		cout << endl << "Date is not ok";
	cout << endl << "Event time: ";
	in >> event.time;
	if (validTime(event.time) == false) 
		cout << endl << "Time is not ok";
	cout << endl << "Event name: ";
	char buffer[100];
	in >> buffer;
	if (event.name != nullptr) {
		delete[] event.name;
		event.name = nullptr;
	}
	event.name = new char[strlen(buffer) + 1];
	strcpy(event.name, buffer);
	if (validName(event.name) == false)
		cout << "Name is too short";
	Event::NO_EVENTS += 1;
}
	void operator<<(ostream& out, Event& event) {
		out << endl << "Event date: " << event.date;
		out << endl << "Event time: " << event.time;
		if (event.name != nullptr)
			out << endl << "Event name: " << event.name;
}
