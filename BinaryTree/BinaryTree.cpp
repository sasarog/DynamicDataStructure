#include <iostream>
using namespace std;
struct TreeElem
{
	int age;
	TreeElem() {
		age = 0;
	}
	TreeElem(int a) {
		age = a;
	}

};
bool operator<(TreeElem a, TreeElem b) {
	return a.age < b.age;
}

class BinaryTree {
	shared_ptr<BinaryTree>left;
	shared_ptr<BinaryTree>right;
	shared_ptr<TreeElem> data;
public:
	BinaryTree();
	BinaryTree(int value);
	void add(int value);
	void remove(int value);
};


BinaryTree::BinaryTree()
{
	this->data = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}
BinaryTree::BinaryTree(int value)
{
	this->data = make_shared<TreeElem>(value);
}
void BinaryTree::add(int value)
{
	if (this->data == nullptr) {
		this->data = make_shared<TreeElem>(value);
		return;
	}
	if (value < this->data->age) {
		if (this->left == nullptr) {
			this->left = make_shared<BinaryTree>(value);
		}
		else {
			this->left->add(value);
		}
	}
	else {
		if (value > this->data->age) {
			if (this->right == nullptr) {
				this->right = make_shared<BinaryTree>(value);
			}
			else {
				this->right->add(value);
			}
		}
	}
}
void BinaryTree::remove(int value)
{
	shared_ptr<BinaryTree> parent = nullptr;
	shared_ptr<BinaryTree> tek = shared_ptr<BinaryTree>(this);
	while (tek != nullptr && tek->data->age != value) {
		parent = tek;
		if (value < tek->left->data->age) {
			tek = tek->left;
		}
		else
		{
			tek = tek->right;
		}
	}

	if (tek == nullptr) {
		return;
	}
	if (tek->left == nullptr) {
		if (parent->left == tek) {
			parent->left = tek->right;
		}
		else {
			parent->right = tek->right;
		}
		return;
	}
	else {
		if (parent->left == tek) {
			parent->left = tek->left;
		}
		else {
			parent->right = tek->left;
		}
		return;
	}


}


int main() {
	BinaryTree eva;
	eva.add(50);
	eva.add(75);
	eva.add(25);
	eva.add(90);
	eva.add(65);
	eva.add(10);
	eva.add(35);
	eva.add(57);
	eva.add(59);
	return 0;
}

/*
	//ќператор сравнени€ динамических типов данных
//bool operator< (TreeElem a, TreeElem b) {
//	return a.age < b.age;
//}
bool operator< (shared_ptr<TreeElem> a, int b) {
	return a->age < b;
}
bool operator< (int b, shared_ptr<TreeElem> a) {
	return b < a->age;
}
bool operator> (int b, shared_ptr<TreeElem> a) {
	return b > a->age;
}
bool operator== (shared_ptr<TreeElem> a, int b) {
	return a->age == b;
}
bool operator==(TreeElem a, TreeElem b) {
	return a.age == b.age;
}

class BinaryTree {

	shared_ptr<BinaryTree> parent;
	shared_ptr<BinaryTree> left;
	shared_ptr<BinaryTree> right;
	shared_ptr<TreeElem> data;
	void forgetByAddr(shared_ptr<BinaryTree> todelete);
	void replaceByAddr(shared_ptr<BinaryTree> toDelete, shared_ptr<BinaryTree> toSave);
	shared_ptr<BinaryTree> giveMaxLeft();
public:void deleteAllParents();
public:
	BinaryTree();
	BinaryTree(shared_ptr<BinaryTree> parent, int value);
	void add(int value);
	void remove(int value);
	~BinaryTree();
};
void BinaryTree::forgetByAddr(shared_ptr<BinaryTree> toDelete)
{
	if (this->left == toDelete) {
		this->left = nullptr;
	}
	if (this->right == toDelete) {
		this->right = nullptr;
	}
	return;
}
void BinaryTree::replaceByAddr(shared_ptr<BinaryTree> toDelete, shared_ptr<BinaryTree> toSave)
{
	if (this->left == toDelete) {
		this->left = toSave;
	}
	else {
		this->right = toSave;
	}
	toSave->parent = shared_ptr<BinaryTree>(this);
}
shared_ptr<BinaryTree> BinaryTree::giveMaxLeft()
{
	if (this->left != nullptr) {
		return this->left->giveMaxLeft();
	}
	return shared_ptr<BinaryTree>(this);
}

void BinaryTree::deleteAllParents()
{
	if (this->parent != nullptr) {

		cout << this->data->age << this->parent.use_count();
	}
	if (this->left != nullptr) {
		this->left->deleteAllParents();
	}
	if (this->right != nullptr) {
		this->right->deleteAllParents();
	}
}

BinaryTree::BinaryTree()
{
	this->data = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}
BinaryTree::BinaryTree(shared_ptr<BinaryTree> parent, int value)
{
	this->parent = parent;
	this->data = make_shared<TreeElem>(value);
}
void BinaryTree::add(int value)
{
	if (this->data == nullptr) {
		this->data = make_shared<TreeElem>(value);
	}
	if (this->data == value) {
		return;
	}
	if (this->data < value) {
		if (this->left == nullptr) {
			this->left = make_shared<BinaryTree>
				(shared_ptr<BinaryTree>(this), value);
		}
		else
		{
			this->left->add(value);
		}
	}
	else {
		if (this->right == nullptr) {
			this->right = make_shared<BinaryTree>(shared_ptr<BinaryTree>(this), value);
		}
		else
		{
			this->right->add(value);
		}
	}

}

void BinaryTree::remove(int value)
{
	if (value < this->data) {
		if (this->left != nullptr) {
			this->left->remove(value);
		}
		else {
			return;
		}
	}
	if (value > this->data) {
		if (this->right != nullptr) {
			this->right->remove(value);
		}
		else {
			return;
		}
	}
	if (this->data == value) {
		if (this->left == nullptr && this->right == nullptr) {
			parent->forgetByAddr(shared_ptr<BinaryTree>(this));
			return;
		}
		if (this->left == nullptr && this->right != nullptr) {
			parent->replaceByAddr(shared_ptr<BinaryTree>(this), this->right);
			return;
		}
		if (this->left != nullptr && this->right == nullptr) {
			parent->replaceByAddr(shared_ptr<BinaryTree>(this), this->left);
			return;
		}
		if (this->left != nullptr && this->right != nullptr) {
			shared_ptr<BinaryTree> tmp = this->right->giveMaxLeft();
			this->data = tmp->data;
			tmp->parent->forgetByAddr(tmp);
			return;
		}

	}
}

BinaryTree::~BinaryTree()
{
	//deleteAllParents();
}
*/