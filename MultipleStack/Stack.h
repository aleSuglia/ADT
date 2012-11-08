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
	StackPointer( const StackPointer<T>& copy )
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

	StackPointer<T> operator=( const StackPointer<T>& copy )
	{
		if( &copy != this )
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

		return *this;

	}
	void create_stack( const value_type& val = 0 )
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
			value_type item = top->getElem();
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

			std::cout << "[ " << curr_pos->getElem();
			curr_pos = curr_pos->getNext();

			while( i < stack.stack_len )
			{
				std::cout << ", " << curr_pos->getElem();
				curr_pos = curr_pos->getNext();
				i++;
			}

			std::cout << " ]" << std::endl;

			/*StackPointer<T> aux_stack;
			typename StackPointer<T>::value_type temp = stack.getTop();

			stack.pop();
			aux_stack.push(temp);
			std::cout << "[ " << temp;

			while( !stack.empty() )
			{
				temp = stack.getTop();
				std::cout << ", " << temp;
				stack.pop();
				aux_stack.push(temp);


			}

			std::cout << " ]" << std::endl;

			while( !aux_stack.empty() )
			{
				stack.push(aux_stack.getTop());
				aux_stack.pop();

			}*/


		}
		return os;

	}

private:
	position top;
	unsigned int stack_len;

};


#endif /* STACK_H_ */