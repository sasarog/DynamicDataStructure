#include <iostream>
#include "LinkedList.h"
using namespace std;
//���������, �������� ������ � ��������

class HashTable {
	//������ �������
	int size;
	//��������� �� ������
	shared_ptr<LinkedList[]> mas;
	//������� �� ������������ ���-��������
	int hashValue(string fio);
public:
	HashTable();
	HashTable(int size);
	void add(string fio, int age, int rost);
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
	//this->mas = make_shared<List[]>(new List[size],std::default_delete<List[]>());
	//this->mas = make_shared<LinkedList[]>(size);
	//this->mas = make_shared<LinkedList[]>();
	this->mas = shared_ptr< LinkedList[] >( new LinkedList[size]);
}
void HashTable::add(string fio, int age, int rost)
{
	//�����, � ����� ������� ������� ���������� ����������� ��������
	int number = hashValue(fio);
	//��������� � ������� ������� ��������
	mas[number].addToTail(fio, age, rost);

}
void HashTable::print(string fio)
{
	//������� ������� �������, ������� ������
	mas[hashValue(fio)].find(fio)->print();
}
int HashTable::hashValue(string fio)
{
	//���������� ��� ����������� ��������
	int result = 0;
	//��� ������������ ���-�������� ����� ������������ ������
	while (fio.length() > 0) {
		//����� ���������� ��������� �������� ��������
		result += pow(fio[0], 2);
		//��������� � ��� ��������� ���� ASCII ���� ������ �����,
		//�������� �� ������ �� �����
		fio.erase(0, 1);
	}
	//���� �������� �������� ���������� ������, ��� ������ �������,
	//��������� �������� �������� ���������� �� ��� ���, ����
	//�������� �� ������ ������, ��� ������ �������
	while (result > this->size) {
		result %= 22;
	}
	//���������� ���������
	return result;
	//��� ��������, �� �������� ������������� ���-�������� ����� ���� �����,
	//������� ����� ��� � ������. ������� ����� �� ����� ������������ �����,
	// ������� ����� � ��������� �� 0 �� ������� �������
}
//����� ����� �������
void HashTable::printAll()
{
	
	for (int i = 0; i < this->size; i++) {
		cout << i + 1 << ": ";
		
	}
}
int main() {
	HashTable eva(50);
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
}