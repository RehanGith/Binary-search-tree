#include <iostream>
#include <stack>
using namespace std;
class Tree {
	int data;
public:
	Tree* left;
	Tree* right;
	Tree(int d = 0, Tree* l = nullptr, Tree* r = nullptr) : data(d), left(l), right(r) {
	}
	void set_data();
	int get_data() const;
	void set_left_right(Tree* l, Tree* r) {
		left = l; right = r;
	}
};
void Tree::set_data() {
	cout << "Enter data: ";
	cin >> data;
}
int Tree::get_data() const {
	return data;
}
void display_preorder(Tree* n) {
	if (n == nullptr)
		return;
	cout << n->get_data() << endl;
	display_preorder(n->left);
	display_preorder(n->right);
}
void display_postorder(Tree* n) {
	if (n == nullptr)
		return;
	display_postorder(n->left);
	display_postorder(n->right);
	cout << n->get_data() << endl;
}
void display_inorder(Tree* n) {
	if (n == nullptr)
		return;
	display_inorder(n->left);
	cout << n->get_data() << endl;
	display_inorder(n->right);
}
int is_BST(Tree* n) {
	static Tree* prev = nullptr;
	if (n == nullptr)
		return 1;
	if(!is_BST(n->left)) 
		return 0;
	if (prev != nullptr && n->get_data() <= prev->get_data()) 
		return 0;
	prev = n;
	return is_BST(n->right);
}
int searching_BST(Tree* t, int key) {
	if (t == nullptr)
		return 0;
	if (key == t->get_data())
		return 1;
	else if (key < t->get_data())
		return searching_BST(t->left, key);
	else
		return searching_BST(t->right, key);
}
void inserting_BST(Tree*& t, int key) {
	static Tree* prev = nullptr;
	if (t == nullptr) {
		t = new Tree(key);
		if (prev && prev->get_data() < key )
			prev->set_left_right(nullptr, t);
		else if(prev && prev->get_data() > key)
			prev->set_left_right(t, nullptr);
	}
	if (t->get_data() == key)
		return;
	else if (key < t->get_data()) {
		prev = t;
		inserting_BST(t->left, key);
	}
	else {
		prev = t;
		inserting_BST(t->right, key);
	}
}
int main() {
	Tree* nl = new Tree(5);
	Tree* nr = new Tree(10);
	Tree* n = new Tree(7, nl, nr);
	Tree* nl_left = new Tree(3);
	Tree* nl_right = new Tree(6);
	Tree* nr_left = new Tree(8);
	Tree* nr_right = new Tree(13);
	nl->set_left_right(nl_left, nl_right);
	nr->set_left_right(nr_left, nr_right);
	inserting_BST(n, 9);
	display_inorder(n);
	delete n, nl, nr, nl_left, nr_left, nr_right, nl_right;

	return 0;
}