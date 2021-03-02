/*
| this is .cpp file of doubly linked and sorted list header
| doubly linked list (by cursor) ADT
|	- insert() + ((sorted)insertItem() + (sorted)deleteItem())
|	= doubly linked and sorted list (by cursor) ADT
| 2017112104 최지환
*/
#include "Listdbl.h"
#include <iostream>

// Constructor
template < class DT>
ListNode<DT>::ListNode(const DT &data,
	// 노드를 만드는 constructor
	ListNode *priorPtr, ListNode *nextPtr) {
	dataItem = data;
	next = nextPtr;
	prior = priorPtr;
}

template<class DT>
DT ListNode<DT>::return_dataItem() {
	return dataItem;
}

// Constructor
template < class DT >
List<DT>::List(int ignored)
{
	// constructor
	head = nullptr;
	cursor = nullptr;
}

template < class DT >
List<DT>::List(List<DT>& copy) {

	List<DT>::gotoPrior();	// 맨 앞으로 커서를 보냄

	while (true) {
		copy.insertItem(List<DT>::getCursor());

		if (List<DT>::get_cursor_next_node() == nullptr)
			break;

		List<DT>::gotoNext();	// 다음 커서로 보냄
	}
}

// Destructor
template < class DT >
List<DT>::~List()
{
	delete cursor;
	delete head;
}

// List manipulation operations
template < class DT >
void List<DT>::insertItem(const DT &newDataItem) throw (bad_alloc)   // Insert after cursor
{
	// cursor를 이용한 sorted insert
	// case 1 : 리스트가 비어있을 경우
	// case 2 : 리스트에 1개이상의 노드가 있는 경우

	// 새로운 노드에 데이터 추가
	ListNode<DT>* location = new ListNode<DT>(newDataItem, nullptr, nullptr);

	if (location != nullptr) {

		// 리스트가 비어있는 경우
		if (List<DT>::isEmpty()) {

			head = location;	// head와 cursor 대입
			cursor = location;
		}
		// 리스트안에 노드가 있는 경우
		else {
			bool moreToSearch = true;
			bool flag = false;

			gotoBeginning();
			while (moreToSearch) {
				if (newDataItem >= cursor->dataItem) {
					if (cursor->next == nullptr) {
						moreToSearch = false;
						flag = true;
					}
					// cursor증가
					else
						cursor = cursor->next;
				}
				else moreToSearch = false;
			}
			if (flag) {
				// location노드 완성
				location->prior = cursor;
				// cursor와 location연결
				cursor->next = location;
				cursor = cursor->next;
			}
			else {
				if (cursor->prior == nullptr) {
					// location노드 완성
					head = location;
					location->next = cursor;
					// cursor와 location연결
					cursor->prior = location;
					cursor->prior->next = cursor;
					// cursor증가
					cursor = cursor->prior;
				}
				else {
					cursor = cursor->prior;
					// location노드 완성
					location->prior = cursor;
					location->next = cursor->next;
					// cursor와 location연결
					cursor->next->prior = location;
					cursor->next = location;
					// cursor증가
					cursor = cursor->next;
				}
			}
		}

	}
	else cout << "Error, Memory is full!" << endl;
}

template < class DT >
void List<DT>::remove() throw (logic_error)     // Remove data item
{
	// by cursor(cursor의 노드 제거)
	// case 1 : 리스트가 비어있을 경우
	// case 2 : 리스트에 1개이상의 노드가 있는 경우
	//		1) 노드가 한 개 일때
	//		2) 노드가 한 개 이상
	//			(1) node가 1개
	//			(2) node > 1
	//				-1 cursor가 맨끝
	//				-2 cursor가 맨끝 제외
	//				-3 cursor가 맨 처음
	ListNode<DT>* tempNode;

	if (!List<DT>::isEmpty()) {
		// 노드 한개 이상
		if (cursor->next == nullptr) {
			// 노드가 한개(The number of Node is only one/ cursor==head)
			if (cursor->prior == nullptr) {
				head = nullptr;
				cursor = nullptr;
			}

			// 노드가 한개이상 커서 맨끝
			else {
				tempNode = cursor;
				// cursor 전으로 옮김
				cursor = cursor->prior;
				// cursor의 다음노드는 nullptr
				cursor->next = nullptr;
				delete tempNode;	// 삭제
			}
		}
		// 노드 한개 이상 커서 맨끝 제외
		else {
			tempNode = cursor;	// 현 cursor를 지우기 위함

			// 커서가 맨 처음
			if (cursor->prior == nullptr) {
				// cursor를 다음으로 옮김
				cursor = cursor->next;
				// cursor 조정
				cursor->prior = nullptr;
				// head 조정
				head = cursor;

				delete tempNode;
			}
			else {
				// cursor 조정
				cursor->prior->next = cursor->next;
				cursor->next->prior = cursor->prior;

				// cursor를 다음으로 옮김
				cursor = cursor->next;

				delete tempNode;
			}
		}
	}
	else cout << "Error, List is empty" << endl;
}

template < class DT >
void List<DT>::deleteItem(DT &name) throw (logic_error)     // Remove data item
{
	// cursor를 이용한 sorted deleteItem
	// cursor를 이용하기 때문에 remove함수를 이용한다.

	if (!List<DT>::isEmpty()) {
		int flag = 0;
		gotoBeginning();

		while (flag != 1) {

			if (name == List<DT>::getCursor())
				break;

			if (List<DT>::get_cursor_next_node() == nullptr) {
				if (flag++) {
					system("echo Can't find flight!");
					break;
				}
			}
			else gotoNext();
		}

		if (flag) {/* do nothing*/} // not error message // cout << "Can't find element!" << endl;
		else List<DT>::remove();

	}
}

template < class DT >
void List<DT>::replace(const DT &newDataItem) throw (logic_error)  // Replace data item
{
	if (!List<DT>::isEmpty())
		cursor->dataItem = newDataItem;
	else cout << "Error, List is empty" << endl;
}

template < class DT >
void List<DT>::clear()                           // Clear list
{
	head = nullptr;
	cursor = nullptr;
}

template < class DT >
ListNode<DT>* List<DT>::return_head() const {	// Get head
	return head;
}

template < class DT >
ListNode<DT>* List<DT>::get_cursor_next_node() const {	// Get next cursor node
	return cursor->next;
}

template < class DT >
ListNode<DT>* List<DT>::get_cursor_prior_node() const {	// Get prior cursor node
	return cursor->prior;
}

//List status operations
template < class DT >
bool List<DT>::isEmpty() const                   // List is empty
{
	if (head == nullptr) return true;
	else return false;
}

template < class DT >
bool List<DT>::isFull() const                    // List is full
{
	ListNode<DT>* tempnode = new ListNode<DT>(0, nullptr, nullptr);
	if (tempnode == nullptr) return true;
	else return false;
}

// List iteration operations
template < class DT >
void List<DT>::gotoBeginning() throw (logic_error)  // Go to beginning
{
	cursor = head;
}

template < class DT >
void List<DT>::gotoEnd() throw (logic_error)    // Go to end
{
	while (cursor->next != nullptr)
		cursor = cursor->next;
}

template < class DT >
bool List<DT>::gotoNext()                       // Go to next data item
{
	if (List<DT>::isEmpty()) {
		return false;
	}
	else {
		if (cursor->next == nullptr) {
			return false;
		}
		else {
			cursor = cursor->next;
			return true;
		}
	}
}

template < class DT >
bool List<DT>::gotoPrior()                       // Go to prior data item
{
	if (List<DT>::isEmpty()) {
		return false;
	}
	else {
		if (cursor->prior == nullptr) {
			cout << "The current cursor is at the first of the list.\n Can't go to prior!" << endl;
			return false;
		}
		else {
			cursor = cursor->prior;
			return true;
		}
	}
}

template < class DT >
DT& List<DT>::getCursor() const throw (logic_error)  // Return data item
{
	if (List<DT>::isEmpty()) {
		cout << "";
		//return DT;
	}
	else return cursor->dataItem;
}

// Output the list structure -- used in testing/debugging
template < class DT >
void List<DT>::showStructure() const
{
	ListNode<DT>* p;   // Iterates through the list

	if (head == nullptr)
		cout << "Empty list" << endl;
	else
	{
		p = head;
		do
		{
			cout << p->dataItem;
			cout << endl;
			p = p->next;
		} while (p != nullptr);
		cout << endl;
	}
}

template < class DT >
bool operator >= (const DT& d1, const DT& d2) {

	if (d1 >= d2) return true;
	else return false;
}

template < class DT >
bool operator == (const DT& d1, const DT& d2) {
	if (d1 == d2) return true;
	else return false;
}