#include <iostream>
using namespace std;
//Структура, хранящая данные о человеке
struct chelovek {
	string fio;
	int age;
	int rost;
	int heart;
	//Конструктор по умолчанию.
	chelovek() {
		this->fio = "";
		this->age = 0;
		this->rost = 0;
		this->heart = 0;
	};
	//Конструктор с параметром
	chelovek(string fio, int age, int rost, int heart) {
		this->age = age;
		this->fio = fio;
		this->rost = rost;
		this->heart = heart;
	}
	//Вывод в консоль одного элемента
	void print() {
		cout <<
			this->fio << " " <<
			this->age << " " <<
			this->rost << " " <<
			this->heart << endl;
	}
};
class HashTable {
	//Размер массива
	int size;
	//Указатель на массив
	shared_ptr<chelovek[]> mas;
	//Функция по высчитыванию хеш-значения
	int hashValue(string fio);
public:
	HashTable();
	HashTable(int size);
	void add(string fio, int age, int rost, int heart);
	void print(string fio);
	void printAll();
};
HashTable::HashTable()
{
	this->size = 0;
	this->mas = nullptr;
}
HashTable::HashTable(int size)
{
	this->size = size;
	this->mas = make_shared<chelovek[]>(size);
}
void HashTable::add(string fio, int age, int rost, int heart)
{
	//Узнаём, в какой элемент массива записывать необходимое значение
	int number = hashValue(fio);
	//Зписываем в элемент массива значения
	mas[number].age = age;
	mas[number].fio = fio;
	mas[number].rost = rost;
	mas[number].heart = heart;

}
void HashTable::print(string fio)
{
	//Выводим элемент массива, который искали
	mas[hashValue(fio)].print();
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
	while (result > this->size) {
		result %= 22;
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
		cout << i + 1 << ": ";
		mas[i].print();
	}
}
int main() {
	HashTable eva(50);
	eva.add("Adam", 12, 3652, 4543);
	eva.add("qwer", 43, 3232, 423);
	eva.add("asd", 54, 3352, 453);
	eva.add("xcv", 1652, 3872, 43);
	eva.add("tyu", 1762, 32, 763);
	eva.add("Read", 12, 32, 433223);
	eva.add("Harek", 12, 32, 4231456);
	eva.print("Adam");
	eva.print("Read");
	eva.printAll();
}