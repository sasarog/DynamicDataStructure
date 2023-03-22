#include <iostream>
using namespace std;
class DLList {
	//Указатель на предыдущий в цепочке элемент
	shared_ptr<DLList> prev = nullptr;
	//Указатель на следующий в цепочке элемент
	shared_ptr<DLList> next = nullptr;
	//Данные, которые ма храним в элементе
	shared_ptr<string> data = nullptr;

public:
	DLList();
	DLList(string s);
	bool isEmpty();
	void addToHead(string s);
	void addToTail(string s);
	void addInside(string s, int pos);
	string getString();

	void deleteElem(int choise);

};
//Конструктор по умолчанию
DLList::DLList()
{
	this->next = nullptr;
	this->data = nullptr;
}
//Конструктор с параметром для заполнения данными
DLList::DLList(string s)
{
	this->data = make_shared<string>(s);
}
//Проверка на то, есть ли хоть один элемент
bool DLList::isEmpty()
{
	if (this->data == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
//Добавление элемента в голову
void DLList::addToHead(string s)
{
	//если ни одного элемента
	if (this->isEmpty()) {
		//Записываем данные в текущий
		this->data = make_shared<string>(s);
		return;
	}
	if (this->next == nullptr) {
		this->next = make_shared<DLList>(s);
		this->next->prev = shared_ptr<DLList>(this);
	}
	else {
		//Если текущий существует, запоминаем бывший справа
		shared_ptr<DLList> tmp = this->next;
		//создаём новый элемент справа
		this->next = make_shared<DLList>(*this->data);
		//в новый справа записываем бывший справа
		this->next->next = tmp;
		//В старом, который был вторым, прописываем предыдущий указатель на новй
		tmp->prev = this->next;
		//В новом элементе указатель на предыдущий прописываем на головной
		this->next->prev = shared_ptr<DLList>(this);
		//В текущий заносим новые данные
		this->data = make_shared<string>(s);
	}
}
//Добавление элемента в хвост
void DLList::addToTail(string s)
{
	//Если список пустой, помещаем данные прямо в первый элемент
	if (this->isEmpty()) {
		this->data = make_shared<string>(s);
		return;
	}
	//Если головной существует, но следующего нет, записываем туда
	if (this->next == nullptr) {
		this->next = make_shared<DLList>(s);
		this->next->prev = shared_ptr<DLList>(this);
	}
	else {
		//Если следующие узлы есть, идём по цепочке в самый хвост
		shared_ptr<DLList> tmp = this->next;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		//Когда прищли в хвост, добавляем новый элемент
		tmp->next = make_shared<DLList>(s);
		//В новый элемент пропсываем указатель, который был до этого хвостовым
		tmp->next->prev = tmp;
	}
}
string DLList::getString()
{

	//Если списка нет, возвращаем устую строку
	if (this->data == nullptr) {
		return "";
	}
	//Если есть только головной элемент, возвращаем данные только из него
	if (this->next == nullptr) {
		return *this->data; 
	}
	//Создаём временный указатель, чтобы ходить по списку
	shared_ptr<DLList> tmp = this->next;
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
}


//Добавление элемента внутрь списка
void DLList::addInside(string s, int pos)
{
	//Тут как и в добавлении в хвост
	if (this->isEmpty()) {
		this->addToHead(s);
		return;
	}
	if (this->next == nullptr) {
		this->next = make_shared<DLList>(s);
		this->next->prev = shared_ptr<DLList>(this);
	}
	else {
		shared_ptr<DLList> tmp = this->next;
		//идём по списку до тех пор, пока не дойдём до нужной позиции, или до хвоста
		for (
			int i = 2;
			i < pos && tmp->next != nullptr;
			i++, tmp = tmp->next
			);
		//Если следующий элемент не пустой, добавляем между двумя
		if (tmp->next != nullptr) {
			//Создаём новый	елемент
			shared_ptr<DLList> newElem = make_shared<DLList>(s);
			//В правый указатель прописываем правый элемент
			newElem->next = tmp->next;
			//В текущий элемент, который слева, прописываем наш новый
			tmp->next = newElem;

			newElem->prev = tmp;
			newElem->next->prev = newElem;
		}
		else {
			//Если пустой, просто добавляем в хвост
			tmp->next = make_shared<DLList>(s);
			tmp->next->prev = tmp;
		}
	}


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
		shared_ptr<DLList> tmp = this->next;
		//Переходим к предпоследнему элементу
		while (tmp->next->next != nullptr)
		{
			tmp = tmp->next;
		}
		//Удаляем указатель на предпоследний элемент
		tmp->next->prev = nullptr;
		//Удаляем указатель на последний элемент
		tmp->next = nullptr;

	}
		  break;
		  //Удалить в голове
	case 1:
		//Переписываем в голову данные из правого элемента
		this->data = this->next->data;
		//У удаляемого элемента удаляем указатель на голову
		this->next->prev = nullptr;
		//Если третий с головы элемент существует
		if (this->next->next != nullptr) {
			//Прописываем в него указатель на головной, поскольку второй удалится
			this->next->next->prev = shared_ptr<DLList>(this);
		}
		//В головной прописываем указатель на следующий элемент, который был у второго
		this->next = this->next->next;//Даже если он был равен nullptr

		break;
	default:
		//Создаём копию указателя из головы (на второй элемент)
		shared_ptr<DLList> tmp = this->next;
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
		tmp->next->next->prev = tmp;
		tmp->next = tmp->next->next;
		break;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	DLList eva("Ольга");
	try {
		eva.addToTail("Антон");
		eva.addToTail("Иван");
		eva.addToTail("Павел");


		eva.deleteElem(2);
		cout << eva.getString();
	}
	catch (exception ex) {
		cout << ex.what();
	}


	return 0;
}