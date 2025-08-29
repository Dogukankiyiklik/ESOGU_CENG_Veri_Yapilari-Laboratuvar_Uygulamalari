#include "Deque.h"
#include <stdexcept>

using namespace std;

///------------------------------------------------------
/// Default constructor
/// 
Deque::Deque() : head(nullptr), tail(nullptr), noOfItems(0) {} //end-Deque

///------------------------------------------------------
/// Destructor
/// 
// !!!!!!!!!! Kuyruktaki t�m elemanlar d�ng� ile silinebilir. Bu y�zden bu i�lem O(n) zamanda ger�ekle�ir. !!!!!!!!!!
Deque::~Deque() {
	while (head != nullptr) {
		DequeNode* temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
	noOfItems = 0;
} //end-~Deque

///------------------------------------------------------
/// Adds a new item to the front of the Deque
/// 
void Deque::AddFront(int item) {
	DequeNode* newNode = new DequeNode(item);
	if (IsEmpty()) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	noOfItems++;
} //end-AddFront

///------------------------------------------------------
/// Adds a new item to the end of the Deque
/// 
void Deque::AddRear(int item) {
	DequeNode* newNode = new DequeNode(item);
	if (IsEmpty()) {
		head = tail = newNode;
	}
	else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	noOfItems++;
} //end-AddRear

///------------------------------------------------------
/// Remove and return the item at the front of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveFront() {
	if (IsEmpty()) {
		throw out_of_range("Deque is empty");
	}

	int frontItem = head->item;
	DequeNode* temp = head;

	if (head == tail) {
		head = tail = nullptr;
	}
	else {
		head = head->next;
		head->prev = nullptr;
	}

	delete temp;
	noOfItems--;

	return frontItem;
} //end-RemoveFront

///------------------------------------------------------
/// Remove and return the item at the rear of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveRear() {
	if (IsEmpty()) {
		throw out_of_range("Deque is empty");
	}

	int rearItem = tail->item;
	DequeNode* temp = tail;

	if (head == tail) {
		head = tail = nullptr;
	}
	else {
		tail = tail->prev;
		tail->next = nullptr;
	}

	delete temp;
	noOfItems--;

	return rearItem;
} //end-RemoveRear

///------------------------------------------------------
/// Return the item at the front of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Front() {
	if (IsEmpty()) {
		throw out_of_range("Deque is empty");
	}
	return head->item;
} //end-Front

///------------------------------------------------------
/// Return the item at the rear of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Rear() {
	if (IsEmpty()) {
		throw out_of_range("Deque is empty");
	}
	return tail->item;
} //end-Rear