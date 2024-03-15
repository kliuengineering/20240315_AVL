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

	// method section

	int get_height()
	{

	}

	int get_balance_factor()
	{

	}

	void update_height()
	{

	}

	void left_rotate()
	{

	}

	void left_right_rotate()
	{

	}

	void right_rotate()
	{

	}

	void right_left_rotate()
	{

	}

public:

	void insert_data()
	{

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