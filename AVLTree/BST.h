#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>
#include <stdexcept>
#include <sstream>

#define max3(a,b,c) (a > b ? (c > a ? c : a) : (c > b ? c : b))

template <class T, class N>
class BST {
  public:

    // tipi
    typedef T value_type;
    typedef N Node;

    // operatori
    virtual void create() = 0;
    virtual bool empty() const =  0;
    virtual void insert( const value_type& ) = 0;
    virtual Node get_min() const = 0;
    virtual Node get_max() const = 0;
    virtual void erase(Node) = 0;

    bool operator==( const BST<T,N>& );
    bool operator!=( const BST<T,N>& );

    template<class U, class I> friend std::ostream& operator<<( std::ostream&, const BST<T,N>& );
    virtual void print(std::ostream& ) const;
    // visit function.
    virtual void previsit(Node); // preorder visit
    virtual void invisita(Node); // simmetric visit
    virtual void postvisit(Node); // post-order visit
    virtual void bstvisit(); // beath binary tree visit
    //virtual void morris_visit();
    virtual int size( Node ); // returns the size of the tree.
    virtual int maxDepth( Node ); // return the tree's depth

  protected:
    virtual Node root() const = 0;
    virtual Node parent(Node) const =  0;
    virtual Node sx(Node) const = 0;
    virtual Node dx(Node) const = 0;
    virtual bool sx_empty(Node) const = 0;
    virtual bool dx_empty(Node) const = 0;
    bool isLeaf( Node ) const;
    void insSubTree( Node, const BST<T,N>&, Node );

    virtual T read(Node) const = 0;
    virtual void write(Node , const value_type& ) = 0;

    virtual void ins_root(Node) = 0;
    virtual void ins_sx(Node) = 0;
    virtual void ins_dx(Node) = 0;

    void build( const BST<T,N>& t1, const BST<T,N>& t2 );
    virtual void printSubTree(std::ostream&, const Node) const;


};

template<class T,class N>
bool BST<T,N>::operator==( const BST<T,N>& t )
{
	std::stringstream tree1, tree2;

	// push onto a specific string stream both the tree.
	tree1 << *this;
	tree2 << t;

	return ( tree1.str() == tree2.str() );
}

template<class T,class N>
bool BST<T,N>::operator!=( const BST<T,N>& t )
{
	return (!(*this==t) );

}
template<class T, class N>
void BST<T,N>::build( const BST<T, N>& t1, const BST<T, N>& t2 )
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
void BST<T,N>::insSubTree(Node n1, const BST<T, N>& t, Node n2 )
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
int BST<T, N>::maxDepth( Node n )
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
int BST<T, N>::size(Node n )
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
void BST<T, N>::previsit(Node n )
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
void BST<T, N>::bstvisit()
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
void BST<T, N>::invisita(Node n )
{
	if( !sx_empty(n) )
		invisita(sx(n));

	std::cout << read(n) << ", ";

	if( !dx_empty(n) )
		invisita(dx(n));


}

template<class T, class N>
void BST<T, N>::postvisit(Node n )
{
	if( !sx_empty(n))
		postvisit(sx(n));
	if( !dx_empty(n) )
		postvisit(dx(n) );

	std::cout << read(n) << ", ";
}

template<class T, class N>
bool BST<T, N>::isLeaf( Node n ) const
{
	return( (sx_empty(n) && dx_empty(n) ) );

}

template <class T, class N>
void BST<T, N>::print( std::ostream& os ) const{
	if (!empty())
		printSubTree(os, root());
	else
		os << "[]" << std::endl;
	os << std::endl;
}

template <class T, class N>
void BST<T, N>::printSubTree(std::ostream& os, const Node n) const{

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
std::ostream& operator<<(std::ostream& out, const BST<T,N>& t) {

	t.print(out);
    return out;
}


#endif /* _BINALBEROC_H_ */

