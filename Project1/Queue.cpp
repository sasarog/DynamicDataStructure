//#include <iostream>
//#include <string>
//using namespace std;
//class Queue {
//	shared_ptr< Queue> nextElem = nullptr;
//	int data;
//public:
//	Queue();
//	Queue(int num);
//	void push(int num);
//	string out();
//	int pop();
//};
////Конструктор
//Queue::Queue() {
//	data = 0;
//}
//Queue::Queue(int num) {
//	this->data = num;
//}
////Вывод элементов очереди
//string Queue::out() {
//	return to_string(this->data) + " " + (nextElem != nullptr ? nextElem->out() : "");
//}
////Помещение элемента в очередь
//void Queue::push(int num) {
//	if (nextElem != nullptr) {
//		nextElem->push(num);
//	}
//	else {
//		nextElem = make_shared<Queue>(num);
//	}
//}
//// Извлечение элемента из очереди
//int Queue::pop() {
//	int outData = this->data;
//	this->data = this->nextElem->data;
//	this->nextElem = this->nextElem->nextElem;
//	//Удалять не нужно, shared_ptr удалится сам
//	return outData;
//}
//
//
//
//int main() {
//	Queue queue1;
//	int i;
//	system("chcp 1251");
//	system("cls");
//	for (i = 1; i <= 5; i++)
//		queue1.push(i);
//	cout << "Изначальная очередь ";
//	cout << queue1.out();
//	cout << endl;
//	cout << "введите еще элемент: ";
//	cin >> i;
//	queue1.push(i);
//	cout << "теперь очередь имеет следующий вид" << endl;
//	cout << queue1.out();
//	cout << endl << "удаление элемента";
//	queue1.pop();
//	cout << endl << "текущие данные";
//	cout << queue1.out();
//	cout << endl << "еще одно добавление элемента";
//	queue1.push(i);
//	cout << queue1.out();
//	cout << endl;
//	system("pause");
//	return 0;
//}