/*
 * IJob.hpp
 *
 *  Created on: 2016. ápr. 16.
 *      Author: K0bi
 */

#ifndef GREEN_LOGIC_IJOB_HPP_
#define GREEN_LOGIC_IJOB_HPP_

class Filter;

class IJob {
public:
	virtual void passed(Filter&) = 0;
	virtual ~IJob() {};
};



#endif /* GREEN_LOGIC_IJOB_HPP_ */
