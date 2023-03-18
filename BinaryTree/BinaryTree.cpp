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
bool operator<(int a, shared_ptr<TreeElem> b) {
	return a < b->age;
}
bool operator>(int a, shared_ptr<TreeElem> b) {
	return a > b->age;
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
	//Если ни одного элемента нет
	if (this->data == nullptr) {
		//То мы создаём корневой
		this->data = make_shared<TreeElem>(value);
		//Выходим из функции
		return;
	}

	//Если добавляемое значение меньше узлового
	if (value < this->data) {
		//Идём налево
		//Если нет левого элемента
		if (this->left == nullptr) {
			//Создаём левый и записываем данные
			this->left = make_shared<BinaryTree>(value);
		}
		//Если левый есть
		else {
			//Просим его добавить значение в дерево
			this->left->add(value);
		}
	}
	//Если добавляемое значение больше узлового
	else {
		//Если справа нет дочернего элемента
		if (this->right == nullptr) {
			//Создаём его и записываем добавляемое значение
			this->right = make_shared<BinaryTree>(value);
		}
		//Если справа уже есть элемент
		else {
			//Просим его добавить данные
			this->right->add(value);
		}
	}
}
void BinaryTree::remove(int value)
{
	//Указатель на родителя
	shared_ptr<BinaryTree> parent = nullptr;
	//Указатель на текущий рассматриваемый элемент
	shared_ptr<BinaryTree> tek = shared_ptr<BinaryTree>(this);
	//Пока не найдём искомый элемент или не покинем дерево
	while (tek != nullptr && tek->data->age != value) {
		//В родителя прописываем указатель на элемент, который был текущим
		parent = tek;
		//В зависимости от того, искомое значение больше или меньше
		if (value < tek->left->data) {
			//Если меньше, идём влево
			tek = tek->left;
		}
		else
		{
			//Если больше идём вправо
			tek = tek->right;
		}
	}
	//Если вышли из дерева, то искомого элемента нет
	if (tek == nullptr) {
		//Выходим из функции
		return;
	}
	//Проверка на то, что в узле один потомок
	//Если слева пусто
	if (tek->left == nullptr) {
		//Если у родителя мы левый
		if (parent->left == tek) {
			//У родителя в левый прописываем наш правый
			parent->left = tek->right;
		}
		else {
			//У родителя правый прописываем наш правый
			parent->right = tek->right;
		}
		//И выходим
		return;
	}
	//Если справа пусто
	else {
		//Если у родителя мы левый
		if (parent->left == tek) {
			//У родителя в левый прописываем наш левый
			parent->left = tek->left;
		}
		else {
			//У родителя правый прописываем наш правый
			parent->right = tek->left;
		}
		//Выходим
		return;

	}
	//Удаление, когда у нас два потомка
	//У элемента есть два потомка, тогда на место элемента поставим
	//наименьший элемент из его правого поддерева
	//Переходим к правому поддереву
	shared_ptr<BinaryTree> replace = tek->right;
	//Ищем его самый левый элемент
	while (replace->left != nullptr) {
		replace = replace->left;
	}
	//Забираем у самого левого элемента его данные
	tek->data = replace->data;
	//Удаляем тот самый самый левый элемент
	replace->remove(replace->data->age);


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
	eva.remove(75);
	return 0;
}

/*
	//Оператор сравнения динамических типов данных
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