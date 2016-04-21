/*
 * Event_Type.hpp
 *
 *  Created on: 2016. márc. 23.
 *      Author: K0bi
 */

#ifndef GREEN_LOGIC_EVENT_TYPE_HPP_
#define GREEN_LOGIC_EVENT_TYPE_HPP_

#include "Visitor.hpp"

class IEvent {
public:
	virtual void accept(const Visitor& visitor) = 0;
	virtual ~Event() {};
};

template <typename Value_type, typename TEventType>
class Event_Type : public IEvent {
public:
	Value_type value;

	Event_Type () = default;
	Event_Type (Value_type value) : value{value} {};

	void accept(const Visitor& visitor) override {
		visitor.visit(static_cast<TEventType&>(*this));
	}
};



class Event_RTC : public Event_Type<int, Event_RTC> {
public:
	Event_RTC(int value) : Event_Type(value) {};
};

class Event_Humidity : public Event_Type<int, Event_Humidity> {
public:
	Event_Humidity(int value) :  Event_Type(value) {};
};

#endif /* GREEN_LOGIC_EVENT_TYPE_HPP_ */
