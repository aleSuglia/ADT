/*
 * main.cpp
 *
 *  Created on: 27/ott/2012
 *      Author: AlexZ
 */
#include <iostream>
#include "ListCursor.h"
#include <string>

int main()
{
	ListCursor<int> my_text;

	ListCursor<int>::position p = my_text.begin();


	my_text.insert(20, p);
	p = my_text.next(p);

	my_text.insert(10, p);
	p = my_text.next(p);

	my_text.insert(23, p);


	std::cout << my_text << std::endl;

}


