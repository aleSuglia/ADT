#ifndef LIST_PUNT_H
#define LIST_PUNT_H

#include "LinearList.h"
#include "ListCell.h"

template <class T>
class ListPunt : public LinearList<T, ListCell<T>*>
{
    public:
    typedef typename LinearList<T,ListCell<T>* >::position position;
    typedef typename LinearList<T,ListCell<T>* >::value_type value_type;

    ListPunt()
    {

    	create();
    }

    ListPunt( const ListPunt<T>& copy_list )
    {

    	this->create();
    	for( ListPunt<T>::position curr1 = copy_list.begin(),curr2 = this->begin();
    	     !copy_list.end(curr1);
    	     curr2 = this->next(curr2),curr1 = copy_list.next(curr1) )
    		this->insert(curr2, copy_list.read(curr1));

    }

    ListPunt<T>& operator=( const ListPunt<T>& copy_list )
    {
    	if( &copy_list != this )
    	{
    		this->create();
    		for( ListPunt<T>::position curr1 = copy_list.begin(),curr2 = this->begin();
    		     !copy_list.end(curr1);
    		     curr2 = this->next(curr2),curr1 = copy_list.next(curr1) )
    			this->insert(curr2, copy_list.read(curr1));


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
    position end_node() const;
    bool end( position ) const;
    position next( position ) const;
    position previous( position ) const;
    value_type read( position ) const;
    void write( position, const value_type& );
    void insert( position&, const value_type& );
    void delete_node( position& );
    void pushFront( const value_type& );
    void pushBack( const value_type& );


    private:
    	void delete_list();
        void create();
        position sentinel_node;
        unsigned int list_len;
};


template< class T>
void ListPunt<T>::delete_list()
{

	position curr = end_node();

	while( curr != begin() )
	{
		position temp = curr;
		curr = previous(curr);
		delete temp;


	}

	delete curr;

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
    return ( list_len == 0 );

}

template< class T>
typename ListPunt<T>::position ListPunt<T>::begin() const
{
    return sentinel_node->getNextNode();
}

template< class T>
typename ListPunt<T>::position ListPunt<T>::end_node() const
{
	return sentinel_node->getPrevNode();
	
}

template< class T>
bool ListPunt<T>::end( position curr ) const
{
    return ( curr == sentinel_node );
}

template< class T>
typename ListPunt<T>::position ListPunt<T>::next( position curr ) const
{
    return curr->getNextNode();
}

template< class T>
typename ListPunt<T>::position ListPunt<T>::previous( position curr ) const
{
    return ( curr == begin() ) ? end_node() : curr->getPrevNode();
}

template< class T>
typename ListPunt<T>::value_type ListPunt<T>::read( position curr ) const
{
    return curr->getElemNode();
}


template<class T>
void ListPunt<T>::write( position curr, const value_type& new_elem )
{
	if( !empty() )
		curr->setElemNode(new_elem);
}

template< class T>
void ListPunt<T>::insert( position& curr, const value_type& value )
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
void ListPunt<T>::delete_node( position& p )
{
    position temp_node = new ListCell<T>;

    temp_node = p; // save the current node which will be deleted.
    (p->getNextNode())->setPrevNode(p->getPrevNode()); // the previous pointer of the next will point to the previous of the current.
    (p->getPrevNode())->setNextNode(p->getNextNode());
    p=p->getNextNode();
    list_len--;

    delete temp_node;


}

template<class T>
void ListPunt<T>::pushBack( const value_type& elem )
{
	position end = end_node()->getNextNode();

	insert(end, elem);

}

template<class T>
void ListPunt<T>::pushFront( const value_type& elem )
{
	position first = begin();

	insert(first, elem);

}
#endif
