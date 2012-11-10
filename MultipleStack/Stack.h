/*
 * Stack.h
 *
 *  Created on: 02/nov/2012
 *      Author: AlexZ
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdexcept>
#include <iostream>
#include "StackNode.h"


template<class T>
class StackPointer
{
public:
	typedef typename StackNode<T>::position position;
	typedef typename StackNode<T>::value_type value_type;

	StackPointer() { create_stack(); stack_len = 0; }
	StackPointer( const value_type& _val ){ create_stack(_val); stack_len = 0; }
	StackPointer( StackPointer<T>& copy )
	{
		if( !copy.empty() )
		{

			position curr_pos = copy.top;
			value_type temp = curr_pos->getElem();
			unsigned int i = 0;

			this->stack_len = copy.stack_len;

			this->push(temp);

			curr_pos = curr_pos->getNext();

			while( i < copy.stack_len )
			{
				temp = curr_pos->getElem();
				this->push(temp);
				curr_pos = curr_pos->getNext();
				i++;

			}


		}

	}

	StackPointer<T>& operator=( const StackPointer<T>& copy_stack )
	{
		if( &copy_stack != this )
		{
			if( !copy_stack.empty() )
			{

				position curr_pos = copy_stack.top;
				value_type temp = curr_pos->getElem();
				unsigned int i = 0;

				this->stack_len = copy_stack.stack_len;

				this->push(temp);

				curr_pos = curr_pos->getNext();

				while( i < copy_stack.stack_len )
				{
					temp = curr_pos->getElem();
					this->push(temp);
					curr_pos = curr_pos->getNext();
					i++;

				}


			}



		}

		return *this;


	}

	~StackPointer()
	{
		delete_stack();


	}
	void delete_stack()
	{
		position curr_pos = top;

		while( curr_pos != 0 )
		{
			position temp = curr_pos;
			curr_pos = curr_pos->getNext();
			delete temp;

		}

		delete curr_pos;




	}
	void create_stack( const value_type& val = value_type() )
	{
		top = new StackNode<T>(val);

	}

	bool empty() const { return (stack_len == 0 ) ? true : false; }

	void push( const value_type& _val )
	{
		top = new StackNode<T>(_val, top);
		stack_len++;

	}

	void pop()
	{
		if( empty() )
			throw std::logic_error("STACK POINTER(Exception): Stack is empty. ");
		else
		{
			position temp = top->getNext();

			delete top;

			top = temp;
			stack_len--;


		}

	}

	value_type getTop() const { return top->getElem(); }
	friend std::ostream& operator<<( std::ostream& os, StackPointer<T>& stack )
	{
		if( !stack.empty() )
		{
			typename StackPointer<T>::position curr_pos = stack.top;
			unsigned int i = 0;

			os << "[ " << curr_pos->getElem();
			curr_pos = curr_pos->getNext();

			while( i < stack.stack_len )
			{
				os << ", " << curr_pos->getElem();
				curr_pos = curr_pos->getNext();
				i++;
			}

			os << " ]" << std::endl;


		}
		return os;

	}

private:
	position top;
	unsigned int stack_len;

};


#endif /* STACK_H_ */
