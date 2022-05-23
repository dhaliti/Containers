/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:22:23 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/21 18:54:15 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterators.hpp"
#include "reverse_iterator.hpp"

#include "Tree.hpp"
#include "pair.hpp"
#include <memory>

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>,
              class Alloc = std::allocator<pair<Key, T> > >
    class map
    {
/*******************************MEMBER FUNCTIONS*******************************/
    public:

    /*--------------------------------Typedefs--------------------------------*/
        typedef Key                                                 				key_type;
        typedef T                                                   				mapped_type;
        typedef ft::pair<key_type,mapped_type>                      				value_type;
        typedef	Compare										       					key_compare;
        typedef	Alloc										       					allocator_type;
        typedef Tree< value_type, Compare, Alloc>			        				tree;
        typedef typename tree::Node							        				Node;
        typedef	map_iterator<bidirectional_iterator_tag, tree>						iterator;
        typedef Tree< const value_type, Compare, Alloc>								const_tree;

        typedef typename allocator_type::reference                  				reference;
        typedef typename tree::value_compare				        				value_compare;
        typedef	map_iterator<bidirectional_iterator_tag, const_tree, tree>			const_iterator;
        typedef	reverse_iterator_map<bidirectional_iterator_tag, tree>				reverse_iterator;
        typedef	reverse_iterator_map<bidirectional_iterator_tag,const_tree, tree>	const_reverse_iterator;
        typedef size_t                                              				size_type;

        /*-----------------------Constructor/Destructor-----------------------*/

        explicit map(const key_compare &comp = key_compare(),
        	const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) {}

        template <class InputIterator>
        map (InputIterator first, InputIterator last,
        const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc)
        {
            for (; first != last; ++first)
                insert(*first);
        }
        map (const map& x) {
			*this = x;
		}

        ~map() {}

        map& operator= (const map& x) {
            clear();
            insert(x.begin(), x.end());
            return *this;
        }

        /*-----------------------Functions-----------------------*/
		iterator begin() {
			return iterator((_tree.size() ? _tree.minimum() : _tree._last()), _tree._last());
		}
	    iterator end() {
			return iterator(_tree._last(), _tree._last());
		}
		const_iterator begin() const {
			return const_iterator((_tree.size() ? _tree.minimum() : _tree._last()), _tree._last());
		}
	    const_iterator end() const {
			return const_iterator(_tree._last(), _tree._last());
		}
		reverse_iterator rbegin() {
			return reverse_iterator((_tree.size() ? _tree.maximum() : _tree._last()), _tree._last());
		}
	    reverse_iterator rend() {
			return reverse_iterator(_tree._last(), _tree._last());
		}
	    const_reverse_iterator rbegin () const {
			return const_reverse_iterator((_tree.size() ? _tree.maximum() : _tree._last()), _tree._last());
		}
	    const_reverse_iterator rend () const {
			return const_reverse_iterator(_tree._last(), _tree._last());
		}

        size_type size() const {
			return _tree.size();
		}

        size_type max_size() const {
			return _tree.max_size();
		}

        bool empty() const {
			return _tree.size() == 0;
		}



        mapped_type& operator[] (const key_type& k)
        {
            iterator it = find(k);
            if (it != end())
                return (*it).second;
            else
            {
                insert(value_type(k, mapped_type()));
                return (*find(k)).second;
            }
        }

        pair<iterator,bool>		insert(const value_type& val) {
			size_type n = this->size();
			_tree.insert(val);                   // ICI 2
			pair<iterator,bool> ret;
			ret.second = (n != this->size());
			ret.first = iterator(this->_tree.find(val.first), this->_tree._last());
			return ret;
		}

        iterator insert (iterator position, const value_type& val)
        {
				// iterator prec = position
                iterator last(position);
				if (value_comp()(*last, val) && value_comp()(val, *++position)) // insert using position as an hint
				{
					this->_tree.insert(val);
					return this->find(val.first);
				}
				return this->insert(val).first;
        }

        void erase(iterator position) {
			_tree.erase((*position).first);
		}

        size_type erase (const key_type& k)
        {
            size_type i = this->size();
            if (!count(k))
                return 0;
            value_type data = *(find(k));
				_tree.erase(data.first);
            return (i != this->size());
        }

        void erase (iterator first, iterator last){
            iterator tmp;
            while (first != last){
                tmp = first;
                ++first;
                erase(tmp);
            }
        }

        void clear() {
			_tree.clear();
		}

        iterator    lower_bound(const key_type& k) {
				for (iterator it = begin(); it != end(); it++)
					if (!_tree.key_comp()((*it).first, k))
						return it;
				return end();
		}

        const_iterator lower_bound (const key_type& k) const {
                for (const_iterator it = begin(); it != end(); it++)
                    if (!_tree.key_comp()((*it).first, k))
                        return it;
                return end();
        }

        const_iterator upper_bound (const key_type& k) const {
                for (const_iterator it = begin(); it != end(); it++)
                    if (_tree.key_comp()(k, (*it).first))
                        return it;
                return end();
        }

        iterator   upper_bound(const key_type& k) {
                for (iterator it = begin(); it != end(); it++)
                    if (_tree.key_comp()(k, (*it).first))
                        return it;
                return end();
        }
        // void swap (map& x){
        //     map tmp = *this;
        //     *this = x;
        //     x = tmp;
        // }

        void swap (map &x) {
            _tree.swap(x._tree);
        }

        size_type count (const key_type& k) const {
            return _tree.count(k);
        }


        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        //            ----------------  Operations ----------------
        iterator find(const key_type& k)
        {
            Node *tmp = _tree.find(k);
            if (tmp)
                return iterator(tmp, _tree._last());
            return end();
        }


        //          ----------------  Capacity ----------------
        void print() {
            _tree.print2D();
        }

        //         ----------------  Allocator ----------------

        value_compare value_comp() const {
			return this->_tree.value_comp();
		}

        allocator_type get_allocator() const {
			return _tree.get_allocator();
		}

        key_compare key_comp() const {
			return _tree.key_comp();
		}

		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
		{
			for (const_iterator it = this->begin(); it != this->end(); it++)
				if (!this->_tree.key_comp()(k, it->first) && !this->_tree.key_comp()(it->first, k))
					return pair<const_iterator, const_iterator>(it++, it);
			return pair<const_iterator, const_iterator>(this->lower_bound(k), this->lower_bound(k));
		}

		pair<iterator,iterator> equal_range(const key_type& k)
		{
			for (iterator it = this->begin(); it != this->end(); it++)
				if (!this->_tree.key_comp()(k, it->first) && !this->_tree.key_comp()(it->first, k))
					return pair<iterator, iterator>(it++, it);
			return pair<iterator, iterator>(this->lower_bound(k), this->lower_bound(k));
		}

    private:
        tree _tree;
    };
}
