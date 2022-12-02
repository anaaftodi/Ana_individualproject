#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include "Event.h"
#include "Location.h"
using namespace std;

int main() {

	int noOfSeatsPerRow[] = { 20,30,35 };
	
	Location location1(7, 10, 5, noOfSeatsPerRow);
	location1.print();
	
	//Location copy = location1;
	//copy.print();

	//cout << location1;
	//cin >> location1;

	//location1 = location1 - 5;
	//cout << location1;

	Event event1("Gala caritabila", "10 decembrie 2022", "Casa Poporului", "20:00");
	Event event2("Gala caritabila", "7 decembrie 2022", "Ateneul Roman", "21:00");
	event1.print();

	//cin >> event1;
	//cout << event1;

	//if (event1 != event2) cout << endl << "The events are different";


	return 0;
}