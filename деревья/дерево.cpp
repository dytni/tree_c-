#include<iostream>
#include<io.h>
#include<stdio.h>
#include<string.h>
#include<stack>
using namespace std;

struct tree
{
	int info;
	tree* r, * l;
};

tree* create(int);
void view(tree* , int );
tree* delete_key(tree*, int, tree*);
void delete_tree(tree*);
void add(int, tree**);
tree* search(tree*, int);
void detour_LeRoRi(tree*);
void detour_RoLeRi(tree*);
void detour_LeRiRo(tree*);
void ind(tree*, int&);
void blns(tree**, int, int, int*);
void Quicksort(int*, int);


int main()
{
	int* a, n, c, kol = 0;
	int l = 0;
	int key;
	tree* root = NULL, * prev = NULL;
	cout << "enter amount of elements\n";
	cin >> n;
	a = new int[n];
	cout << "enter a[1]\n";
	cin >> a[0];
	root = create(a[0]);
	for (int i = 1; i < n; i++) {
		cout << "enter a[" << i + 1 << "]\n";
		cin >> a[i];
		add(a[i], &root);
	}
	do {

		cout << "Select function\t 1- enter elements of tree\t 2- detour\t 3- view\t 4- search by key\t 5- delete by key\t 6- delete tree\t 7- balance tree\ 8- individual\t\t 0- exit\n";
		cin >> c;
		switch (c) {
		case 1:
			cout << "enter element\n";
			cin >> key;
			add(key, &root);
			break;
		case 2:
			int choise;
			cout << "select algorithm of detour:" << endl;
			cout << "1 detour from left to right;" << endl;
			cout << "2 detour from top to down;" << endl;
			cout << "3 detour from down to top;" << endl;
			cout << "0 exit" << endl;
			cin >> choise;
			cout << endl;
			switch (choise)
			{
			case 1:
				detour_LeRoRi(root);
				break;
			case 2:
				detour_RoLeRi(root);
				break;
			case 3:
				detour_LeRiRo(root);
				break;
			default:
			case 0:
				cout << "exit" << endl;
				break;
			}
			cout << endl;
			break;
		case 3:
			view(root, l);
			break;
		case 4:
			cout << "enter key\t";

			cin >> key;
			search(root, key);
			break;
		case 5:
			cout << "enter key\t";
			cin >> key;
			delete_key(root, key, prev);
			break;
		case 6:
			delete_tree(root);
			cout << "tree was deleted\n";
			break;
		case 7:
			Quicksort(a, n);
			blns(&root, l, n, a);
			delete[] a;
			break;
		case 8:
			ind(root, kol);
			cout << "amount of leaf  =  " << kol << endl;
			break;
		}
	} while (c != 0);
	delete_tree(root);
}
tree* create(int data)
{
	tree* t = new tree;
	t->r = NULL;
	t->l = NULL;
	t->info = data;
	return t;

}
void add(int data, tree** t)
{
	tree* tmp = *t;
	if (data > tmp->info)
	{
		if (tmp->r == NULL)
		{
			tmp->r = create(data);
			return ;
		}
		else
		{
			add(data, &(tmp->r));
		}
	}
	if (data < tmp->info)
	{
		if (tmp->l == NULL)
		{
			tmp->l = create(data);
			return ;
		}
		else
		{
			add(data, &(tmp->l));
		}
	}
}
tree* search(tree* t, int key)
{
	if (t != NULL)
	{
		if (t->info == key)
		{
			cout << t->info << endl;
			return t;
		}
		if (key > t->info) { t = search((t->r), key); }
		if (key < t->info) { t = search((t->l), key); }
	}
	if (t == NULL) { cout << "value not found\n"; }
	return t;
}
void delete_tree(tree* t)
{
	if (t != NULL)
	{
		delete_tree(t->l);
		delete_tree(t->r);
		delete t;
	}
}
tree* delete_key(tree* t, int key, tree* prev)
{

	tree* Del = t, * Prev_Del = 0, * R, * Prev_R;
	while (Del != 0 && Del->info != key)
	{
		Prev_Del = Del;
		if (Del->info > key)
		{
			Del = Del->l;
		}
		else
		{
			Del = Del->r;
		}
	}
	if (Del == 0)
	{
		cout << "value not found\n";
		return t;
	}
	if (Del->r == 0)
	{
		R = Del->l;
	}
	else
	{
		if (Del->l == 0)
		{
			R = Del->r;
		}
		else
		{
			Prev_R = Del;
			R = Del->l;
			while (R->r != 0)
			{
				Prev_R = R;
				R = R->r;
			}
			if (Prev_R == Del)
			{
				R->r = Del->r;
			}
			else
			{
				R->r = Del->r;
				Prev_R->r = R->l;
				R->l = Prev_R;
			}
		}
	}
	if (Del == t)
	{
		t = R;
	}
	else
	{
		if (Del->info < Prev_Del->info)
		{
			Prev_Del->l = R;
		}
		else
		{
			Prev_Del->r = R;
		}
	}
	delete Del;
	return t;

}
void view(tree* t, int lev)
{
	int i;
	if (t != NULL) {
		view(t->r, lev + 1);

		for (i = 1; i <= lev; i++) { cout << "   "; }
		cout << t->info << endl;
		view(t->l, lev + 1);
	}
}
void detour_LeRoRi(tree* t)
{
	if (t != 0)
	{
		detour_LeRoRi(t->l);
		cout << t->info << endl;
		detour_LeRoRi(t->r);
	}
}
void detour_RoLeRi(tree* t)
{
	if (t != 0)
	{
		cout << t->info << endl;
		detour_RoLeRi(t->l);
		detour_RoLeRi(t->r);
	}
}
void detour_LeRiRo(tree* t)
{
	if (t != 0)
	{
		detour_LeRiRo(t->l);
		detour_LeRiRo(t->r);
		cout << t->info << endl;
	}

}
void Quicksort(int* a, int n)
{
	int i, j, L = 0, R = n - 1, ch_i = 1, r;
	int* c = new int[n];
	c[0] = 0;
	c[1] = n - 1;
	while (ch_i >= 0)
	{
		L = c[ch_i - 1];
		R = c[ch_i];
		ch_i -= 2;
		i = L;
		j = R;
		while (i <= j)
		{
			while (a[i] < a[(L + R) / 2])
			{
				i++;
			}
			while (a[j] > a[(L + R) / 2])
			{
				j--;
			}
			if (i <= j)
			{
				r = a[i];
				a[i] = a[j];
				a[j] = r;
				i++;
				j--;
			}
		}
		if (L < j)
		{
			ch_i += 2;
			c[ch_i - 1] = L;
			c[ch_i] = j;
		}
		if (i < R)
		{
			ch_i += 2;
			c[ch_i - 1] = i;
			c[ch_i] = R;
		}
	}
	delete[]c;
}
void blns(tree** t, int n, int k, int* a)
{
	if (n == k)
	{
		*t = NULL;
		return;
	}
	else
	{
		int m = (n + k) / 2;
		*t = new tree;
		(*t)->info = a[m];
		blns(&(*t)->l, n, m, a);
		blns(&(*t)->r, m + 1, k, a);
	}
}
void ind(tree* t, int &c)
{
	
	if (t != 0)
	{
		ind(t->l,c);
		ind(t->r,c);
		if (t->l == NULL && t->r == NULL) { c++; }
	}
}
