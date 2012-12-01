/*
 * BinTreeNode.h
 *
 *  Created on: 23/nov/2012
 *      Author: AlexZ
 */

#ifndef BINTREENODE_H_
#define BINTREENODE_H_

template<class T>
class BinTreeNode
{
public:
	typedef T value_type;
	typedef BinTreeNode* Node;


	BinTreeNode(const value_type& _label = value_type(), Node l = 0, Node r = 0, Node f = 0 ) : label(_label), left(l), right(r), parent(f) {}
	BinTreeNode(const BinTreeNode& copy_node )
	{
		*this = copy_node;
	}

	BinTreeNode& operator=( const BinTreeNode& copy_node )
	{
		if( &copy_node != this )
		{
			label = copy_node.label;
			left = copy_node.left;
			right = copy_node.right;
			parent = copy_node.parent;
		}
		return *this;

	}

	bool operator==( const BinTreeNode& n2 )
	{
		return ( label == n2.label );

	}

	bool operator!=( const BinTreeNode& n2 )
	{
		return ( !(*this == n2 ) );
	}


	Node father() const { return parent; }

	Node left_node()const { return left; }
	Node right_node() const{ return right; }
	value_type get_label() const { return label; }

	void set_father( Node n ) { parent = father; }
	void set_left_node( Node _new ) { left = _new; }
	void set_right_node(Node _new ){ right = _new; }
	void set_label( const value_type& _label ){ label = _label; }

private:
	value_type label; // current node label
	Node left; // left son
	Node right; // right son
	Node parent; // father


};

#endif /* BINTREENODE_H_ */
