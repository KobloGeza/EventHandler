//============================================================================
// Name        : EventHandler.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>

#include "Green_logic/Visitor.hpp"
#include "Green_logic/Event_Queue.hpp"
#include "Green_logic/Event_Observable.hpp"
#include "Green_logic/Job.hpp"

using namespace std;

Visitor 	visitor;
Event_Queue event_queue;

void processNext() {
	while (1) {
		this_thread::sleep_for(std::chrono::seconds(1));
		cerr << __FUNCTION__ << endl;

		auto event = event_queue.pop();
		if (event) {
			event->accept(visitor);
		}
	}
}

static int a = 0;
void createEvent() {
	while (1) {
		this_thread::sleep_for(std::chrono::seconds(2));
		cerr << __FUNCTION__ << endl;


		event_queue.push(Event_Humidity(a++));

		if (a==10) a=0;
	}
}

void Job1_done() {
	cerr << __FUNCTION__ << endl;
}

int main() {

	Job job1(true, Job1_done);
	job1.attachFilter<Event_Humidity>(
			[](const Event_Humidity& event) -> bool {return(event.value > 2);}
	);
	job1.attachFilter<Event_Humidity>(
			[](const Event_Humidity& event) -> bool {return(event.value > 5);}
	);

	thread thread_eater(processNext);
	thread thread_feeder(createEvent);

	thread_eater.join();
	thread_feeder.join();
	return 0;
}
