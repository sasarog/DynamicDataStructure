#include <iostream>
using namespace std;
class List {
	//Указатель на следующий в цепочке элемент
	shared_ptr<List> next = nullptr;
	//Данные, которые ма храним в элементе
	string data = "";

public:
	List();
	List(string s);
	bool isEmpty();
	void addToHead(string s);
	void addToTail(string s);
	void addInside(string s, int pos);
	string getString();

};
//Конструктор по умолчанию
List::List()
{

}
//Конструктор с параметром для заполнения данными
List::List(string s)
{
	this->data = s;
}
//Проверка на то, есть лои хоть один элемент
bool List::isEmpty()
{
	if (this->data == "") {
		return true;
	}
	else {
		return false;
	}
}
//Добавление элемента в голову
void List::addToHead(string s)
{
	//если ни одного элемента
	if (this->isEmpty()) {
		//Записываем данные в текущий
		this->data = s;
	}
	else {
		//Если текущий существует, запоминаем бывший справа
		shared_ptr<List> tmp = this->next;
		//создаём новый элемент справа
		this->next = make_shared<List>(this->data);
		//в новый справа записываем бывший справа
		this->next->next = tmp;
		//В текущий заносим новые данные
		this->data = s;


	}
}
//Добавление элемента в хвост
void List::addToTail(string s)
{
	//Если список пустой, помещаем данные прямо в первый элемент
	if (this->isEmpty()) {
		this->data = s;
		return;
	}
	//Если головной существует, но следующего нет, записываем туда
	if (this->next == nullptr) {
		this->next = make_shared<List>(s);
	}
	else {
		//Если следующие узлы есть, идём по цепочке в самый хвост
		shared_ptr<List> tmp = this->next;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		//Когда прищли в хвост, добавляем новый элемент
		tmp->next = make_shared<List>(s);
	}
}
string List::getString()
{

	//Если списка нет, возвращаем устую строку
	if (this->data == "") {
		return "";
	}
	//Если есть только головное элемент, возвращаем данные только из него
	if (this->next == nullptr) {
		return this->data + ".";
	}
	//Создаём временный указатель, чтобы ходить по списку
	shared_ptr<List> tmp = this->next;
	//Вписываем данные из головного элемента
	string result = this->data + "\n";
	//Пока не дойдём до хвоста
	while (tmp->next != nullptr)
	{
		//Добавляем к итоговой строке все данные из каждого элемента
		result += tmp->data + "\n";
		//Переходим к следующему элементу
		tmp = tmp->next;
	}
	//дописываенм хвостовой элемент
	result += tmp->data + ".";
	//Возвращаем итоговую получившуюся строку
	return result;
}


//Добавление элемента внутрь списка
void List::addInside(string s, int pos)
{
	//Тут как и в добавлении в хвост
	if (this->isEmpty()) {
		this->addToHead(s);
		return;
	}
	if (this->next == nullptr) {
		this->next = make_shared<List>(s);
	}
	else {
		shared_ptr<List> tmp = this->next;
		//идём по списку до тех пор, пока не дойдём до нужной позиции, или до хвоста
		for (
			int i = 0;
			i < pos && tmp->next != nullptr;
			i++, tmp = tmp->next
			);
		//Если следующий элемент не пустой, добавляем между двумя
		if (tmp->next != nullptr) {
			//Создаём новый	елемент
			shared_ptr<List> newElem = make_shared<List>(s);
			//В правый указатель прописываем правый элемент
			newElem->next = tmp->next;
			//В текущий элемент, который слева, прописываем наш новый
			tmp->next = newElem;
		}
		else {
			//Если пустой, просто добавляем в хвост
			tmp->next = make_shared<List>(s);
		}
	}

}

int main() {
	setlocale(LC_ALL, "Russian");
	List eva("Ольга");
	eva.addToTail("Антон");
	eva.addToTail("Иван");
	eva.addToTail("Павел");
	cout << eva.getString();


	return 0;
}