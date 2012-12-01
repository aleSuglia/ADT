#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <iostream>
#include <queue>
#include <stdexcept>
#include <sstream>

#define max3(a,b,c) (a > b ? (c > a ? c : a) : (c > b ? c : b))
#define min3(a,b,c) (a < b ? (c < a ? c : a) : (c < b ? c : b))

template <class T, class N>
class Bin_tree {
  public:

    // tipi
    typedef T value_type;
    typedef N Node;

    // operatori
    virtual void create() = 0;
    virtual bool empty() const =  0;

    virtual Node root() const = 0;
    virtual Node parent(Node) const =  0;
    virtual Node sx(Node) const = 0;
    virtual Node dx(Node) const = 0;
    virtual bool sx_empty(Node) const = 0;
    virtual bool dx_empty(Node) const = 0;
    bool isLeaf( Node ) const;
    void insSubTree( Node, const Bin_tree<T,N>&, Node );

    virtual void erase(Node) = 0;
    virtual T read(Node) const = 0;
    virtual void write(Node , const value_type& ) = 0;

    virtual void ins_root(Node) = 0;
    virtual void ins_sx(Node) = 0;
    virtual void ins_dx(Node) = 0;

    // visit function.
    virtual void previsit(Node); // preorder visit
    virtual void invisita(Node); // simmetric visit
    virtual void postvisit(Node); // post-order visit
    virtual void bstvisit(); // breadth binary tree visit
    //virtual void morris_visit();
    virtual int size( Node ) const; // returns the size of the tree.
    virtual int maxDepth( Node ) const; // return the tree's depth
    void build( const Bin_tree<T,N>& t1, const Bin_tree<T,N>& t2 );

    void epurateVal(Node, const value_type& ); // remove a specific value from the tree
    void epurateLeaves( Node, const value_type& ); // removes from the leaves the value type passed to the function.
    value_type get_max( Node ) const; // get the max value contained in the tree.
    value_type get_min( Node ) const; // get the minimum value contained in the tree
    //void mutation( const Node, const Node );



    bool operator==( const Bin_tree<T,N>&  );
    bool operator!=( const Bin_tree<T,N>&  );
    virtual void print(std::ostream& ) const;

private:
    virtual void printSubTree(std::ostream&, const Node) const;


};

template<class T,class N>
bool Bin_tree<T,N>::operator==( const Bin_tree<T,N>& t )
{
	std::stringstream tree1, tree2;

	// push onto a specific string stream both the tree.
	tree1 << *this;
	tree2 << t;

	return ( tree1.str() == tree2.str() );
}

template<class T,class N>
bool Bin_tree<T,N>::operator!=( const Bin_tree<T,N>& t )
{
	return (!(*this==t) );

}

template<class T, class N>
typename Bin_tree<T,N>::value_type Bin_tree<T,N>::get_min( Node n ) const
{
	value_type min_left,  min_right;
	if( !sx_empty(n) )
		min_left = get_min(sx(n));
	if( !dx_empty(n) )
		min_right = get_min(dx(n));

	return min3( min_left, min_right, read(n) );


}

template<class T, class N>
void Bin_tree<T, N>::build( const Bin_tree<T,N>& t1, const Bin_tree<T,N>& t2 )
{

	Node n = Node();

	ins_root(n); // create root
	write(n, 0 );
	ins_sx(n); // create left child
	ins_dx(n); // create right child

	insSubTree( sx(n), t1, t1.root() );

	insSubTree( dx(n), t2, t2.root() );

}


template<class T, class N>
void Bin_tree<T, N>::insSubTree(Node n1, const Bin_tree<T,N>& t, Node n2 )
{

	if( t.empty() || !isLeaf(n1) )
		throw std::logic_error("BinTree (Exception ) : Invalid values passed to the function. ");

	write(n1, t.read(n2) );

	if( !t.sx_empty(n2) )
	{
		ins_sx(n1);
		insSubTree(sx(n1), t, t.sx(n2) );

	}

	if( !t.dx_empty(n2) )
	{
		ins_dx(n1);
		insSubTree(dx(n1), t, t.dx(n2) );

	}

}

template<class T, class N>
int Bin_tree<T,N>::maxDepth( Node n ) const
{

	int count_right = 0;
	int count_left = 0;

	// count the left side
	if( !sx_empty(n) )
		count_left = maxDepth(sx(n));
	// count the right side
	if( !dx_empty(n) )
		count_right = maxDepth(dx(n));

	// now take the longest
	if( count_right > count_left )
		return 1 + count_right;
	else
		return 1 + count_left;

}

template<class T, class N>
int Bin_tree<T,N>::size(Node n ) const
{
	int count_left = 0;
	int count_right = 0;

	if( !sx_empty(n) )
		count_left = size(sx(n));
	if( !dx_empty(n) )
		count_right = size(dx(n));

	return 1 + count_left + count_right;

}


template<class T, class N>
void Bin_tree<T,N>::previsit(Node n )
{
	// visit the node n
	std::cout << read(n) << ", ";
	if( !sx_empty(n) )
	{
		previsit(sx(n));
	}


	if( !dx_empty(n) )
	{
		previsit(dx(n) );

	}


}

template<class T, class N>
void Bin_tree<T,N>::bstvisit()
{
	//
	std::queue<N> q;

	q.push(root());

	while( !q.empty() )
	{
		Node n = q.front();
		q.pop();
		std::cout << read(n) << ", ";
		if( !sx_empty(n) )
			q.push(sx(n));
		if( !dx_empty(n) )
			q.push(dx(n));


	}

}

template<class T, class N>
void graphTree( const Bin_tree<T,N>& t )
{
	std::queue<N> q;
	typename Bin_tree<T,N>::value_type last_pushed;

	q.push(t.root());

	while( !q.empty() )
	{
		typename Bin_tree<T,N>::Node n = q.front();

		q.pop();

		std::cout << t.read(n) << ", ";

		if( t.read(n) == last_pushed )
			std::cout << std::endl;

		if( !t.sx_empty(n) )
		{
			last_pushed = t.sx(n);
			q.push(t.sx(n));
		}
		if( !t.dx_empty(n) )
		{
			last_pushed = t.dx(n);
			q.push(t.dx(n));
		}

	}




}
template<class T, class N>
void Bin_tree<T,N>::invisita(Node n )
{
	if( !sx_empty(n) )
		invisita(sx(n));

	std::cout << read(n) << ", ";

	if( !dx_empty(n) )
		invisita(dx(n));


}

template<class T, class N>
void Bin_tree<T,N>::postvisit(Node n )
{
	if( !sx_empty(n))
		postvisit(sx(n));
	if( !dx_empty(n) )
		postvisit(dx(n) );

	std::cout << read(n) << ", ";
}

template<class T, class N>
bool Bin_tree<T,N>::isLeaf( Node n ) const
{
	return( (sx_empty(n) && dx_empty(n) ) );

}

template<class T, class N>
typename Bin_tree<T,N>::value_type Bin_tree<T,N>::get_max( Node t ) const
{
	value_type max_left = value_type(), max_right = value_type();

	if( !sx_empty(t) )
		max_left = get_max(sx(t));
	if( !dx_empty(t) )
		max_right = get_max(dx(t));

	return max3(max_left, max_right, read(t));


}

template<class T, class N>
void Bin_tree<T,N>::epurateLeaves( Node n, const value_type& val )
{
	if( !empty() ) // if it's not empty the tree
	{
		if( !sx_empty(n) )
			epurateLeaves( sx(n), val );
		if( !dx_empty(n) )
			epurateLeaves( dx(n), val );

		if( val == read(n) )
			erase(n);


	}


}


template <class T, class N>
void Bin_tree<T,N>::epurateVal( Node curr_nodo, const value_type& val )
{
	if( !empty() )
	{
		if ( read(curr_nodo) == val )
			erase(curr_nodo);
		else
			if( !sx_empty(curr_nodo) )
				epurateVal(sx(curr_nodo), val );

		if( !dx_empty(curr_nodo) )
			epurateVal(dx(curr_nodo), val);

	}

}

/*template<class T, class N>
void Bin_tree<T,N>::mutation( Node a_node, Node b_node )
{


}*/

template <class T, class N>
void Bin_tree<T,N>::print( std::ostream& os ) const{
	if (!empty())
		printSubTree(os, root());
	else
		os << "[]" << std::endl;
	os << std::endl;
}

template <class T, class N>
void Bin_tree<T,N>::printSubTree(std::ostream& os, const Node n) const{

	os << "[" << read(n) << ", ";
	if (!sx_empty(n))
		printSubTree(os, sx(n));
	else os << "NIL";
	os << ", ";
	if (!dx_empty(n))
		printSubTree(os, dx(n));
	else os << "NIL";
	os << " ]";
}

template<class T, class N>
std::ostream& operator<<(std::ostream& out, const Bin_tree<T, N>& t) {

	t.print(out);
    return out;
}


#endif /* _BINALBEROC_H_ */

