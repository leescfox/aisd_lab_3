#include <iostream>
#include <locale>
using namespace std;

struct AVLnode* rotateright(struct AVLnode* Node, int balA, int balB);
struct AVLnode* rotateleft(struct AVLnode* Node, int balA, int balB);
void rebalance(struct AVLnode* Node);
struct AVLnode* find(int info, struct AVLnode* Node);
void add(int info, struct Root* root);
struct AVLnode* create_first(int info, struct Root* head);
void create_elem(struct AVLnode* mama, int info, string side);
void ebalance(struct AVLnode* lower);
struct Head* create_head();
struct Root* create_root();
void push(struct Head* HEAD, struct AVLnode* Node);
struct AVLnode* pop(struct Head* HEAD);
struct AVLnode* find_root(struct AVLnode* Node);
struct AVLnode* peek(struct Head* HEAD);
struct AVLnode* out(struct Head* HEAD);
void KLP(struct Head* HEAD, struct AVLnode* Node);
void LKP(struct Head* HEAD, struct AVLnode* Node);
void LPK(struct Head* HEAD, struct AVLnode* Node);
void Width(struct Head* HEAD, struct AVLnode* Node);
void Delete(int number, struct Root* root);
void del_rebalance(struct AVLnode* Node, struct Root* root);

struct AVLnode
{
	int data;
	struct AVLnode* left;
	struct AVLnode* right;
	struct AVLnode* parent;
	int balance;
};

struct Root
{
	struct AVLnode* top;
};

struct Odnosv {
	struct AVLnode* part;
	struct Odnosv* next;
};

struct Head {
	struct Odnosv* top;
};

int main()
{
	setlocale(LC_ALL, "RUS");
	int num;
	struct Head* HEAD = create_head();
	struct Root* root = create_root();
	cout << "Введите массив чисел. Чтобы прекратить ввод, введите слово или символ.\n";
	cin >> num;
	if (!cin.fail())
	{
		create_first(num, root);
		while (true)
		{
			cin >> num;
			if (!cin.fail())
			{
				add(num, root);
			}
			else
				break;
		}
	}
	cout << "Отсортированный массив:" << endl;
	LKP(HEAD, root->top);
	return 0;
}

struct AVLnode* pop(struct Head* HEAD)
{
	struct Odnosv* temp = HEAD->top;
	HEAD->top = HEAD->top->next;
	struct AVLnode* temp2 = temp->part;
	delete temp;
	return temp2;
}

void push(struct Head* HEAD, struct AVLnode* Node)
{
	struct Odnosv* elem = new struct Odnosv;
	elem->part = Node;
	elem->next = HEAD->top;
	HEAD->top = elem;
}

struct AVLnode* peek(struct Head* HEAD)
{
	return HEAD->top->part;
}

struct Head* create_head()
{
	struct Head* HEAD = new struct Head;
	HEAD->top = NULL;
	return HEAD;
}

struct Root* create_root()
{
	struct Root* ROOT = new struct Root;
	ROOT->top = NULL;
	return ROOT;
}

struct AVLnode* out(struct Head* HEAD)
{
	struct Odnosv* temp = HEAD->top;
	struct Odnosv* temp2 = NULL;
	struct AVLnode* Node = NULL;
	while (temp->next != NULL)
	{
		temp2 = temp;
		temp = temp->next;
	}
	Node = temp->part;
	if (temp2 != NULL)
	{
		temp2->next = NULL;
		delete temp;
	}
	else
	{
		delete temp;
		HEAD->top = NULL;
	}
	return Node;
}

void ebalance(struct AVLnode* lower)
{
	while (lower->parent != NULL)
	{
		if (lower->parent->left == lower)
		{
			lower->parent->balance = lower->parent->balance - 1;
		}
		else
			lower->parent->balance = lower->parent->balance + 1;
		if (lower->parent->balance == 0)
			break;
		else if (lower->parent->balance == -2 || lower->parent->balance == 2)
		{
			rebalance(lower->parent);
			break;
		}
		lower = lower->parent;
	}
}

void create_elem(struct AVLnode* mama, int info, string side)
{
	struct AVLnode* elem = new struct AVLnode;
	elem->data = info;
	elem->left = NULL;
	elem->right = NULL;
	elem->parent = mama;
	elem->balance = 0;
	if (side == "left")
		mama->left = elem;
	else if (side == "right")
		mama->right = elem;
}

struct AVLnode* create_first(int info, struct Root* head)
{
	struct AVLnode* root = new struct AVLnode;
	root->data = info;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	root->balance = 0;
	head->top = root;
	return root;
}

void add(int info, struct Root* root)
{
	struct AVLnode* Node = root->top;
	while (true)
	{
		if (info < Node->data)
		{
			if (Node->left == NULL)
			{
				create_elem(Node, info, "left");
				ebalance(Node->left);
				root->top = find_root(Node);
				break;
			}
			else
			{
				Node = Node->left;
			}

		}
		else
		{
			if (Node->right == NULL)
			{
				create_elem(Node, info, "right");
				ebalance(Node->right);
				root->top = find_root(Node);
				break;
			}
			else
			{
				Node = Node->right;
			}
		}
	}
}

struct AVLnode* find(int info, struct AVLnode* Node)
{
	while (Node != NULL && info != Node->data)
	{
		if (info < Node->data)
		{
			Node = Node->left;
		}
		else if (info > Node->data)
		{
			Node = Node->right;
		}
	}
	return Node;
}

void rebalance(struct AVLnode* Node)
{
	if (Node->balance == 2 && Node->right != NULL)
	{
		if (Node->right->balance == 0)
			Node = rotateleft(Node, 1, -1);
		else if (Node->right->balance == 1)
			Node = rotateleft(Node, 0, 0);
		else
		{
			if (Node->right->left->balance == -1)
			{
				Node->right = rotateright(Node->right, Node->right->balance, Node->right->left->balance);
				Node = rotateleft(Node, 0, 1);
			}
			else if (Node->right->left->balance == 1)
			{
				Node->right = rotateright(Node->right, Node->right->balance, Node->right->left->balance);
				Node = rotateleft(Node, -1, 0);
			}
			else
			{
				Node->right = rotateright(Node->right, Node->right->balance, Node->right->left->balance);
				Node = rotateleft(Node, 0, 0);
			}
		}
	}
	else if (Node->balance == -2 && Node->left != NULL)
	{
		if (Node->left->balance == 0)
		{
			Node = rotateright(Node, -1, 1);
		}
		else if (Node->left->balance == -1)
		{
			Node = rotateright(Node, 0, 0);
		}
		else
		{
			if (Node->left->right->balance == -1)
			{
				Node->left = rotateleft(Node->left, Node->left->balance, Node->left->right->balance);
				Node=rotateright(Node, 1, 0);
			}
			else if (Node->left->right->balance == 1)
			{
				Node->left = rotateleft(Node->left, Node->left->balance, Node->left->right->balance);
				Node=rotateright(Node, 0, -1);
			}
			else
			{
				Node->left = rotateleft(Node->left, Node->left->balance, Node->left->right->balance);
				Node=rotateright(Node, 0, 0);
			}
		}
	}

}

struct AVLnode* rotateleft(struct AVLnode* Node, int balA, int balB)
{
	struct AVLnode* temp = Node->right;
	Node->right = temp->left;
	if (temp->left != NULL)
		temp->left->parent = Node;
	temp->left = Node;
	temp->parent = Node->parent;
	if (Node->parent != NULL)
	{
		if (Node->parent->left == Node)
			Node->parent->left = temp;
		else Node->parent->right = temp;
	}
	Node->parent = temp;
	Node->balance = balA;
	temp->balance = balB;
	return temp;
}

struct AVLnode* rotateright(struct AVLnode* Node, int balA, int balB)
{
	struct AVLnode* temp = Node->left;
	Node->left = temp->right;
	if (temp->right!=NULL)
		temp->right->parent = Node;
	temp->right = Node;
	temp->parent = Node->parent;
	if (Node->parent != NULL)
	{
		if (Node->parent->left == Node)
			Node->parent->left = temp;
		else Node->parent->right = temp;
	}
	Node->parent = temp;
	Node->balance = balA;
	temp->balance = balB;
	return temp;
}

struct AVLnode* find_root(struct AVLnode* Node)
{
	while (Node->parent != NULL)
	{
		Node = Node->parent;
	}
	return Node;
}

void KLP(struct Head* HEAD, struct AVLnode* Node)
{
	if (Node != NULL)
	{
		struct AVLnode* n = NULL;
		push(HEAD, Node);
		while (HEAD->top != NULL)
		{
			n = pop(HEAD);
			cout << n->data << " ";
			if (n->right != NULL)
			{
				push(HEAD, n->right);
			}
			if (n->left != NULL)
			{
				push(HEAD, n->left);
			}
		}
		cout << endl;
	}
}

void LKP(struct Head* HEAD, struct AVLnode* Node) //сортировка
{
	if (Node != NULL)
	{
		while (HEAD->top != NULL || Node != NULL)
		{
			if (Node != NULL)
			{
				push(HEAD, Node);
				Node = Node->left;
			}
			else
			{
				Node = pop(HEAD);
				cout << Node->data << " ";
				Node = Node->right;
			}
		}
		cout << endl;
	}
}

void LPK(struct Head* HEAD, struct AVLnode* Node)
{
	if (Node != NULL)
	{
		struct AVLnode* lastV = NULL;
		struct AVLnode* look = NULL;
		while (HEAD->top != NULL || Node != NULL)
		{
			if (Node != NULL)
			{
				push(HEAD, Node);
				Node = Node->left;
			}
			else
			{
				look = peek(HEAD);
				if (look->right != NULL && lastV != look->right)
				{
					Node = look->right;
				}
				else
				{
					cout << look->data << " ";
					lastV = pop(HEAD);
				}
			}
		}
		cout << endl;
	}
}

void Width(struct Head* HEAD, struct AVLnode* Node)
{
	if (Node != NULL)
	{
		push(HEAD, Node);
		while (HEAD->top != NULL)
		{
			Node = out(HEAD);
			cout << Node->data << " ";
			if (Node->left != NULL)
			{
				push(HEAD, Node->left);
			}

			if (Node->right != NULL)
			{
				push(HEAD, Node->right);
			}
		}
		cout << endl;
	}
}

void Delete(int number, struct Root* root)
{
	struct AVLnode* Node = root->top;
	struct AVLnode* temp = find(number, Node);
	if (temp != NULL)
	{
		struct AVLnode* temp2 = temp->right;
		if (temp2 != NULL)
		{
			while (temp2->left != NULL)
				temp2 = temp2->left;
			temp->data = temp2->data;
			if (temp2 != temp->right)
			{
				temp2->parent->balance++;
				temp2->parent->left = NULL;
			}
			else
			{
				temp2->parent->balance--;
				temp->right = NULL;
			}
			temp = temp2->parent;
			delete temp2;
			temp2 = NULL;
			del_rebalance(temp, root);
		}
		else if (temp->left != NULL)
		{
			temp->data = temp->left->data;
			delete temp->left;
			temp->left = NULL;
			temp->balance = 0;
			del_rebalance(temp, root);
		}
		else
		{
			if (temp->parent == NULL)
			{
				delete temp;
				temp = NULL;
				root->top = NULL;
			}
			else
			{
				temp2 = temp->parent;
				if (temp2->left == temp)
				{
					temp2->balance++;
					temp2->left = NULL;
				}
				else
				{
					temp2->balance--;
					temp2->right = NULL;
				}
				delete temp;
				temp = NULL;
				del_rebalance(temp2, root);
			}
		}
	}
	else
	{
		cout << "Element " << number << " doesn't exist" << endl;
	}
}

void del_rebalance(struct AVLnode* Node, struct Root* root)
{
	struct AVLnode* List = Node;
	if (List->balance == 2 || List->balance == -2)
	{
		rebalance(List);
	}
	else if (List->balance == 0)
	{
		while (List->parent != NULL && List->balance == 0)
		{
			if (List->parent->left == List)
			{
				List->parent->balance++;
			}
			else
				List->parent->balance--;
			List = List->parent;
		}
		if (List->balance == -2 || List->balance == 2)
			rebalance(List);
	}
	root->top = find_root(List);
}