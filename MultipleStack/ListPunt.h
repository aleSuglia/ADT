#ifndef LIST_PUNT_H
#define LIST_PUNT_H

#include "Linear_list.h"
#include "ListCell.h"

template <class T>
class ListPunt : public Linear_list<T, ListCell<T>*>
{
    public:
    typedef typename Linear_list<T,ListCell<T>* >::position position;
    typedef typename Linear_list<T,ListCell<T>* >::value_type value_type;

    ListPunt()
    {

    	create();
    }

    ListPunt( const ListPunt<T>& copy_list )
    {

    	this->create();
    	for( ListPunt<T>::position curr1 = copy_list.begin(),curr2 = this->begin();
    	     !copy_list.end(curr1);
    	     curr1 = copy_list.next(curr1) )
    		this->insert(copy_list.read(curr1), curr2);

    }

    ListPunt<T>& operator=( const ListPunt<T>& copy_list )
    {
    	if( &copy_list != this )
    	{

    		this->create();
    		for( ListPunt<T>::position curr1 = copy_list.begin(),curr2 = this->begin();
    		     !copy_list.end(curr1);
    		     curr1 = copy_list.next(curr1) )
    			this->insert(copy_list.read(curr1), curr2);


    	}

    	return *this;

    }

    ListPunt(const value_type& val )
    {

    	create();
    	position first = begin();
    	insert(first, val);



    }
    ~ListPunt()
    {
    	if( !empty() )
    		delete_list();


    }


    bool empty() const;
    position begin() const;
    bool end( position ) const;
    position next( position ) const;
    position previous( position ) const;
    value_type read( position ) const;
    void write( const value_type&, position );
    void insert( const value_type&, position );
    void erase( position );

    // some useful member-operators.
    ListPunt<T>& operator+=( const ListPunt<T>& );


    private:
    	void delete_list();
        void create();
        position sentinel_node;
        unsigned int list_len;
};


template<class T>
ListPunt<T>& ListPunt<T>::operator+=( const ListPunt<T>& rhs )
{
	// insert at the end of the list copying all the values.
	for( position curr_rhs = rhs.begin();
		 !rhs.end(curr_rhs);
		 curr_rhs = rhs.next(curr_rhs) )
	{
		this->pushBack( rhs.read(curr_rhs));

	}

	return *this;

}

template<class T>
ListPunt<T> operator+( const ListPunt<T>& lhs, const ListPunt<T>& rhs )
{
	ListPunt<T> ret = lhs;

	ret += rhs;

	return ret;

}

template< class T>
void ListPunt<T>::delete_list()
{

	position curr = begin();

	while( !end(curr) )
	{
		position temp = curr;
		curr = next(curr);
		delete temp;


	}
}

template< class T>
void ListPunt<T>::create()
{

	sentinel_node = new ListCell<T>;
	sentinel_node->setNextNode(sentinel_node);
	sentinel_node->setPrevNode(sentinel_node);
	sentinel_node->setElemNode(T());

	list_len = 0;

}
template< class T>
bool ListPunt<T>::empty() const
{
    return ( this->size() == 0 );

}

template< class T>
typename ListPunt<T>::position ListPunt<T>::begin() const
{
    return sentinel_node->getNextNode();
}


template<class T>
bool ListPunt<T>::end(position curr) const
{
	return (curr == sentinel_node);
}

template< class T>
typename ListPunt<T>::position ListPunt<T>::next( position curr ) const
{
    return curr->getNextNode();
}

template< class T>
typename ListPunt<T>::position ListPunt<T>::previous( position curr ) const
{
    return ( curr == begin() ) ? this->end_node() : curr->getPrevNode();
}

template< class T>
typename ListPunt<T>::value_type ListPunt<T>::read( position curr ) const
{
    return curr->getElemNode();
}


template<class T>
void ListPunt<T>::write( const value_type& new_elem, position curr )
{
	if( !empty() )
		curr->setElemNode(new_elem);
}

template< class T>
void ListPunt<T>::insert( const value_type& value, position curr )
{

    position temp_node = new ListCell<T>;
    temp_node->setElemNode(value);
    (curr->getPrevNode())->setNextNode(temp_node);
    temp_node->setPrevNode(curr->getPrevNode());
    temp_node->setNextNode(curr);
    curr->setPrevNode(temp_node);
    curr = temp_node;

    list_len++;

}

template< class T>
void ListPunt<T>::erase( position p )
{
    position temp_node = new ListCell<T>;

    temp_node = p; // save the current node which will be deleted.
    (p->getNextNode())->setPrevNode(p->getPrevNode()); // the previous pointer of the next will point to the previous of the current.
    (p->getPrevNode())->setNextNode(p->getNextNode());
    p=p->getNextNode();
    list_len--;

    delete temp_node;


}

//Constant operator which doesn't modify the structure.

template<class T>
bool operator==(const ListPunt<T>& list1, const ListPunt<T>& list2 )
{
	typename ListPunt<T>::position curr1 = list1.begin(), curr2 = list2.begin();

	for( ; !list1.end(curr1) && !list2.end(curr2);
			curr1 = list1.next(curr1), curr2 = list2.next(curr2) )
	{
		// if we arrive here, we have to exit with false because we've found an element which is not equal
		// to the other of the second list.
		if( list1.read(curr1) != list2.read(curr2) )
			return false;

	}

	// in this case, we have two identical list.
	return true;


}

template<class T>
bool operator!=(const ListPunt<T>& list1, const ListPunt<T>& list2 )
{
	// if list1 != list2 -> true
	// otherwise -> false
	return !(list1 == list2);


}


#endif
