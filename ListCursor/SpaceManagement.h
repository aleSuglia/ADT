/*
 * SpaceManagement.h
 *
 *  Created on: 10/nov/2012
 *      Author: AlexZ
 */

#ifndef SPACEMANAGEMENT_H_
#define SPACEMANAGEMENT_H_

#include <stdexcept>

const unsigned int SPACE_DIM = 100;


template<class T>
class Space
{

public:
	typedef unsigned int cursor;
	typedef T value_type;
	typedef struct space_cell
	{
		cursor next;
		cursor prev;
		value_type elem;

	}SpaceCell;

	/*< ------------------------- Space Vector ---------------------------------------->*/
		static SpaceCell* space;
		static Space* global_ptr;
		static cursor free_list; // initial value of the free list.
		static unsigned int free_list_length; // available list cells
		static bool allocated;
private:
		void move( cursor&, cursor& );
public:
	~Space()
	{
		delete space;
		delete global_ptr;
		free_list_length = 0;
		free_list = 0;

	}

	static Space<T>* getInstance();
	void create_space();
	cursor get_free_cell();
	void set_free_cell(cursor );
	unsigned int get_avail_space() const;
	void release_cell(cursor& );
	void get_cell(cursor& );
	void set_next( cursor, cursor );
	cursor get_next( cursor ) const;
	void set_prev(cursor, cursor);
	cursor get_prev(cursor) const;
	value_type get_elem( cursor ) const;
	void set_elem( cursor, const value_type& );

};

template<class T> typename Space<T>::SpaceCell* Space<T>::space = NULL;
template<class T> typename Space<T>::Space* Space<T>::global_ptr = NULL;
template<class T> typename Space<T>::cursor Space<T>::free_list = 0;
template<typename T> unsigned int Space<T>::free_list_length = 0;
template<typename T> bool Space<T>::allocated = false;


template<class T>
void Space<T>::get_cell( cursor& curr )
{
	global_ptr->move(global_ptr->free_list, curr);

}

template<class T>
void Space<T>::release_cell(cursor& curr )
{
	global_ptr->move(curr, global_ptr->free_list);
}

template<class T>
Space<T>* Space<T>::getInstance()
{
	if( !allocated )
	{
		allocated = true;
		global_ptr = new Space();
		global_ptr->create_space();
	}
	return global_ptr;

}

template<class T>
unsigned int Space<T>::get_avail_space() const
{
	return free_list_length;

}
template<class T>
typename Space<T>::cursor Space<T>::get_free_cell()
{
	return free_list;

}

template<class T>
void Space<T>::set_free_cell( cursor new_free_cell )
{
	if( new_free_cell >= SPACE_DIM )
		throw std::domain_error("SPACE(Exception) : Unable to assign the new free cell.");
	else
		free_list = new_free_cell;
}
template< class T>
void Space<T>::move( cursor& new_cell, cursor& curr_pos  )
{
	cursor temp = global_ptr->space[new_cell].next;
	global_ptr->space[global_ptr->space[new_cell].prev].next = global_ptr->space[new_cell].next;
	global_ptr->space[global_ptr->space[new_cell].next].prev = global_ptr->space[new_cell].prev;
	/*global_ptr->space[new_cell].prev = global_ptr->space[curr_pos].prev;
	global_ptr->space[global_ptr->space[curr_pos].prev].next = new_cell;
	global_ptr->space[new_cell].next = curr_pos;
	global_ptr->space[curr_pos].prev = new_cell;*/
	global_ptr->space[global_ptr->space[curr_pos].prev].next = new_cell;
	global_ptr->space[new_cell].prev = global_ptr->space[curr_pos].prev;
	global_ptr->space[new_cell].next = curr_pos;
	global_ptr->space[curr_pos].prev = new_cell;
	curr_pos = new_cell;
	new_cell = temp;

}

template< class T>
void Space<T>::create_space()
{
	global_ptr->space = new SpaceCell[SPACE_DIM];

	for( unsigned int i = 0; i < SPACE_DIM; ++i )
	{
		global_ptr->space[i].next = ( (i+1) % SPACE_DIM );
		global_ptr->space[i].prev = ( (i+1) % SPACE_DIM ) - 1;
		global_ptr->space[i].elem = value_type();


	}

	/*for( unsigned int i = 0; i < SPACE_DIM; ++i )
		std::cout << "NEXT " << global_ptr->space[i].next << " PREV : " << global_ptr->space[i].prev << "\n";
	*/

	global_ptr->free_list = 0;
	global_ptr->free_list_length = SPACE_DIM;


}

template< class T>
void Space<T>::set_next( cursor curr_pos, cursor next_pos )
{
	if( curr_pos >= SPACE_DIM )
		throw std::logic_error("SPACE(Exception) - set_next() : Out of bounds.");
	else
		global_ptr->space[curr_pos].next = next_pos;
}

template<class T>
typename Space<T>::cursor Space<T>::get_next( cursor curr_pos ) const
{
	if( curr_pos >= SPACE_DIM )
		throw std::logic_error("SPACE(Exception) - get_next() : Out of bounds. ");
	else
		return global_ptr->space[curr_pos].next;

}

template<class T>
void Space<T>::set_prev(cursor curr_pos, cursor prev_pos )
{
	if( curr_pos >= SPACE_DIM )

		throw std::logic_error("SPACE(Exception) - set_prev() : Out of bounds.");
	else
		global_ptr->space[curr_pos].prev = prev_pos;



}

template<class T>
typename Space<T>::cursor Space<T>::get_prev(cursor curr_pos ) const
{
	if( curr_pos >= SPACE_DIM )
		throw std::logic_error("SPACE(Exception) - get_prev() : Out of bounds. ");
	else
		return global_ptr->space[curr_pos].prev;

}

template<class T>
typename Space<T>::value_type Space<T>::get_elem( cursor curr_pos ) const
{
	if( curr_pos >= SPACE_DIM )
		throw std::logic_error("SPACE(Exception) - get_elem() : Out of bounds. ");
	else
		return global_ptr->space[curr_pos].elem;

}

template<class T>
void Space<T>::set_elem( cursor curr_pos, const value_type& val )
{
	if( curr_pos >= SPACE_DIM )
			throw std::logic_error("SPACE(Exception) - set_elem() : Out of bounds. ");
	else
		global_ptr->space[curr_pos].elem = val;

}



#endif /* SPACEMANAGEMENT_H_ */
