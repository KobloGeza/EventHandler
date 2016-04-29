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
	using Job_func		= std::function<void()>;

	Filters filters_active;		//filters need to pass before this job can be executed
	Filters filters_all;		//copy of the filters to be able to restore it if job is repeatable

	bool		repeatable_job;
	Job_func	job_func;


	void removeFilter(Filters& filters, IFilter& filter) {
		auto new_end = std::remove_if(filters.begin(), filters.end(),
				[&filter](const FilterPtr& i){ return (&filter == i.get()); });
		filters.erase(new_end, filters.end());
	}

public:

	Job(bool repeatable, Job_func job_func): repeatable_job{repeatable}, job_func{job_func} {};

	template <typename TEventType>
	void attachFilter(std::function<bool(const TEventType&)> checker) {
		auto filter = std::make_shared<Filter_Type<TEventType>>(*this, checker);
		filters_active.push_back(filter);
		if (repeatable_job) {
			filters_all.push_back(filter);
		}

		Event_Observable<TEventType>::getInstance().register_observer(filter);
	}

	void detachFilter(IFilter& filter) {
		removeFilter(filters_all, filter);
	}

	void detachAllFilter() {
		filters_all.clear();
	}

	void passed(IFilter& filter) {
		//if single shot job, we simply remove passed filters from the active ones
		removeFilter(filters_active, filter);
		//std::cout << "filter check passed, remain: " << filters_active.size() << std::endl;

		//if none of them left we can fire up this job
		if (filters_active.empty()) {
			//std::cout << "PASSED" << std::endl;
			//do the job
			job_func();

			if (repeatable_job) {
				//restore active list
				filters_active = filters_all;
			}
		}

	}
};



#endif /* JOB_HPP_ */
