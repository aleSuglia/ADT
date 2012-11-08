/*
 * StackNode.h
 *
 *  Created on: 02/nov/2012
 *      Author: AlexZ
 */

#ifndef STACKNODE_H_
#define STACKNODE_H_

template< class T>
class StackNode
{
public:
	typedef T value_type;
	typedef StackNode<T>* position;
	StackNode() : next(0), elem(0){}
	StackNode( const StackNode<T>& copy )
	{
		this->next = copy.getNext();
		this->elem = copy.getElem();

	}
	StackNode( const value_type& val, position next_ptr = 0 ) : next(next_ptr), elem(val){}
	StackNode<T>& operator=(const StackNode<T>& copy_node )
	{
		if( &copy_node != this )
		{
			this->next = copy_node.getNext();
			this->elem = copy_node.getElem();

		}
		return *this;

	}


	position getNext() { return next; }
	void setNext(const position& _next) { next = _next; }
	value_type getElem() { return elem; }
	void setElem( const value_type& new_elem ){ elem = new_elem; }

private:
	StackNode<T>* next;
	value_type elem;

};




#endif /* STACKNODE_H_ */
