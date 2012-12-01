/*
 * BinTreePointer.h
 *
 *  Created on: 23/nov/2012
 *      Author: AlexZ
 */

#ifndef BINTREEPOINTER_H_
#define BINTREEPOINTER_H_

#include "Bin_tree.h"
#include "BinTreeNode.h"

#include <stdexcept>

template<class T>
class BinTreePointer : public Bin_tree<T, BinTreeNode<T>* >
{
public:
	typedef typename Bin_tree<T,BinTreeNode<T>* >::value_type value_type;
	typedef typename Bin_tree<T,BinTreeNode<T>* >::Node Node;

	BinTreePointer()
	{
		create();

	}

	BinTreePointer(const value_type& val )
	{

		create();
		ins_root( Node(val) );

	}

	BinTreePointer( const BinTreePointer& copy_tree )
	{
		*this = copy_tree;

	}

	~BinTreePointer()
	{
		try
		{
			erase(tree_root); // destroy all the tree.
			tree_root = NULL;
		}catch( std::logic_error& )
		{

		}


	}

	void create()
	{
		tree_root = NULL;
	}


	BinTreePointer& operator= ( const BinTreePointer& copy_tree )
	{

		if( &copy_tree != this )
		{
			Node n = Node();
			ins_root(n);
			n = root();

			write(n, copy_tree.read(copy_tree.root()));
			ins_sx(n);
			ins_dx(n);

			n = sx(root());
			this->insSubTree( n, copy_tree, copy_tree.sx(copy_tree.root()) );

			n = parent(sx(root() ) );
			n = dx(n);

			this->insSubTree( n, copy_tree, copy_tree.dx( copy_tree.root() ) );

		}

		return *this;
	}

	void ins_root( Node n = 0)
	{
		if( tree_root != 0 )
		{
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : Root exists. ");

		}
		else
		{
			if( n != 0 )
				tree_root = new BinTreeNode<T>( read(n), 0, 0, 0);
			else
				tree_root = new BinTreeNode<T>( value_type(), 0, 0, 0 );

		}
	}


	void write( Node n, const value_type& val )
	{
		if( n == NULL )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : You're trying to write in an incorrect node.");
		else
			n->set_label(val);
	}

	value_type read( Node n ) const
	{
		if( n == NULL )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : You're trying to read from an incorrect node.");
		else
			return n->get_label();

	}
	bool empty() const { return ( tree_root == NULL ); }
	Node sx(Node n ) const { return n->left_node(); }
	Node dx( Node n ) const { return n->right_node(); }
    Node root() const{ return tree_root; }
    Node parent(Node n ) const{ return n->father(); }

    bool sx_empty(Node n) const{ return ( n->left_node() == NULL ); }
    bool dx_empty(Node n) const { return ( n->right_node() == NULL); }
    bool isLeaf( Node n ) const { return ( sx_empty(n) && dx_empty(n)); }

    void ins_sx( Node n )
	{
		if( empty() )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : Root doesn't exist.");
		if( sx(n) != NULL )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : The left node already exist. ");
		else
		{
			Node new_sx = new BinTreeNode<T>(value_type(), 0, 0, n); // create the left son of the n node.
			n->set_left_node(new_sx);

		}
	}

	void ins_sx( const value_type& val, Node n )
	{
		if( empty() )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : Root doesn't exist.");
		if( !sx_empty(n) )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : The right node already exist. ");
		else
		{
			Node new_sx = new BinTreeNode<T>(val, 0, 0, n); // create the left son of the n node.
			n->set_left_node(new_sx);

		}


	}

	void ins_dx( Node n )
	{
		if( empty() )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : Root already exist. ");
		if( !dx_empty(n) )
			throw std::logic_error("BIN_TREE_POINTER (Exception ) : There is already a right node. ");
		else
		{
			Node new_right = new BinTreeNode<T>( value_type(), 0, 0, n);
			n->set_right_node(new_right);


		}

	}

	void erase( Node n )
	{
		if( empty() )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : Empty tree.");
		if( n == NULL )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : Unable to remove an incorrect node.");
		else
		{
			if( !sx_empty(n) )
				erase(sx(n));
			if( !dx_empty(n) )
				erase(dx(n));
			if( n != tree_root ) // if the node it is not the root, correct the parent.
			{
				Node p = n->father();
				Node temp_node;

				if( p->left_node() == n )
				{
					p->set_left_node(NULL);
					delete n;
				}
				else
				{
					p->set_right_node(NULL);
					delete n;
				}

			}
			else
			{
				delete tree_root;
				tree_root = NULL;
			}


		}


	}

	/*
	 * Swap the subtree in the n1 node, with the subtree, in the n2 node.
	 * */
	void mutation( Node n1, BinTreePointer& t2, Node n2 )
	{
		if( n1 == 0 || n2 == 0 )
			throw std::logic_error("BIN_TREE_POINTER (Exception) : Invalid pointer passed to the function.");

		BinTreePointer<value_type> temp1(0);


		// copy the first subtree which starts from n1
		temp1.insSubTree(temp1.root(), *this, n1 );

		if( !sx_empty(n1) )
			erase( sx(n1) );

		if( !dx_empty(n1) )
			erase( dx(n1) );

		this->insSubTree(n1, t2, n2 );

		// copy the second subtree which starts from n2( of the second tree )

		if( !t2.sx_empty(n2) )
			t2.erase( sx(n2) );
		if( !t2.dx_empty(n2) )
			t2.erase( dx(n2) );

		t2.insSubTree(n2, temp1, temp1.root() );


	}
	void ins_dx( const value_type& val, Node n )
	{
		if( empty() )
			throw std::logic_error("BIN_TREE_POINTER ( Exception ) : Root already exist. ");
		if( !dx_empty(n) )
			throw std::logic_error("BIN_TREE_POINTER (Exception ) : There is already a right node. ");
		else
		{
			Node new_right = new BinTreeNode<T>(val, 0,0, n);
			n->set_right_node(new_right);


		}


	}

private:
	Node tree_root;
};

#endif /* BINTREEPOINTER_H_ */
