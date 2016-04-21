/*
 * Event_Queue.hpp
 *
 *  Created on: 2016. márc. 23.
 *      Author: K0bi
 */

#ifndef GREEN_LOGIC_EVENT_QUEUE_HPP_
#define GREEN_LOGIC_EVENT_QUEUE_HPP_

#include <memory>
#include <queue>
#include <utility>
#include "Event_Type.hpp"
#include "Misc.hpp"

using std::queue;

class Event_Queue {
	using EventPtr 	= std::shared_ptr<Event>;
	using Queue 	= std::queue<EventPtr>;

	Queue queue;

public:
	Event_Queue() {}

	template <typename TEventType>
	void push(TEventType& event) {
		//queue.push(misc::make_unique<TEventType>(event));
		queue.push(std::make_shared<TEventType>(event));
	}

	template <typename TEventType>
	void push(TEventType&& event) {
		//queue.push(misc::make_unique<TEventType>(event));
		queue.push(std::make_shared<TEventType>(event));
	}

	EventPtr pop() {
		if (queue.empty())  return (nullptr);

		EventPtr event_ptr = queue.front();
		queue.pop();
		return event_ptr;
	}
};


#endif /* GREEN_LOGIC_EVENT_QUEUE_HPP_ */
