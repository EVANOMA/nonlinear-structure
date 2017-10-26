#include<iostream>
using namespace std;

#include "TestBinary.cpp"
using namespace TestBinary;

void visit(int &item)
{
	cout << item << endl;
}



int main() {
	AVL_Tree<int> a1;
	a1.insert(2);	
	a1.insert(1);
	a1.insert(5);
	a1.insert(0);
	a1.insert(4);
	a1.insert(6);
	a1.insert(3);
	a1.remove(6);
	a1.preorder_traversal(visit);
	return 0;
}

/*

*/