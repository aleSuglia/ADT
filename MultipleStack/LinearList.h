#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

#include <iostream>
#include <stdexcept>

template <class T, class P>
class LinearList
{
 public:
    typedef T value_type;
    typedef P position;
    LinearList() {}
    ~LinearList() {}
    LinearList( const LinearList& ) {}
    virtual void create() = 0;
    virtual bool empty() const = 0;
    virtual position begin() const = 0;
    virtual position end_node() const = 0;
    virtual bool end( position ) const = 0;
    virtual position next( position ) const = 0;
    virtual position previous( position ) const = 0;
    virtual value_type read( position ) const = 0;
    virtual void write( position, const value_type& ) = 0;
    virtual void insert( position &, const value_type& ) = 0;
    virtual void delete_node( position & ) = 0;
    virtual void pushBack( const value_type& ) = 0;
    virtual void pushFront( const value_type& ) = 0;

    int size() const
    {
        int len = 0;

        for( position curr = begin();
              curr != end_node();
              curr = next(curr) )
              ++len;

        return len;
    }

};

template< class T, class P >
std::ostream& operator<<(std::ostream& os, const LinearList<T,P> &l){
	typename LinearList<T,P>::position p;

	if ( !l.empty() )
	{
		p = l.begin();
		std::cout << "[";
		while ( !l.end(p) ){
			if (p != l.begin())
				std::cout << ", " << l.read(p);
			else
				std::cout << l.read(p);
			p = l.next(p);
		}
		std::cout << "]" << std::endl;

	}

	return os;
}

#endif
