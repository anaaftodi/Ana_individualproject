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

	private:

		static int* copyArray(int* array, int noElements) {
		int* copy = new int[noElements];
		for (int i = 0; i < noElements; i++) {
			copy[i] = array[i];
		}
		return copy;
	}
		
};
