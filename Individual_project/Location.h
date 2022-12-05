#pragma once
#include<iostream>
#include<string>
using namespace std;

class Location {

private:

	int noOfSeats = 0;
	int noOfRows = 0;
	int noOfZones = 0;
	int* noOfSeatsPerRow = nullptr;

public:

	const static int MIN_SEATS_PER_ROW = 1;
	const static int MAX_SEATS_PER_ROW = 50;

	int getNoOfSeats() {
		return this->noOfSeats;
	}
	void setNoOfSeats(int noOfSeats) {
		if (noOfSeats < 1) {
			throw "Wrong number of seats";
		}
		this->noOfSeats = noOfSeats;
	}

	int getNoOfRows() {
		return this->noOfRows;
	}
	void setNoOfRows(int noOfRows) {
		if (noOfRows < 1) {
			throw "Wrong number of rows";
		}
		this->noOfRows = noOfRows;
	}

	int getNoOfZones() {
		return this->noOfZones;
	}
	void setNoOfZones(int noOfZones) {
		if (noOfZones < 1) {
			throw "Wrong number of zones";
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
			if (noOfNewSeatsPerRow[i] < Location::MIN_SEATS_PER_ROW || noOfNewSeatsPerRow[i]>Location::MAX_SEATS_PER_ROW) {
				throw "Number of seats is not alright";
			}
			if (this->noOfSeatsPerRow != nullptr)
				delete[] this->noOfSeatsPerRow;
			this->noOfSeatsPerRow = new int[noOfNewRows];
			for (int i = 0; i < noOfNewRows; i++) {
				this->noOfSeatsPerRow[i] = noOfNewSeatsPerRow[i];
			}
			this->noOfRows = noOfNewRows;
		}
	}
		int* getNoOfSeatsPerRow() {
			int* copy = this->copyArray(this->noOfSeatsPerRow, this->noOfRows);
			return copy;
		}
		~Location() {
			cout << endl << "Location destructor";
			if (this->noOfSeatsPerRow != nullptr) {
				delete[]this->noOfSeatsPerRow;
			}
		}
		Location() {
			cout << endl << "Calling location default constructor";
		}
		Location(int noOfZones, int noOfSeats, int noOfRows, int* noOfSeatsPerRow) {
			this->setNoOfZones(noOfZones);
			this->setNoOfSeats(noOfSeats);
			this->setNoOfRows(noOfRows);
			this->setNoOfSeatsPerRow(noOfSeatsPerRow, noOfRows);
		}
		Location(const Location & location) {
			cout << endl << "Copy constructor";
			this->setNoOfRows(location.noOfRows);
			this->setNoOfSeats(location.noOfSeats);
			this->setNoOfZones(location.noOfZones);
			this->setNoOfSeatsPerRow(location.noOfSeatsPerRow, location.noOfRows);
		}
		void print() {
			for (int i = 1; i < noOfRows; i++) {
				cout << endl << "Number of seats on row " << i << " is :" << this->noOfSeatsPerRow[i];
			}
			cout << endl << "The number of zones is: " << this->noOfZones;
			cout << endl << "The number of seats is: " << this->noOfSeats;
			cout << endl << "The number of rows is: " << this->noOfRows;
		}
		int getTotalNoOfSeats() {
			int s = 0;
			for (int i = 0; i < this->noOfZones; i++) {
				for (int j = 0; j < this->noOfRows; j++) {
					s = s + this->noOfSeatsPerRow[i];
				}
			}
			return s;
		}
		void operator=(const Location & location) {
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
				this->noOfSeatsPerRow = new int[location.noOfRows];
				for (int i = 0; i < location.noOfRows; i++) {
					this->noOfSeatsPerRow[i] = location.noOfSeatsPerRow[i];
				}
			}
			else this->noOfSeatsPerRow = nullptr;
		}

		friend void operator<< (ostream & out, Location & location);
		friend void operator>> (istream & in, Location & location);

private:

	static int* copyArray(int* array, int noElements) {
		int* copy = new int[noElements];
		for (int i = 0; i < noElements; i++) {
			copy[i] = array[i];
		}
		return copy;
	}
};

	bool validateNoOfSeats(int noOfSeats) {
		if (noOfSeats < 1) return false;
		else return true;
	}
	bool validateNoOfZones(int noOfZones) {
		if (noOfZones < 1) return false;
		else return true;
	}
	bool validateNoOfRows(int noOfRows) {
		if (noOfRows < 1) return false;
		else return true;
	}
	bool validateNoOfSeatsPerRow(int* noOfSeatsPerRow, int noOfRows) {
		for (int i = 0; i < noOfRows; i++) {
			if (noOfSeatsPerRow[i]<Location::MIN_SEATS_PER_ROW || noOfSeatsPerRow[i]>Location::MAX_SEATS_PER_ROW)
				return false;
			else return true;
		}
	}

	void operator<<(ostream& out, Location& location) {
		out << endl << "Number of seats: " << location.noOfSeats;
		out << endl << "Number of rows: " << location.noOfRows;
		out << endl << "Number of zones: " << location.noOfZones;
		out << endl << "Number of seats per row: ";
		for (int i = 0; i < location.noOfRows; i++) {
			out << location.noOfSeatsPerRow[i] << " ";
		}
	}
	void operator>>(istream& in, Location& location) {
		cout << endl << "Number of zones: ";
		in >> location.noOfZones;
		if (validateNoOfZones(location.noOfZones) == false)
		cout << endl << "Wrong number of zones";
		cout << endl << "Number of seats: ";
		in >> location.noOfSeats;
		if (validateNoOfSeats(location.noOfSeats) == false)
			cout << endl << "Wrong number of seats";
		cout << endl << "Number of rows: ";
		in >> location.noOfRows;
		if (validateNoOfRows(location.noOfRows) == false)
			cout << endl << "Wrong number of rows";
		cout << endl << "Number of seats per row: ";
		if (location.noOfSeatsPerRow != nullptr) {
			delete[]location.noOfSeatsPerRow;
			location.noOfSeatsPerRow = nullptr;
		}
		location.noOfSeatsPerRow = new int[location.noOfRows];
		for (int i = 0; i < location.noOfRows; i++) {
			in >> location.noOfSeatsPerRow[i];
			if (validateNoOfSeatsPerRow(location.noOfSeatsPerRow,location.noOfRows) == false)
				cout << endl << "Wrong number of seats per row";
		}
	}
	Location operator-(Location location, int val) {
		Location result = location;
		result.setNoOfSeats(location.getNoOfSeats() - val);
		return result;
	}
	Location operator+(Location location, int val) {
		Location result = location;
		result.setNoOfSeats(location.getNoOfSeats() + val);
		return result;
	}
