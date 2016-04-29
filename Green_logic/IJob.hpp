/*
 * IJob.hpp
 *
 *  Created on: 2016. ápr. 16.
 *      Author: K0bi
 */

#ifndef GREEN_LOGIC_IJOB_HPP_
#define GREEN_LOGIC_IJOB_HPP_

class IFilter;

class IJob {
public:
	virtual void passed(IFilter&) = 0;
	virtual ~IJob() {};
};



#endif /* GREEN_LOGIC_IJOB_HPP_ */
