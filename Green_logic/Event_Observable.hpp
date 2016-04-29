/*
 * Event_Observable.hpp
 *
 *  Created on: 2016. márc. 23.
 *      Author: K0bi
 */

#ifndef GREEN_LOGIC_EVENT_OBSERVABLE_HPP_
#define GREEN_LOGIC_EVENT_OBSERVABLE_HPP_

#include <memory>
#include <vector>
#include <algorithm>
#include "Filter.hpp"

using std::vector;

template <typename TEventType>
class Event_Observable {
	using Observer	= std::weak_ptr<Filter_Type<TEventType>>;
	using Observers = vector<Observer>;

	Observers observers;

public:
	static Event_Observable& getInstance() {
		static Event_Observable event_observable;
		return event_observable;
	}

	void register_observer(Observer&& ob) {
		observers.push_back(ob);
	}

	void unregister_observer(Observer& ob) {
		auto new_end = std::remove(observers.begin(), observers.end(), ob);
		observers.erase(new_end, observers.end());
	}

	void notify(const TEventType& event) {
		std::cout << observers.size() << std::endl;
		for(auto &ob : observers) {
			if (auto spt = ob.lock()) {
				spt->notify(event);
			}
		}

		//cleanup ghost filters
		auto new_end = std::remove_if(observers.begin(), observers.end(),
				[](Observer& ob){ return (ob.expired()); });
		observers.erase(new_end, observers.end());
	}


};




#endif /* GREEN_LOGIC_EVENT_OBSERVABLE_HPP_ */
