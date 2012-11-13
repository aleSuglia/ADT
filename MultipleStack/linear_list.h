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
class Linear_list{
 public:
	typedef T value_type;   // the type of object, T, stored in the list
	typedef P position;

	// operators
	virtual void create() = 0;
	virtual bool empty() const = 0; // true if the list's size is 0
	virtual value_type read(position) const = 0;
	virtual void write(const value_type & x, position p) = 0; // write x at position p
	virtual position begin() const = 0;  // returns a position pointing to the beginning of the list
	virtual bool end(position) const = 0; // returns a boolean value which indicate if the curr position is the end.
	//virtual position end_node() const = 0; // returns a position pointing to the end of the list
	virtual position next(position) const = 0; // returns the next position
	virtual position previous(position) const = 0; // return the previous position
	virtual void insert(const value_type &, position) = 0; // insert an element
	virtual void erase(position pos) = 0; // erases the element at position pos
	//virtual void insertOrd( const value_type& ) = 0; // insert the new element at the correct position


	position end_node() const
	{
		position curr = begin();

		while( !end(next(curr)) )
		{
			curr = next(curr);

		}

		return curr;


	}


	void merge( const Linear_list<T,P>& copy_list1, const Linear_list<T,P>& copy_list2 )
	{
		Linear_list<T,P>::position curr1, curr2, curr3;

		curr1 = copy_list1.begin();
		curr2 = copy_list2.begin();
		curr3 = begin();

		while( !copy_list1.end(curr1) && !copy_list2.end(curr2) )
		{
			if( copy_list1.read(curr1) <= copy_list2.read(curr2) )
			{
				insert(read(curr1), curr3);
				curr1 = copy_list1.next(curr1);
			
			}
			else
			{
				insert(copy_list2.read(curr2), curr3);
				curr2 = copy_list2.next(curr2);
				
			}
	
			curr3 = next(curr3);

		}


		//Copy the first list if it's not finished

		while( !copy_list1.end(curr1) )
		{
			insert( copy_list1.read(curr1), curr3);
			curr3 = next(curr3);
			curr1 = copy_list1.next(curr1);
		
		}

		while( !copy_list2.end(curr2) )
		{
			insert(copy_list2.read(curr2), curr3);
			curr3 = next(curr3);
			curr2 = copy_list2.next(curr2);
		}

	

	
	
	}

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

	/*
	 * Precondition: the list should not be empty.
	 *
	 *
	 * */
	bool find( const value_type& elem )const
	{
		if( empty() )
		{
			throw std::logic_error("List(Exception) : The list is empty. ");

		}
		else
		{
			Linear_list<T,P>::position curr = begin();

			while( !end(curr) )
			{
				if ( read(curr) == elem )
				{

					return true;
				}
				curr = next(curr);


			}

			return false;


		}

	}
	bool findOrdList( const value_type & elem )
	{
		/*
			PRECONDITION : the list should not be empty.
			ASSERTION : the list should be ordered.
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
		position pos_begin, pos_end;
		int mid = size() / 2, i = 1;

		for( pos_begin = begin(), pos_end = end_node();
			 i != mid;
			 pos_begin = next(pos_begin), pos_end = previous(pos_end), i++ )
		{
			value_type temp = read(pos_begin);
			write(pos_begin, read(pos_end));
			write(pos_end, temp );


		}



	}

	void clear()
	{
		position curr = end_node();

		while( !empty() )
		{
			position temp = curr;
			curr = previous(curr);
			erase(temp);
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

	void pushBack( const value_type& elem )
	{
		position end = end_node()->getNextNode();

		insert(elem, end);

	}

	void pushFront( const value_type& elem )
	{
		insert(elem, begin());

	}

	void popFront()
	{
		erase(begin());


	}


	void popBack()
	{
		erase(end_node());

	}

};

/* sovraccarica <<. Attenzione se il tipo restituito da read non è primitivo, allora
 * anche per questo tipo bisogna sovraccaricare l'operatore <<
 */
template< class T, class P >
ostream& operator<<(ostream& os, const Linear_list<T,P> &l){
	typename Linear_list<T,P>::position p;
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

template< class T, class P>
istream& operator<<( istream& in, const Linear_list<T,P>& l )
{
	if( in && l.empty() )
	{
		in.clear();

		typename Linear_list<T,P>::value_type temp;
		typename Linear_list<T,P>::position curr_pos = l.begin();

		while( in >> temp )
		{
			l.insert(curr_pos, temp);
			curr_pos = l.next(curr_pos);

		}


	}

	return in;

}



#endif // _LISTALIN_H

