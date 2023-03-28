#pragma once
#include <iostream>
using namespace std;
struct chel {
	string fio;
	int age;
	int rost;
	//����������� �� ���������.
	chel() {
		this->fio = "";
		this->age = 0;
		this->rost = 0;
	};
	//����������� � ����������
	chel(string fio, int age, int rost) {
		this->age = age;
		this->fio = fio;
		this->rost = rost;
	}
	//����� � ������� ������ ��������
	void print() {
		cout <<
			this->fio << " " <<
			this->age << " " <<
			this->rost << " " <<
			endl;
	}
};
class LinkedList: public enable_shared_from_this<LinkedList> {
	//��������� �� ��������� � ������� �������
	shared_ptr<LinkedList> next = nullptr;
	//������, ������� �� ������ � ��������
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
//����������� �� ���������
LinkedList::LinkedList()
{
	this->next = nullptr;
	this->data = nullptr;
}
inline LinkedList::LinkedList(int eva)
{
	this->data = nullptr;
}
//����������� � ���������� ��� ���������� �������
LinkedList::LinkedList(string s, int age, int rost)
{
	this->data = make_shared<chel>(s, age, rost);
}
//�������� �� ��, ���� �� ���� ���� �������
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
//���������� �������� � ������
void LinkedList::addToHead(string s, int age, int rost)
{
	//���� �� ������ ��������
	if (this->isEmpty()) {
		//���������� ������ � �������
		this->data = make_shared<chel>(s,age,rost);
		return;
	}
	if (this->next == nullptr) {
		this->next = make_shared<LinkedList>(s, age, rost);
	}
	else {
		//���� ������� ����������, ���������� ������ ������
		shared_ptr<LinkedList> tmp = this->next;
		//������ ����� ������� ������
		this->next = make_shared<LinkedList>(this->data);
		//� ����� ������ ���������� ������ ������
		this->next->next = tmp;
		//� ������� ������� ����� ������
		this->data = make_shared<chel>(s, age, rost);


	}
}
//���������� �������� � �����
void LinkedList::addToTail(string s, int age, int rost)
{
	//���� ������ ������, �������� ������ ����� � ������ �������
	if (this->isEmpty()) {
		this->data = make_shared<chel>(s, age, rost);
		return;
	}
	//���� �������� ����������, �� ���������� ���, ���������� ����
	if (this->next == nullptr) {
		this->next = make_shared<LinkedList>(make_shared<chel>(s,age,rost));
	}
	else {
		//���� ��������� ���� ����, ��� �� ������� � ����� �����
		shared_ptr<LinkedList> tmp = this->next;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		//����� ������ � �����, ��������� ����� �������
		tmp->next = make_shared<LinkedList>(this->data);
	}
}
string LinkedList::getString()
{
	return "";
	/*
	//���� ������ ���, ���������� ����� ������
	if (this->data == nullptr) {
		return "";
	}
	//���� ���� ������ �������� �������, ���������� ������ ������ �� ����
	if (this->next == nullptr) {
		return *this->data;
	}
	//������ ��������� ���������, ����� ������ �� ������
	shared_ptr<List> tmp = this->next;
	//��������� ������ �� ��������� ��������
	string result = *this->data + "\n";
	//���� �� ����� �� ������
	while (tmp->next != nullptr)
	{
		//��������� � �������� ������ ��� ������ �� ������� ��������
		result += *tmp->data + "\n";
		//��������� � ���������� ��������
		tmp = tmp->next;
	}
	//����������� ��������� �������
	result += *tmp->data;
	//���������� �������� ������������ ������
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


//���������� �������� ������ ������
void LinkedList::addInside(string s, int pos)
{
	////��� ��� � � ���������� � �����
	//if (this->isEmpty()) {
	//	this->addToHead(s, , );
	//	return;
	//}
	//if (this->next == nullptr) {
	//	this->next = make_shared<List>(s);
	//}
	//else {
	//	shared_ptr<List> tmp = this->next;
	//	//��� �� ������ �� ��� ���, ���� �� ����� �� ������ �������, ��� �� ������
	//	for (
	//		int i = 2;
	//		i < pos && tmp->next != nullptr;
	//		i++, tmp = tmp->next
	//		);
	//	//���� ��������� ������� �� ������, ��������� ����� �����
	//	if (tmp->next != nullptr) {
	//		//������ �����	�������
	//		shared_ptr<List> newElem = make_shared<List>(s);
	//		//� ������ ��������� ����������� ������ �������
	//		newElem->next = tmp->next;
	//		//� ������� �������, ������� �����, ����������� ��� �����
	//		tmp->next = newElem;
	//	}
	//	else {
	//		//���� ������, ������ ��������� � �����
	//		tmp->next = make_shared<List>(s);
	//	}
	//}


}
/// <summary>
/// �������� �������� �� ������
/// </summary>
/// <param name="chiose">����� ��������. | 1. ������� � ������ | 0. ������� � ������.| ����� - ������� ���-�� � �������</param>
void LinkedList::deleteElem(int choise)
{
	//���� ������� ����� ������ ����, ������ ����� ������
	if (choise < 0) {
		throw runtime_error("������ ��������.\n����� ������ 0");
	}
	//���� �� ���������� �� ������ ��������, ����� ������.
	if (this->data == nullptr) {
		throw runtime_error("������ ��������.\n����������� �������� � ������");
	}
	//���� ������� ������ ����, ������� ���
	if (this->next == nullptr) {
		this->data = nullptr;
		return;
	}
	//������� ������ ������, ����� ��������� ���������
	switch (choise)
	{
		//������� � ������
	case 0: {
		//������ ��������� ���������, 
		//����� ������� � �������������� ��������
		shared_ptr<LinkedList> tmp = this->next;
		//��������� � �������������� ��������
		while (tmp->next->next != nullptr)
		{
			tmp = tmp->next;
		}
		//������� ��������� �� ��������� �������
		tmp->next = nullptr;

	}
		  break;
		  //������� � ������
	case 1:
		//������������ � ������ ������ �� ������� ��������
		this->data = this->next->data;
		this->next = this->next->next;

		break;
	default:
		//������ ����� ��������� �� ������ (�� ������ �������)
		shared_ptr<LinkedList> tmp = this->next;
		//��� ������ �� ��������, ������� ����� �������
		for (int i = 2; i < choise && tmp->next != nullptr; i++) {
			tmp = tmp->next;
		}
		//���� ��� ����������, ��� ����� �� ����������, ������� ���
		if (tmp->next == nullptr) {
			this->deleteElem(0);
			return;
		}
		//���� ����� �� �� ����������, ������������ ��������� ���, 
		//����� ���������� �� �������� ������ ������ 
		tmp->next = tmp->next->next;
		break;
	}
}

inline void LinkedList::deleteElem(string name)
{
	if (this->data == nullptr) {
		throw runtime_error("������ ��������: ����������� �������� � ������\n");
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
