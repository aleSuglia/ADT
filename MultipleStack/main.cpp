/*
 * main.cpp
 *
 *  Created on: 02/nov/2012
 *      Author: AlexZ
 */

//#include "MultipleStack.h"
#include <iostream>
#include <string>
#include "Stack.h"
#include "ListPunt.h"

int main()
{

	ListPunt<StackPointer<int> > my_stack;

	my_stack.insert(my_stack.begin(), StackPointer<int>() );



}


