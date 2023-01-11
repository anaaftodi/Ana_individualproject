#pragma once
#include "Location.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
using namespace std;

enum TicketType {VIP, TRIBUNE, LAWN, BOX, OTHER};

class Ticket {

	private:

		TicketType type = LAWN;
		const int ticketId;
		double ticketPrice = 0;
		char* guestName = nullptr;
		int guestAge = 0;
		Location location;

	public:

		const static int MIN_NAME_SIZE = 3;
		const static int MIN_AGE = 16;
		static int NO_TICKETS_SOLD;

		TicketType getType() {
			return this->type;
		}
		void setType(TicketType type) {
			this->type = (TicketType)type;
		}
		void setTicketPrice(int ticketPrice) {
			if (ticketPrice <= 0) {
				throw "Wrong price";
			}
			this->ticketPrice = ticketPrice;
		}
		double getTicketPrice() {
			return this->ticketPrice;
		}
		void setGuestAge(int guestAge) {
			if (guestAge < Ticket::MIN_AGE) {
				throw "The guest should be accompanied by an adult";
			}
			this->guestAge = guestAge;
		}
		int getGuestAge() {
			return this->guestAge;
		}
		void setGuestName(const char* guestName) {
			if (strlen(guestName) < Ticket::MIN_NAME_SIZE) {
				throw "Name is too short";
			}
			if (this->guestName != nullptr)
				delete[]this->guestName;
			this->guestName = new char[strlen(guestName) + 1];
			strcpy(this->guestName, guestName);
		}
		char* getGuestName() {
			char* copyGuestName = this->copyArray(this->guestName);
			return copyGuestName;
		}
		Ticket() :ticketId(0) {
			cout << endl << "The default constructor";
			this->setType(LAWN);
			this->setTicketPrice(0);
			this->setGuestAge(16);
			this->setGuestName("John Doe");
		}
		Ticket(int ID, const char* guestName, int guestAge, TicketType type, double ticketPrice):ticketId(ID) {
			this->setGuestName(guestName);
			this->setGuestAge(guestAge);
			this->setType(type);
			this->setTicketPrice(ticketPrice);
			Ticket::NO_TICKETS_SOLD++;
		}
		Ticket(const Ticket& ticket) :ticketId(ticket.ticketId) {
			cout << endl << "The copy constructor";
			this->setGuestName(ticket.guestName);
			this->setGuestAge(ticket.guestAge);
			this->setTicketPrice(ticket.ticketPrice);
			this->setType(ticket.type);
			Ticket::NO_TICKETS_SOLD++;
		}
		~Ticket() {
			cout << endl << "The ticket destructor";
			this->deleteTicket();
			Ticket::NO_TICKETS_SOLD--;
		}
		void deleteTicket() {
			if (this->guestName != nullptr) {

			}
		}
		static int getCount() {
			return NO_TICKETS_SOLD;
		}
		virtual void ticketsSold() {
			cout << endl << "The number of tickets sold is: " << Ticket::NO_TICKETS_SOLD;
		}
		double ticketDiscount() {
			double newTicketPrice = 0;
			newTicketPrice = this->ticketPrice - (0.10 * this->ticketPrice);
			return newTicketPrice;
		}
		void operator=(const Ticket& ticket) {
			if (this == &ticket) {
				return;
			}
			if (this->guestName) {
				delete[]this->guestName;
				this->guestName = nullptr;
			}
			if (ticket.guestName != nullptr) {
				this->guestName = new char[strlen(ticket.guestName) + 1];
				strcpy(this->guestName, ticket.guestName);
			}
			else
				this->guestName = nullptr;
			this->guestAge = ticket.guestAge;
			this->ticketPrice = ticket.ticketPrice;
			this->type = ticket.type;
			Ticket::NO_TICKETS_SOLD++;
		}
		virtual void print() {
			cout << endl << "Ticket's id: " << this->ticketId;
			cout << endl << "Guest's age: " << this->guestAge;
			cout << endl << "Ticket price: " << this->ticketPrice;
			if (this->guestName != nullptr) {
				cout << endl << "Guest's name: " << this->guestName;
			}
			cout << endl << "Ticket type: ";
			if (this->type == 0) cout << "VIP";
			if (this->type == 1) cout << "TRIBUNE";
			if (this->type == 2) cout << "LAWN";
			if (this->type == 3) cout << "BOX";
			if (this->type == 4) cout << "OTHER";
		}
		bool freeTickets() {
			if (Ticket::NO_TICKETS_SOLD >= location.getTotalNoOfSeats()) {
				return true;
			}
			else
				return false;
		}
		bool operator<(Ticket& ticket) {
			return this->ticketPrice < ticket.ticketPrice;
		}
		void operator*=(float x) {
			 this->ticketPrice *= x;
		}
		friend void operator<<(ostream& out, Ticket& ticket);
		friend void operator>>(istream& in, Ticket& ticket);

	private:

		static char* copyArray(const char* array) {
			char* copy = new char[strlen(array) + 1];
			for (int k = 0; k < strlen(array) + 1; k++) {
				copy[k] = array[k];
			}
			copy[strlen(array) + 1] = '\0';
			return copy;
		}
};

int Ticket::NO_TICKETS_SOLD = 0;

class AvailableTickets : public Ticket {

	int availableTickets = 15;

public:

	AvailableTickets(int availableTickets, int ticketId, const char* guestName, int guestAge, TicketType type, double ticketPrice) :Ticket(ticketId, guestName, guestAge, type, ticketPrice), availableTickets(availableTickets) {

	}
	void print() {
		this->Ticket::print();
		if (this->availableTickets > 0) {
			cout << endl << "Number of available tickets: " << this->availableTickets;
			this->availableTickets--;
		}
		else cout << endl << "No available tickets";
	}
	void ticketsSold() {
		this->Ticket::ticketsSold();
		cout << endl << "Number of tickets sold is: " << Ticket::NO_TICKETS_SOLD - this->availableTickets;
	}
};

bool validateName(const char* guestName) {
	if (strlen(guestName) < Ticket::MIN_NAME_SIZE)
		return false;
	else return true;
}
bool validatePrice(double ticketPrice) {
	if (ticketPrice <= 0) return false;
	else return true;
}
bool validateAge(int guestAge) {
	if (guestAge < Ticket::MIN_AGE)
		return false;
	else return true;
}
bool validateType(string val) {
	if (val == "VIP")
		return true;
	else
		if (val == "TRIBUNE")
			return true;
		else
			if (val == "LAWN")
				return true;
			else
				if (val == "BOX")
					return true;
				else
					if (val == "OTHER")
						return true;
					else
						return false;
}

	void operator>>(istream& in, Ticket& ticket) {
		if (ticket.freeTickets() == true) {
			srand(time(0));
			cout << endl << "Ticket ID: ";
			int id = rand();
			cout << id;
			cout << endl << "Guest's name: ";
			in >> ticket.guestAge;
			while (validateName(ticket.guestName) == false) {
				cout << endl << "Wrong name, retry";
				in >> ticket.guestName;
			}
			cout << endl << "Guest's age: ";
			in >> ticket.guestAge;
			while (validateAge(ticket.guestAge) == false) {
				cout << endl << "Wrong age,retry";
				in >> ticket.guestAge;
			}
			cout << endl << "Ticket price: ";
			in >> ticket.ticketPrice;
			while (validatePrice(ticket.ticketPrice) == false) {
				cout << endl << "Wrong price";
				in >> ticket.ticketPrice;
			}
			cout << endl << "What kind of ticket would you like? ";

			//https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/

			string k;
			in >> k;
			transform(k.begin(), k.end(), k.begin(), ::toupper);
			if (k == "VIP")
				ticket.type = VIP;
			if (k == "LAWN")
				ticket.type = LAWN;
			if (k == "TRIBUNE")
				ticket.type = TRIBUNE;
			if (k == "BOX")
				ticket.type = BOX;
			if (k == "OTHER")
				ticket.type = OTHER;
			while (validateType(k) == false) {
				cout << endl << "Wrong type, choose from VIP,LAWN,BOX,TRIBUNE OR OTHER";
				in >> k;
				transform(k.begin(), k.end(), k.begin(), ::toupper);
				if (k == "VIP")
					ticket.type = TicketType::VIP;
				if (k == "LAWN")
					ticket.type = TicketType::LAWN;
				if (k == "TRIBUNE")
					ticket.type = TicketType::TRIBUNE;
				if (k == "BOX")
					ticket.type = TicketType::BOX;
				if (k == "OTHER")
					ticket.type = TicketType::OTHER;
			}
			Ticket::NO_TICKETS_SOLD++;
		}
		else
			cout << endl << "No free tickets.";
}
void operator<<(ostream& out, Ticket& ticket) {
	if (ticket.guestName != nullptr)
		out << endl << "Guest's name: " << ticket.guestName;
	out << endl << "Guest's age: " << ticket.guestAge;
	out << endl << "Ticket price: " << ticket.ticketPrice;
	out << endl << "Ticket type: " << ticket.type;
	out << endl << "Ticket ID: " << ticket.ticketId;
}