#ifndef _LISTALIN_H
#define _LISTALIN_H

#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::ostream;
using std::istream;

// classe astratta listaLinare
template< class T, class P >
class LinearList{
 public:
	typedef T value_type;   // the type of object, T, stored in the list
	typedef P position;


	// operators
	virtual void create_list() = 0;
	virtual bool empty() const = 0; // true if the list's size is 0
	virtual value_type read(position) const = 0;
	virtual void write(const value_type & x, position p) = 0; // write x at position p
	virtual position begin() const = 0;  // returns a position pointing to the beginning of the list
	virtual bool end(position) const = 0; // returns a boolean value which indicate if the curr position is the end.
	virtual position end_node() const = 0; // returns a position pointing to the end of the list
	virtual position next(position) const = 0; // returns the next position
	virtual position prev(position) const = 0; // return the previous position
	virtual void insert(const value_type &, position) = 0; // insert an element
	virtual void erase(position pos) = 0; // erases the element at position pos
	//virtual void insertOrd( const value_type& ) = 0; // insert the new element at the correct position
	virtual void pushFront( const value_type & ) = 0;
	virtual void pushBack( const value_type &) = 0;
/*
	virtual void popBack() = 0;
	virtual void popFront() = 0;

	Linear_list<T,P> merge( const Linear_list<T,P>& copy_list )
	{
		Linear_list<T,P> merge_list;
		Linear_list<T,P>::position curr1, curr2, curr3;

		curr1 = begin();
		curr2 = copy_list.begin();
		curr3 = merge_list.begin();

		while( !end(curr1) && !copy_list.end(curr2) )
		{
			if( read(curr1) <= copy_list.read(curr2) )
			{
				merge_list.insert(read(curr1), curr3);
				curr1 = next(curr1);

			}
			else
			{
				merge_list.insert(copy_list.read(curr2), curr3);
				curr2 = copy_list.next(curr2);

			}

			curr3 = merge_list.next(curr3);

		}


			Copy the first list if it's not finished

		while( !end(curr1) )
		{
			merge_list.insert( read(curr1), curr3);
			curr3 = merge_list.next(curr3);
			curr1 = merge_list.next(curr1);

		}

		while( !copy_list.end(curr2) )
		{
			merge_list.insert(copy_list.read(curr2), curr3);
			curr3 = merge_list.next(curr3);
			curr2 = copy_list.next(curr2);
		}


		return merge_list;


	}*/

	void multilist( int dec_value )
	{
		int num_digit = 0;
		int temp;
		position curr = begin();

		while( dec_value )
		{
			temp = dec_value % 10;
			dec_value /= 10;


			num_digit++;
			pushFront(temp);
			curr = next(curr);

		}


	}
	void epurate()
	{
		/*
			PRECONDITION: The list must exist
		*/

		if( empty() )
		{
			throw std::logic_error("THE LIST IS EMPTY. FILL IT WITH SOME VALUES.");

		}
		else
		{
			position curr1 = begin(), curr2;

			while( !end(curr1) )
			{
				curr2  = next(curr1);

				while( !end(curr2) )
				{
					if( read(curr1 ) == read(curr2) )
						erase(curr2);
					else
						curr2 = next(curr2);

				}

				curr1 = next(curr1);

			}



		}


	}

	bool findOrdList( const value_type & elem )
	{
		/*
			PRECONDITION : the list should not be empty
		*/
		if( empty() )
		{
			throw std::logic_error("LIST IS EMPTY. PLEASE, FILL IT.");

		}
		else
		{
			position curr1 = begin();
			bool find = false;

			while( !end(curr1) && find != true )
			{
				if( elem == read(curr1) )
					find = true;
				else
					if( elem <= read(curr1) )
						find = false;
				else
					curr1 = next(curr1);

			}



			return find;

		}


	}

	int size() const
	{
		int len = 0;

		for( position curr = begin(); !end(curr); curr = next(curr) )
			++len;

		return len;


	}

	void reverse()
	{
		position p1;
		int mid = size() / 2, i = 1;

		for( p1 = begin();
			 i <= mid;
			 p1 = next(p1) )
		{
			value_type temp_node = read(p1);
			write(read(size() - p1 + 1),p1);
			write(temp_node, size() - p1 + 1);
			++i;
		}



	}

	bool palindroma() const
	{
		int mid = size() / 2;
		position p1;
		int i = 1;

		for( p1 = begin();
			 i != mid;
			 p1 = next(p1), i++ )
		{
			if( read(p1) != read(size() - p1 + 1 ) )
				return false;


		}

		return true;
	}

	// funzioni di servizio
	//friend ostream& operator<< <T,P>(ostream&, const Linear_list<T,P>&);

	/* Altre funzioni di servizio implementabili */
	/*
		virtual int size() const;  // returns the size of the list
		virtual void push_front(const value_type &); // insert a new element at the beginning
		virtual void push_back(const value_type &); // insert a new element at the end
		virtual void pop_front(); // removes the first element
		virtual void pop_back(); // removes the last element
		virtual void clear(); // erases all the elements
	*/

};

/* sovraccarica <<. Attenzione se il tipo restituito da read non è primitivo, allora
 * anche per questo tipo bisogna sovraccaricare l'operatore <<
 */
template< class T, class P >
ostream& operator<<(ostream& os, const LinearList<T,P> &l){

	typename LinearList<T,P>::position p;

	p = l.begin();
	cout << "[";
	while (!l.end(p)){
		if (p != l.begin())
			cout << ", " << l.read(p);
		else
			cout << l.read(p);
		p = l.next(p);
	}
	cout << "]" << endl;
	return os;
}



#endif // _LISTALIN_H

