#pragma once
#include <iostream>
using namespace std;
struct chel {
	string fio;
	int age;
	int rost;
	//Конструктор по умолчанию.
	chel() {
		this->fio = "";
		this->age = 0;
		this->rost = 0;
	};
	//Конструктор с параметром
	chel(string fio, int age, int rost) {
		this->age = age;
		this->fio = fio;
		this->rost = rost;
	}
	//Вывод в консоль одного элемента
	void print() {
		cout <<
			this->fio << " " <<
			this->age << " " <<
			this->rost << " " <<
			endl;
	}
};
class LinkedList: public enable_shared_from_this<LinkedList> {
	//Указатель на следующий в цепочке элемент
	shared_ptr<LinkedList> next = nullptr;
	//Данные, которые ма храним в элементе
	shared_ptr<chel> data = nullptr;

public:
	LinkedList();
	LinkedList(int eva);
	LinkedList(string s, int age, int rost);
	LinkedList(shared_ptr<chel> chel);
	bool isEmpty();
	void addToHead(string s, int age, int rost);
	void addToTail(string s, int age, int rost);
	void addInside(string s, int pos);
	string getString();
	shared_ptr<chel> find(string name);
	void deleteElem(int choise);
	void deleteElem(string name);
	void printAllFromLinkedList();

};
//Конструктор по умолчанию
LinkedList::LinkedList()
{
	this->next = nullptr;
	this->data = nullptr;
}
inline LinkedList::LinkedList(int eva)
{
	this->data = nullptr;
}
//Конструктор с параметром для заполнения данными
LinkedList::LinkedList(string s, int age, int rost)
{
	this->data = make_shared<chel>(s, age, rost);
}
//Проверка на то, есть ли хоть один элемент
bool LinkedList::isEmpty()
{
	if (this->data == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
inline LinkedList::LinkedList(shared_ptr<chel> chel)
{
	this->data = chel;
}
//Добавление элемента в голову
void LinkedList::addToHead(string s, int age, int rost)
{
	//если ни одного элемента
	if (this->isEmpty()) {
		//Записываем данные в текущий
		this->data = make_shared<chel>(s,age,rost);
		return;
	}
	if (this->next == nullptr) {
		this->next = make_shared<LinkedList>(s, age, rost);
	}
	else {
		//Если текущий существует, запоминаем бывший справа
		shared_ptr<LinkedList> tmp = this->next;
		//создаём новый элемент справа
		this->next = make_shared<LinkedList>(this->data);
		//в новый справа записываем бывший справа
		this->next->next = tmp;
		//В текущий заносим новые данные
		this->data = make_shared<chel>(s, age, rost);


	}
}
//Добавление элемента в хвост
void LinkedList::addToTail(string s, int age, int rost)
{
	//Если список пустой, помещаем данные прямо в первый элемент
	if (this->isEmpty()) {
		this->data = make_shared<chel>(s, age, rost);
		return;
	}
	//Если головной существует, но следующего нет, записываем туда
	if (this->next == nullptr) {
		this->next = make_shared<LinkedList>(make_shared<chel>(s,age,rost));
	}
	else {
		//Если следующие узлы есть, идём по цепочке в самый хвост
		shared_ptr<LinkedList> tmp = this->next;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		//Когда прищли в хвост, добавляем новый элемент
		tmp->next = make_shared<LinkedList>(this->data);
	}
}
string LinkedList::getString()
{
	return "";
	/*
	//Если списка нет, возвращаем устую строку
	if (this->data == nullptr) {
		return "";
	}
	//Если есть только головной элемент, возвращаем данные только из него
	if (this->next == nullptr) {
		return *this->data;
	}
	//Создаём временный указатель, чтобы ходить по списку
	shared_ptr<List> tmp = this->next;
	//Вписываем данные из головного элемента
	string result = *this->data + "\n";
	//Пока не дойдём до хвоста
	while (tmp->next != nullptr)
	{
		//Добавляем к итоговой строке все данные из каждого элемента
		result += *tmp->data + "\n";
		//Переходим к следующему элементу
		tmp = tmp->next;
	}
	//дописываенм хвостовой элемент
	result += *tmp->data;
	//Возвращаем итоговую получившуюся строку
	return result;
	*/
}

inline shared_ptr<chel> LinkedList::find(string name)
{
	if (this->data == nullptr) {
		throw domain_error("List is empty");
	}
	if (this->data->fio == name) {
		return this->data;
	}
	shared_ptr<LinkedList> tmp = this->next;
	while (tmp->data->fio != name && tmp->next != nullptr) {
		tmp = tmp->next;
	}
	if (tmp->data->fio != name) {
		throw domain_error("Element is not exist");
	}
	return tmp->data;
}


//Добавление элемента внутрь списка
void LinkedList::addInside(string s, int pos)
{
	////Тут как и в добавлении в хвост
	//if (this->isEmpty()) {
	//	this->addToHead(s, , );
	//	return;
	//}
	//if (this->next == nullptr) {
	//	this->next = make_shared<List>(s);
	//}
	//else {
	//	shared_ptr<List> tmp = this->next;
	//	//идём по списку до тех пор, пока не дойдём до нужной позиции, или до хвоста
	//	for (
	//		int i = 2;
	//		i < pos && tmp->next != nullptr;
	//		i++, tmp = tmp->next
	//		);
	//	//Если следующий элемент не пустой, добавляем между двумя
	//	if (tmp->next != nullptr) {
	//		//Создаём новый	елемент
	//		shared_ptr<List> newElem = make_shared<List>(s);
	//		//В правый указатель прописываем правый элемент
	//		newElem->next = tmp->next;
	//		//В текущий элемент, который слева, прописываем наш новый
	//		tmp->next = newElem;
	//	}
	//	else {
	//		//Если пустой, просто добавляем в хвост
	//		tmp->next = make_shared<List>(s);
	//	}
	//}


}
/// <summary>
/// Удаление элемента из списка
/// </summary>
/// <param name="chiose">Выбор действия. | 1. Удалить в голове | 0. Удалить в хвосте.| Число - удалить где-то в средине</param>
void LinkedList::deleteElem(int choise)
{
	//Если принято число меньше ноля, просто выдаём ошибку
	if (choise < 0) {
		throw runtime_error("Ошибка удаления.\nЧисло меньше 0");
	}
	//Если не существует ни одного элемента, выдаём ошибку.
	if (this->data == nullptr) {
		throw runtime_error("Ошибка удаления.\nОтсутствуют элементы в списке");
	}
	//Если элемент только один, удаляем его
	if (this->next == nullptr) {
		this->data = nullptr;
		return;
	}
	//Остался только случай, когда элементов несколько
	switch (choise)
	{
		//Удалить в хвосте
	case 0: {
		//Создаём временный указатель, 
		//чтобы перейти к предпоследнему элементу
		shared_ptr<LinkedList> tmp = this->next;
		//Переходим к предпоследнему элементу
		while (tmp->next->next != nullptr)
		{
			tmp = tmp->next;
		}
		//Удаляем указатель на последний элемент
		tmp->next = nullptr;

	}
		  break;
		  //Удалить в голове
	case 1:
		//Переписываем в голову данные из правого элемента
		this->data = this->next->data;
		this->next = this->next->next;

		break;
	default:
		//Создаём копию указателя из головы (на второй элемент)
		shared_ptr<LinkedList> tmp = this->next;
		//идём циклом до элемента, который нужно удалить
		for (int i = 2; i < choise && tmp->next != nullptr; i++) {
			tmp = tmp->next;
		}
		//Если так получилось, что дошли до последнего, удаляем его
		if (tmp->next == nullptr) {
			this->deleteElem(0);
			return;
		}
		//Если дошли не до последнего, переписываем указатели так, 
		//чтобы избавиться от элемента внутри списка 
		tmp->next = tmp->next->next;
		break;
	}
}

inline void LinkedList::deleteElem(string name)
{
	if (this->data == nullptr) {
		throw runtime_error("Ошибка удаления: Отсутствуют элементы в списке\n");
	}
	if (this->data->fio == name) {
		this->data = this->next == nullptr ? nullptr : this->next->data;
		this->next = this->next == nullptr ? nullptr : this->next->next;
	}
}

inline void LinkedList::printAllFromLinkedList()
{
	if (this->data == nullptr) {
		return;
	}
	this->data->print();
	if (this->next != nullptr) {
		this->next->printAllFromLinkedList();
	}
}
