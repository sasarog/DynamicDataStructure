#include <iostream>
using namespace std;

struct DLLData {
	DLLData() {
		cout << "Введите строку  ";
		cin >> this->s;
		cout << "Введите число";
		cin >> this->i;
	}
	DLLData(string s, int i) {
		this->s = s;
		this->i = i;
	}
	DLLData(DLLData& data) {
		this->i = data.i;
		this->s = data.s;
	}
	string s;
	int i;
	void print() {
		cout << "Строка: " << this->s << endl
			<< "Число: " << this->i << endl;
	}
};
struct DLLElement {
	//Указатель на предыдущий в цепочке элемент
	shared_ptr<DLLElement> prev;
	//Указатель на следующий в цепочке элемент
	shared_ptr<DLLElement> next;
	//Данные, которые ма храним в элементе
	shared_ptr<DLLData> data;
	DLLElement() {
		this->data = make_shared<DLLData>();
	}
	DLLElement(string s, int i) {
		this->data = make_shared<DLLData>(s, i);
	}
	DLLElement(
		shared_ptr<DLLElement> prev,
		shared_ptr<DLLElement> next
	) {
		this->prev = prev;
		this->next = next;
		this->data = make_shared<DLLData>();
	}
	DLLElement(
		shared_ptr<DLLElement> prev,
		shared_ptr<DLLElement> next,
		string s,
		int i
	) {
		this->prev = prev;
		this->next = next;
		this->data = make_shared<DLLData>(s, i);
	}

};
class DLList {
	//Элемент, на который мы ссылаемся из класса
	shared_ptr<DLLElement> elem;
	void goToHead();
	void goToTail();
	void stepToLeft();
	void stepToRight();
	void checkHaveElement();
public:
	DLList();
	DLList(string s, int i);
	bool isEmpty();
	void addToHead(string s, int i);
	void addToTail(string s, int i);
	void addInside(string s, int iData, int pos);
	string getString();

	void deleteElem(int choise);

};
void DLList::goToHead()
{
	this->checkHaveElement();
	while (this->elem->prev != nullptr)
	{
		this->elem = this->elem->prev;
	}
}
void DLList::goToTail()
{
	this->checkHaveElement();
	while (this->elem->next != nullptr) {
		this->elem = this->elem->next;
	}

}
void DLList::stepToLeft()
{
	checkHaveElement();
	if (this->elem->prev != nullptr) {
		this->elem = this->elem->prev;
	}
}
void DLList::stepToRight()
{
	checkHaveElement();
	if (this->elem->next != nullptr) {
		this->elem = this->elem->next;
	}
}
void DLList::checkHaveElement()
{
	if (this->elem == nullptr) {
		throw runtime_error("Нет элемента");
	}
}
//Конструктор по умолчанию
DLList::DLList()
{
	this->elem = nullptr;
}
//Конструктор с параметром для заполнения данными
DLList::DLList(string s, int i)
{
	this->elem = make_shared<DLLElement>(s, i);
}
//Проверка на то, есть ли хоть один элемент
bool DLList::isEmpty()
{
	if (this->elem == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
//Добавление элемента в голову
void DLList::addToHead(string s, int i)
{
	shared_ptr<DLLElement> newElem = make_shared<DLLElement>(s, i);
	//если ни одного элемента
	if (this->isEmpty()) {
		//Записываем данные в текущий
		this->elem = newElem;
		return;
	}
	this->goToHead();

	newElem->next = this->elem;
	this->elem->prev = newElem;
	this->goToHead();
}
//Добавление элемента в хвост
void DLList::addToTail(string s, int i)
{
	shared_ptr<DLLElement> newElem = make_shared<DLLElement>(s, i);
	//Если список пустой, помещаем данные прямо в первый элемент
	if (this->isEmpty()) {
		this->elem = newElem;
		return;
	}
	this->goToTail();
	this->elem->next = newElem;
	newElem->prev = this->elem;


}
// Потом дописать
string DLList::getString()
{

	this->goToHead();
	string result = "";
	while (this->elem->next != nullptr) {
		result += this->elem->data->s + " ";
		this->stepToRight();
	}
	result += this->elem->data->s + " ";
	return result;
}


//Добавление элемента внутрь списка
void DLList::addInside(string s, int iData, int pos)
{
	this->goToHead();
	for (int i = 1; i <= pos && this->elem->next != nullptr; i) {
		this->elem = this->elem->next;
	}
	shared_ptr<DLLElement> newElem = make_shared<DLLElement>(s, iData);
	newElem->next = this->elem->next;
	newElem->prev = this->elem;
	this->elem->next->prev = newElem;
	this->elem->next = newElem;
}
/// <summary>
/// Удаление элемента из списка
/// </summary>
/// <param name="chiose">Выбор действия. | 1. Удалить в голове | 0. Удалить в хвосте.| Число - удалить где-то в средине</param>
void DLList::deleteElem(int choise)
{
	//Если принято число меньше ноля, просто выдаём ошибку
	if (choise < 0) {
		throw runtime_error("Ошибка удаления.\nЧисло меньше 0");
	}
	//Если не существует ни одного элемента, выдаём ошибку.
	checkHaveElement();
	//Если элемент только один, удаляем его
	if (this->elem->next == nullptr && this->elem->prev == nullptr) {
		this->elem = nullptr;
		return;
	}
	//Остался только случай, когда элементов несколько
	switch (choise)
	{
		//Удалить в хвосте
	case 0: {
		//Создаём временный указатель, 

		//Переходим к предпоследнему элементу
		this->goToTail();
		this->stepToLeft();

		//Удаляем указатель на предпоследний элемент
		this->elem->next->prev = nullptr;
		this->elem->next = nullptr;
		//Удаляем указатель на последний элемент
	}
		  break;
		  //Удалить в голове
	case 1:
		//Переписываем в голову данные из правого элемента
		this->goToHead();
		this->stepToRight();
		this->elem->prev->next = nullptr;
		this->elem->prev = nullptr;
		break;
	default:
		this->goToHead();
		for (int i = 2; i < choise && this->elem->next != nullptr; i++) {
			this->elem = this->elem->next;
		}
		if (this->elem->next == nullptr) {
			this->deleteElem(0);
			return;

		}
		this->elem->next->next->prev = elem;
		elem->next = elem->next->next;
		break;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	DLList eva("Ольга",1);
	try {
		eva.addToTail("Антон",2);
		eva.addToTail("Иван", 3);
		eva.addToTail("Павел", 4);


		eva.deleteElem(1);
		cout << eva.getString();
	}
	catch (exception ex) {
		cout << ex.what();
	}


	return 0;
}