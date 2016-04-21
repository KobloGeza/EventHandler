/*
 * Job.hpp
 *
 *  Created on: 2016. ápr. 16.
 *      Author: K0bi
 */

#ifndef JOB_HPP_
#define JOB_HPP_

#include <memory>
#include "IJob.hpp"
#include "Filter.hpp"
#include "Event_Observable.hpp"

class Job : public IJob {
	using FilterPtr 	= std::shared_ptr<IFilter>;
	using Filters 		= std::vector<FilterPtr>;
	//using Check_func 	= std::function<bool(Event_Type&)>;

	Filters filters_active;
	Filters filters_all;
	bool	single_shot_job;
public:

	template <typename TEventType>
	void addFilter(std::function<bool(const TEventType&)> checker) {
		auto filter = std::make_shared<Filter_Type<TEventType>>(*this, checker);
		filters_active.push_back(filter);
		if (single_shot_job) {
			filters_all.push_back(filter);
		}

		Event_Observable<TEventType>::getInstance().register_observer(filter);
	}

	void removeFilter(IFilter& filter) {
		auto new_end = std::remove_if(filters.begin(), filters.end(),
				[&filter](const FilterPtr& i){ return (&filter == i.get()); });
		filters.erase(new_end, filters.end());
	}

	void removeAllFilter(IFilter& filter) {
		filters.clear();
	}
	void passed(IFilter& filter) {
		//if single shot job, we simply remove passed filters
		//and ready if none of them left
		if (single_shot_job) {
			removeFilter(filter);
		} else {
			auto new_end = std::remove(filters_active.begin(), filters_active.end(), filter);
			std::move(new_end, std::back_inserter(filters_passed));
			filters_active.erase(new_end, filters_active.end());
		}

		//if none active filter remain

		std::cout << "PASSED , remain: " << filters.size() << std::endl;
	}
};



#endif /* JOB_HPP_ */
