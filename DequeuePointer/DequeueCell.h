/*
 * DequeueCell.h
 *
 *  Created on: 09/nov/2012
 *      Author: AlexZ
 */

#ifndef DEQUEUECELL_H_
#define DEQUEUECELL_H_

#include <iostream>

template<typename T>
class DequeueCell
{

public:
	typedef DequeueCell* position;
	typedef T value_type;

	DequeueCell() : elem(value_type()), prev(NULL), next(NULL) {}
	DequeueCell( const value_type& val, position _prev = NULL, position _next = NULL )
				: elem(val), prev(_prev), next(_next) {}
	DequeueCell( const DequeueCell<T>& copy )
	{
		elem = copy.elem;
		next = copy.next;
		prev = copy.prev;

	}
	~DequeueCell(){}

	DequeueCell<T>& operator=( const DequeueCell<T>& copy )
	{
		if( &copy != this )
		{
			elem = copy.elem;
			next = copy.next;
			prev = copy.prev;
		}
		return *this;
	}

	void set_next( position _next ) { next = _next; }
	position get_next() const { return next; }
	void set_elem( const value_type& _val ) { elem = _val; }
	value_type get_elem() const { return elem; }
	position get_prev( ) const { return prev; }
	void set_prev( position _prev ) { prev = _prev; }

	template <typename U> friend std::ostream& operator<<( std::ostream&, const DequeueCell<U>& );
private:
	value_type elem;
	position prev;
	position next;
};

template<typename U>
std::ostream& operator<<( std::ostream& os, const DequeueCell<U>& cell )
{
	os << cell->get_elem();
	return os;

}



#endif /* DEQUEUECELL_H_ */
