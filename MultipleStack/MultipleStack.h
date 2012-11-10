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
	typedef T stack_type;
	typedef typename ListPunt<StackPointer<T> >::value_type basic_value;
	typedef typename ListPunt<StackPointer<T> >::position basic_position;

	MultipleStack(){}
	MultipleStack(const MultipleStack<T>& copy_stack )
	{
		this->stacks = copy_stack.stacks;


	}
	MultipleStack( unsigned int n_stack  = 10)
	{
		basic_position curr_stack;

		for( curr_stack = stacks.begin();
			 curr_stack != stacks.end_node();
			 curr_stack = stacks.next(curr_stack) )
			stacks.insert(curr_stack, StackPointer<T>());

	}

	basic_value top( unsigned int num_stack )
	{
		basic_position curr_stack = stacks.begin();

		for( int i = 0; i < num_stack && !stacks.end(curr_stack); ++i )
			curr_stack = stacks.next(curr_stack);

		stack_type this_stack = stacks.read(curr_stack);

		return this_stack.top();



	}

	void push( unsigned int num_stack, const basic_value& val )
	{
		basic_position curr_stack = stacks.begin();

		for( int i = 0; i < num_stack && !stacks.end(curr_stack); ++i )
			curr_stack = stacks.next(curr_stack);

		stack_type this_stack = stacks.read(curr_stack);

		this_stack.push(val);


	}

	void pop( unsigned int num_stack )
	{
		basic_position curr_stack = stacks.begin();

		for( int i = 0; i < num_stack && !stacks.end(curr_stack); ++i )
			curr_stack = stacks.next(curr_stack);

		stack_type this_stack = stacks.read(curr_stack);

		this_stack.pop();


	}




private:
	ListPunt< StackPointer<T> > stacks;

};

#endif /* MULTIPLESTACK_H_ */
