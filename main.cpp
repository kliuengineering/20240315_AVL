#include <iostream>
#include <vector>
#include <iterator>

template <class T>
class AVL
{
private:

	/*** variables / structures section ***/
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





	/*** method section begins ***/

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


	Node* left_rotate(Node *x)
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


	Node* right_rotate(Node *y)
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


	Node* left_right_rotate(Node* node)
	{
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}


	Node* right_left_rotate(Node *node)
	{
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}


	// utility - insertion
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


	// overloaded in-rder-print
	void print_in_order(Node* node)
	{
		if (node)
		{
			print_in_order(node->left);

			std::cout << node->data << "    ";

			print_in_order(node->right);
		}
	}


	// utulity - find minimum value node, use case: delete node
	Node* min_value_node(Node* node)
	{
		Node* current = node;

		while (current && current->left)
		{
			current = current->left;
		}

		return current;
	}


	// utility - delete node
	Node* delete_node(Node* node, const T& data)
	{
		if (!node) return node;

		// 1. perform BST delete
		if (data < node->data)
			node->left = delete_node(node->left, data);
		else if (data > node->data)
			node->right = delete_node(node->right, data);
		
		else
		{
			Node* temp;

			// case -> 0 or 1 child
			if (!node->left || !node->right)
			{
				temp = node->left ? node->left : node->right;
				
				// case -> no child
				if (temp == nullptr)
				{
					temp = node;
					node = nullptr;
				}

				// case -> 1 child
				else
				{
					Node *delete_node = node;
					node = temp;
					delete delete_node;
					return node;
					
				}

				delete temp;
			}

			// case -> with 2 children
			else
			{
				temp = min_value_node(node->right);
				node->data = temp->data;
				node->right = delete_node(node->right, temp->data);
			}
		}

		// return if there is only 1 node left
		if (!node) return node;


		// 2. update the height of the current node
		update_height(node);


		// 3. check for balancing
		int balance = get_balance_factor(node);

		// left left case
		if ( (balance > 1) && (get_balance_factor(node->left) >=0) )
			return right_rotate(node);

		// right right case
		if ( (balance < -1) && (get_balance_factor(node->right) <= 0) )
			return left_rotate(node);

		// left right case
		if ((balance > 1) && (get_balance_factor(node->left) < 0) )
		{
			node->left = left_rotate(node->left);
			return right_rotate(node);
		}

		// right left case
		if ((balance < -1) && (get_balance_factor(node->right) > 0) )
		{
			node->right = right_rotate(node->right);
			return left_rotate(node);
		}

		
		return node;
	}


	// utility - delete tree
	void delete_tree(Node* node)
	{
		if (node)
		{
			delete_tree(node->left);
			delete_tree(node->right);
			delete node;
		}
	}

	// utility - search
	Node* search_data(Node* node, const T& data)
	{
		Node* current = node;

		while (current)
		{
			if (data == current->data)
			{
				return current;
			}
			else if (data < current->data)
			{
				current = current->left;
			}
			else
				current = current->right;
		}

		return nullptr;
	}


	// Helper method to search and keep track of the parent
	void search_and_print_details(Node* node, const T& data, Node* parent) {
		if (!node) {
			std::cout << "Data not found.\n";
			return;
		}

		if (data == node->data) {
			std::cout << "Node Data: " << node->data << "\n";
			std::cout << "Node Height: " << node->height << "\n";
			if (parent) {
				std::cout << "Parent Node Data: " << parent->data << "\n";
			}
			else {
				std::cout << "This node is the root and has no parent.\n";
			}
		}
		else if (data < node->data) {
			search_and_print_details(node->left, data, node); // Pass current node as parent
		}
		else {
			search_and_print_details(node->right, data, node); // Pass current node as parent
		}
	}





public:

	// default constructor
	AVL() : root(nullptr) {}

	// destructor
	~AVL()
	{
		delete_tree(root);
	}

	void insert_data(const T& data)
	{
		root = insert(root, data);
	}

	void delete_data(const T& data)
	{
		root = delete_node(root, data);
	}

	bool search_data(const T& data)
	{
		Node *search_result = search_data(root, data);
		
		if (search_result)
			return true;
		else
			return false;

	}


	// New method to initiate search and print details
	void search_and_print_details(const T& data) {
		Node* parent = nullptr;
		search_and_print_details(root, data, parent);
	}


	// in order print
	void print_in_order(void)
	{
		print_in_order(root);
	}

};


void MakeStringTree(AVL<std::string> &my_tree)
{
	std::vector<std::string> my_vector = { "Milton", "Ajax", "Clarington", "Brock", "Oshawa", "Pickering", "Uxbridge", "Whitby", "Burlington", "Oakville", "Brampton","Caledon","Mississauga","Aurora","Georgina" };
	
	for (std::vector<std::string>::iterator itr = my_vector.begin(); itr != my_vector.end(); itr++)
	{
		my_tree.insert_data(*itr);
	}
}


void MakeIntTree(AVL<int>& my_tree)
{
	my_tree.insert_data(95);
	my_tree.insert_data(301);
	my_tree.insert_data(501);
	my_tree.insert_data(801);
	my_tree.insert_data(90);
	my_tree.insert_data(70);
	my_tree.insert_data(80);
	my_tree.insert_data(25);
	my_tree.insert_data(67);
	my_tree.insert_data(89);
	my_tree.insert_data(11);
}


void MakeFloatTree(AVL<float>& my_tree)
{
	my_tree.insert_data(84.8);
	my_tree.insert_data(103.5);
	my_tree.insert_data(67.8);
	my_tree.insert_data(90.3);
	my_tree.insert_data(23.5);
	my_tree.insert_data(67.1);
	my_tree.insert_data(44.5);
	my_tree.insert_data(89.2);
	my_tree.insert_data(100.5);
	my_tree.insert_data(300.2);
}


int main(void)
{
	AVL<std::string> string_tree;
	AVL<int> int_tree;
	AVL<float> float_tree;


	MakeStringTree(string_tree);
	MakeIntTree(int_tree);
	MakeFloatTree(float_tree);


	std::cout << "The original string tree is: \n";
	string_tree.print_in_order(); puts(""); puts("");
	std::cout << "Now let's add \"Stouffville\" to the tree... \n";
	string_tree.insert_data("Stouffville");
	std::cout << "The new string tree is: \n";
	string_tree.print_in_order(); puts(""); puts("");


	std::cout << "The original int tree is: \n";
	int_tree.print_in_order(); puts(""); puts("");
	std::cout << "Now let's add 506 to the tree... \n";
	int_tree.insert_data(506);
	std::cout << "The new int tree is: \n";
	int_tree.print_in_order(); puts(""); puts("");


	std::cout << "The original float tree is: \n";
	float_tree.print_in_order(); puts(""); puts("");
	std::cout << "Now let's add 88.5 to the tree... \n";
	float_tree.insert_data(88.5);
	std::cout << "The new float tree is: \n";
	float_tree.print_in_order(); puts(""); puts("");


	std::cout << "The original string tree is: \n";
	string_tree.print_in_order(); puts(""); puts("");
	std::cout << "Now let's delete \"Caledon\" from the tree... \n";
	string_tree.delete_data("Caledon");
	std::cout << "The new string tree is: \n";
	string_tree.print_in_order(); puts(""); puts("");


	std::cout << "The original int tree is: \n";
	int_tree.print_in_order(); puts(""); puts("");
	std::cout << "Now let's delete 89 from the tree... \n";
	int_tree.delete_data(89);
	std::cout << "The new int tree is: \n";
	int_tree.print_in_order(); puts(""); puts("");


	std::cout << "The original float tree is: \n";
	float_tree.print_in_order(); puts(""); puts("");
	std::cout << "Now let's delete 23.5 from the tree... \n";
	float_tree.delete_data(23.5);
	std::cout << "The new float tree is: \n";
	float_tree.print_in_order(); puts(""); puts("");


	std::cout << "Let's do a search for Whitby...\n";
	string_tree.search_and_print_details("Whitby"); puts("");
	
	
	std::cout << "Let's do a search for 11...\n";
	int_tree.search_and_print_details(11); puts("");


	std::cout << "Let's do a search for 90.3...\n";
	float_tree.search_and_print_details(90.3); puts("");


	return 0;
}