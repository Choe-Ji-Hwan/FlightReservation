#pragma once
//--------------------------------------------------------------------
//
//	doubly linked and sorted list
//	the Doubly Linked and Sorted List ADT of 2017112104 최지환
//
//--------------------------------------------------------------------

#include <new>
#include <stdexcept>

using namespace std;

template < class DT >         // Forward declaration of the List class
class List;

template < class DT >
class ListNode                // Facilitator class for the List class
{
public:
	DT return_dataItem();		// 노드의 정보 추출
private:
	
	// Constructor
	ListNode(const DT &data,
		ListNode *priorPtr, ListNode *nextPtr);

	// Data members
	DT dataItem;        // List data item
	ListNode *prior,    // Pointer to the previous data item
		*next;     // Pointer to the next data item

	friend class List<DT>;
};

//--------------------------------------------------------------------

template < class DT >
class List
{
public:
	// Constructor
	List(int ignored = 0);
	// Copy constructor
	List<DT>(List<DT>& copy);
	// Destructor
	~List();

	// List manipulation operations
	void insertItem(const DT &newDataItem)    // Insert after cursor
		throw (bad_alloc);
	void remove()
		throw (logic_error);
	void deleteItem(DT &name)                           // Remove data item
		throw (logic_error);
	void replace(const DT &newDataItem)   // Replace data item
		throw (logic_error);
	void clear();                           // Clear list
	ListNode<DT>* return_head() const;		// Return head
	ListNode<DT>* get_cursor_next_node() const;	// Get next cursor node
	ListNode<DT>* get_cursor_prior_node() const;// Get prior cursor node

	// List status operations
	bool isEmpty() const;                   // List is empty
	bool isFull() const;                    // List is full

	// List iteration operations
	void gotoBeginning()                    // Go to beginning
		throw (logic_error);
	void gotoEnd()                          // Go to end
		throw (logic_error);
	bool gotoNext();                        // Go to next data item
	bool gotoPrior();                       // Go to prior data item
	DT& getCursor() const                    // Return data item
		throw (logic_error);

	// Output the list structure -- used in testing/debugging
	void showStructure() const;

	friend bool operator >= (DT& d1, DT& d2);
	friend bool operator == (DT& d1, DT& d2);

private:

	// Data members
	ListNode<DT> *head,     // Pointer to the beginning of the list
		*cursor;   // Cursor pointer
};