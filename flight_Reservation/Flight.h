#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include "ListDbl.cpp"
#include "QueueLnk.cpp"
#include "Client.h"

class Client;

class Flight {
public:
	Flight();

	void insert_number(std::string num);	// 이름 입력
	void insert_from_city(std::string fc);	// 출발지 입력
	void insert_to_city(std::string tc);	// 도착지 입력
	void insert_capacity(std::string ca);	// 수용인원 입력

	std::string return_number();	// 비행기 번호 반환

	void reserv_client(Client& c, std::ofstream& f);	// 이 비행기에 예약
	void cancel_client(Client& c, std::ofstream& f);	// 이 비행기의 예약취소

	void print_flight_info(std::ofstream& f);	// 비행기 정보 출력1
	void print2_flight_info(std::ofstream& f);	// 비행기 정보 출력2

	void print_reserv_list(std::ofstream& f);	// 이 비행기의 예약 고객리스트 출력
	void print_stand_by_list(std::ofstream& f);	// 이 비행기의 대기 고객리스트 출력

	void update_flight_list(List<Flight>* f);	// 전,후 비행기들 업데이트

	List<Client>* return_resrv_list();	// 이 비행기의 예약 고객리스트 반환


	// 연산자 오버로딩
	friend bool operator >= (const Flight& d1, const Flight& d2);
	friend bool operator == (const Flight& d1, const Flight& d2);

private:
	int number_of_client;
	std::string number;		// 번호
	std::string from_city;	// 출발지
	std::string to_city;	// 도착지
	int capacity;			// 최대 탑승객 수
	bool reserv_end;		// 예약이 가득 찼는지

	List<Client>* reserv_list;	// 비행기편 예약한 고객 리스트
	Queue<Client>* stand_by_list; // 비행기편 대기 고객 리스트

	ListNode<Flight>* next_flight;	// 다음 비행기편의 노드
	ListNode<Flight>* prior_flight;	// 전 비행기 편의 노드

	QueueNode<Client>* stand_by_rear;	// 대기 리스트의 front
	QueueNode<Client>* stand_by_front;	// 대기 리스트의 rear
};

Flight::Flight() : capacity(0) {
	reserv_list = new List<Client>;
	stand_by_list = new Queue<Client>;
	reserv_end = false;
	number_of_client = 0;

	next_flight = nullptr;
	prior_flight = nullptr;

	stand_by_rear = nullptr;
	stand_by_front = nullptr;;
}

// 이름 입력
void Flight::insert_number(std::string num) { number = num; }

// 출발지 입력
void Flight::insert_from_city(std::string fc) { from_city = fc; }

// 도착지 입력
void Flight::insert_to_city(std::string tc) { to_city = tc; }

// 수용인원 입력

void Flight::insert_capacity(std::string ca) { capacity = std::stoi(ca); }

// 비행기 번호 반환
std::string Flight::return_number() { return number; }

// 이 비행기에 예약
void Flight::reserv_client(Client & c, std::ofstream& f) {

	int flag = 0;	// 표지

					// 예약 리스트가 비어 있는 경우
	if (reserv_list->isEmpty())
		flag = 2;

	// 예약 리스트안에 1명이라도 있는 경우
	// 예약 리스트를 훑어본다.
	else {
		reserv_list->gotoBeginning();

		while (flag != 2) {

			if (c == reserv_list->getCursor())
				break;

			if (reserv_list->get_cursor_next_node() == nullptr) {
				if (flag++) break;
			}
			else reserv_list->gotoNext();
		}
	}
	if (stand_by_list->find(c)) reserv_end = true;

	// 예약리스트에 존재하지 않고, 대기 리스트에도 존재하지 않을경우 추가
	if (flag == 2 && !stand_by_list->find(c)) {

		// 예약이 꽉 찬 경우 대기 리스트에 저장
		if (number_of_client >= capacity) {
			stand_by_list->enqueue(c);
			c.insert_my_standby_flight(this);
		}
		// 예약이 차지 않은 경우 예약 리스트에 저장
		else {
			reserv_list->insertItem(c);
			c.insert_my_reserv_flight(this);
		}

		number_of_client++;
		if (number_of_client >= capacity) reserv_end = true;
	}
	// 예약리스트에 존재할 때
	else if (flag != 2) {
		std::cout << c.return_name() << " is already exist in reservation list" << endl;
		f << c.return_name() << " is already exist in reservation list" << endl;
	}
	// 대기리스트에 존재할 때
	else if (stand_by_list->find(c)) {
		std::cout << c.return_name() << " is already exist in stand-by list" << endl;
		f << c.return_name() << " is already exist in stand-by list" << endl;
	}
	
}

// 이 비행기의 예약취소
void Flight::cancel_client(Client& c, std::ofstream& f) {

	int flag = 0;	// 표지
					// 예약자 찾는 과정
					// 리스트를 훑어본다.
	// c객체로 작동하는 것은 c객체 또한 리스트를 가지고 있기 때문에 조정
	reserv_list->gotoBeginning();

	while (flag != 1) {

		if (reserv_list->getCursor() == c)
			break;

		if (reserv_list->get_cursor_next_node() == nullptr && flag++) {

			std::system("echo Can't find Client to reservation list!");
			std::cout << std::endl;
			f << "Can't find Client to reservation list!" << std::endl << std::endl;
			break;
		}
		else reserv_list->gotoNext();
	}
	// 찾음
	if (flag != 1) {

		// 대기인원이 있는 경우
		if (number_of_client > capacity) {
			reserv_list->deleteItem(c);
			c.delete_my_reserv_flight(this);	// c(Client)객체의 예약명단에서도 뺀다
			number_of_client--;

			Client temp = stand_by_list->dequeue();
			temp.delete_my_standby_flight(this);
			reserv_list->insertItem(temp);
			reserv_list->getCursor().insert_my_standby_flight(this);
			reserv_end = true;
		}
		// 대기인원이 없는 경우
		else {
			reserv_list->deleteItem(c);
			c.delete_my_reserv_flight(this);
			number_of_client--;
			reserv_end = false;
		}
	}
	// 없음
	else {
		// 혹시 대기인원에 있나
		if (reserv_end)
			if (stand_by_list->find(c)) {
				stand_by_list->find_remove(c);
				c.delete_my_standby_flight(this);
			}
	}
	// 업데이트
	stand_by_front = stand_by_list->return_front();
	stand_by_rear = stand_by_list->return_rear();
}

// 비행기 정보 출력1
void Flight::print_flight_info(std::ofstream& f) {
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Flight-number\t: " << number << std::endl;
	std::cout << "From-city \t: " << from_city << std::endl;
	std::cout << "to-city\t\t: " << to_city << std::endl;
	std::cout << "capacity\t\t: " << capacity << std::endl;
	if (reserv_end) {
		std::cout << "reserved-number\t: " << capacity << std::endl;
	}
	else std::cout << "reserved-number\t: " << number_of_client << std::endl;

	f << "-----------------------------" << std::endl;
	f << "Flight-number\t: " << number << std::endl;
	f << "From-city \t: " << from_city << std::endl;
	f << "to-city\t\t: " << to_city << std::endl;
	f << "capacity\t\t: " << capacity << std::endl;
	if (reserv_end) {
		f << "reserved-number\t: " << capacity << std::endl;
	}
	else f << "reserved-number\t: " << number_of_client << std::endl;
}

// 비행기 정보 출력2
void Flight::print2_flight_info(std::ofstream& f) {
	std::cout << "Flight-number\t: " << number << std::endl;
	std::cout << "From-city\t\t: " << from_city << std::endl;
	std::cout << "to-city\t\t: " << to_city << std::endl;

	f << "Flight-number\t: " << number << std::endl;
	f << "From-city\t\t: " << from_city << std::endl;
	f << "to-city\t\t: " << to_city << std::endl;
}

// 이 비행기의 예약 고객리스트 출력
void Flight::print_reserv_list(std::ofstream& f) {

	// 예약 리스트가 비어 있지 않는 경우
	if (number_of_client) {

		int flag = 0;

		reserv_list->gotoBeginning();

		std::cout << "reservation list: ";
		f << "reservation list: ";
		while (flag != 1) {

			reserv_list->getCursor().print_name(f);

			if (reserv_list->get_cursor_next_node() == nullptr && flag++) {
				std::cout << std::endl;
				f << std::endl << std::endl;
				break;
			}
			else reserv_list->gotoNext();
		}
	}
	// 예약 리스트가 비어 있는 경우
	else {
		std::cout << "empty reservation list";
		f << "empty reservation list";
	}
}

// 이 비행기의 대기 고객리스트 출력
void Flight::print_stand_by_list(std::ofstream& f) {

	// 대기 리스트가 비어있지 않는 경우
	if (!stand_by_list->empty()) {
		Queue<Client>* newqueue = new Queue<Client>;

		std::cout << "stand-by list   : ";
		f << "stand-by list   : ";
		while (!stand_by_list->empty()) {
			Client temp = stand_by_list->dequeue();
			temp.print_name(f);
			newqueue->enqueue(temp);
		}

		while (!newqueue->empty()) {
			stand_by_list->enqueue(newqueue->dequeue());
		}
		delete newqueue;
		std::cout << "\n-----------------------------" << std::endl;
		f << "\n-----------------------------" << std::endl;
	}
	// 대기 리스트가 비어있는 경우
	else {
		std::cout << "empty stand-by list" << std::endl;;
		std::cout << "-----------------------------" << std::endl;
		f << "empty stand-by list" << std::endl;;
		f << "-----------------------------" << std::endl;
	}

}

// 전,후 비행기들 업데이트
void Flight::update_flight_list(List<Flight>* f) {
	next_flight = f->get_cursor_next_node();
	prior_flight = f->get_cursor_prior_node();
}

// 이 비행기의 예약 고객리스트 반환
List<Client>* Flight::return_resrv_list() {
	return reserv_list;
}


// 연산자 오버로딩
bool operator >= (const Flight& d1, const Flight& d2) {

	if (d1.number >= d2.number) return true;
	else return false;
}

bool operator == (const Flight& d1, const Flight& d2) {
	if (d1.number == d2.number) return true;
	else return false;
}