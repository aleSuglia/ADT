/*
 * AVLTree.h
 *
 *  Created on: 08/dic/2012
 *      Author: AlexZ
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "BST.h"
#include "BSTreeNode.h"

typedef enum
{
	NO_ROT = -1, LEFT_ROT, RIGHT_ROT, RIGHT_LEFT_ROT, LEFT_RIGHT_ROT
} direction;

template<class T>
class AVLTree: public BST<T, BSTreeNode<T, T>*>
{
public:
	typedef typename BST<T, BSTreeNode<T, T>*>::value_type item;
	typedef typename BST<T, BSTreeNode<T, T>*>::Node Node;

	AVLTree()
	{
		create();

	}

	AVLTree(const AVLTree& bs_copy)
	{
		*this = bs_copy;

	}

	AVLTree& operator=(const AVLTree& copy_tree)
	{
		if (&copy_tree != this)
		{
			create();

			if (!copy_tree.empty())
			{
				ins_root();

				this->insSubTree(root(), copy_tree, copy_tree.root());
			}
		}

		return *this;

	}

	~AVLTree()
	{
		destroy(root());

	}
	bool empty() const
	{
		return (tree_root == 0);
	}
	Node root() const
	{
		return tree_root;
	}
	item read(Node n) const
	{
		if (n == 0)
			throw std::logic_error(
					"AVL Tree (Exception ) : Invalid node passed to the function.");
		else
			return n->get_label();

	}

	void write(Node n, const item& val)
	{
		if (n == 0)
			throw std::logic_error(
					"AVL Tree (Exception) : Invalid node passed to the function. ");
		else
		{
			n->set_item_key(val);
			n->set_label(val);
		}
	}

	// insert a node in a correct way which respect the rules of the BST.
	void insert(const item& v)
	{
		insert(root(), v);
		// After we have inserted the new node, try to
		// balance the tree.
		/*
		 * 1st case : unbalanced in the right subtree.
		 * 2nd case : unbalanced in the left subtree.
		 * 3rd case : unbalanced in the left tree
		 * 4th case : unbalanced in the right tree
		 *
		 * */
		direction dir_rot = NO_ROT;
		Node unb_node = checkBalance(get_node(v), dir_rot);

		if (unb_node != NULL)
		{
			// if the new node is in the right subtree of the left subtree
			// of the unbalanced node
			// Right-Left CASE

			if (!dx_empty(unb_node) && !sx_empty(dx(unb_node)))
				if (dir_rot == LEFT_ROT && is_member(dx(unb_node), v)
						&& is_member(sx(dx(unb_node)), v))
					dir_rot = RIGHT_LEFT_ROT;

			// if the new node is in the left subtree of the right subtree
			// of the unbalanced node
			// Left-Right CASE
			if (!sx_empty(unb_node) && !dx_empty(sx(unb_node)))
				if (dir_rot == RIGHT_ROT && is_member(sx(unb_node), v)
						&& is_member(dx(sx(unb_node)), v))
					dir_rot = LEFT_RIGHT_ROT;

			switch (dir_rot)
			{
			// single left rotation needed.
			case LEFT_ROT:
				leftRotation(unb_node);
				break;
				// single right rotation needed.
			case RIGHT_ROT:
				rightRotation(unb_node);
				break;
			case LEFT_RIGHT_ROT:
				leftRotation(sx(unb_node));
				rightRotation(unb_node);
				break;
			case RIGHT_LEFT_ROT:
				rightRotation(dx(unb_node));
				leftRotation(unb_node);
				break;
			case NO_ROT: // no rotation needed, nothing to be done.
				break;
			}
		}

	}

	void insert(Node n, const item& v)
	{
		if (empty())
		{

			ins_root(new BSTreeNode<T, T>(v));

		}
		else if (is_member(tree_root, v))
			throw std::logic_error(
					"AVL Tree( Exception ) : The element is present.");
		else
		{
			if (v < read(n) && !sx_empty(n))
			{
				insert(sx(n), v);
			}
			else if (v < read(n) && sx_empty(n))
			{
				ins_sx(n);
				write(sx(n), v);
			}
			if (v > read(n) && !dx_empty(n))
			{

				insert(dx(n), v);

			}
			else if (v > read(n) && dx_empty(n))
			{
				ins_dx(n);
				write(dx(n), v);
			}

		}

	}

	void erase(const item& val)
	{
		erase(get_node(val));

	}
	void erase(Node n)
	{

		if (empty())
		{
			throw std::logic_error("AVL Tree ( Exception ) : Tree is empty. ");

		}
		else if (!is_member(tree_root, n->get_label()))
			throw std::logic_error(
					"AVL Tree ( Exception ) : The element doesn't belong to the tree.");
		else // if this two condition are not verified, we can remove the node.
		{
			// if the node is a leaf
			if (sx_empty(n) && dx_empty(n))
			{
				if (n != tree_root)
				{
					if (parent(n)->get_right() == n)
						parent(n)->set_right(0);
					else
						parent(n)->set_left(0);
					delete n;
					n = 0;

				}
				else
				{
					delete tree_root;
					tree_root = 0;

				}

			}
			else // I have to remove the node and then fix the parent and its right child.
			if (sx_empty(n) && !dx_empty(n))
			{
				if (n != tree_root)
				{
					Node p = parent(n), r_child = dx(n); // save the parent.

					// if n is on the right.
					if (p->get_right() == n)
						p->set_right(r_child); // the new right child of the parent of n is the right-child of n
					else
						p->set_left(r_child);

					r_child->set_parent(p); // the parent of the right child of n is the parent of n.
				}
				else
				{
					tree_root = dx(n);

				}

				delete n;
				n = 0;

			}
			else if (!sx_empty(n) && dx_empty(n))
			{
				if (n != tree_root)
				{
					Node p = parent(n), l_child = sx(n);

					if (p->get_right() == n)
						p->set_right(l_child);
					else
						p->set_left(l_child);

					l_child->set_parent(p);

				}
				else
					tree_root = sx(n);

				delete n;
				n = 0;

			}
			else // the node that will be removed has got two child.
			{
				Node min = get_min(dx(n));

				// it is not a leaf node, so we have to fix correctly this case.
				if (!this->isLeaf(min) && parent(min)->get_right() == min)
					parent(min)->set_right(dx(min));
				else
				{

					if (parent(min)->get_right() == min)
						parent(min)->set_right(0);
					else
						parent(min)->set_left(0);
				}
				write(n, read(min)); // change the label of the n node
				delete min;
				min = 0;

			}
		}

	}

	Node get_min() const
	{
		return get_min(root());

	}
	Node get_max() const
	{
		return get_max(root());

	}

	bool is_member(Node curr_node, const item& n)
	{
		if (empty())
			return false;
		else
		{
			if (read(curr_node) == n)
				return true;
			if (!sx_empty(curr_node) && n < read(curr_node))
				return is_member(sx(curr_node), n);
			if (!dx_empty(curr_node) && n > read(curr_node))
				return is_member(dx(curr_node), n);

		}

		return false;

	}

private:
	Node get_max(Node n) const
	{

		if (empty())
		{
			throw std::logic_error("AVL Tree ( Exception ) : Empty tree. ");

		}
		else
		{

			// if we have only the root.
			if (sx_empty(n) && dx_empty(n))
				return n;
			else // if we haven't right child.
			if (dx_empty(n))
				return n;

			// when we have a balanced tree
			// we can go through the right
			// subtree looking for the max value.
			return get_max(dx(n));

		}

	}
	Node get_min(Node n) const
	{
		if (empty())
		{
			throw std::logic_error("AVL Tree ( Exception ) : Empty tree. ");

		}
		else
		{
			if (sx_empty(n) && dx_empty(n))
			{
				return n;

			}
			else if (sx_empty(n))
				return n;

			return get_min(sx(n));

		}

	}

	Node get_node(const item& val)
	{
		if (!is_member(root(), val))
			std::logic_error(
					"AVL Tree ( Exception ) : It's not present the value searched.");

		return get_node(val, root());

	}

	Node get_node(const item& val, Node n)
	{
		if (read(n) == val)
			return n;

		// go to the right
		if (val > read(n) && !dx_empty(n))
			return get_node(val, dx(n));
		else // go to the left
		if (val < read(n) && !sx_empty(n))
			return get_node(val, sx(n));
		else
			return 0;

	}

	Node parent(Node n) const
	{
		if (n == root())
			throw std::logic_error(
					"AVL Tree ( Exception ) : You cannot retrieve the root's father.");
		else
		{
			return n->get_parent();

		}
	}

	void create()
	{
		tree_root = 0;
	}

	Node sx(Node n) const
	{
		if (sx_empty(n))
			throw std::logic_error(
					"AVL Tree (Exception ) : Empty left child. ");
		else
			return n->get_left();
	}

	Node dx(Node n) const
	{
		if (dx_empty(n))
			throw std::logic_error(
					"AVL Tree (Exception ) : Empty right child. ");
		else
			return n->get_right();

	}
	bool sx_empty(Node n) const
	{
		return (n->get_left() == 0);
	}
	bool dx_empty(Node n) const
	{
		return (n->get_right() == 0);
	}

	void ins_sx(Node n)
	{
		if (n == 0)
			throw std::logic_error("AVL Tree (Exception) : Invalid node.");
		else
		{
			Node new_node = new BSTreeNode<T, T>(item(), item(), n);
			n->set_left(new_node);

		}

	}

	void ins_dx(Node n)
	{
		if (n == 0)
			throw std::logic_error("AVL Tree (Exception) : Invalid node.");
		else
		{
			Node new_node = new BSTreeNode<T, T>(item(), item(), n);
			n->set_right(new_node);

		}

	}

	void ins_root(Node n = 0)
	{

		if (tree_root != 0)
			throw std::logic_error("AVL Tree (Exception) : Root exists.");

		// if I've passed a null node, allocate space for the root and initialize it.

		if (n == 0)
		{
			tree_root = new BSTreeNode<T, T>(item(), item());

		}
		else // in this case, copy the node n in the root.
		{
			tree_root = new BSTreeNode<T, T>(n->get_label(), n->get_key());

		}

	}
	void destroy(Node n)
	{
		if (!empty())
		{
			if (!sx_empty(n))
				destroy(sx(n));
			if (!dx_empty(n))
				destroy(dx(n));

			// effectively deallocate and destroy the
			// memory location.
			delete n;
			n = 0;
		}

	}

	/* Member declaration */
	Node tree_root; // root of the AVL

private:
	// private methods

	/**
	 * \brief Makes a left rotation of the subtree
	 * with root in x
	 *
	 * */
	void leftRotation(Node z)
	{
		Node y = dx(z), x = ( dx_empty(y) ) ? 0 : dx(y);



		if (z != root())
		{
			y->set_parent(parent(z));
			// if z is a left child.
			if( z == sx(parent(z)) )
				parent(z)->set_left(y);
			else
				parent(z)->set_right(y);
		}
		else
			y->set_parent(0);

		if (!sx_empty(y))
			z->set_right(sx(y));
		else
			z->set_right(0);

		// y is the new root
		y->set_left(z);
		y->set_right(x);

		// x and z are y's child
		if( x != NULL ) // couldn't be present.
			x->set_parent(y);
		z->set_parent(y);
		if (z == tree_root)
			tree_root = y;

	}

	/**
	 * \brief Makes a right rotation of the subtree
	 * with root in x
	 *
	 * */

	void rightRotation(Node z)
	{
		Node y = sx(z), x = ( sx_empty(y) ) ? 0 : sx(y);


		if (z != root())
		{
			y->set_parent(parent(z));
			if( z == dx(parent(z)) )
				parent(z)->set_right(y);
			else
				parent(z)->set_left(y);
		}
		else
			y->set_parent(0);

		// y's right child became the new left child of z.
		if (!dx_empty(y))
			z->set_left(dx(y));
		else
			z->set_left(0);

		// y is the new root.
		y->set_right(z);
		y->set_left(x);

		// x and y are their child.
		if( x != NULL )
			x->set_parent(y);
		z->set_parent(y);
		if (z == tree_root)
			tree_root = y;

	}

	// controls if an AVL Tree is balanced or not
	Node checkBalance(Node n, direction& d)
	{
		Node curr_node = n;
		int r_height = 0, l_height = 0, balance = 0, curr_balance = 0;
		bool unbalanced = false, end = false;
		Node unbalanced_node;

		while (!end)
		{
			l_height = (sx_empty(curr_node)) ? 0 : this->size(sx(curr_node));
			r_height = (dx_empty(curr_node)) ? 0 : this->size(dx(curr_node));
			curr_balance = r_height - l_height;

			// if some node has illegal balance factor.
			if ((curr_balance) >= 2 || (curr_balance) <= -2)
			{
				// both are positive numbers and the current balance is greater than the old.
				if ((curr_balance > 0 && balance >= 0)
						&& (curr_balance > balance))
				{
					unbalanced = true;
					unbalanced_node = curr_node;
					d = LEFT_ROT;
					balance = curr_balance;
				}
				else if ((curr_balance < 0 && balance <= 0)
						&& (curr_balance < balance))
				{
					unbalanced = true;
					unbalanced_node = curr_node;
					d = RIGHT_ROT;
					balance = curr_balance;
				}

			}
			if (curr_node != root())
				curr_node = parent(curr_node);
			else
				end = true;

		}

		return (unbalanced) ? unbalanced_node : 0;

	}

};

#endif /* AVLTREE_H_ */
