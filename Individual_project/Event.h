#pragma once
#include<iostream>
#include <string>
using namespace std;

class Event{

private:

	char* name = nullptr;
	string time = " ";
	string date = " ";
	string place = " ";

	static int NO_EVENTS;

public:

	const static int MIN_NAME_SIZE=3;

	char* getName() {
		char* nameCopy = this->copyArray(this->name);
		return nameCopy;
	}
	void setName(const char* name) {
		if (strlen(name) < Event::MIN_NAME_SIZE) {
			throw "Invalid name";
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
		this->time = time;
	}
	string getDate() {
		return this->date;
	}
	void setDate(string date) {
		this->date = date;
	}
	string getPlace() {
		return this->place;
	}
	void setPlace(string place) {
		this->place = place;
	}
	~Event() {
		cout << endl << "Event destructor";
		this->deleteEvent();
		Event::NO_EVENTS -= 1;
	}
	void deleteEvent(){
		if (this->name != nullptr) {
			delete[]this->name;
			this->name = nullptr;
		}
	}
	Event() {
		this->setDate("Unknown");
		this->setTime("Unknown");
		this->setName("Event");
		cout << endl << "Calling event default constructor";
		Event::NO_EVENTS += 1;
	}
	Event(const char* name, string date, string place, string time) {
		this->setName(name);
		this->setDate(date);
		this->setPlace(place);
		this->setTime(time);

		Event::NO_EVENTS += 1;
	}
	Event(const Event& event) {
		cout << endl << "Copy constructor";
		this->setName(event.name);
		this->setDate(event.date);
		this->setPlace(event.place);
		this->setTime(event.time);
		Event::NO_EVENTS += 1;
	}
	void print() {
		cout << endl << "Event date: " << this->date;
		cout << endl << "Event time: " << this->time;
		cout << endl << "Event place: " << this->place;
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
		this->place = event.place;
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
		Event::NO_EVENTS++;
	}
	bool operator!=(Event event) {
		if (this->date != event.date) return true;
		else return false;
	}
	bool operator==(Event event) {
		if (this->date == event.date && this->time == event.time && this->place == event.place) return true;
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

void operator>>(istream& in, Event& event) {
	cout << endl << "Event date: ";
	in >> event.date;
	cout << endl << "Event time: ";
	in >> event.time;
	cout << endl << "Event place: ";
	in >> event.place;
	cout << endl << "Event name: ";
	char buffer[100];
	in >> buffer;
	if (event.name != nullptr) {
		delete[] event.name;
		event.name = nullptr;
	}
	event.name = new char[strlen(buffer) + 1];
	strcpy(event.name, buffer);
}
void operator<<(ostream& out, Event& event) {
	out << endl << "Event date: " << event.date;
	out << endl << "Event time: " << event.time;
	out << endl << "Event place: " << event.place;
	out << endl << (event.name != nullptr ? "Event name: " + string(event.name) : "No event name");
}
