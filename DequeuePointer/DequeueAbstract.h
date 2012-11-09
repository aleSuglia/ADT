/*
 * dequeue.h
 *
 *  Created on: 09/nov/2012
 *      Author: AlexZ
 */

#ifndef DEQUEUE_H_
#define DEQUEUE_H_

template<typename Type, typename Pos >
class Dequeue
{
public:
	typedef Type value_type;
	typedef Pos position;

	virtual bool empty() const = 0;
	virtual void push_back( const value_type& ) = 0;
	virtual void push_front( const value_type& ) = 0;
	virtual void pop_back() = 0;
	virtual void pop_front() = 0;
	virtual void create_dequeue( ) = 0;
	virtual unsigned int size() const = 0;
	virtual value_type get_head() const = 0;
	virtual value_type get_tail() const = 0;
};

#endif /* DEQUEUE_H_ */
