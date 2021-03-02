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

	void insert_number(std::string num);	// �̸� �Է�
	void insert_from_city(std::string fc);	// ����� �Է�
	void insert_to_city(std::string tc);	// ������ �Է�
	void insert_capacity(std::string ca);	// �����ο� �Է�

	std::string return_number();	// ����� ��ȣ ��ȯ

	void reserv_client(Client& c, std::ofstream& f);	// �� ����⿡ ����
	void cancel_client(Client& c, std::ofstream& f);	// �� ������� �������

	void print_flight_info(std::ofstream& f);	// ����� ���� ���1
	void print2_flight_info(std::ofstream& f);	// ����� ���� ���2

	void print_reserv_list(std::ofstream& f);	// �� ������� ���� ������Ʈ ���
	void print_stand_by_list(std::ofstream& f);	// �� ������� ��� ������Ʈ ���

	void update_flight_list(List<Flight>* f);	// ��,�� ������ ������Ʈ

	List<Client>* return_resrv_list();	// �� ������� ���� ������Ʈ ��ȯ


	// ������ �����ε�
	friend bool operator >= (const Flight& d1, const Flight& d2);
	friend bool operator == (const Flight& d1, const Flight& d2);

private:
	int number_of_client;
	std::string number;		// ��ȣ
	std::string from_city;	// �����
	std::string to_city;	// ������
	int capacity;			// �ִ� ž�°� ��
	bool reserv_end;		// ������ ���� á����

	List<Client>* reserv_list;	// ������� ������ �� ����Ʈ
	Queue<Client>* stand_by_list; // ������� ��� �� ����Ʈ

	ListNode<Flight>* next_flight;	// ���� ��������� ���
	ListNode<Flight>* prior_flight;	// �� ����� ���� ���

	QueueNode<Client>* stand_by_rear;	// ��� ����Ʈ�� front
	QueueNode<Client>* stand_by_front;	// ��� ����Ʈ�� rear
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

// �̸� �Է�
void Flight::insert_number(std::string num) { number = num; }

// ����� �Է�
void Flight::insert_from_city(std::string fc) { from_city = fc; }

// ������ �Է�
void Flight::insert_to_city(std::string tc) { to_city = tc; }

// �����ο� �Է�

void Flight::insert_capacity(std::string ca) { capacity = std::stoi(ca); }

// ����� ��ȣ ��ȯ
std::string Flight::return_number() { return number; }

// �� ����⿡ ����
void Flight::reserv_client(Client & c, std::ofstream& f) {

	int flag = 0;	// ǥ��

					// ���� ����Ʈ�� ��� �ִ� ���
	if (reserv_list->isEmpty())
		flag = 2;

	// ���� ����Ʈ�ȿ� 1���̶� �ִ� ���
	// ���� ����Ʈ�� �Ⱦ��.
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

	// ���ฮ��Ʈ�� �������� �ʰ�, ��� ����Ʈ���� �������� ������� �߰�
	if (flag == 2 && !stand_by_list->find(c)) {

		// ������ �� �� ��� ��� ����Ʈ�� ����
		if (number_of_client >= capacity) {
			stand_by_list->enqueue(c);
			c.insert_my_standby_flight(this);
		}
		// ������ ���� ���� ��� ���� ����Ʈ�� ����
		else {
			reserv_list->insertItem(c);
			c.insert_my_reserv_flight(this);
		}

		number_of_client++;
		if (number_of_client >= capacity) reserv_end = true;
	}
	// ���ฮ��Ʈ�� ������ ��
	else if (flag != 2) {
		std::cout << c.return_name() << " is already exist in reservation list" << endl;
		f << c.return_name() << " is already exist in reservation list" << endl;
	}
	// ��⸮��Ʈ�� ������ ��
	else if (stand_by_list->find(c)) {
		std::cout << c.return_name() << " is already exist in stand-by list" << endl;
		f << c.return_name() << " is already exist in stand-by list" << endl;
	}
	
}

// �� ������� �������
void Flight::cancel_client(Client& c, std::ofstream& f) {

	int flag = 0;	// ǥ��
					// ������ ã�� ����
					// ����Ʈ�� �Ⱦ��.
	// c��ü�� �۵��ϴ� ���� c��ü ���� ����Ʈ�� ������ �ֱ� ������ ����
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
	// ã��
	if (flag != 1) {

		// ����ο��� �ִ� ���
		if (number_of_client > capacity) {
			reserv_list->deleteItem(c);
			c.delete_my_reserv_flight(this);	// c(Client)��ü�� �����ܿ����� ����
			number_of_client--;

			Client temp = stand_by_list->dequeue();
			temp.delete_my_standby_flight(this);
			reserv_list->insertItem(temp);
			reserv_list->getCursor().insert_my_standby_flight(this);
			reserv_end = true;
		}
		// ����ο��� ���� ���
		else {
			reserv_list->deleteItem(c);
			c.delete_my_reserv_flight(this);
			number_of_client--;
			reserv_end = false;
		}
	}
	// ����
	else {
		// Ȥ�� ����ο��� �ֳ�
		if (reserv_end)
			if (stand_by_list->find(c)) {
				stand_by_list->find_remove(c);
				c.delete_my_standby_flight(this);
			}
	}
	// ������Ʈ
	stand_by_front = stand_by_list->return_front();
	stand_by_rear = stand_by_list->return_rear();
}

// ����� ���� ���1
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

// ����� ���� ���2
void Flight::print2_flight_info(std::ofstream& f) {
	std::cout << "Flight-number\t: " << number << std::endl;
	std::cout << "From-city\t\t: " << from_city << std::endl;
	std::cout << "to-city\t\t: " << to_city << std::endl;

	f << "Flight-number\t: " << number << std::endl;
	f << "From-city\t\t: " << from_city << std::endl;
	f << "to-city\t\t: " << to_city << std::endl;
}

// �� ������� ���� ������Ʈ ���
void Flight::print_reserv_list(std::ofstream& f) {

	// ���� ����Ʈ�� ��� ���� �ʴ� ���
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
	// ���� ����Ʈ�� ��� �ִ� ���
	else {
		std::cout << "empty reservation list";
		f << "empty reservation list";
	}
}

// �� ������� ��� ������Ʈ ���
void Flight::print_stand_by_list(std::ofstream& f) {

	// ��� ����Ʈ�� ������� �ʴ� ���
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
	// ��� ����Ʈ�� ����ִ� ���
	else {
		std::cout << "empty stand-by list" << std::endl;;
		std::cout << "-----------------------------" << std::endl;
		f << "empty stand-by list" << std::endl;;
		f << "-----------------------------" << std::endl;
	}

}

// ��,�� ������ ������Ʈ
void Flight::update_flight_list(List<Flight>* f) {
	next_flight = f->get_cursor_next_node();
	prior_flight = f->get_cursor_prior_node();
}

// �� ������� ���� ������Ʈ ��ȯ
List<Client>* Flight::return_resrv_list() {
	return reserv_list;
}


// ������ �����ε�
bool operator >= (const Flight& d1, const Flight& d2) {

	if (d1.number >= d2.number) return true;
	else return false;
}

bool operator == (const Flight& d1, const Flight& d2) {
	if (d1.number == d2.number) return true;
	else return false;
}