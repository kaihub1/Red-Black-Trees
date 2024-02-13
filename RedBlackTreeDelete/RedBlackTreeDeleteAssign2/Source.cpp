#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>


using namespace std;


struct Node
{
	int value = 0;
	char color = 'r';
	Node* left = NULL;
	Node* right = NULL;

};


class RnBTree
{

private:

	int redcount = 0;
	bool doubleblack = false;

	void Addrec(int value, Node*& trav)
	{

		if (trav == NULL)
		{
			trav = new Node;
			redcount = 1;
			trav->value = value;
			trav->color = 'r';
		}
		else
		{
			if (trav->value > value) // left
			{
				Addrec(value, trav->left);
				if (redcount == 2)
				{
					if (trav->right && trav->right->color == 'r')
					{
						trav->color = 'r';
						trav->left->color = 'b';
						trav->right->color = 'b';
						redcount = 1;
					}
					else
					{
						if (trav->left->left && trav->left->left->color == 'r')
						{
							RightRotate(trav);
						}
						else
						{
							LeftRotate(trav->left);
							RightRotate(trav);
						}
						trav->color = 'b'; // look into the colors for this
						trav->right->color = 'r';
						trav->left->color = 'r';
						redcount = 0;
					}
				}
				else if (redcount == 1)
				{
					if (trav->color == 'r')
					{
						redcount = 2;

					}
					else
					{
						redcount = 0;
					}
				}
				else
				{
					if (trav->color == 'r')
					{
						redcount = 1;
					}
					else
					{
						redcount = 0;
					}
				}

			}
			else // right
			{


				Addrec(value, trav->right);
				if (redcount == 2)
				{
					if (trav->left && trav->left->color == 'r') // find out the color
					{
						trav->color = 'r';
						trav->left->color = 'b';  // find out the colors
						trav->right->color = 'b';
						redcount = 1;
					}
					else
					{
						if (trav->right->right && trav->right->right->color == 'r')  // check the color
						{
							LeftRotate(trav);  // check the rotate
						}
						else
						{
							RightRotate(trav->right);  // check the rotate is it left? 
							LeftRotate(trav);
						}
						trav->color = 'b';
						trav->right->color = 'r'; // /*left*/? and check the color
						trav->left->color = 'r';
						redcount = 0;
					}
				}
				else if (redcount == 1)
				{
					if (trav->color == 'r')
					{
						redcount = 2;

					}
					else
					{
						redcount = 0;
					}
				}
				else
				{
					if (trav->color == 'r')
					{
						redcount = 1;
					}
					else
					{
						redcount = 0;
					}
				}

			}
		}
	}

	void RightRotate(Node*& trav)
	{
		Node* temp = trav;
		trav = temp->left;
		temp->left = trav->right;
		trav->right = temp;

	}

	void LeftRotate(Node*& trav)
	{
		Node* tempL = trav;
		trav = trav->right;
		tempL->right = trav->left;
		trav->left = tempL;

	}

	void clearTree(Node*& trav)
	{

		if (trav == NULL)
		{

			return;
		}
		else
		{
			clearTree(trav->left);
			clearTree(trav->right);
			delete trav;
			trav = NULL;
		}

	}

	void inorder(Node* trav)
	{

		if (trav == NULL)
		{
			return;
		}
		else
		{
			inorder(trav->left);
			cout << trav->value << " ";

			inorder(trav->right);
		}
	}

	bool search(Node* trav, int val)
	{
		if (trav == NULL)
		{
			return false;
		}
		else if (trav->value == val)
		{
			return true;
		}
		else if (trav->value > val) // we go left
		{

			search(trav->left, val);

		}
		else                             // right
		{
			search(trav->right, val);
		}

	}

	void showTree(Node* trav, int low, int high, int depth)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (trav == NULL)
		{
			return;
		}
		int mid = (low + high) / 2;

		showTree(trav->left, low, mid, depth + 1); // left side
		showTree(trav->right, mid, high, depth + 1); // right side

		GoTO(mid, depth);


		if (root->color == 'r') {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		}
		else {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}

		cout << trav->value << " (" << trav->color << ") ";

	}

	void leftcases(Node*& trav)
	{
		if(doubleblack)
		{ 
			if (case2left(trav))
			{
				adjust2left(trav);

				if (case5left(trav->left))
				{
					adjust5left(trav->left);
					adjust6left(trav->left);

				}
				else if(case4left(trav->left))
				{
					adjust4left(trav->left);
				}
				
			}
			else if (case3left(trav))
			{
				adjust3left(trav);
			}
			else if (case4left(trav))
			{
				adjust4left(trav);
			}
			else if (case5left(trav))
			{
				adjust5left(trav);

			}
			else if (case6left(trav))
			{
				adjust6left(trav);
			}
		}
		
	}

	bool case2left(Node* trav)
	{
		if (trav->color == 'b' && trav->right && trav->right->color == 'r' && (trav->right->left == NULL || trav->right->left->color == 'b') && (trav->right->right == NULL || trav->right->right->color == 'b'))
		{
			return true;
		}


		return false;


	}

	void adjust2left(Node*& trav)
	{
		LeftRotate(trav);
		trav->left->color = 'r';
		trav->color = 'b';
	}

	bool case3left(Node* trav)
	{
		if (trav->color == 'b' && trav->right && trav->right->color == 'b' && (trav->right->left == NULL || trav->right->left->color == 'b') && (trav->right->right == NULL || trav->right->right->color == 'b'))
		{
			return true;
		}
		return false;
	}

	void adjust3left(Node*& trav)
	{
		trav->right->color = 'r';
	}

	bool case4left(Node* trav)
	{
		if (trav->color == 'r' && trav->right && trav->right->color == 'b' && (trav->right->left == NULL || trav->right->left->color == 'b') && (trav->right->right == NULL || trav->right->right->color == 'b'))
		{
			return true;
		}


		return false;


	}

	void adjust4left(Node*& trav)
	{
		trav->color = trav->right->color;
		trav->right->color = 'r';

		doubleblack = false;
	}

	bool case5left(Node* trav)
	{
		if (trav->right && trav->right->color == 'b' && trav->right->left && trav->right->left->color == 'r' && (!trav->right->right || (trav->right->right && trav->right->right->color == 'b')))
		{
			return true;
		}


		return false;

	}

	void adjust5left(Node*& trav)
	{

		RightRotate(trav);
		trav->right->color = 'b';
		trav->right->right->color = 'r';

	}

	bool case6left(Node* trav)
	{
		if (trav->right && trav->right->color == 'b' && trav->right->right && trav->right->right->color == 'r')
		{
			return true;
		}


		return false;


	}

	void adjust6left(Node*& trav)
	{
		LeftRotate(trav);
		char color = trav->color;
		trav->color = trav->left->color;
		trav->left->color = color;
		trav->right->color = 'b';
		doubleblack = false;

	}


	void rightcases(Node*& trav)
	{
		if (doubleblack)
		{
			if (case2right(trav))
			{
				adjust2right(trav);

				if (case5right(trav->right))
				{
					adjust5right(trav->right);
					adjust6right(trav->right);

				}
				else if(case4right(trav->right))
				{
					adjust4right(trav->right);
				}

			}
			else if (case3right(trav))
			{
				adjust3right(trav);
			}
			else if (case4right(trav))
			{
				adjust4right(trav);
			}
			else if (case5right(trav))
			{
				adjust5right(trav);

			}
			else if (case6right(trav))
			{
				adjust6right(trav);
			}
		}

	}

	bool case2right(Node*trav)
	{
		if (trav->color == 'b' && trav->left && trav->left->color == 'r' && (trav->left->right == NULL || trav->left->right->color == 'b') && (trav->left->left == NULL || trav->left->left->color == 'b'))
		{
			return true;
		}
		
		
		return false;
		

	}

	void adjust2right(Node*&trav)
	{
		RightRotate(trav);
		trav->right->color = 'r';
		trav->color = 'b';
	}

	bool case3right(Node* trav)
	{
		if (trav->color == 'b' && trav->left && trav->left->color == 'b' && (trav->left->right == NULL || trav->left->right->color == 'b') && (trav->left->left == NULL || trav->left->left->color == 'b'))
		{
			return true;
		}
		return false;
	}

	void adjust3right(Node*& trav)
	{
		trav->left->color = 'r';
	}

	bool case4right(Node* trav)
	{
		if (trav->color == 'r' && trav->left && trav->left->color == 'b' && (trav->left->right == NULL || trav->left->right->color == 'b') && (trav->left->left == NULL || trav->left->left->color == 'b'))
		{
			return true;
		}
		
		
		return false;
		

	}

	void adjust4right(Node*& trav)
	{
		trav->color = trav->left->color;
		trav->left->color = 'r';

		doubleblack = false;
	}

	bool case5right(Node* trav)
	{
		if (trav->left && trav->left->color == 'b' && trav->left->right && trav->left->right->color == 'r' && (!trav->left->left || (trav->left->left && trav->left->left->color == 'b'))) 
		{
			return true;
		}
		
		
		return false;
		
	}

	void adjust5right(Node*& trav)
	{

		LeftRotate(trav);
		trav->left->color = 'b';
		trav->left->left->color = 'r';

	}

	bool case6right(Node* trav)
	{
		if (trav->left && trav->left->color == 'b' && trav->left->left && trav->left->left->color == 'r')
		{
			return true;
		}
		
		
		return false;
		

	}

	void adjust6right(Node*& trav)
	{
		RightRotate(trav);
		char color = trav->color;
		trav->color = trav->right->color;
		trav->right->color = color;
		trav->left->color = 'b';
		doubleblack = false;

	}


	void removeRec(Node*& trav, int deletevalue)
	{

		if (trav->value != deletevalue) // current value is not the value to delete 
		{
			if (deletevalue < trav->value) // go down to right (>) move down to left (<)
			{
				removeRec(trav->left, deletevalue);
				leftcases(trav);

			}
			else
			{
				removeRec(trav->right, deletevalue);
				rightcases(trav);
			}
		}
		else // found the value to delete 
		{
			if (trav->left)  
			{
				Node* temp = trav->left;  
				int val = temp->value;
				while (temp->right)
				{
					temp = temp->right;
					val = temp->value;
				}
				trav->value = val;
				removeRec(trav->left, val);
				leftcases(trav);
				
			}
			else if (trav->right) // there's a right node
			{

				Node* temp1 = trav->right;
				int val1 = temp1->value;
				while (temp1->left)
				{
					temp1 = temp1->left;
					val1 = temp1->value;
				}
				trav->value = val1;
				removeRec(trav->right, val1);
				rightcases(trav);

			}
			else // no children
			{
				if (trav->color == 'b') // node is black
				{
					doubleblack = true; // doubleblack = true
				}
				delete trav; //delete trav and set to NULL
				trav = nullptr;
			}

		}
	}

public:
	Node* root = NULL;

	void Addnode(int value)
	{

		Addrec(value, root);
		root->color = 'b';
		redcount = 0; // goes back to the top(reset)
	}

	void clearTree()
	{
		clearTree(root);

	}

	void inorder()
	{

		inorder(root);
	}

	bool search(int val)
	{

		if (search(root, val) == true)
		{
			cout << "value exists" << endl;
			return true;
		}
		else
		{
			cout << "value does not exists" << endl;
			return false;
		}

	}

	void remove(int num)
	{
		removeRec(root, num);
		root->color = 'b';
		doubleblack = false;

	}

	void GoTO(int x, int y)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		pos.X = x; //Column
		pos.Y = y; //Row
		SetConsoleCursorPosition(hConsole, pos);

	}

	void showtree()
	{

		showTree(root, 0, 80, 1);

	}





};

int main()
{

	RnBTree rbTree;

	char k = ' ';
	int in;
	int d;

	/*rbTree.Addnode(50);
	rbTree.Addnode(25);
	rbTree.Addnode(70);
	rbTree.Addnode(65);
	rbTree.Addnode(60);*/



	while (k != '7')
	{
		cout << "KAIF MENU! PLEASE PRESS ANY OF THESE NUMBERS(1-6)" << endl;
		cout << "1.)ADD vlaue: " << endl;
		cout << "2.)Search vlaue: " << endl;
		cout << "3.)Clear: " << endl;
		cout << "4.)Place in order: " << endl;
		cout << "5.)Number to delete: " << endl;
		cout << "6.)View tree " << endl;
		cout << "Press any other key to exit: " << endl;
		cin >> k;

		switch (k)
		{

		case '1':
			cout << "PLZ put in a value: " << endl;
			cin >> in;
			rbTree.Addnode(in);

			break;
		case '2':
			cout << "Search value" << endl;
			int s;
			cin >> s;
			rbTree.search(s);
			break;
		case '3':
			rbTree.clearTree();
			break;
		case '4':
			rbTree.inorder();
			cout << endl;
			break;
		case '5':
			cout << "Enter num to delete: " << endl;
			cin >> d;
			rbTree.remove(d);
			break;
		case '6':
			cout << "View Tree: " << endl;
			//string addfile;
			system("cls");
			rbTree.showtree();
			rbTree.GoTO(20, 20); // goto funtion and put it in the bottom of the screen
			system("pause");
			system("cls");
			break;
		default:
			exit(0);
			break;
		}


	}

}