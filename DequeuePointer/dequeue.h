/*
 * DequeueVector.h
 *
 *  Created on: 09/nov/2012
 *      Author: AlexZ
 */

#ifndef DEQUEUEVECTOR_H_
#define DEQUEUEVECTOR_H_

#include "DequeueCell.h"
#include "DequeueAbstract.h"
#include <stdexcept>

template<typename T>
class dequeue : public Dequeue<T, DequeueCell<T>* >
{
public:
	typedef typename Dequeue<T, DequeueCell<T>* >::position position;
	typedef typename Dequeue<T, DequeueCell<T>* >::value_type value_type;

private:
	position head;
	position tail;
	size_t dequeue_len;

public:
	dequeue()
	{
		create_dequeue();
		dequeue_len = 0;

	}
	dequeue( const value_type& val )
	{
		create_dequeue(val);
		dequeue_len = 1;

	}

	dequeue( const dequeue<T>& copy_dequeue )
	{
		if( !empty() )
		{
			position curr_pos = copy_dequeue.head;

			while( curr_pos != copy_dequeue.tail )
			{
				this->push_back(curr_pos->getElem());
				curr_pos = curr_pos->getNext();

			}

			dequeue_len = copy_dequeue.dequeue_len;

		}


	}
	~dequeue()
	{
		destroy_dequeue();
		dequeue_len = 0;

	}

	bool empty() const
	{
		return ( dequeue_len == 0 );
	}
	void create_dequeue()
	{
		head = tail = new DequeueCell<T>(value_type());


	}

	void create_dequeue( const value_type& val )
	{
		head = new DequeueCell<T>(val);
		head->set_next(NULL);
		head->set_prev(NULL);
		tail = head;
		dequeue_len = 1;


	}

	void destroy_dequeue()
	{

		position curr_pos = tail;

		while( curr_pos != head )
		{
			position temp = curr_pos;
			curr_pos = curr_pos->get_prev();
			delete temp;

		}

		delete curr_pos;

	}

	void push_back( const value_type& val )
	{
		// if it is not the first node
		if( !empty() )
		{
			// create the new node and initialize it
			tail->set_next( new DequeueCell<T>(val, tail, 0));
			tail = tail->get_next();
			dequeue_len++;

		}
		else
		{
			head = tail = new DequeueCell<T>(val, 0, 0);

			dequeue_len++;

		}
	}
	void push_front( const value_type &val )
	{
		// create the node, initialize it and connect it to the head
		if( !empty() )
		{
			head->set_prev(new DequeueCell<T>(val, 0, head));
			head = head->get_prev();
		}
		else // if there aren't any cells, we need to create the head which is equal to the tail.
		{
			tail = head = new DequeueCell<T>(val, 0, 0);


		}
		dequeue_len++;


	}

	void pop_front()
	{
		position temp_node = head;
		head = head->get_next();
		head->set_prev(NULL);

		delete temp_node;
		dequeue_len--;

	}

	void pop_back()
	{
		position temp_node = tail;
		tail = tail->get_prev();
		tail->set_next(NULL);
		delete temp_node;
		dequeue_len--;

	}

	value_type get_tail() const
	{
		if( !empty() )
			return tail->get_elem();
		else
			throw std::logic_error("(Dequeue Exception) : Dequeue is empty!No element in the tail.");
	}

	value_type get_head() const
	{
		if( !empty() )
			return head->get_elem();
		else
			throw std::logic_error("(Dequeue Exception) : Dequeue is empty! No element in the head. ");
	}

	template< typename U> friend std::ostream& operator<<( std::ostream&, const dequeue<U>& );

	unsigned int size() const { return dequeue_len; }


};

template<typename U>
std::ostream& operator<<( std::ostream& os, const dequeue<U>& deck )
{
	if(!deck.empty() )
	{
		typename dequeue<U>::position curr_pos = deck.head;

		os << "[ " << curr_pos->get_elem();
		curr_pos = curr_pos->get_next();

		while( curr_pos != NULL )
		{
			os << ", " << curr_pos->get_elem();
			curr_pos = curr_pos->get_next();


		}

		os << " ]" << std::endl;



	}

	return os;


}


#endif /* DEQUEUEVECTOR_H_ */
