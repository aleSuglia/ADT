/*
 * QueueP.h
 *
 *  Created on: 01/dic/2012
 *      Author: AlexZ
 */

#ifndef QUEUEP_H_
#define QUEUEP_H_

#include "PriorityQueue.h"
#include "BinTreePointer.h"
#include <iostream>


template<class T>
class QueueP : public PriorityQueue<T,BinTreeNode<T>* >
{
public:
	typedef typename PriorityQueue<T, BinTreeNode<T>* >::position Node;
	typedef typename PriorityQueue<T, BinTreeNode<T>* >::item item;

	QueueP()
	{
		create();

	}
	QueueP( const item& val )
	{
		create();
		tree.ins_root(BinTreeNode<T>(val));
		last = tree.root();


	}

	~QueueP()
	{
		/*
		 *  everything was done by the destructor
		 *  of the BinTreePointer class.
		*/

	}
	QueueP( const QueueP& copy_q )
	{
		*this = copy_q;
	}

	QueueP& operator=( const QueueP& copy_q )
	{
		if( &copy_q != this )
		{
			tree = copy_q.tree;
			last = copy_q.last;

		}

		return *this;

	}

	void create()
	{
		last = NULL;
	}

	bool empty() const
	{
		return ( tree.empty() );

	}

	void insert( const item& val )
	{
		// if there aren't node, create the first one.
		if( tree.empty() )
		{
			tree.ins_root();

			tree.write(tree.root(), val);

			last = tree.root();


		}
		else
		if( last == tree.root() ) // we have only the root
		{
			tree.ins_sx(tree.root());
			tree.write(tree.sx(tree.root()), val);
			last = tree.sx(tree.root()); // last inserted node.
		}
		else
		if( tree.sx(tree.parent(last)) == last ) // if the last node is a "left-node"
		{
			tree.ins_dx( tree.parent(last) );
			tree.write( tree.dx(tree.parent(last)), val);
			last = tree.dx(tree.parent(last)); // last inserted node.
		}
		else
		{
			Node iter = last;

			// goes up to the root if iter is a right node
			while( iter != tree.root() && iter == tree.dx(tree.parent(iter))  )
			{
				iter = tree.parent(last);

			}

			if( iter != tree.root() )
			{

				iter = tree.dx(tree.parent(iter)); // goes to the right sibling

			}

			// go down on the left until we found a leaf node
			while( !tree.isLeaf(iter) )
			{
				iter = tree.sx(iter);

			}

			// we Have found it. insert a new left node of it.
			tree.ins_sx(iter);
			tree.write( tree.sx(iter), val);
			last = tree.sx(iter);


		}

		fixUp();

	}

	item min() const
	{
		return tree.read(tree.root());

	}

	void deleteMin()
	{
		if( empty() )
			throw std::logic_error("QueueTree (Exception) : Empty Priority Queue.");

		if( last == tree.root() ) // we have only the root.
		{
			tree.erase(tree.root());

		}
		else
		{
			tree.write(tree.root(), tree.read(last)); // modify the label of the root.

		}

		if( !tree.empty() )
		{
			// the last node is a right node
			if (last == tree.dx(tree.parent(last)))
			{
				Node temp_last = last;
				last = tree.sx(tree.parent(last));
				tree.erase(temp_last);

			}
			else // last is a left-node.
			{
				Node iter = last;
				Node useless_node = last;

				// in this case we have to go up
				while (iter != tree.root() && iter == tree.sx(tree.parent(iter)))
				{
					iter = tree.parent(iter);
				}

				if (iter != tree.root())
				{
					iter = tree.sx(tree.parent(iter)); // goes to its left sibling.

				}

				// goes down until we found a leaf node.
				while (!tree.dx_empty(iter) && !tree.isLeaf(iter))
				{

					iter = tree.dx(iter);

				}

				// we finally found the new last node.
				last = iter;
				tree.erase(useless_node); // remove the old last node.
			}

			fixDown(tree.root());
		}
	}

	item max() const
	{
		return tree.read(tree.root());

	}


private:
	Node last; // represents the last leaf of the priority queue.
	BinTreePointer<item> tree;


	void fixUp()
	{
		// take the last node and go up with it.
		Node iter = last;

		while( iter != tree.root() && tree.read(iter) < tree.read(tree.parent(iter)) )
		{
			_swap( iter, tree.parent(iter) );
			if( iter != tree.root() )
				iter = tree.parent(iter);


		}

	}
	void fixDown( Node n )
	{

		bool flag = true;

		Node iter;

		// now we have to found the new last node.
		while( !tree.isLeaf(n) && flag )
		{
			// move to the left child.
			iter = tree.sx(n);

			if( iter != last && !tree.dx_empty(n) && tree.read(iter) > tree.read(tree.dx(n) ) )
				iter = tree.dx(n); // move to the right, it's the minimum

			// if the child has a priority lower than the current node, swap them.
			if( (flag = tree.read(n) > tree.read(iter) ) )
			{
				_swap(n, iter);
				n = iter;
			}

		}


	}

	void _swap( Node n1, Node n2 )
	{
		item temp = tree.read(n1);
		tree.write(n1, tree.read(n2));
		tree.write(n2, temp);


	}

};

//template<class T>
//std::ostream& operator<< ( std::ostream& os, const QueueP<T>& q )
//{
//	os << q.tree << std::endl;
//
//	return os;
//
//}

#endif /* QUEUEP_H_ */
