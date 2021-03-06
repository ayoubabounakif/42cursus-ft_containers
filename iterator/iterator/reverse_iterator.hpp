/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:08:58 by aabounak          #+#    #+#             */
/*   Updated: 2021/12/15 18:30:49 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iterator>
# include "../random_access_iterator/random_access_iterator.hpp"
# include "../iterator_traits/iterator_traits.hpp"

//! if Linux 1
// #define ptrdiff_t __gnu_cxx::ptrdiff_t

namespace ft {
    template <class Iterator>
    class reverse_iterator {
        public:

                    /* ------------ Member Types ----------- */
            typedef Iterator    iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type        value_type;
            typedef typename iterator_traits<Iterator>::difference_type   difference_type;
            typedef typename iterator_traits<Iterator>::pointer           pointer;
            typedef typename iterator_traits<Iterator>::reference         reference;

                    /* ----------- Member Functions ---------- */    
                /* ---- Constructors & Destructor respectively ---- */
            reverse_iterator() : _iter() {};
            reverse_iterator( iterator_type const &it ) { iterator_type tmp = it; --tmp; _iter = tmp; }
            template< class U >
                reverse_iterator( const reverse_iterator<U>& other ) : _iter(--other.base()) {}
            virtual ~reverse_iterator() {};

                /* Misc Operators */
            reverse_iterator& operator+= ( difference_type rhs ) { _iter -= rhs; return *this; };
            reverse_iterator& operator-= ( difference_type rhs ) { _iter += rhs; return *this; };

            reference operator*() const { return *_iter; }
            pointer   operator->() const { return &*_iter; }

            reference operator[]( difference_type rhs ) const { return (_iter[-rhs]); };

                /* Arithmetic Operators */
            reverse_iterator& operator++() { --_iter; return *this; }
            reverse_iterator& operator--() { ++_iter; return *this; }
            reverse_iterator  operator++( int ) { reverse_iterator tmp = *this; ++(*this); return tmp; }
            reverse_iterator  operator--( int ) { reverse_iterator tmp = *this; --(*this); return tmp; }

            reverse_iterator operator+( difference_type rhs ) const { return reverse_iterator(_iter - (rhs - 1)); }
            reverse_iterator operator-( difference_type rhs ) const { return reverse_iterator(_iter + (rhs + 1)); }

            operator reverse_iterator<const iterator_type> () const { return reverse_iterator<const iterator_type>(_iter) ; }

            iterator_type base() const { iterator_type tmp = _iter; ++tmp; return tmp; }

        protected:
            iterator_type   _iter;
    };

            /* ----------- Non-member function overloads ----------- */
    /* ------------------------ Relational Operators ------------------------ */
            /* ---------------- Equivalent Operators --------------- */
            /* Here are some operators whose work is same.
                (a != b) is equivalent to !(a == b)
                (a > b) equivalent to (b < a)
                (a <= b) equivalent to !(b < a) */

        /* --TO-DO:
        //! 1 - \\ ------- Should do the comparaison by base() ---------
        //! 2 - \\ ------- https://stackoverflow.com/questions/46648555/check-whether-a-reverse-iterator-has-crossed-forward-iterator-or-not/46648975 ------- */


    template< class Iter >
        reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) { return reverse_iterator<Iter>(it.base() - n); }
    template< class Iterator >
        typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) { return (rhs.base() - lhs.base()); }
/*     template <class T>
        reverse_iterator<T> operator- (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return (rhs.base() - lhs.base()); } */
	template < class T >
		bool operator== (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return lhs.base() == rhs.base(); }
	template < class T >
		bool operator!= (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return !operator==(lhs, rhs); }
	template < class T >
 		bool operator<  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return rhs.base() < lhs.base(); }
	template < class T >
 		bool operator>  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return !operator<(lhs, rhs); }
	template < class T >
 		bool operator<=  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return !operator<(rhs, lhs); }
	template < class T >
 		bool operator>=  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return !operator<=(lhs, rhs); }
}
