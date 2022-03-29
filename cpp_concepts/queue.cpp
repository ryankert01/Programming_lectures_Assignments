#include<iostream>
using namespace std;

size_t max = -1;

template < class T >
class Node {
public:
	using value_type = T;
	using size_type = unsigned int;
	using iterator = value_type*;
	int data;
	Node* link;
};

template < class T >
class queue {
public:
	using value_type = T;
	using size_type = unsigned int;
	using iterator = value_type*;
	queue() 
		:
		head(), last()
	{
		head = last = new Node < T >;
		head->link = nullptr;
		head->data = -1;
	}
	~queue() {
		Node< T >* tra = this->head;
		Node< T >* del = this->head;
		while (tra) {
			tra = tra->link;
			delete del;
			del = tra;
		}
	}

	void enqueue(int a) {
		Node< T >* prev = last;
		last = new Node< T >;
		last->data = a;
		last->link = nullptr;
		if (prev)prev->link = last;
		else prev = last;
	}

	void dequeue() {
		if(head->link)
		if (head->link->data != -1 and head->link->data != max) {
			Node< T >* de = head->link;
			head->link = de->link;
			delete de;
		}
	}

	void printQueue() {
		Node< T >* prev = head->link;
		while (prev) {
			cout << prev->data << " ";
			prev = prev->link;
		}
		cout << endl;
	}
private:
	Node< T >* head;
	Node< T >* last;
};

int main() {
	queue< size_t >a;
	for (int i = 1; i < 12; i++)
		a.enqueue(i);
	a.printQueue();
	for (int i = 1; i < 5; i++)
		a.dequeue();
	a.printQueue();
	for (int i = 12; i < 19; i++)
		a.enqueue(i);
	a.printQueue();
}
