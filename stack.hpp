/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:29:57 by dhaliti           #+#    #+#             */
/*   Updated: 2022/06/04 11:29:11 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> >
    class stack
    {
    public:
        typedef Container	container_type;
		typedef	T			value_type;
		typedef size_t		size_type;
    protected:
        container_type _container;
    public:

/****************************CONSTRUCTOR/DESTRUCTOR****************************/
        explicit stack(const container_type& ctnr = container_type()) {
            _container = ctnr;
        }

        ~stack() {};

/**********************************FUNCTIONS***********************************/

        void push(const value_type& val) {
			_container.push_back(val);
		}

		void pop() {
			_container.pop_back();
		}

		value_type &top() {
			return _container.back();
		}

		value_type &top() const {
			return _container.back();
		}

		size_type size() {
			return _container.size();
		}
        bool empty() {
			return _container.empty();
		}

        bool operator==(const stack &rhs) const {
            return _container == rhs._container;
        }

        bool operator!=(const stack &rhs) const {
            return _container != rhs._container;
        }

        bool operator<(const stack &rhs) const {
            return _container < rhs._container;
        }

        bool operator>(const stack &rhs) const {
            return _container > rhs._container;
        }

        bool operator<=(const stack &rhs) const {
            return _container <= rhs._container;
        }

        bool operator>=(const stack &rhs) const {
            return _container >= rhs._container;
        }
    };
}
