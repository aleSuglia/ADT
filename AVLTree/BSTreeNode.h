/*
 * BSTreeNode.h
 *
 *  Created on: 28/nov/2012
 *      Author: AlexZ
 */

#ifndef BSTREENODE_H_
#define BSTREENODE_H_

template<class I, class K>
class BSTreeNode
{
public:
	typedef I item;
	typedef K key;
	typedef BSTreeNode* bst_node;

	// default constructor
	BSTreeNode( const item& lab = item(), const key& k = key(), bst_node p = 0, bst_node l = 0, bst_node r = 0 )
				: label(lab), item_key(k), parent(p), left(l), right(r)
	{}

	// default copy-constructor
	BSTreeNode( const BSTreeNode& copy_node )
	{
		*this = copy_node;

	}
	// default constructor ( declare it empty in order to protect it )
	~BSTreeNode(){}

	// operator =
	BSTreeNode& operator=( const BSTreeNode& copy_node )
	{
		if( &copy_node != this )
		{
			label = copy_node.label;
			item_key = copy_node.item_key;
			left = copy_node.left;
			right = copy_node.right;
		}

		return *this;
	}

	// get operator
	item get_label() const { return label; }
	key get_key() const { return item_key; }
	bst_node get_left() const { return left; }
	bst_node get_right() const { return right; }
	bst_node get_parent() const { return parent; }


	// set operator

	void set_label( const item& _item ) { label = _item; }
	void set_left( bst_node _left ) { left = _left; }
	void set_right( bst_node _right ) { right = _right; }
	void set_item_key( const key& k ) { item_key = k; }
	void set_parent( bst_node p ) { parent = p; }

private:
	item label;
	key item_key;
	bst_node parent;
	bst_node left;
	bst_node right;


};

#endif /* BSTREENODE_H_ */
