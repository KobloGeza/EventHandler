/*
 * Visitor.hpp
 *
 *  Created on: 2016. márc. 23.
 *      Author: K0bi
 */

#ifndef GREEN_LOGIC_VISITOR_HPP_
#define GREEN_LOGIC_VISITOR_HPP_

#include "Event_Observable.hpp"
class Event_RTC;
class Event_Humidity;

class Visitor {
public:
	void visit(const Event_RTC& event) const {
		Event_Observable<Event_RTC>::getInstance().notify(event);
	};

	void visit(const Event_Humidity& event) const {
		Event_Observable<Event_Humidity>::getInstance().notify(event);
	};
};


#endif /* GREEN_LOGIC_VISITOR_HPP_ */
