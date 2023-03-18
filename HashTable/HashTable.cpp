#include <iostream>
using namespace std;
struct chelovek {
	string fio;
	int age;
	int rost;
	int heart;
	chelovek() {
		this->fio = "";
	};
	chelovek(string fio, int age, int rost, int heart) {
		this->age = age;
		this->fio = fio;
		this->rost = rost;
		this->heart = heart;
	}
	void print() {
		cout <<
			this->fio << " " <<
			this->age << " " <<
			this->rost << " " <<
			this->heart << endl;
	}
};
class HashTable {
	int size;
	shared_ptr<chelovek[]> mas;
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
	int number = hashValue(fio);
	mas[number].age = age;
	mas[number].fio = fio;
	mas[number].rost = rost;
	mas[number].heart = heart;

}
void HashTable::print(string fio)
{
	mas[hashValue(fio)].print();
}
int HashTable::hashValue(string fio)
{
	int result = 0;
	while (fio.length() > 0) {
		result += pow(fio[0], 2);
		fio.erase(0, 1);
	}
	while (result > this->size) {
		result %= 22;
	}
	return result;
}
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
	eva.add("Readan", 12, 32, 433223);
	eva.add("Harek", 12, 32, 4231456);
	eva.print("Adam");
	eva.print("Readan");
	eva.printAll();
}