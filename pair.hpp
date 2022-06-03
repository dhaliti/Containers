/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:29:35 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/20 17:29:37 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template <class T, class U>
    class pair
    {
        public:
            typedef T first_type;
            typedef U second_type;
            pair() : first(), second() {}
            pair(const T &first, const U &second) : first(first), second(second) {}
            pair(const pair &other) : first(other.first), second(other.second) {}
            pair &operator=(const pair &other)
            {
                first = other.first;
                second = other.second;
                return *this;
            }
            template<class V, class W>
            pair(const pair<V, W> &other) : first(other.first), second(other.second) {}

            bool operator==(const pair &other) const { return (first == other.first && second == other.second); }
            bool operator!=(const pair &other) const { return !(*this == other); }
            bool operator<(const pair &other) const { return (first < other.first || (first == other.first && second < other.second)); }
            bool operator>(const pair &other) const { return (first > other.first || (first == other.first && second > other.second)); }
            bool operator<=(const pair &other) const { return !(*this > other); }
            bool operator>=(const pair &other) const { return !(*this < other); }

            // make_pair(const T &first, const U &second) : first(first), second(second) {}

        first_type first;
        second_type second;
    };

    template <class T1, class T2>ft::pair<T1, T2>    make_pair(T1 x, T2 y) {
		return ft::pair<T1, T2>(x, y);
	}

}
