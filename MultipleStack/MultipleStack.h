/*
 * MultipleStack.h
 *
 *  Created on: 02/nov/2012
 *      Author: AlexZ
 */

#ifndef MULTIPLESTACK_H_
#define MULTIPLESTACK_H_

#include "Stack.h"
#include "ListPunt.h"

// default stack number
const int def_stack_num = 10;

template<class T>
class MultipleStack
{
public:
	typedef T _Stack;
	typedef typename ListPunt<StackPointer<T> >::value_type basic_value;
	typedef typename ListPunt<StackPointer<T> >::position basic_position;

	//MultipleStack(){}
	MultipleStack(const MultipleStack<T>& copy_stack )
	{
		this->stacks = copy_stack.stacks;


	}
	MultipleStack( unsigned int n_stack  = 10)
	{
		typename ListPunt<StackPointer<T> >::position curr_stack = stacks.begin();
		StackPointer<T> temp(0);

		for( unsigned int i = 0; i < n_stack; i++ )
		{
			stacks.insert(curr_stack, temp);
			curr_stack = stacks.next(curr_stack);

		}


	}

	basic_value top( unsigned int num_stack )
	{
		typename ListPunt<StackPointer<T> >::position curr_stack = stacks.begin();
		StackPointer<T> my_stack;

		for( unsigned int i = 0; i < num_stack; i++ )
		{
			curr_stack = stacks.next(curr_stack);

		}

		my_stack = curr_stack->getElemNode();

		return my_stack.getTop();

	}

	void push( unsigned int num_stack, const basic_value& val )
	{
		typename ListPunt<StackPointer<T> >::position curr_stack = stacks.begin();
		StackPointer<T> my_stack;

		for( unsigned int i = 0; i < num_stack; i++ )
		{
			curr_stack = stacks.next(curr_stack);

		}

		my_stack = curr_stack->getElemNode();

		my_stack.push(val);


	}

	void pop( unsigned int num_stack )
	{

		typename ListPunt<StackPointer<T> >::position curr_stack = stacks.begin();
		StackPointer<T> my_stack;

		for( unsigned int i = 0; i < num_stack; i++ )
		{
			curr_stack = stacks.next(curr_stack);

		}

		my_stack = curr_stack->getElemNode();

		my_stack.pop();

	}




private:
	ListPunt< StackPointer<T> > stacks;

};

#endif /* MULTIPLESTACK_H_ */
