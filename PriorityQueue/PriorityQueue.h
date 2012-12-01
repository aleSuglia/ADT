/*
 * PriorityQueue.h
 *
 *  Created on: 01/dic/2012
 *      Author: AlexZ
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <iostream>
#include <stdexcept>
#include <vector>

template<class T, class P>
class PriorityQueue
{
public:
	typedef T item;
	typedef P position;


	PriorityQueue(){}
	~PriorityQueue(){}
	PriorityQueue( const PriorityQueue& p){}


	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual void insert( const item& ) = 0;
	virtual item min() const = 0;
	virtual void deleteMin() = 0;
	virtual item max() const = 0;

private:
	//virtual void fixUp();
	//virtual void fixDown( position );


};

template<class T, class P>
std::ostream& operator<<( std::ostream& os, PriorityQueue<T,P>& p )
{
	os << "[ ";

	if( !p.empty() )
	{
		typename PriorityQueue<T,P>::item temp = p.min();
		std::vector<T> save;

		save.push_back(temp);
		p.deleteMin();
		os << temp;


		while( !p.empty() )
		{

			temp = p.min();
			save.push_back(temp);
			p.deleteMin();
			os << ", " << temp;

		}
		// recreate the priority queue.
		for( typename std::vector<T>::iterator it = save.begin();
			 it != save.end();
			 ++it )
			p.insert(*it);

	}
	os << " ]";

	return os;

}

#endif /* PRIORITYQUEUE_H_ */
