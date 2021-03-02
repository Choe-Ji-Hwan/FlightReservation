#pragma once
#include "Client.h"
#include "Flight.h"

class Client;
class Flight;

class InfoReserv {
public:
	InfoReserv(List<Client>* c, List<Flight>* f);

	// 고객이름으로 고객노드 찾기
	void matching_client(List<Client>* c_list, std::string name, ofstream& f, bool& exist);

	// PP전용, 현재 client의 예약,대기정보 출력
	void print_client_reserv_list(List<Flight>* f_list, std::ofstream& f, bool& exist);

private:
	Client* cur_client;		// 예약정보를 보고 싶은 고객
	Flight* cur_flight;		// 현재 비행기

	ListNode<Flight>* next_flight;	// 다음 비행기편
	ListNode<Flight>* prior_flight;	// 전 비행기편

	ListNode<Client>* next_client;	// 다음 고객
	ListNode<Client>* prior_client;	// 전 고객

	bool flag;	// 예약에 있으면 true, 대기에 있으면 false
};

InfoReserv::InfoReserv(List<Client>* c, List<Flight>* f) {

	next_client = c->get_cursor_next_node();
	prior_client = c->get_cursor_prior_node();

	next_flight = f->get_cursor_next_node();
	prior_flight = f->get_cursor_prior_node();
}

// 고객이름으로 고객노드 찾기

void InfoReserv::matching_client(List<Client>* c_list, std::string name, std::ofstream& f, bool& exist) {

	// 예약을 실시한 고객의 리스트와 입력받은 이름을 넣는다.
	int flag1 = 0;
	c_list->gotoBeginning();
	while (true) {

		if (c_list->get_cursor_next_node() == nullptr) {
			if (flag1++)
				break;
		}
		// 고객 노드를 찾으면 cur_client에 대입
		if (name == c_list->getCursor().return_name()) {
			cur_client = &(c_list->getCursor());
			exist = true;
			break;
		}
		c_list->gotoNext();
	}
	// 리스트에 이름이 없는 경우 오류출력
	if (flag1 == 2) {
		cout << name << " is not exist in Flight reservation&stand-by list" << endl;
		f << name << " is not exist in Flight reservation&stand-by list" << endl;
		exist = false;
	}
}

// PP전용, 현재 client의 예약,대기정보 출력
void InfoReserv::print_client_reserv_list(List<Flight>* f_list, std::ofstream& f, bool& exist) {

	if (exist) {
		int flag2 = 0;
		std::cout << "-----------------------------" << std::endl;
		f << "-----------------------------" << std::endl;
		// 현재 cur_client는 이 객체의 고객으로 저장되어 있다.
		cur_client->return_myf_reserv_list()->gotoBeginning();
		cur_client->return_myf_standby_list()->gotoBeginning();
		f_list->gotoBeginning();
		while (true) {

			if (f_list->get_cursor_next_node() == nullptr) {
				if (flag2++)
					break;
			}
			// 고객의 예약리스트 확인
			if (&(cur_client->return_myf_reserv_list()->getCursor()) != nullptr) {
				if (f_list->getCursor() == cur_client->return_myf_reserv_list()->getCursor()) {
					f_list->getCursor().print2_flight_info(f);
					std::cout << "(status)->reservation ok " << std::endl << std::endl;
					f << "(status)->reservation ok " << std::endl << std::endl;
					cur_client->return_myf_reserv_list()->gotoNext();
					flag = true;
				}
			}
			// 고객의 대기리스트 확인
			if (&(cur_client->return_myf_standby_list()->getCursor()) != nullptr) {
				if (f_list->getCursor() == cur_client->return_myf_standby_list()->getCursor()) {
					f_list->getCursor().print2_flight_info(f);
					std::cout << "(status)->stand-by status " << std::endl << std::endl;
					f << "(status)->stand-by status " << std::endl << std::endl;
					cur_client->return_myf_standby_list()->gotoNext();
					flag = false;
				}
			}

			f_list->gotoNext();
		}

		std::cout << "-----------------------------" << std::endl << std::endl;
		f << "-----------------------------" << std::endl << std::endl;
	}
}
