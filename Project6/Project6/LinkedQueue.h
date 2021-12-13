#include "Node.h"
class LinkedQueue {
public:
	Node* front;
	Node* rear;

	LinkedQueue() :front(NULL), rear(NULL) {}
	~LinkedQueue() { while (!isEmpty()) delete dequeue(); }

	bool isEmpty() { return front == NULL; }

	void enqueue(Node* p) {
		if (isEmpty()) front = rear = p;
		else {
			rear->setLink(p);
			rear = p;
		}
	}
	Node* dequeue() {
		if (isEmpty()) return NULL;
		Node* p = front;
		front = front->link;
		if (front == NULL)rear = NULL;
		return p;
	}

	Node* peek() { return front; }
};