/*
 * main.cpp
 *
 *  Created on: 09/nov/2012
 *      Author: AlexZ
 */


#include "dequeue.h"
#include <iostream>
#include <string>

class Man
{
private:
	std::string nome;
	int eta;

public:
	Man(): nome(std::string()), eta(0) {}
	Man( const std::string& str, const int _eta ) : nome( str), eta(_eta){}
	Man( const Man& copy_man )
	{
		nome = copy_man.nome;
		eta = copy_man.eta;

	}
	std::string get_nome() const { return nome; }
	int get_eta() const { return eta; }


};

std::ostream& operator<<( std::ostream& os, const Man& man )
{
	os << "NOME : " << man.get_nome() << " ETA: " << man.get_eta();
	return os;
}

int main()
{
	dequeue<Man> deck;
	Man m1("EIRON", 30);
	Man m2("JACK", 32);

	for( int count = 10; count > 0; count-- )
	{
		if( (count % 2) == 0 ) deck.push_front(m1);
		else deck.push_back(m2);
	}
	std::cout << "THIS IS MY DEQUEUE " << deck << std::endl;

}
