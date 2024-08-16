#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
template<typename T>
struct queueNode {
	T data;
	queueNode* next;
	queueNode* Pre;

	queueNode() :next(nullptr), Pre(nullptr) {}
	queueNode(const T& d) :data(d), next(nullptr), Pre(nullptr) {}
};

template <typename T>
class Queue {
private:
	queueNode<T>* front;
	queueNode<T>* rear;
	size_t  size;

	void putFirstqueueNode(const T& val);
	void removeLastQueueNode();
public:
	Queue();
	Queue(const Queue<T>& other);
	~Queue();

	void enQueue(const T& val);
	bool deQueue();

	bool search(const T& val);
	bool displayQueue() const;

	T Top() const;

	size_t QueueSize() const;
	bool isEmpty() const;
	bool isFull() const;

	Queue<T>& operator = (const Queue<T>& other);

};
//CONSTRUCTOR (default,copy) & DESTRUCTOR--------------------------------------
template<typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr), size(0) {
}
template<typename T>
Queue<T>::Queue(const Queue<T>& other) {
	front = rear = nullptr;
	queueNode<T>* temp = other.front;
	while (temp) {
		enQueue(temp->data);
		temp = temp->next;
	}
}
template<typename T>
Queue<T>::~Queue()
{
	queueNode<T>* temp;
	while (front) {
		temp = front->next;
		delete front;
		front = temp;
	}
	rear = nullptr;
}
//DISPLAY----------------------------------------------------------------------
template<typename T>
bool Queue<T>::displayQueue() const
{
	if (!front)
		return false;
	queueNode<T>* temp = front;
	while (temp) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
	return true;
}
template<typename T>
T Queue<T>::Top() const
{
	if (!isEmpty())
		return front->data;
	throw
		out_of_range("ERROR: Invalid Memory Access");
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
template<typename T>
inline size_t Queue<T>::QueueSize() const
{
	return size;
}
template<typename T>
inline bool Queue<T>::isEmpty() const
{
	return !front;
}
template<typename T>
inline bool Queue<T>::isFull() const
{
	return false;
}
//OPERATOR OVERLOADING---------------------------------------------------------
template<typename T>
inline Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	queueNode<T>* temp;
	while (this->front) {//delete current Queue
		temp = this->front->next;
		delete this->front;
		this->front = temp;
	}
	this->rear = nullptr;
	temp = other.front;
	while (temp) {//fill it again with data of other object
		this->enQueue(temp->data);
		temp = temp->next;
	}
	return *this;
}
//ENQUEUE----------------------------------------------------------------------
template<typename T>
void Queue<T>::enQueue(const T& val)
{
	if (!front) {
		putFirstqueueNode(val);
		return;
	}
	queueNode<T>* newqueueNode = new queueNode<T>(val);
	rear->next = newqueueNode;
	newqueueNode->Pre = rear;
	rear = newqueueNode;
	size++;
}
//DEQUEUE----------------------------------------------------------------------
template<typename T>
bool Queue<T>::deQueue()
{
	if (!front)
		return false;
	if (!front->next) {
		removeLastQueueNode();
		return true;
	}
	queueNode<T>* temp = front;
	front = front->next;
	front->Pre = nullptr;
	delete temp;
	size--;
	return true;
}
//SEARCH-----------------------------------------------------------------------
template<typename T>
bool Queue<T>::search(const T& val)
{
	if (!front)
		return false;
	for (queueNode<T>* i = front; i; i = i->next)
		if (i->data == val)
			return true;
	return false;
}
//HELPERS----------------------------------------------------------------------
template<typename T>
void Queue<T>::removeLastQueueNode()
{
	delete front;
	rear = front = nullptr;
	size = 0;
}
template<typename T>
void Queue<T>::putFirstqueueNode(const T& val) {
	queueNode<T>* newqueueNode = new queueNode<T>(val);
	front = rear = newqueueNode;
	size++;
}
#endif // QUEUE_H
