/*
 * Misc.hpp
 *
 *  Created on: 2016. ápr. 16.
 *      Author: K0bi
 */

#ifndef GREEN_LOGIC_MISC_HPP_
#define GREEN_LOGIC_MISC_HPP_

#include <memory>
#include <utility>

namespace misc {

    template<typename T,typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

}

#endif /* GREEN_LOGIC_MISC_HPP_ */
