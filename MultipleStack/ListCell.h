#ifndef LIST_CELL_H
#define LIST_CELL_H

#include <iostream>

template <class T>
class ListCell
{
    public:
        typedef T value_type;
        typedef ListCell* position;

        /* <----------- Constructor Definition ------------------------> */
        ListCell() : elem(T()), next(0), prev(0) { }
        ListCell( const value_type& first_val ) : elem(first_val), next(0), prev(0) {}
        explicit ListCell( const value_type& first_val, const position& next_node, const position& prev_node )
        	: elem(first_val), next(next_node), prev(prev_node) {}

        ~ListCell() { }

        /* <----------- ListCell operators ---------------------------> */
        position getPrevNode () const { return prev; }
        position getNextNode () const { return next; }
        void setNextNode( position curr ) { next = curr; }
        void setPrevNode( position curr ) { prev = curr; }
        value_type getElemNode( ) const { return elem; }
        void setElemNode( const value_type& new_val ) { elem = new_val; }


    private:
        value_type elem;
        position next;
        position prev;

};

/*
 * Overloading of the << operator
 * in order to print correctly everytime of
 * data.
 *
 * */
template<class T>
std::ostream& operator <<( std::ostream& os, const ListCell<T>& cell )
{
	return os << cell.getElemNode();

}

#endif
