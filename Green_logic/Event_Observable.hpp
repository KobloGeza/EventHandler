/*
 * Event_Observable.hpp
 *
 *  Created on: 2016. m�rc. 23.
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

	void register_observer(Observer& ob) {
		observers.push_back(ob);
	}

	void unregister_observer(Observer& ob) {
		auto new_end = std::remove(observers.begin(), observers.end(), ob);
		observers.erase(new_end, observers.end());
	}

	void notify(const TEventType& event) {
		for(auto &ob : observers) {

			if (auto spt = ob.lock()) {
				ob->notify(event);
			} else {
				unregister_observer(ob); //TODO: will it crash?
			}
		}
	}


};




#endif /* GREEN_LOGIC_EVENT_OBSERVABLE_HPP_ */
