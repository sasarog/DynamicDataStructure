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
	void print() {
		cout << this->age << " ";
	}
};
bool operator<(TreeElem a, TreeElem b) {
	return a.age < b.age;
}
bool operator<(int a, shared_ptr<TreeElem> b) {
	return a < b->age;
}
bool operator>(int a, shared_ptr<TreeElem> b) {
	return a > b->age;
}

class BinaryTree:public enable_shared_from_this<BinaryTree> {
	shared_ptr<BinaryTree>left;
	shared_ptr<BinaryTree>right;
	shared_ptr<TreeElem> data;
public:
	BinaryTree();
	BinaryTree(int value);
	void add(int value);
	void remove(int value);
	void print();
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
	//���� �� ������ �������� ���
	if (this->data == nullptr) {
		//�� �� ������ ��������
		this->data = make_shared<TreeElem>(value);
		//������� �� �������
		return;
	}

	//���� ����������� �������� ������ ��������
	if (value < this->data) {
		//��� ������
		//���� ��� ������ ��������
		if (this->left == nullptr) {
			//������ ����� � ���������� ������
			this->left = make_shared<BinaryTree>(value);
		}
		//���� ����� ����
		else {
			//������ ��� �������� �������� � ������
			this->left->add(value);
		}
	}
	//���� ����������� �������� ������ ��������
	else {
		//���� ������ ��� ��������� ��������
		if (this->right == nullptr) {
			//������ ��� � ���������� ����������� ��������
			this->right = make_shared<BinaryTree>(value);
		}
		//���� ������ ��� ���� �������
		else {
			//������ ��� �������� ������
			this->right->add(value);
		}
	}
}
void BinaryTree::remove(int value)
{
	//��������� �� ��������
	shared_ptr<BinaryTree> parent = nullptr;
	//��������� �� ������� ��������������� �������
	shared_ptr<BinaryTree> tek = nullptr;
	//����������, ������ ������� �������� �������
	if (value < this->data) {
		tek = this->left;
	}
	else {
		tek = this->right;
	}

	//���� �� ����� ������� ������� ��� �� ������� ������
	while (tek != nullptr && tek->data->age != value) {
		//� �������� ����������� ��������� �� �������, ������� ��� �������
		//parent = tek;
		//� ����������� �� ����, ������� �������� ������ ��� ������
		if (value < tek->left->data) {
			//���� ������, ��� �����
			tek = tek->left;
		}
		else
		{
			//���� ������ ��� ������
			tek = tek->right;
		}
	}
	//���� ����� �� ������, �� �������� �������� ���
	if (tek == nullptr) {
		//������� �� �������
		return;
	}
	//�������� ��������� ��������
	if (tek->left == nullptr && tek->right == nullptr) {
		//���� � �������� �� �����
		if (parent->left == tek) {
			//� �������� � ����� ����������� ��� ������
			parent->left = nullptr;
		}
		else {
			//� �������� ������ ����������� ��� ������
			parent->right = nullptr;
		}
		//� �������
		return;
	}



	//�������� �� ��, ��� � ���� ���� �������
	//���� ����� �����
	if (tek->left == nullptr && tek->right != nullptr) {
		//���� � �������� �� �����
		if (parent->left == tek) {
			//� �������� � ����� ����������� ��� ������
			parent->left = tek->right;
		}
		else {
			//� �������� ������ ����������� ��� ������
			parent->right = tek->right;
		}
		//� �������
		return;
	}
	//���� ������ �����
	if(tek->left != nullptr && tek->right == nullptr) {
		//���� � �������� �� �����
		if (parent->left == tek) {
			//� �������� � ����� ����������� ��� �����
			parent->left = tek->left;
		}
		else {
			//� �������� ������ ����������� ��� ������
			parent->right = tek->left;
		}
		//�������
		return;

	}
	//��������, ����� � ��� ��� �������
	//� �������� ���� ��� �������, ����� �� ����� �������� ��������
	//���������� ������� �� ��� ������� ���������
	//��������� � ������� ���������
	shared_ptr<BinaryTree> replace = tek->right;
	//���� ��� ����� ����� �������
	while (replace->left != nullptr) {
		replace = replace->left;
	}
	//���������� � ������ ������ �������� ��� ������
	shared_ptr<TreeElem> tmpData = replace->data;
	//������� ��� ����� ����� ����� �������
	tek->remove(replace->data->age);

	tek->data = tmpData;


}
void BinaryTree::print()
{
	this->data->print();
	if (this->right != nullptr) {
		this->right->print();
	}
	if (this->left != nullptr) {
		this->left->print();
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
	eva.remove(59);
	eva.print();
	return 0;
}