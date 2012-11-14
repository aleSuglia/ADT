/*
 * ListCursor.h
 *
 *  Created on: 27/ott/2012
 *      Author: AlexZ
 */

#ifndef LISTCURSOR_H_
#define LISTCURSOR_H_

#include "LinearList.h"
#include "SpaceManagement.h"
#include <stdexcept>


/*
 * IN THIS ALGEBRA, WE ASSUME THAT THE 0 POSITION
 * OF THE SPACE VECTOR DOESN'T EXIST, SO THIS VALUE
 * WILL BE USED IN ORDER TO MARK THE END OF THE LIST.
 *
 *
 * */

const int NIL = -1;

template< class T>
class ListCursor : public LinearList<T, unsigned int >
{
public:
	/*<-------------------------- Type Definition ------------------------------------> */
	typedef typename LinearList<T,unsigned int >::position position;
	typedef typename LinearList<T,unsigned int >::value_type value_type;

	Space<T>* shared_space;

	/*<------------------------- Public Method's definition -------------------------->*/

	ListCursor()
	{
		shared_space = Space<T>::getInstance();
		create_list(sentinel_node);
		list_len = 0;


	}
	ListCursor(const ListCursor& copy )
	{
		list_len = copy.list_len;
		position copy_pos = copy.begin();
		position curr_pos = begin();

		while( copy_pos != end_node() )
		{
			insert(curr_pos, copy.shared_space.get_elem(copy_pos));
			copy_pos = copy.next(copy_pos);
			curr_pos = next(curr_pos);

		}


	}
	// initialize the list with a single node.
	explicit ListCursor(const value_type& val )
	{
		create_list(sentinel_node);

		position p = next(sentinel_node);
		insert(p, val );



	}
	~ListCursor()
	{
		position curr_pos = end_node();

		while( curr_pos != begin() )
		{
			position temp = curr_pos;
			curr_pos = prev(curr_pos);
			erase(temp);


		}

		erase(curr_pos);


	}

	void create_list()
	{}
	void create_list( position &temp )
	{
		temp = shared_space->get_free_cell();
		shared_space->set_prev( shared_space->get_next(temp), shared_space->get_prev(temp));
		shared_space->set_prev(shared_space->get_prev(temp), shared_space->get_next(temp));
		shared_space->set_free_cell(shared_space->get_next(temp));
		shared_space->set_next(temp, temp);
		shared_space->set_prev(temp, temp);


	}
	position begin() const
	{
		return shared_space->get_next(sentinel_node);

	}
	position end_node() const
	{
		return shared_space->get_prev(sentinel_node);

	}
	bool empty() const
	{
		return (list_len == 0);

	}
	bool end( position curr_pos ) const
	{
		return( shared_space->get_next(curr_pos) == sentinel_node );


	}
	position next( position curr_pos ) const
	{
		if( curr_pos >= SPACE_DIM )
			throw std::domain_error("LIST CURSOR(Exception) : Out of bounds. ");
		else
			return shared_space->get_next(curr_pos);
	}
	position prev( position curr_pos ) const
	{
		if( curr_pos >= SPACE_DIM )
			throw std::domain_error("LIST CURSOR(Exception) : Out of bounds. ");
		else
			return shared_space->get_prev(curr_pos);

	}
	void write(const value_type& val, position curr_pos  )
	{
		if( curr_pos >= SPACE_DIM )
			throw std::domain_error("LIST CURSOR(Exception) : Out of bounds. ");
		else
			shared_space->set_elem(curr_pos, val);


	}
	void insert( const value_type& val, position curr_pos )
	{
		position new_cell = curr_pos;

		shared_space->get_cell(new_cell);

		write(val, new_cell);
		list_len++;

	}

	value_type read(position curr_pos ) const
	{
		if( curr_pos >= SPACE_DIM )
			throw std::logic_error("LIST CURSOR( Exception ) : Out of bounds. ");
		else
			return shared_space->get_elem(curr_pos);

	}
	void erase( position curr_pos )
	{
		shared_space->release_cell(curr_pos);

		list_len--;

	}
	void pushBack( const value_type& val )
	{
		// gets the free cell available
		position end_pos = end_node();
		shared_space->get_cell(end_pos);

		write(val, end_pos);

		list_len++;



	}
	void pushFront( const value_type& val )
	{
		// gets the free cell available
		position begin_pos = begin();
		shared_space->get_cell(begin_pos);

		write(val, begin_pos);

		list_len++;


	}
	unsigned int length() const
	{
		return list_len;
	}


private:
	position sentinel_node; // head of the current list.
	unsigned int list_len; // current list length


};







#endif /* LISTCURSOR_H_ */
