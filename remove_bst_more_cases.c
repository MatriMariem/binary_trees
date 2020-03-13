#include "binary_trees.h"

/**
 * find_inorder_successor - finds the successor of a node
 * using the inorder traversal
 * @root: root of the tree
 * @node: the node
 * Return: a pointer to the inorder successor
 */
bst_t *find_inorder_successor(bst_t *root, bst_t *node)
{
	bst_t *successor;

	if (!node->right)
	{
		successor = NULL;
		while (root != node)
		{
			if (node->n < root->n)
			{
			successor = root;
			root = root->left;
			}
			else
				root = root->right;
		}
		return (successor);
	}
	else
	{
		node = node->right;
		while (node->left)
		{
			node = node->left;
		}
		return (node);
	}
}

/**
 * bst_remove - a function that removes a node from a Binary Search Tree
 * @root: a pointer to the root node of the tree
 * @value: the value to remove in the tree
 * Return: a pointer to the root
 */
bst_t *bst_remove(bst_t *root, int value)
{
	bst_t *node, *successor;

	if (!root)
		return (NULL);
	node = (bst_t *)root;
	while (node)
	{
		if (node->n == value)
		{
			successor = find_inorder_successor(root, node);
			if (!successor && !node->parent)
			{
				root = NULL;
			}
			else if (!successor)
			{
				if (node == node->parent->right)
					node->parent->right = NULL;
				else
					(node->parent->left) = NULL;
			}
			else if (successor)
			{
				if (successor->parent)
					successor->parent->left = successor->right;
				if (successor->right)
					successor->right->parent = successor->parent;
				if (node->right)
					node->right->parent = successor;
				if (node->left)
					node->left->parent = successor;
				successor->right = node->right;
				successor->left = node->left;
				successor->parent = node->parent;
				if (node == root)
				{
					root = successor;
				}
				else
				{
					if (node->parent && node == node->parent->left)
						node->parent->left = successor;
					else if (node->parent)
						node->parent->right = successor;
				}
			}
			free(node);
			return (root);
		}
		else if (node->n > value)
			node = node->left;
		else if (node->n < value)
			node = node->right;
	}
	return (root);
}
