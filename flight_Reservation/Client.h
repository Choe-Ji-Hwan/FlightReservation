#pragma once
#include "Flight.h"

class Flight;

class Client {
public:
	Client();

	void insert_my_reserv_flight(Flight* f);	// �� ���� ���ฮ��Ʈ �߰�
	void delete_my_reserv_flight(Flight* f);	// �� ���� ���ฮ��Ʈ ����

	void insert_my_standby_flight(Flight* f);	// �� ���� ��⸮��Ʈ �߰�
	void delete_my_standby_flight(Flight* f);	// �� ���� ��⸮��Ʈ ����

	void insert(std::string n);		// �̸� �Է�
	std::string return_name();		// �̸� ��ȯ

	void update_client_list(List<Client>* c);	// �� ��,���� �� ������Ʈ

	
	void print_name(std::ofstream& f);	// �̸� ���� ���

	List<Flight>* return_myf_reserv_list();		// ���� ����Ʈ ��ȯ
	List<Flight>* return_myf_standby_list();	// ��� ����Ʈ ��ȯ

	// ������ �����ε�
	friend bool operator >= (const Client& d1, const Client& d2);
	friend bool operator == (const Client& d1, const Client& d2);
	friend bool operator != (const Client& q1, const Client& q2);

private:
	std::string name;	// ���� �̸�

	List<Flight>* myf_resev_list;	// ����� ����Ʈ
	List<Flight>* myf_standby_list;	// ���� ����Ʈ

	ListNode<Client>* next_client;	// ���� �� ������(���ο��� �Է¹��� ���ĸ���Ʈ����)
	ListNode<Client>* prior_client;	// �� �� ������	(���ο��� �Է¹��� ���ĸ���Ʈ����)
};


Client::Client() {
	myf_standby_list = new List<Flight>;
	myf_resev_list = new List<Flight>;
	next_client = nullptr;
	prior_client = nullptr;
}

// �� ���� ���ฮ��Ʈ �߰�
void Client::insert_my_reserv_flight(Flight* f) {
	myf_resev_list->insertItem(*f);
}

// �� ���� ���ฮ��Ʈ ����
void Client::delete_my_reserv_flight(Flight* f) {
	myf_resev_list->deleteItem(*f);
}

// �� ���� ��⸮��Ʈ �߰�

void Client::insert_my_standby_flight(Flight* f) {
	myf_standby_list->insertItem(*f);
}

// �� ���� ��⸮��Ʈ ����
void Client::delete_my_standby_flight(Flight* f) {
	myf_standby_list->deleteItem(*f);
}

// �̸� �Է�
void Client::insert(std::string n) { name = n; }

// �̸� ��ȯ
std::string Client::return_name() { return name; }

// �� ��,���� �� ������Ʈ
void Client::update_client_list(List<Client>* c) {
	next_client = c->get_cursor_next_node();
	prior_client = c->get_cursor_prior_node();
}

// �̸� ���� ���
void Client::print_name(std::ofstream& f) { 

	std::cout << "(" << name << ") "; 
	f << "(" << name << ") ";

}

// ���� ����Ʈ ��ȯ
List<Flight>* Client::return_myf_reserv_list() {
	return myf_resev_list;
}

// ��� ����Ʈ ��ȯ
List<Flight>* Client::return_myf_standby_list() {
	return myf_standby_list;
}

// ������ �����ε�
bool operator >= (const Client& d1, const Client& d2) {

	if (d1.name >= d2.name) return true;
	else return false;
}

bool operator == (const Client& d1, const Client& d2) {
	if (d1.name == d2.name) return true;
	else return false;
}

bool operator != (const Client& q1, const Client& q2) {
	if (q1 != q2) return true;
	else return false;
}
