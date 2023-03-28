#include <iostream>
#include "LinkedList.h"
using namespace std;
//Структура, хранящая данные о человеке

class HashTable {
	//Размер массива
	int size;
	//Указатель на массив
	shared_ptr<LinkedList[]> mas;
	//Функция по высчитыванию хеш-значения
	int hashValue(string fio);
public:
	HashTable();
	HashTable(int size);
	void add(string fio, int age, int rost);
	void print(string fio);
	void printAll();
	void remove(string fio);
};
HashTable::HashTable()
{
	this->size = 0;
	this->mas = nullptr;
}
HashTable::HashTable(int size)
{
	this->size = size;
	//this->mas = make_shared<List[]>(new List[size],std::default_delete<List[]>());
	//this->mas = make_shared<LinkedList[]>(size);
	//this->mas = make_shared<LinkedList[]>();
	this->mas = shared_ptr< LinkedList[] >( new LinkedList[size]);
}
void HashTable::add(string fio, int age, int rost)
{
	//Узнаём, в какой элемент массива записывать необходимое значение
	int number = hashValue(fio);
	//Зписываем в элемент массива значения
	mas[number].addToTail(fio, age, rost);

}
void HashTable::print(string fio)
{
	//Выводим элемент массива, который искали
	mas[hashValue(fio)].find(fio)->print();
}
int HashTable::hashValue(string fio)
{
	//Переменная для возвращения значения
	int result = 0;
	//Для формирования хеш-значения будем использовать строку
	while (fio.length() > 0) {
		//Любым алгоритмом формируем выходное значение
		result += pow(fio[0], 2);
		//Поскольку в это алгоритме берём ASCII коды каждой буквы,
		//отрезаем от строки по букве
		fio.erase(0, 1);
	}
	//Если выходное значение получилось больше, чем размер массива,
	//уменьшаем значение выходной переменной до тех пор, пока
	//значение не станет меньше, чем размер массива
	while (result >= this->size) {
		result %= this->size;
	}
	//Возвращаем результат
	return result;
	//Сам алгоритм, по которому высчитывается хеш-значение может быть любым,
	//который придёт вам в голову. Главное чтобы по итогу возвращалось число,
	// которое будет в диапазоне от 0 до размера массива
}
//Вывод всего массива
void HashTable::printAll()
{
	
	for (int i = 0; i < this->size; i++) {
		cout << i + 1 << ": \n";
		mas[i].printAllFromLinkedList();
		cout << "\n";
	}
}
void HashTable::remove(string fio)
{
	mas[hashValue(fio)].deleteElem(fio);
}
int main() {
	setlocale(LC_ALL, "Russian");
	HashTable eva(7);
	try {
		eva.add("Adam", 12, 3652);
		eva.add("qwer", 43, 3232);
		eva.add("asd", 54, 3352);
		eva.add("xcv", 1652, 3872);
		eva.add("tyu", 1762, 32);
		eva.add("Read", 12, 32);
		eva.add("Harek", 12, 32);

		eva.print("Adam");
		eva.print("Read");
		eva.printAll();
		eva.remove("Adam");
		eva.remove("Read");
		eva.remove("Read");
		eva.printAll();
	}

	catch (exception ex) {
		cerr << ex.what();
	}
}