#include <iostream>
#include <stack>
#include <queue>
using namespace std;
class Tree {
	int data;
public:
	Tree* left;
	Tree* right;
	Tree(int d = 0, Tree* l = nullptr, Tree* r = nullptr) : data(d), left(l), right(r) {
	}
	void set_data(int d = 0);
	int get_data() const;
	void set_left_right(Tree* l, Tree* r) {
		left = l; right = r;
	}
};
void Tree::set_data(int d) {
	if (d == 0) {
		cout << "Enter data: ";
		cin >> data;
	}
	data = d;
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
void level_trevarsal(Tree* root ) {
	if (root == nullptr)
		return;
	queue<Tree*> q1;
	q1.push(root);
	q1.push(nullptr);
	while (q1.empty() != true) {
		Tree* node = q1.front();
		q1.pop();
		if (node != nullptr) {
			cout << node->get_data() << " ";
			if (node->left != nullptr)
				q1.push(node->left);
			if (node->right != nullptr)
				q1.push(node->right);
		}
		else if (!q1.empty()) {
			q1.push(nullptr);
		}
		
	}
}
int sumAtLevel(Tree* root, int k) {
	if (root == nullptr) {
		cout << "Tree is empty" << endl;
	}
	queue<Tree*> q1;
	q1.push(root);
	q1.push(nullptr);
	int level{}, sum{};
	while (q1.empty() != true) {
		Tree* node = q1.front();
		q1.pop();
		if (node != nullptr) {
			if (level == k)
				sum += node->get_data();
			if (node->left != nullptr)
				q1.push(node->left);
			if (node->right != nullptr)
				q1.push(node->right);
		}
		else if (!q1.empty()) {
			q1.push(nullptr);
			level++;
		}

	}
	return sum;
}
int height(Tree* t) {
	if (t == nullptr)
		return 0;
	int left_height = height(t->left);
	int right_height = height(t->right);
	return max(left_height, right_height) + 1;
}
void creating(Tree*& t, int key) {
	static Tree* prev = nullptr;
	if (t == nullptr) {
		t = new Tree(key);
		if (prev && prev->get_data() < key)
			prev->right = t;
		else if (prev && prev->get_data() > key)
			prev->left = t;
	}
	else {
		if (t->get_data() == key)
			return;
		else if (key < t->get_data()) {
			prev = t;
			creating(t->left, key);
		}
		else {
			prev = t;
			creating(t->right, key);
		}
	}
}
void create_BST(Tree*& n, int* arr, int size) {
	Tree* t = n;
	for (int i = 0; i < size; i++) {
		creating(n, arr[i]);
	}
	cout << "Binary Search is Created" << endl;
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
Tree* searching_BST(Tree* t, int key) {
	if (t == nullptr) {
		cout << "key is not found" << endl;
		return nullptr;
	}
	if (key == t->get_data())
		return t;
	else if (key < t->get_data())
		return searching_BST(t->left, key);
	else
		return searching_BST(t->right, key);
}

int find_max(Tree* t) {
	if (t == nullptr) {
		cout << "Tree is Empty" << endl;
		return -1;
	}
	if (t->right == nullptr)
		return t->get_data();
	return find_max(t->right);
}
int find_min(Tree* t) {
	if (t == nullptr) {
		cout << "Tree is Empty" << endl;
		return -1;
	}
	if (t->left == nullptr)
		return t->get_data();
	find_min(t->left);
}
int iterative_search(Tree* t, int key) {
	while (t != nullptr) {
		if (t->get_data() == key)
			return 1;
		else if (key < t->get_data())
			t = t->left;
		else
			t = t->right;
	}
	return -1;
}
Tree* insert(Tree* root, int key) {
	if (root == nullptr)
		return new Tree(key);
	else if (root->get_data() < key)
		root->right = insert(root->right, key);
	else if (root->get_data() > key)
		root->left = insert(root->left, key);
	return root;
}

Tree* inorder_suc(Tree* cur) {
	while (cur && cur->left != nullptr) {
		cur = cur->left;
	}
	return cur;
}
Tree* delete_node(Tree* root, int key) {
	if (root == nullptr) {
		cout << "Key not Found" << endl;
		return nullptr;
	}
	else if (root->get_data() < key)
		root->right = delete_node(root->right, key);
	else if (root->get_data() > key)
		root->left = delete_node(root->left, key);
	else {
		if (root->right == nullptr) {
			Tree* temp = root->left;
			delete root;
			return temp;
		}
		else if (root->left == nullptr) {
			Tree* temp = root->right;
			delete root;
			return temp;
		}
		Tree* temp = inorder_suc(root->right);
		root->set_data(temp->get_data());
		root->right = delete_node(root->right, temp->get_data());
	}
	return root;
}
Tree* createBSTpreorder(int preorder[], int* pre_index, int key, int max, int min, int n) {
	Tree* root = nullptr;
	if (*pre_index >= n)
		return root;
	if (key > min && key < max) {
		root = new Tree(key);
		*pre_index = *pre_index + 1;
		if (*pre_index < n)
			root->left = createBSTpreorder(preorder, pre_index, preorder[*pre_index], key, min, n);
		if (*pre_index < n)
			root->right = createBSTpreorder(preorder, pre_index, preorder[*pre_index], max,key, n);
	}
	return root;
}
Tree* deleteWithnoChild(Tree* root, int key) {
	if (root == nullptr) {
		cout << "Key not Found" << endl;
		return nullptr;
	}
	else if (root->get_data() < key)
		root->right = deleteWithnoChild(root->right, key);
	else if (root->get_data() > key)
		root->left = deleteWithnoChild(root->left, key);
	else {
		delete root;
		return nullptr;
	}
	return root;
}
Tree* deleteWithoneChild(Tree* root, int key) {
	if (root == nullptr) {
		cout << "Key not Found" << endl;
		return nullptr;
	}
	else if (root->get_data() < key)
		root->right = deleteWithoneChild(root->right, key);
	else if (root->get_data() > key)
		root->left = deleteWithoneChild(root->left, key);
	else {
		if (root->right == nullptr) {
			Tree* temp = root->left;
			delete root;
			return temp;
		}
		else {
			Tree* temp = root->right;
			delete root;
			return temp;
		}
		
	}
	return root;
}

int main() {
	int arr[6]{ 7,5,4,6, 8, 9 };
	Tree* root = nullptr;
	int preindex = 0;
	root = createBSTpreorder(arr, &preindex, arr[0], INT_MAX, INT_MIN, 6);
	cout << sumAtLevel(root, 2);
	return 0;
}