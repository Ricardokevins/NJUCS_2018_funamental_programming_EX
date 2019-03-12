#include<iostream>
#include<cstdlib>
using namespace std;

struct TNode {
	int data;
	int num;
	TNode * A[10];
};
typedef struct TNode * links;

links root = NULL;

void insert_at_root(int x)
{
	links newhead = new TNode;
	for (int i(0); i < 10; i++)
	{
		newhead->A[i] = NULL;
	}
	newhead->data = x;
	if (root == NULL)
		newhead->num = 0;
	else
		newhead->num = 1;
	newhead->A[0] = root;
	root = newhead;
}

void insert_after(TNode *node, int x, int y)
{
	if (node == NULL)
	{
		return;
	}
	if (node->data == x)
	{
		links newnode = new TNode;
		newnode->data = y;
		for (int i(0); i < 10; i++)
		{
			newnode->A[i] = NULL;
		}
		newnode->num = 0;
		int s(0);
		while (node->A[s] != NULL)
		{
			s++;
		}
		node->A[s] = newnode;
		node->num++;
		return;
	}

	for (int i(0); i < node->num; i++)
	{
		links temp = node->A[i];
		if (temp->data == x)
		{
			links newnode = new TNode;
			newnode->data = y;
			for (int i(0); i < 10; i++)
			{
				newnode->A[i] = NULL;
			}
			newnode->num = 0;
			int s(0);
			while (temp->A[s] != NULL)
			{
				s++;
			}
			temp->A[s] = newnode;
			temp->num++;
			return;
		}
		insert_after(temp, x, y);
	}
}

void delete_node(TNode *node, int x)
{
	if (node == NULL)
	{
		return;
	}
	if (root->data == x)
	{
		delete root;
		root = NULL;
	}
	for (int i(0); i < node->num; i++)
	{
		links temp = node->A[i];
		if (temp->data == x && temp->A[0] == NULL)
		{
			delete node->A[i];
			node->A[i] = NULL;
			node->num--;
			for (int j(i); j < 10; j++)
			{
				node->A[j] = node->A[j + 1];
			}
			return;
		}
		delete_node(temp, x);
	}
}

void print(TNode *node, int n)
{
	if (node == NULL)
		return;
	if (n == -1)
	{
		cout << node->data << " ";
		for (int i(0); i < node->num; i++)
		{
			print(node->A[i], -1);
		}
	}
	else
	{

		if (n == 0)
			return;
		cout << node->data << " ";
		for (int i = 0; i < node->num; i++)
		{
			links temp = node->A[i];
			print(temp, n - 1);
		}
	}
}

int equalstr(char*a, char *b)
{
	int flag(1);
	while (*a != '\0'&&*b != '\0')
	{
		if (*a != *b)
		{
			flag = 0;
			return flag;
		}
		a++;
		b++;
	}
	if (*a != *b)
	{
		flag = 0;
		return flag;
	}
	return flag;

}

int main()
{
	char A[50];
	int x, y;
	char B[40] = "insert_at_root";
	char C[40] = "insert_after";
	char D[40] = "print";
	char E[40] = "delete";
	while (cin >> A) {
		if (equalstr(A, B)) {
			cin >> x;
			insert_at_root(x);
		}
		else if (equalstr(A, C)) {
			cin >> x>>y;
			insert_after(root,x,y);
		}
		else if (equalstr(A, D)) {
			cin >> x ;
			print(root ,x);
			cout << endl;
		}
		else if (equalstr(A, E)) {
			cin >> x;
			delete_node(root,x);
		}
	}
	return 0;
}
