#include "QueType.h"

class EmptyQueue {};

class FullQueue {};

template <class ItemType>
QueType<ItemType>::QueType() {
    // Class constructor.
    maxQue = 501;
    front = rear = 0;
    items = new ItemType[maxQue];
}

template <class ItemType>
QueType<ItemType>::QueType(int max) {
    // Parameterized class constructor.
    maxQue = max + 1;
    front = rear = 0;
    items = new ItemType[maxQue];
}

template <class ItemType>
QueType<ItemType>::~QueType() {
    // Class destructor.
    delete[] items;
    front = rear = -1;
}

template <class ItemType>
void QueType<ItemType>::makeEmpty() {
    // Function: Initializes the queue to an empty state.
    // Post: Queue is empty.
    front = rear = 0;
}

template <class ItemType>
bool QueType<ItemType>::isEmpty() const {
    // Function: Determines whether the queue is empty.
    // Post: Function value = (queue is empty)
    return front == rear;
}

template <class ItemType>
bool QueType<ItemType>::isFull() const {
    // Function: Determines whether the queue is full.
    // Post: Function value = (queue is full)
    return ((rear + 1) % maxQue) == front;
}

template <class ItemType>
void QueType<ItemType>::enqueue(ItemType newItem) {
    // Function: Adds newItem to the rear of the queue.
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is at rear of queue.
    if(isFull()) {
        throw QueueOverflow();
    }
    rear = (rear + 1) % maxQue;
    items[rear] = newItem;
}

template <class ItemType>
void QueType<ItemType>::dequeue(ItemType& item) {
    // Function: Removes front item from the queue and returns it
    // in item.
    // Post: If (queue is empty) EmptyQueue exception is thrown
    //       and item is undefined
    //       else front element has been removed from queue and
    //       item is a copy of removed element.
    if(isEmpty()) {
        throw QueueUnderflow();
    }
    front = (front + 1) % maxQue;
    item = items[front];
}

template <class ItemType>
ItemType QueType<ItemType>::peek() {
    // returns the item at the front of the queue without
    // removing the item from the queue
    if(isEmpty()) {
        throw QueueUnderflow();
    }
    return items[(front + 1) % maxQue];
}

template <class ItemType>
int QueType<ItemType>::length() {
    // Function: returns the number of items in the queue
    if(rear >= front) {
        return rear - front;
    }
    // if rear is before front
    return maxQue - front + rear;
}

template <class ItemType>
void QueType<ItemType>::printQueue(ofstream& stream) {
    // displays QueueItems
    if(isEmpty()) {
        stream << "Queue is Empty" << endl;
        return;
    }
    ItemType tempItem;
    int length = this->length();
    for(int i = 0; i < length; i++) {
        dequeue(tempItem);
        stream << tempItem << "\t";
        enqueue(tempItem);
    }
    stream << endl;
}
