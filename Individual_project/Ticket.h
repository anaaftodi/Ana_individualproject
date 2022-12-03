#pragma once
#include<iostream>
#include<string>
using namespace std;

enum TicketType {VIP, TRIBUNE,LAWN,BOX,OTHER};

class Ticket {

	private:

		TicketType type = LAWN;
		const int ticketId;
		double ticketPrice = 0;
		char* guestName = nullptr;
		int guestAge = 0;

	public:

		const static int MIN_NAME_SIZE = 3;
		const static int MIN_AGE = 16;

		TicketType getType() {
			return this->type;
		}
		void setType(TicketType type) {
			this->type = (TicketType)type;
		}
		void setTicketPrice(int ticketPrice) {
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
		}
		Ticket(const Ticket& ticket) :ticketId(ticket.ticketId) {
			cout << endl << "The copy constructor";
			this->setGuestName(ticket.guestName);
			this->setGuestAge(ticket.guestAge);
			this->setTicketPrice(ticket.ticketPrice);
			this->setType(ticket.type);
		}
		~Ticket() {
			cout << endl << "The ticket destructor";
			this->deleteTicket();
		}
		void deleteTicket() {
			if (this->guestName != nullptr) {

			}
		}
		void print() {
			cout << endl << "The ticket ID is: " << this->ticketId;
			if (this->guestName != nullptr) {
				cout << endl << "The guest name is: " << this->guestName;
			}
			cout << endl << "The ticket type is: ";
			if (this->type == 0) 
				cout << "VIP";
			if (this->type == 1) 
				cout << "TRIBUNE";
			if (this->type == 2) 
				cout << "LAWN";
			if (this->type == 3) 
				cout << "BOX";
			cout << endl << "The ticket price is: " << this->ticketPrice;
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
			this->guestName = ticket.guestName;
			this->guestAge = ticket.guestAge;
			this->ticketPrice = ticket.ticketPrice;
			this->type = ticket.type;
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

void operator>>(istream& in, Ticket& ticket) {
	cout << endl << "Guest's name: ";
	char buffer[100];
	in >> buffer;
	if (ticket.guestName != nullptr) {
		delete[]ticket.guestName;
		ticket.guestName = nullptr;
	}
	ticket.guestName = new char[strlen(buffer) + 1];
	strcpy(ticket.guestName, buffer);
	cout << endl << "Guest's age: ";
	in >> ticket.guestAge;
	cout << endl << "Ticket price: ";
	in >> ticket.ticketPrice;
	cout << endl << "What kind of ticket would you like? ";
	int type;
	in >> type;
	if (type == VIP) 
		ticket.type = VIP;
	if (type == LAWN) 
		ticket.type = LAWN;
	if (type == TRIBUNE) 
		ticket.type = TRIBUNE;
	if (type == BOX) 
		ticket.type = BOX;
}
void operator<<(ostream& out, Ticket& ticket) {
	out << endl << (ticket.guestName != nullptr ? "Guest's name: " + string(ticket.guestName) : "John Doe");
	out << endl << "Guest's age: " << ticket.guestAge;
	out << endl << "Ticket price: " << ticket.ticketPrice;
	out << endl << "Ticket type: " << ticket.type;
}