/*
 * Filter.hpp
 *
 *  Created on: 2016. ápr. 16.
 *      Author: K0bi
 */

#ifndef GREEN_LOGIC_FILTER_HPP_
#define GREEN_LOGIC_FILTER_HPP_

#include <iostream>
#include "IJob.hpp"

class IFilter {
protected:
	IJob&	owner;
public:
	IFilter(IJob& owner) : owner{owner} {};
};

template <typename TEventType>
class Filter_Type : public IFilter {
	using Check_func 	= std::function<bool(const TEventType&)>;
	Check_func checker	= [](){ return true; };

public:
	Filter_Type(IJob& owner): IFilter{owner} {};
	Filter_Type(IJob& owner, Check_func& checker) : IFilter{owner}, checker{checker} {};

	void notify(const TEventType& event) {
		if (checker(event.value)) {
			//callback owner if check passed
			owner.passed(*this);
		} else {
			std::cout << "filter check failed" << std::endl;
		}
	}

};



#endif /* GREEN_LOGIC_FILTER_HPP_ */
