#pragma once
#include "Client.h"
#include "Flight.h"

class Client;
class Flight;

class InfoReserv {
public:
	InfoReserv(List<Client>* c, List<Flight>* f);

	// ���̸����� ����� ã��
	void matching_client(List<Client>* c_list, std::string name, ofstream& f, bool& exist);

	// PP����, ���� client�� ����,������� ���
	void print_client_reserv_list(List<Flight>* f_list, std::ofstream& f, bool& exist);

private:
	Client* cur_client;		// ���������� ���� ���� ��
	Flight* cur_flight;		// ���� �����

	ListNode<Flight>* next_flight;	// ���� �������
	ListNode<Flight>* prior_flight;	// �� �������

	ListNode<Client>* next_client;	// ���� ��
	ListNode<Client>* prior_client;	// �� ��

	bool flag;	// ���࿡ ������ true, ��⿡ ������ false
};

InfoReserv::InfoReserv(List<Client>* c, List<Flight>* f) {

	next_client = c->get_cursor_next_node();
	prior_client = c->get_cursor_prior_node();

	next_flight = f->get_cursor_next_node();
	prior_flight = f->get_cursor_prior_node();
}

// ���̸����� ����� ã��

void InfoReserv::matching_client(List<Client>* c_list, std::string name, std::ofstream& f, bool& exist) {

	// ������ �ǽ��� ���� ����Ʈ�� �Է¹��� �̸��� �ִ´�.
	int flag1 = 0;
	c_list->gotoBeginning();
	while (true) {

		if (c_list->get_cursor_next_node() == nullptr) {
			if (flag1++)
				break;
		}
		// �� ��带 ã���� cur_client�� ����
		if (name == c_list->getCursor().return_name()) {
			cur_client = &(c_list->getCursor());
			exist = true;
			break;
		}
		c_list->gotoNext();
	}
	// ����Ʈ�� �̸��� ���� ��� �������
	if (flag1 == 2) {
		cout << name << " is not exist in Flight reservation&stand-by list" << endl;
		f << name << " is not exist in Flight reservation&stand-by list" << endl;
		exist = false;
	}
}

// PP����, ���� client�� ����,������� ���
void InfoReserv::print_client_reserv_list(List<Flight>* f_list, std::ofstream& f, bool& exist) {

	if (exist) {
		int flag2 = 0;
		std::cout << "-----------------------------" << std::endl;
		f << "-----------------------------" << std::endl;
		// ���� cur_client�� �� ��ü�� ������ ����Ǿ� �ִ�.
		cur_client->return_myf_reserv_list()->gotoBeginning();
		cur_client->return_myf_standby_list()->gotoBeginning();
		f_list->gotoBeginning();
		while (true) {

			if (f_list->get_cursor_next_node() == nullptr) {
				if (flag2++)
					break;
			}
			// ���� ���ฮ��Ʈ Ȯ��
			if (&(cur_client->return_myf_reserv_list()->getCursor()) != nullptr) {
				if (f_list->getCursor() == cur_client->return_myf_reserv_list()->getCursor()) {
					f_list->getCursor().print2_flight_info(f);
					std::cout << "(status)->reservation ok " << std::endl << std::endl;
					f << "(status)->reservation ok " << std::endl << std::endl;
					cur_client->return_myf_reserv_list()->gotoNext();
					flag = true;
				}
			}
			// ���� ��⸮��Ʈ Ȯ��
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
