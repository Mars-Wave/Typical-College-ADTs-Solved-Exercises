// EDp7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Bintree.h"
#include "List.h"
using namespace std;
void example1();
Bintree<int> readBintree();
void showBintree(Bintree<int> t);
int sumOfLevel(Bintree<int> t, int depth);
int specialNodes(Bintree<int> t, int depth, int &total, int prod);

int main()
{
	int numcases;
	int total;
	cin >> numcases;
	for (int i = 0; i < numcases; i++)
	{
		total = 0;
		Bintree<int> t = readBintree();
		specialNodes(t, t.depth(), total, 1);
		cout << total << endl;
	}
	return 0;
}

// It reads a binary tree of integers from the standard input
Bintree<int> readBintree() {
	char c;
	cin >> c;
	switch (c) {
	case '#': return Bintree<int>();
	case '[': {
		int raiz;
		cin >> raiz;
		cin >> c;
		return Bintree<int>(raiz);
	}
	case '(': {
		Bintree<int> left = readBintree();
		int root;
		cin >> root;
		Bintree<int> right = readBintree();
		cin >> c;
		return Bintree<int>(left, root, right);
	}
	default:
		return Bintree<int>();
	}
}

int sumOfLevel(Bintree<int> t, int depth) {
	if (depth == 0) {
		int aux = 0;
		List<int> l = t.inorder();
		List<int>::Iterator it = l.cbegin();
		while (it != l.cend()) {
			aux += it.elem();
			it.next();
		}
		return aux;
	}
	else if (t.numNodes() == 1)
	{
		return 0;
	}
	else {
		depth--;
		return sumOfLevel(t.leftChild(), depth) + sumOfLevel(t.rightChild(), depth);
	}
}

int specialNodes(Bintree<int> t, int depth, int &total, int prod)
{
	if (t.empty()) {
		return 1;
	}
	else {
		int aux = specialNodes(t.leftChild(), t.leftChild().depth(), total, prod * t.root()) * specialNodes(t.rightChild(), t.rightChild().depth(), total, prod * t.root());
		if (aux == prod)
		{
			total++;
		}
		return aux * t.root();
	}
}

// It shows one tree using in-order tour
void showBintree(Bintree<int> t) {
	List<int> l = t.inorder();
	List<int>::Iterator it = l.cbegin();
	while (it != l.cend()) {
		cout << it.elem() << " ";
		it.next();
	}
}

// Example of building and showing one tree
void example1() {
	Bintree<int> t1 = Bintree<int>(Bintree<int>(1), 7, Bintree<int>(3));
	Bintree<int> t = Bintree<int>(t1, 4, Bintree<int>(9));
	showBintree(t);
}

