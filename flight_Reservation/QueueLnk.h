#pragma once
//--------------------------------------------------------------------
//
//	linked queue
//	the Linked Queue ADT of 2017112104 √÷¡ˆ»Ø
//
//--------------------------------------------------------------------

template < class QE >
class Queue;

template < class QE >
class QueueNode;

template < class QE >
class Queue
{
public:

	// Constructor
	Queue(int ignored = 0);

	// Destructor
	~Queue();

	// Queue manipulation operations
	void enqueue(const QE &newElement);    // Enqueue element
	QE& dequeue();                            // Dequeue element
	QueueNode<QE>* return_front() const;		 // Return front
	QueueNode<QE>* return_rear() const;			 // Return rear
	void clear();                            // Clear queue
	void find_remove(QE& item);
	bool find(QE& item);

	// Queue status operations
	int empty() const;                       // Queue is empty
	int full() const;                        // Queue is full

	// Output the queue structure -- used in testing/debugging
	void showStructure() const;

	friend bool operator != (QE& q1, QE& q2);
private:

	// Data members
	QueueNode<QE> *front,   // Pointer to the front element
		*rear;    // Pointer to the rear element
};

template < class QE >
class QueueNode               // Facilitator class for the Queue class
{
private:

	// Constructor
	QueueNode(const QE &elem, QueueNode *nextPtr);

	// Data members
	QE element;          // Queue element
	QueueNode *next;     // Pointer to the next element

	friend class Queue<QE>;
};

//--------------------------------------------------------------------