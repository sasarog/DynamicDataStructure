#include <iostream>
using namespace std;

struct DLLData {
	DLLData() {
		cout << "������� ������  ";
		cin >> this->s;
		cout << "������� �����";
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
		cout << "������: " << this->s << endl
			<< "�����: " << this->i << endl;
	}
};
struct DLLElement {
	//��������� �� ���������� � ������� �������
	shared_ptr<DLLElement> prev;
	//��������� �� ��������� � ������� �������
	shared_ptr<DLLElement> next;
	//������, ������� �� ������ � ��������
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
	//�������, �� ������� �� ��������� �� ������
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
		throw runtime_error("��� ��������");
	}
}
//����������� �� ���������
DLList::DLList()
{
	this->elem = nullptr;
}
//����������� � ���������� ��� ���������� �������
DLList::DLList(string s, int i)
{
	this->elem = make_shared<DLLElement>(s, i);
}
//�������� �� ��, ���� �� ���� ���� �������
bool DLList::isEmpty()
{
	if (this->elem == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
//���������� �������� � ������
void DLList::addToHead(string s, int i)
{
	shared_ptr<DLLElement> newElem = make_shared<DLLElement>(s, i);
	//���� �� ������ ��������
	if (this->isEmpty()) {
		//���������� ������ � �������
		this->elem = newElem;
		return;
	}
	this->goToHead();

	newElem->next = this->elem;
	this->elem->prev = newElem;
	this->goToHead();
}
//���������� �������� � �����
void DLList::addToTail(string s, int i)
{
	shared_ptr<DLLElement> newElem = make_shared<DLLElement>(s, i);
	//���� ������ ������, �������� ������ ����� � ������ �������
	if (this->isEmpty()) {
		this->elem = newElem;
		return;
	}
	this->goToTail();
	this->elem->next = newElem;
	newElem->prev = this->elem;


}
// ����� ��������
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


//���������� �������� ������ ������
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
	checkHaveElement();
	//���� ������� ������ ����, ������� ���
	if (this->elem->next == nullptr && this->elem->prev == nullptr) {
		this->elem = nullptr;
		return;
	}
	//������� ������ ������, ����� ��������� ���������
	switch (choise)
	{
		//������� � ������
	case 0: {
		//������ ��������� ���������, 

		//��������� � �������������� ��������
		this->goToTail();
		this->stepToLeft();

		//������� ��������� �� ������������� �������
		this->elem->next->prev = nullptr;
		this->elem->next = nullptr;
		//������� ��������� �� ��������� �������
	}
		  break;
		  //������� � ������
	case 1:
		//������������ � ������ ������ �� ������� ��������
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
	DLList eva("�����",1);
	try {
		eva.addToTail("�����",2);
		eva.addToTail("����", 3);
		eva.addToTail("�����", 4);


		eva.deleteElem(1);
		cout << eva.getString();
	}
	catch (exception ex) {
		cout << ex.what();
	}


	return 0;
}