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
	shared_ptr<BinaryTree> tek = nullptr;
	//Переделать, нельзя удалить корневой элемент
	if (value < this->data) {
		tek = this->left;
	}
	else {
		tek = this->right;
	}

	//Пока не найдём искомый элемент или не покинем дерево
	while (tek != nullptr && tek->data->age != value) {
		//В родителя прописываем указатель на элемент, который был текущим
		//parent = tek;
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
	//Удаление листового элемента
	if (tek->left == nullptr && tek->right == nullptr) {
		//Если у родителя мы левый
		if (parent->left == tek) {
			//У родителя в левый прописываем наш правый
			parent->left = nullptr;
		}
		else {
			//У родителя правый прописываем наш правый
			parent->right = nullptr;
		}
		//И выходим
		return;
	}



	//Проверка на то, что в узле один потомок
	//Если слева пусто
	if (tek->left == nullptr && tek->right != nullptr) {
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
	if(tek->left != nullptr && tek->right == nullptr) {
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
	//Запоминаем у самого левого элемента его данные
	shared_ptr<TreeElem> tmpData = replace->data;
	//Удаляем тот самый самый левый элемент
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