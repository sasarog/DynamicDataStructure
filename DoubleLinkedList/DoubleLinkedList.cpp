#include <iostream>
using namespace std;
class DLList {
	//��������� �� ���������� � ������� �������
	shared_ptr<DLList> prev = nullptr;
	//��������� �� ��������� � ������� �������
	shared_ptr<DLList> next = nullptr;
	//������, ������� �� ������ � ��������
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
//����������� �� ���������
DLList::DLList()
{
	this->next = nullptr;
	this->data = nullptr;
}
//����������� � ���������� ��� ���������� �������
DLList::DLList(string s)
{
	this->data = make_shared<string>(s);
}
//�������� �� ��, ���� �� ���� ���� �������
bool DLList::isEmpty()
{
	if (this->data == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
//���������� �������� � ������
void DLList::addToHead(string s)
{
	//���� �� ������ ��������
	if (this->isEmpty()) {
		//���������� ������ � �������
		this->data = make_shared<string>(s);
		return;
	}
	if (this->next == nullptr) {
		this->next = make_shared<DLList>(s);
		this->next->prev = shared_ptr<DLList>(this);
	}
	else {
		//���� ������� ����������, ���������� ������ ������
		shared_ptr<DLList> tmp = this->next;
		//������ ����� ������� ������
		this->next = make_shared<DLList>(*this->data);
		//� ����� ������ ���������� ������ ������
		this->next->next = tmp;
		//� ������, ������� ��� ������, ����������� ���������� ��������� �� ����
		tmp->prev = this->next;
		//� ����� �������� ��������� �� ���������� ����������� �� ��������
		this->next->prev = shared_ptr<DLList>(this);
		//� ������� ������� ����� ������
		this->data = make_shared<string>(s);
	}
}
//���������� �������� � �����
void DLList::addToTail(string s)
{
	//���� ������ ������, �������� ������ ����� � ������ �������
	if (this->isEmpty()) {
		this->data = make_shared<string>(s);
		return;
	}
	//���� �������� ����������, �� ���������� ���, ���������� ����
	if (this->next == nullptr) {
		this->next = make_shared<DLList>(s);
		this->next->prev = shared_ptr<DLList>(this);
	}
	else {
		//���� ��������� ���� ����, ��� �� ������� � ����� �����
		shared_ptr<DLList> tmp = this->next;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		//����� ������ � �����, ��������� ����� �������
		tmp->next = make_shared<DLList>(s);
		//� ����� ������� ���������� ���������, ������� ��� �� ����� ���������
		tmp->next->prev = tmp;
	}
}
string DLList::getString()
{

	//���� ������ ���, ���������� ����� ������
	if (this->data == nullptr) {
		return "";
	}
	//���� ���� ������ �������� �������, ���������� ������ ������ �� ����
	if (this->next == nullptr) {
		return *this->data; 
	}
	//������ ��������� ���������, ����� ������ �� ������
	shared_ptr<DLList> tmp = this->next;
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
}


//���������� �������� ������ ������
void DLList::addInside(string s, int pos)
{
	//��� ��� � � ���������� � �����
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
		//��� �� ������ �� ��� ���, ���� �� ����� �� ������ �������, ��� �� ������
		for (
			int i = 2;
			i < pos && tmp->next != nullptr;
			i++, tmp = tmp->next
			);
		//���� ��������� ������� �� ������, ��������� ����� �����
		if (tmp->next != nullptr) {
			//������ �����	�������
			shared_ptr<DLList> newElem = make_shared<DLList>(s);
			//� ������ ��������� ����������� ������ �������
			newElem->next = tmp->next;
			//� ������� �������, ������� �����, ����������� ��� �����
			tmp->next = newElem;

			newElem->prev = tmp;
			newElem->next->prev = newElem;
		}
		else {
			//���� ������, ������ ��������� � �����
			tmp->next = make_shared<DLList>(s);
			tmp->next->prev = tmp;
		}
	}


}
/// <summary>
/// �������� �������� �� ������
/// </summary>
/// <param name="chiose">����� ��������. | 1. ������� � ������ | 0. ������� � ������.| ����� - ������� ���-�� � �������</param>
void DLList::deleteElem(int choise)
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
		shared_ptr<DLList> tmp = this->next;
		//��������� � �������������� ��������
		while (tmp->next->next != nullptr)
		{
			tmp = tmp->next;
		}
		//������� ��������� �� ������������� �������
		tmp->next->prev = nullptr;
		//������� ��������� �� ��������� �������
		tmp->next = nullptr;

	}
		  break;
		  //������� � ������
	case 1:
		//������������ � ������ ������ �� ������� ��������
		this->data = this->next->data;
		//� ���������� �������� ������� ��������� �� ������
		this->next->prev = nullptr;
		//���� ������ � ������ ������� ����������
		if (this->next->next != nullptr) {
			//����������� � ���� ��������� �� ��������, ��������� ������ ��������
			this->next->next->prev = shared_ptr<DLList>(this);
		}
		//� �������� ����������� ��������� �� ��������� �������, ������� ��� � �������
		this->next = this->next->next;//���� ���� �� ��� ����� nullptr

		break;
	default:
		//������ ����� ��������� �� ������ (�� ������ �������)
		shared_ptr<DLList> tmp = this->next;
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
		tmp->next->next->prev = tmp;
		tmp->next = tmp->next->next;
		break;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	DLList eva("�����");
	try {
		eva.addToTail("�����");
		eva.addToTail("����");
		eva.addToTail("�����");


		eva.deleteElem(2);
		cout << eva.getString();
	}
	catch (exception ex) {
		cout << ex.what();
	}


	return 0;
}