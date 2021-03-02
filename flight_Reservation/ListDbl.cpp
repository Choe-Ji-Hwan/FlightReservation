/*
| this is .cpp file of doubly linked and sorted list header
| doubly linked list (by cursor) ADT
|	- insert() + ((sorted)insertItem() + (sorted)deleteItem())
|	= doubly linked and sorted list (by cursor) ADT
| 2017112104 ����ȯ
*/
#include "Listdbl.h"
#include <iostream>

// Constructor
template < class DT>
ListNode<DT>::ListNode(const DT &data,
	// ��带 ����� constructor
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

	List<DT>::gotoPrior();	// �� ������ Ŀ���� ����

	while (true) {
		copy.insertItem(List<DT>::getCursor());

		if (List<DT>::get_cursor_next_node() == nullptr)
			break;

		List<DT>::gotoNext();	// ���� Ŀ���� ����
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
	// cursor�� �̿��� sorted insert
	// case 1 : ����Ʈ�� ������� ���
	// case 2 : ����Ʈ�� 1���̻��� ��尡 �ִ� ���

	// ���ο� ��忡 ������ �߰�
	ListNode<DT>* location = new ListNode<DT>(newDataItem, nullptr, nullptr);

	if (location != nullptr) {

		// ����Ʈ�� ����ִ� ���
		if (List<DT>::isEmpty()) {

			head = location;	// head�� cursor ����
			cursor = location;
		}
		// ����Ʈ�ȿ� ��尡 �ִ� ���
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
					// cursor����
					else
						cursor = cursor->next;
				}
				else moreToSearch = false;
			}
			if (flag) {
				// location��� �ϼ�
				location->prior = cursor;
				// cursor�� location����
				cursor->next = location;
				cursor = cursor->next;
			}
			else {
				if (cursor->prior == nullptr) {
					// location��� �ϼ�
					head = location;
					location->next = cursor;
					// cursor�� location����
					cursor->prior = location;
					cursor->prior->next = cursor;
					// cursor����
					cursor = cursor->prior;
				}
				else {
					cursor = cursor->prior;
					// location��� �ϼ�
					location->prior = cursor;
					location->next = cursor->next;
					// cursor�� location����
					cursor->next->prior = location;
					cursor->next = location;
					// cursor����
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
	// by cursor(cursor�� ��� ����)
	// case 1 : ����Ʈ�� ������� ���
	// case 2 : ����Ʈ�� 1���̻��� ��尡 �ִ� ���
	//		1) ��尡 �� �� �϶�
	//		2) ��尡 �� �� �̻�
	//			(1) node�� 1��
	//			(2) node > 1
	//				-1 cursor�� �ǳ�
	//				-2 cursor�� �ǳ� ����
	//				-3 cursor�� �� ó��
	ListNode<DT>* tempNode;

	if (!List<DT>::isEmpty()) {
		// ��� �Ѱ� �̻�
		if (cursor->next == nullptr) {
			// ��尡 �Ѱ�(The number of Node is only one/ cursor==head)
			if (cursor->prior == nullptr) {
				head = nullptr;
				cursor = nullptr;
			}

			// ��尡 �Ѱ��̻� Ŀ�� �ǳ�
			else {
				tempNode = cursor;
				// cursor ������ �ű�
				cursor = cursor->prior;
				// cursor�� �������� nullptr
				cursor->next = nullptr;
				delete tempNode;	// ����
			}
		}
		// ��� �Ѱ� �̻� Ŀ�� �ǳ� ����
		else {
			tempNode = cursor;	// �� cursor�� ����� ����

			// Ŀ���� �� ó��
			if (cursor->prior == nullptr) {
				// cursor�� �������� �ű�
				cursor = cursor->next;
				// cursor ����
				cursor->prior = nullptr;
				// head ����
				head = cursor;

				delete tempNode;
			}
			else {
				// cursor ����
				cursor->prior->next = cursor->next;
				cursor->next->prior = cursor->prior;

				// cursor�� �������� �ű�
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
	// cursor�� �̿��� sorted deleteItem
	// cursor�� �̿��ϱ� ������ remove�Լ��� �̿��Ѵ�.

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