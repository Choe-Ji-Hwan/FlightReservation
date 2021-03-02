#pragma once
#include "Flight.h"

class Flight;

class Client {
public:
	Client();

	void insert_my_reserv_flight(Flight* f);	// 이 고객의 예약리스트 추가
	void delete_my_reserv_flight(Flight* f);	// 이 고객의 예약리스트 삭제

	void insert_my_standby_flight(Flight* f);	// 이 고객의 대기리스트 추가
	void delete_my_standby_flight(Flight* f);	// 이 고객의 대기리스트 삭제

	void insert(std::string n);		// 이름 입력
	std::string return_name();		// 이름 반환

	void update_client_list(List<Client>* c);	// 내 전,후의 고객 업데이트

	
	void print_name(std::ofstream& f);	// 이름 형식 출력

	List<Flight>* return_myf_reserv_list();		// 예약 리스트 반환
	List<Flight>* return_myf_standby_list();	// 대기 리스트 반환

	// 연산자 오버로딩
	friend bool operator >= (const Client& d1, const Client& d2);
	friend bool operator == (const Client& d1, const Client& d2);
	friend bool operator != (const Client& q1, const Client& q2);

private:
	std::string name;	// 고객의 이름

	List<Flight>* myf_resev_list;	// 예약된 리스트
	List<Flight>* myf_standby_list;	// 대기된 리스트

	ListNode<Client>* next_client;	// 다음 고객 포인터(메인에서 입력받은 정렬리스트에서)
	ListNode<Client>* prior_client;	// 전 고객 포인터	(메인에서 입력받은 정렬리스트에서)
};


Client::Client() {
	myf_standby_list = new List<Flight>;
	myf_resev_list = new List<Flight>;
	next_client = nullptr;
	prior_client = nullptr;
}

// 이 고객의 예약리스트 추가
void Client::insert_my_reserv_flight(Flight* f) {
	myf_resev_list->insertItem(*f);
}

// 이 고객의 예약리스트 삭제
void Client::delete_my_reserv_flight(Flight* f) {
	myf_resev_list->deleteItem(*f);
}

// 이 고객의 대기리스트 추가

void Client::insert_my_standby_flight(Flight* f) {
	myf_standby_list->insertItem(*f);
}

// 이 고객의 대기리스트 삭제
void Client::delete_my_standby_flight(Flight* f) {
	myf_standby_list->deleteItem(*f);
}

// 이름 입력
void Client::insert(std::string n) { name = n; }

// 이름 반환
std::string Client::return_name() { return name; }

// 내 전,후의 고객 업데이트
void Client::update_client_list(List<Client>* c) {
	next_client = c->get_cursor_next_node();
	prior_client = c->get_cursor_prior_node();
}

// 이름 형식 출력
void Client::print_name(std::ofstream& f) { 

	std::cout << "(" << name << ") "; 
	f << "(" << name << ") ";

}

// 예약 리스트 반환
List<Flight>* Client::return_myf_reserv_list() {
	return myf_resev_list;
}

// 대기 리스트 반환
List<Flight>* Client::return_myf_standby_list() {
	return myf_standby_list;
}

// 연산자 오버로딩
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
