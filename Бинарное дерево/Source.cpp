#include <iostream>

using namespace std;

struct Node
{
	int  key;
	Node* parent{nullptr};
	Node* left{ nullptr };
	Node* right{ nullptr };
};

class BinaryTree
{

	Node* root;

public:
	BinaryTree() :root{nullptr}{}

	~BinaryTree()
	{
		Delete(root);
	}

	void Add(int value)
	{
		Node* newnode = new Node;
		newnode->key = value;

		Node* newparent{nullptr};
		Node* current{root};

		while (current)
		{
			newparent = current;

			if (newnode->key < current->key)
				current = current->left;
			else
				current = current->right;
		}

		newnode->parent = newparent;

		if (!newparent)
			root = newnode;
		else
		{
			if (newnode->key < newparent->key)
				newparent->left = newnode;
			else
				newparent->right = newnode;
		}

	}

	void Print()
	{
		Print(root);
	}

	void Print(Node* current)                   // Delete 
	{
		if (current)                              
		{
			Print(current->left);                   //1
			cout << current->key << " ";             
			Print(current->right);                    //2
		}                                          // delete current
	}

	Node* Search(int value)
	{
		Node* current{ root };

		while (current && current->key != value)
		{
			if ( current->key > value)
				current = current->left;
			else
				current = current->right;
		}

		return current;
	}

	Node* Min()
	{
		return Min(root);
	}

	Node* Min(Node* current)
	{
		while (current->left)
			current = current->left;
		return current;
	}

	Node* Max()
	{
		return Max(root);
	}

	Node* Max(Node* current)
	{
		while (current->right)
			current = current->right;
		return current;
	}

	Node* Next(Node* current) 
	{
		if (current->right) return Min(current->right);

		Node* tempnode{ current->parent };
		while (tempnode && tempnode->right == current)
		{
			current = tempnode;
			tempnode = tempnode->parent;
		}

		return tempnode;
	}

	Node* Prev(Node* current)
	{
		if (current->left) return Max(current->left);

		Node* tempnode{ current->parent };

		while (tempnode && tempnode->left == current)
		{
			current = tempnode;
			tempnode = tempnode->parent;
		}

		return tempnode;
	}

	void Ddelete()
	{
		Delete(root);
	}

	void Delete(Node* current)
	{
		if (current)
		{
			Delete(current->left);
			Delete(current->right);

			if (current->parent->left == current)
				current->parent->left = nullptr;
			else
				current->parent->right = nullptr;

			delete current;
		}
	}

	void Remove(Node* current)
	{
		Node* nextnode;
		if (!current->left || !current->right)
			nextnode = current;
		else
			nextnode = Next(current);
		Node* tempnode;

		if (nextnode->left)
			tempnode = nextnode->left;
		else
			tempnode = nextnode->right;

		if (tempnode)
			tempnode->parent = nextnode->parent;
		if (!nextnode->parent)
			root = tempnode;
		else
		{
			if (nextnode == nextnode->parent->left)
				nextnode->parent->left = tempnode;
			else
				nextnode->parent->right = tempnode;
		}
		
		if (current != nextnode)
			current->key = nextnode->key;

		delete nextnode;

	}

};

int main()
{
	BinaryTree bintree;
	bintree.Add(25);
	bintree.Add(65);
	bintree.Add(45);
	bintree.Add(10);
	bintree.Add(15);
	bintree.Add(2);
	bintree.Add(20);
	bintree.Add(75);
	bintree.Add(3);
	bintree.Add(27);
	bintree.Add(17);

	bintree.Print();

	Node* p;

	cout << endl;

	if (p = bintree.Search(45))
		cout << p->key;
	else
		cout << "Not faund" << "\n";
	cout << endl;

	bintree.Print(p);

	cout << endl;

	cout << "min = " << bintree.Min()->key << " max = " << bintree.Max()->key;

	cout << endl;

	cout << bintree.Next(bintree.Search(20))->key;

	cout << endl;

	cout << bintree.Prev(bintree.Search(20))->key;

	return 0;
}