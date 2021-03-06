/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:30:22 by dhaliti           #+#    #+#             */
/*   Updated: 2022/06/04 11:38:38 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template< bool x, class T = void> struct enable_if{};

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template <class T>
    struct is_integral {
		static const bool value = false;
	};

    template <>
    struct is_integral<bool> {
		static const bool value = true;
	};

    template <>
    struct is_integral<char> {
		static const bool value = true;
	};

    template <>
    struct is_integral<wchar_t> {
		static const bool value = true;
	};

    template <>
    struct is_integral<signed char> {
		static const bool value = true;
	};

    template <>
    struct is_integral<short int> {
		static const bool value = true;
	};

    template <>
    struct is_integral<int> {
		static const bool value = true;
	};

    template <>
    struct is_integral<long int> {
		static const bool value = true;
	};

    template <>
    struct is_integral<long long int> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned char> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned short int> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned int> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned long int> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned long long int> {
		static const bool value = true;
	};

    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
            for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
            {
                if (*first1 < *first2) return true;
                if (*first2 < *first1) return false;
            }

            return (first1 == last1) && (first2 != last2);
    }
}
