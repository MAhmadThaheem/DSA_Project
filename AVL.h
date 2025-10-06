#pragma once
#include"User.h"
#include<ctime>
#include<vector>
#include<algorithm>
struct myNode
{
	Node* data;
	myNode* left;
	myNode* right;
	int height;
	myNode()
	{
		left = right = NULL;
		height = 0;
	}
};
class AVL
{
public:
	myNode* root;
	AVL()
	{
		root = NULL;
	}
	int getHeight(myNode*& root)
	{
		if (!root) return -1;
		return root->height;
	}
	bool checkBalanceOrNot(myNode*& root)		//check balance
	{
		if (getHeight(root->left) - getHeight(root->right) > 1 || getHeight(root->left) - getHeight(root->right) < -1)
		{
			return true;
		}
		return false;
	}
	myNode* leftRotation(myNode*& root)
	{
		myNode* child = root->right;
		myNode* childLeft = child->left;
		child->left = root;
		root->right = childLeft;
		//updating height
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
		child->height = 1 + max(getHeight(child->left), getHeight(child->right));
		return child;
	}
	myNode* rightRotation(myNode*& root)
	{
		myNode* child = root->left;
		myNode* childRight = child->right;
		child->right = root;
		root->left = childRight;
		//updating height
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
		child->height = 1 + max(getHeight(child->left), getHeight(child->right));
		return child;
	}
	myNode* insertB(myNode*& root, Node*& newUser)
	{
		if (!root)
		{
			root = new myNode;
			root->data = newUser;
			return root;
		}
		else if (newUser->name < root->data->name)
		{
			root->left = insertB(root->left, newUser);
		}
		else if (root->data->name < newUser->name)
		{
			root->right = insertB(root->right, newUser);
		}
		//setting height
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
		//checking balance factor
		int balance_factor = getHeight(root->left) - getHeight(root->right);
		if (checkBalanceOrNot(root))
		{
			//left left case
			if (balance_factor > 1 && newUser->name < root->left->data->name)
			{
				return rightRotation(root);
			}
			//right right
			else if (balance_factor < -1 && root->right->data->name < newUser->name)
			{
				return leftRotation(root);
			}
			//left right
			else if (balance_factor > 1 && newUser->name > root->left->data->name)
			{
				root->left = leftRotation(root->left);
				return rightRotation(root);
			}
			//right left case 
			else if (balance_factor < -1 && newUser->name < root->right->data->name)
			{
				root->right = rightRotation(root->right);
				return leftRotation(root);
			}
		}
		else
		{
			return root;
		}
        return root;
	}
	void searchNode(myNode *&root, Node*&temp, string name)
	{
		if (!root)
		{
			return;
		}
		if (root->data->name > name)
		{
			searchNode(root->left, temp, name);
			return;
		}
		else if (root->data->name < name)
		{
			searchNode(root->right, temp, name);
			return;
		}
		else
		{
			temp = root->data;
			return;
		}
	}
	myNode* delTree(myNode* root)
	{
		if (!root)	return NULL;
		root->left = delTree(root->left);
		root->right = delTree(root->right);
		delete root;
		root = NULL;
		return root;
	}
	~AVL()
	{
		root = delTree(root);
	}
};
