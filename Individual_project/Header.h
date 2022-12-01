#pragma once
#include<iostream>
#include<string>
using namespace std;

class location {

	private:

		int noOfSeats = 0;
		int noOfRows = 0;
		int noOfZones = 0;
		int* noOfSeatsPerRow = nullptr;

	public:

		const static int MIN_NO_OF_SEATS = 50;
		const static int MAX_NO_OF_SEATS = 10000;
		const static int MIN_NO_OF_ROWS = 50;
		const static int MAX_NO_OF_ROWS = 200;
		const static int MIN_NO_OF_ZONES = 1;
		const static int MAX_NO_OF_ZONES = 4;
		const static int MIN_SEATS_PER_ROW = 1;
		const static int MAX_SEATS_PER_ROW = 50;

		int getNoOfSeats() {
			return this->noOfSeats;
		}
		void setNoOfSeats(int noOfSeats) {
			if (noOfSeats<location::MIN_NO_OF_SEATS || noOfSeats>location::MAX_NO_OF_SEATS) {
				throw "Invalid number of seats";
			}
			this->noOfSeats = noOfSeats;
		}

		int getNoOfRows() {
			return this->noOfRows;
		}
		void setNoOfRows(int noOfRows) {
			if (noOfRows<location::MIN_NO_OF_ROWS || noOfRows>location::MAX_NO_OF_ROWS) {
				throw "Invalid number of rows";
			}
			this->noOfRows = noOfRows;
		}

		int getZones() {
			return this->noOfZones;
		}
		void setZones(int noOfZones) {
			if (noOfZones<location::MIN_NO_OF_ZONES || noOfZones>location::MAX_NO_OF_ZONES) {
				throw "Invalid zone";
			}
			this->noOfZones = noOfZones;
		}

		void setNoOfSeatsPerRow(int* noOfNewSeatsPerRow, int noOfNewRows) {
			if (noOfNewRows <= 0) {
				throw "Number of rows is not alright";
			}
			if (noOfNewSeatsPerRow == nullptr) {
				throw "The SeatsPerRow pointer is not alright";
			}
			for (int i = 0; i < noOfRows; i++) {
				if (noOfNewSeatsPerRow[i] < location::MIN_SEATS_PER_ROW || noOfNewSeatsPerRow[i]>location::MAX_SEATS_PER_ROW) {
					throw "Number of seats is not alright";
				}
			}
			if (this->noOfSeatsPerRow != nullptr)
				delete[] this->noOfSeatsPerRow;
			this->noOfSeatsPerRow = new int[noOfNewRows];
			for (int i = 0; i < noOfNewRows; i++) {
				this->noOfSeatsPerRow[i] = noOfNewSeatsPerRow[i];
			}
			this->noOfRows = noOfNewRows;
		}
		int* getNoSeatsPerRow() {
			int* copy = this->copyArray(this->noOfSeatsPerRow, this->noOfRows);
			return copy;
		}

		~location() {
			cout << endl << "Location destructor";
			if (this->noOfSeatsPerRow != nullptr) {
				delete[]this->noOfSeatsPerRow;
			}
		}
		location() {
			cout << endl << "Calling location default constructor";
		}
		location(int noOfSeats, int noOfRows, int* noOfSeatsPerRow) {
			this->setNoOfSeats(noOfSeats);
			this->setNoOfRows(noOfRows);
			this->setNoOfSeatsPerRow(noOfSeatsPerRow,noOfRows);
		}
		location(const location& location){
			cout << endl << "Copy constructor";
			this->setNoOfRows(location.noOfRows);
			this->setNoOfSeats(location.noOfSeats);
			this->setZones(location.noOfZones);
			this->setNoOfSeatsPerRow(location.noOfSeatsPerRow,location.noOfRows);
		}
		void operator=(const location& location) {
			if (this == &location) {
				return;
			}
			this->noOfRows = location.noOfRows;
			this->noOfSeats = location.noOfSeats;
			this->noOfZones = location.noOfZones;
			if (this->noOfSeatsPerRow) {
				delete[]this->noOfSeatsPerRow;
				this->noOfSeatsPerRow = nullptr;
			}
			if (location.noOfSeatsPerRow != nullptr) {
				this->noOfSeatsPerRow = new int[location.noOfRows + 1];
				for (int i = 0; i < location.noOfRows; i++) {
					this->noOfSeatsPerRow[i] = location.noOfSeatsPerRow[i];
				}
			}
			else this->noOfSeatsPerRow = nullptr;
		}
		friend void operator<< (ostream& out, event event);
		friend void operator>> (istream& in, event& event);
		
	private:

		static int* copyArray(int* array, int noElements) {
		int* copy = new int[noElements];
		for (int i = 0; i < noElements; i++) {
			copy[i] = array[i];
		}
		return copy;
	}
		
};

class event {
	 
	private:

		char* name=nullptr;
		string time=" ";
		string date=" ";
		string place = " ";
		string duration = " ";

		static int NO_EVENTS;
		
	public:

		char* getName() {
			char* nameCopy = new char[strlen(this->name) + 1];
			strcpy(nameCopy, this->name);
			return nameCopy;
		}
		void setName(const char* newName) {
			if (this->name != nullptr) {
				delete[] this->name;
			}
			this->name = new char[strlen(newName) + 1];
			strcpy(this->name, newName);
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
		string getDuration() {
			return this->duration;
		}
		void setDuration(string duration) {
			this->duration = duration;
		}
		~event() {
			cout << endl << "Event destructor";
			if (this->name != nullptr) {
				delete[]this->name;
			}
			event::NO_EVENTS -= 1;
		}
		event() {
			cout << endl << "Calling event default constructor";
		}
		event(char* name, string date, string place, string time) {
			this->setName(name);
			this->setDate(date);
			this->setPlace(place);
			this->setTime(time);
		}
		event(const event& event){
			cout << endl << "Copy constructor";
			this->setName(event.name);
			this->setDate(event.date);
			this->setDuration(event.duration);
			this->setPlace(event.place);
			this->setTime(event.time);
		}
		static int getNoEvents() {
			return event::NO_EVENTS;
		}
		void operator=(const event& event) {
			if (this == &event) {
				return;
			}
			this->date = event.date;
			this->duration = event.duration;
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
		}
		friend void operator<< (ostream& out, event event);
		friend void operator>> (istream& in, event& event);
};

int event::NO_EVENTS = 0;
