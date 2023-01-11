#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include "Event.h"
#include "Location.h"
#include"Ticket.h"
#include<stdlib.h>
#include<time.h>
using namespace std;

int main() {

	int noOfSeatsPerRow[] = { 20,30,35 };
	
	Location location1(7, 10, 5, noOfSeatsPerRow);
	location1.print();
	
	//Location copy = location1;
	//copy.print();

	//cout << location1;
	//cin >> location1;

	location1 = location1 - 5;
	cout << location1;

	Event event1("Gala caritabila", "10 decembrie 2022", "20:00");
	Event event2("Gala caritabila", "7 decembrie 2022", "21:00");
	event1.print();

	//cin >> event1;
	//cout << event1;

	//Event event3 = event1;
	//cout << event3;

	if (event1 != event2) cout << endl << "The events are different";

	Ticket ticket1(7, "Ana Aftodi", 20, LAWN, 30);
	ticket1.print();

	Ticket ticket2(9, "Maria Ion", 33, VIP, 70);

	/*if (ticket1 < ticket2) {
		cout << endl << "Ticket 2 is more expensive";
	}*/

	/*ticket1 *= 5;
	cout << ticket1;*/

	//Ticket copy = ticket1;
	//copy.print();

	//cout << ticket1;
	//cin >> ticket1;

	srand(time(0));
	Ticket bilet(rand(), "Ana Aftodi", 20, VIP, 80);
	cout << bilet;

	cout << endl << ticket1.ticketDiscount();


	return 0;
}