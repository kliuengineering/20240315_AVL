#include <iostream>


template <class T>
class AVL
{
private:

	// variables / structures section
	// do i need to add more variables?
	typedef struct Node
	{
		Node* left;
		Node* right;
		T data;
		int height;

		Node(const T& data) : left(nullptr), right(nullptr), data(data), height(1) {}
	}Node;

	// root node here
	Node* root;

	// method section

	int get_height(Node* node)
	{
		if (!node) return 0;
		else return node->height;
	}

	int get_balance_factor(Node *node)
	{
		if (!node) return 0;
		else return get_height(node->left) - get_height(node->right);
	}

	void update_height(Node *node)
	{
		node->height = 1 + std::max(get_height(node->left), get_height(node->right));
	}

	void left_rotate(Node *x)
	{
		Node* y = x->right;
		Node* temp = y->left;

		// rotation
		y->left = x;
		x->right = temp;

		// update height
		update_height(x);
		update_height(y);

		return y;
	}

	void right_rotate(Node *y)
	{
		Node* x = y->left;
		Node* temp = x->right;

		// rotation
		x->right = y;
		y->left = temp;

		// update height
		update_height(x);
		update_height(y);

		return x;
	}

	void left_right_rotate(Node* node)
	{
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}

	void right_left_rotate(Node *node)
	{
		node->right = right_rotate(node);
		return left_rotate(node);
	}

	// utility method - insertion
	Node* insert(Node* node, const T& data)
	{
		// 1. regular BST insertion
		if (!node) 
			return new Node(data);

		if (data < node->data)
			node->left = insert(node->left, data);			// +1 level deeper to the left

		else if (data > node->data)
			node->right = insert(node->right, data);		// +1 level deeper to the right

		else
			return node;									// -1 level 

		// 2. update height of parent
		update_height(node);

		// 3. get the balance factor
		int balance = get_balance_factor(node);


		// 4. below are 4 cases to deal with unbalanced node

		// left left case
		if ((balance > 1) && (data < (node->left->data)))
			return right_rotate(node);

		// right right case
		if ((balance < -1) && (data > node->right->data))
			return left_rotate(node);

		// left right case
		if ((balance > 1) && (data > node->left->data))
			return left_right_rotate(node);

		// right left case
		if ((balance < -1) && (data < node->right->data))
			return right_left_rotate(node);

		// default case -> unchange
		return node;
	}

public:

	// default constructor
	AVL() : root(nullptr) {}

	void insert_data(const T& data)
	{
		root = insert(root, data);
	}

	void delete_data()
	{

	}

	void search_data()
	{

	}

	void print_in_order()
	{

	}

};

int main(void)
{

	return 0;
}