/*
 * tester.cpp
 *
 *  Created on: 01/dic/2012
 *      Author: AlexZ
 */

#include "QueueP.h"

int main()
{
	QueueP<int> q;

	q.insert(10);
	q.insert(20);
	q.insert(2);
	q.insert(3);
	q.insert(8);
	q.insert(30);

	q.deleteMin();

	std::cout << "Priority Queue " << q << std::endl;

}

