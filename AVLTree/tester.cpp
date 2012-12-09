/*
 * tester.cpp
 *
 *  Created on: 09/dic/2012
 *      Author: AlexZ
 */

#include "AVLTree.h"

int main()
{
	AVLTree<int> my_avl;

	my_avl.insert(30);
	my_avl.insert(20);
	my_avl.insert(34);
	my_avl.insert(36);
	my_avl.insert(25);
	std::cout << my_avl << std::endl;
	my_avl.insert(21);
	std::cout << my_avl << std::endl;
	my_avl.insert(22);
	my_avl.insert(23);


	std::cout << my_avl << std::endl;

}
