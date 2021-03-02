//----------------------------------------------------------------------------------------
//
//  �ڷᱸ���׽ǽ�01 2017112104 ����ȯ midterm project
//	Flight Reservation System
//
//
//	*���� : 1. ��� ����Ʈ�� �� �������� ��� ����Ʈ(Queue)�� ����Ѵ�.
//	*���� : 2. ���� ����Ʈ�� ������ ���̰�, �� �ٸ� ����Ʈ�̴�.
//				(����⿡ ����(�̸���) -> capacity�� ������ ��� ����Ʈ�� ������.)
//				(Dubly Linked List) ���
//	*���� : 3. ���� ���� ���� ����⸦ ���� �����ϴ�(���� ���� ������ �����̴�.)
//
//
//	��� ���ư��� �� ������ ����
//	��ɹ� : ��ɼ���		(�������)
//		1) �Է�/���� (�Է��� ������ �о� �Է¹޴´�. ���پ� ����� �����ִ�)
//					(���� ��ɾ �ش���� �ʴ� ��ɾ�� Error)
//			IF : ���ο� ������� �߰�			(IF flight_number from_city to_city capacity)
//			DF : ��������� ����Ʈ���� ����	(DF flight_number)
//			RP : ���� ������� ����		(RP name flight_number)
//			CP : ���� ���ฮ��Ʈ���� ����	(CP name flight_number)
//				 ->��⸮��Ʈ�� ù��° ��� ������ ����Ʈ�� �߰�
//
//		2) �μ�
//			PA : ��������� ������ ���� ����� ��(�̸���), ����� ���(ť�� ������) �μ�
//					(PA)
//			PF : ������� ��ȣ������ ��������� ���� �μ�	(PF)
//			PR : Ư�� ��������� PA�� ����	(PA flight_number)
//				  -> ����� ���� ���ٸ� Error
//			pp : ������ ���� ���� ��ȹ�� ������� ��ȣ ������ �μ�	(PP name)
//				 -> ��Ÿ�� �������(�����, ������, ����ok?����)
//------------------------------------------------------------------------------------------

#include "Flight.h"
#include "Client.h"
#include "InfoReserv.h"

using namespace std;

int main() {

	// �ߺ��� �ȵǰ� ���� ����Ʈ�ȿ� �ִ� ����Ʈ�� Ŭ�����ȿ� ����
	List<Client>* c_list = new List<Client>;	// ��ü �� ����Ʈ(�ߺ����)
	List<Flight>* f_list = new List<Flight>;	// ��ü ������� ����Ʈ(�ߺ����)

	ifstream openfile("samplein.p1.txt");
	ofstream write_file("OUTFILE.P1.txt");
	string token;
	string temp;
	int flag = 0;
	int length = 0;

	// ������ �� ������ �� Ȯ��
	if (openfile.is_open()) {
		// EOF���� �� ���� �ݺ�
		while (!openfile.eof()) {

			// �� �پ� token�� �Է�
			getline(openfile, token, '\n');

			// ��ɾ� ����
			string cmd = token.substr(0, 2);

			//IF: ���ο� ������� �߰�(IF flight_number from_city to_city capacity)
			if (cmd == "IF") {
				Flight* newflight = new Flight;
				cout << token << endl;	// ��� ���
				write_file << token << endl;
				token = token.substr(3);	// ��� ������ string token�� �Է�

				length = token.length();	// �����Է�

				// Flight��ü ��忡 ���� �Է�
				int flag = 0;
				for (int i = 0; i < length; i++) {
					temp = "";
					while (token[i] != ' ') {
						temp += token[i];
						i++;
						if (length <= i) break;
					}

					flag++;
					if (flag == 1)		newflight->insert_number(temp);
					else if (flag == 2) newflight->insert_from_city(temp);
					else if (flag == 3) newflight->insert_to_city(temp);
					else if (flag == 4) newflight->insert_capacity(temp);
				}

				// ����Ⱑ �̹� ���� �ϸ� ����⸦ ���� �ʴ´�.
				int flag2 = 0;
				f_list->gotoBeginning();

				while (flag2 != 1) {
					if (f_list->isEmpty()) {	// ����� ����Ʈ�� ������� -> ����x
						flag2++;
						break;
					}
					if (temp == f_list->getCursor().return_number())	// ������ ��
						break;

					// cursor�� ���� ��带 �˻��ϱ� ������ ������ ��� �˻� ��
					// flag2�� 1�� ������ �ѹ� �� �̰��� �����ϸ� break;
					if (f_list->get_cursor_next_node() == nullptr) {	
						if (flag2++) {
							break;
						}
					}
					else f_list->gotoNext();
				}
				if (flag != 0) {
					f_list->insertItem(*newflight);
					newflight->update_flight_list(f_list);
				}
				delete newflight;
			}

			//DF : ��������� ����Ʈ���� ����	(DF flight_number)
			else if (cmd == "DF") {

				cout << token << endl;
				write_file << token << endl;
				token = token.substr(3);	// ��� ������ string token�� �Է�

				length = token.length();	// �����Է�

				for (int i = 0; i < length; i++) {
					temp = "";
					while (token[i] != ' ') {
						temp += token[i];
						i++;
						if (length <= i) break;
					}
				}

				int flag2 = 0;
				f_list->gotoBeginning();

				while (flag2 != 2) {

					if (temp == f_list->getCursor().return_number())
						break;
					// cursor�� ���� ��带 �˻��ϱ� ������ ������ ��� �˻� ��
					// flag2�� 1�� ������ �ѹ� �� �̰��� �����ϸ� break;
					if (f_list->get_cursor_next_node() == nullptr) {
						if (flag2++) {
							cout << "Can't find flight!" << endl << endl;
							write_file << "Can't find flight!" << endl << endl;
							break;
						}
					}
					else f_list->gotoNext();
				}
				if (flag2 != 2) {
					Flight delete_soon_flight = f_list->getCursor();
					f_list->deleteItem(delete_soon_flight);
					
					// ���� ����/��� ����Ʈ���� ����
					int flag3 = 0;
					c_list->gotoBeginning();

					while (flag3 != 2) {

						if(c_list->getCursor().return_myf_reserv_list() != nullptr)
						c_list->getCursor().delete_my_reserv_flight(&delete_soon_flight);

						if(c_list->getCursor().return_myf_standby_list() != nullptr)
						c_list->getCursor().delete_my_standby_flight(&delete_soon_flight);

						// cursor�� ���� ��带 �˻��ϱ� ������ ������ ��� �˻� ��
						// flag2�� 1�� ������ �ѹ� �� �̰��� �����ϸ� break;
						if (c_list->get_cursor_next_node() == nullptr) {
							if (flag3++) {
								break;
							}
						}
						else c_list->gotoNext();
					}
				}
			}

			//RP : ���� ������� ����		(RP name flight_number)
			else if (cmd == "RP") {

				Client* newclient = new Client;

				cout << token << endl;
				write_file << token << endl;
				token = token.substr(3);	// ��� ������ string token�� �Է�

				length = token.length();	// �����Է�

				int flag = 0;
				int flag2 = 0;
				int flag3 = 0;

				for (int i = 0; i < length; i++) {
					temp = "";
					while (token[i] != ' ') {
						temp += token[i];
						i++;
						if (length <= i) break;
					}

					flag++;
					if (flag == 1) {
						newclient->insert(temp);

						c_list->gotoBeginning();

						while (flag3 != 1) {
							if (c_list->isEmpty()) {
								flag3++;
								break;
							}
							if (temp == c_list->getCursor().return_name())
								break;

							// cursor�� ���� ��带 �˻��ϱ� ������ ������ ��� �˻� ��
							// flag3�� 1�� ������ �ѹ� �� �̰��� �����ϸ� break;
							if (c_list->get_cursor_next_node() == nullptr) {
								if (flag3++) {
									break;
								}
							}
							else c_list->gotoNext();
						}
					}
					

					else if (flag == 2) {

						f_list->gotoBeginning();

						while (flag2 != 1) {

							if (temp == f_list->getCursor().return_number())
								break;

							// cursor�� ���� ��带 �˻��ϱ� ������ ������ ��� �˻� ��
							// flag2�� 1�� ������ �ѹ� �� �̰��� �����ϸ� break;
							if (f_list->get_cursor_next_node() == nullptr) {
								if (flag2++) {
									system("echo Can't find flight!");
									write_file << "Can't find flight!" << endl;
									break;
								}
							}
							else f_list->gotoNext();
						}

						if (flag2 != 1) {
							if (flag3 != 1) {
								f_list->getCursor().reserv_client(c_list->getCursor(), write_file);
								delete newclient;
							}
							else {
								f_list->getCursor().reserv_client(*newclient, write_file);
								c_list->insertItem(*newclient);
								newclient->update_client_list(c_list);
								delete newclient;
							}
						}
					}
				}
			}


			//	CP : ���� ���ฮ��Ʈ���� ����	(CP name flight_number)
			//			->��⸮��Ʈ�� ù��° ��� ������ ����Ʈ�� �߰�
			else if (cmd == "CP") {

				Client* newclient = new Client;
				cout << token << endl;
				write_file << token << endl;
				token = token.substr(3);	// ��� ������ string token�� �Է�

				length = token.length();	// �����Է�

				int flag = 0;
				int flag2 = 0;

				for (int i = 0; i < length; i++) {
					temp = "";
					while (token[i] != ' ') {
						temp += token[i];
						i++;
						if (length <= i) break;
					}

					flag++;
					if (flag == 1) {
						newclient->insert(temp);
					}

					else if (flag == 2) {

						f_list->gotoBeginning();

						while (flag2 != 2) {

							if (temp == f_list->getCursor().return_number())
								break;
							// cursor�� ���� ��带 �˻��ϱ� ������ ������ ��� �˻� ��
							// flag2�� 1�� ������ �ѹ� �� �̰��� �����ϸ� break;
							if (f_list->get_cursor_next_node() == nullptr ) {
								if (flag2++) {
									cout << "Can't find flight!" << endl << endl;
									write_file << "Can't find flight!" << endl << endl;
									break;
								}
							}
							else f_list->gotoNext();
						}
						if (flag2 != 2) {
							f_list->getCursor().cancel_client(*newclient, write_file);
							newclient->update_client_list(c_list);
							delete newclient;
						}
					}
				}
			}

			//	PA : ��������� ���������� ����� ��(�̸���), ����� ���(ť�� ������) �μ�
			//		(PA)
			else if (cmd == "PA") {

				cout << token << endl;
				write_file << token << endl;

				bool flag = false;
				int flag2 = 0;

				f_list->gotoBeginning();

				while (flag2 != 1) {

					f_list->getCursor().print_flight_info(write_file);
					f_list->getCursor().print_reserv_list(write_file);
					cout << endl;
					write_file << endl;
					f_list->getCursor().print_stand_by_list(write_file);
					cout << endl;
					write_file << endl;

					// cursor�� ���� ��带 �˻��ϱ� ������ ������ ��� �˻� ��
					// flag2�� 1�� ������ �ѹ� �� �̰��� �����ϸ� break;
					if (f_list->get_cursor_next_node() == nullptr && flag2++) {
						cout << endl;
						break;
					}
					else f_list->gotoNext();
				}
			}
			//	PF : ������� ��ȣ������ ��������� ���� �μ�	(PF)

			else if (cmd == "PF") {
				cout << token << endl;
				write_file << token << endl;
				

				bool flag = false;
				int flag2 = 0;

				f_list->gotoBeginning();

				while (flag2 != 1) {

					f_list->getCursor().print_flight_info(write_file);
					
					cout << endl;
					write_file << endl;

					// cursor�� ���� ��带 �˻��ϱ� ������ ������ ��� �˻� ��
					// flag2�� 1�� ������ �ѹ� �� �̰��� �����ϸ� break;
					if (f_list->get_cursor_next_node() == nullptr && flag2++) {
						cout << endl;
						write_file << endl;
						break;
					}
					else f_list->gotoNext();
				}
			}
			//PR : Ư�� ��������� PA�� ����	(PA flight_number)
			//		  -> ����� ���� ���ٸ� Error
			else if (cmd == "PR") {
				cout << token << endl;
				write_file << endl << token << endl;
				

				token = token.substr(3);	// ��� ������ string token�� �Է�

				length = token.length();	// �����Է�

				int flag = 0;

				for (int i = 0; i < length; i++) {
					temp = "";
					while (token[i] != ' ') {
						temp += token[i];
						i++;
						if (length <= i) break;
					}

					f_list->gotoBeginning();

					while (flag != 1) {

						if (temp == f_list->getCursor().return_number())
							break;

						// cursor�� ���� ��带 �˻��ϱ� ������ ������ ��� �˻� ��
						// flag�� 1�� ������ �ѹ� �� �̰��� �����ϸ� break;
						if (f_list->get_cursor_next_node() == nullptr && flag++) {

							system("echo Can't find flight!");
							write_file << "Can't find flight!" << endl;
							break;
						}
						else f_list->gotoNext();
					}
				}
				if (flag != 1) {
					f_list->getCursor().print_flight_info(write_file);
					cout << endl;
					write_file << endl;
				}
			}
			//pp : ������ ���� ���� ��ȹ�� ������� ��ȣ ������ �μ�	(PP name)
			//		 -> ��Ÿ�� �������(�����, ������, ����ok?����)
			else if (cmd == "PP") {
				InfoReserv* info_client = new InfoReserv(c_list, f_list);
			
				cout << token << endl;
				write_file << token << endl;
				token = token.substr(3);	// ��� ������ string token�� �Է�

				bool find = false;
				info_client->matching_client(c_list, token, write_file, find);
				info_client->print_client_reserv_list(f_list, write_file, find);
				delete info_client;
			}
			
			else {
				system("echo Error command");
				write_file << "Error command" << endl;
			}
		}
	}
	openfile.close();
	write_file.close();
	delete c_list;
	delete f_list;
}