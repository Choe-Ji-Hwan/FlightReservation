//----------------------------------------------------------------------------------------
//
//  자료구조및실습01 2017112104 최지환 midterm project
//	Flight Reservation System
//
//
//	*주의 : 1. 대기 리스트는 한 비행편의 대기 리스트(Queue)를 사용한다.
//	*주의 : 2. 예약 리스트는 예약한 것이고, 또 다른 리스트이다.
//				(비행기에 예약(이름순) -> capacity가 넘으면 대기 리스트로 보낸다.)
//				(Dubly Linked List) 사용
//	*주의 : 3. 고객은 여러 대의 비행기를 예약 가능하다(여러 나라를 여행할 예정이다.)
//
//
//	어떻게 돌아가는 지 간단한 설명
//	명령문 : 명령설명		(명령형태)
//		1) 입력/삭제 (입력은 파일을 읽어 입력받는다. 한줄씩 명령이 적혀있다)
//					(만약 명령어가 해당되지 않는 명령어면 Error)
//			IF : 새로운 비행기편 추가			(IF flight_number from_city to_city capacity)
//			DF : 비행기편을 리스트에서 삭제	(DF flight_number)
//			RP : 고객을 비행기편에 예약		(RP name flight_number)
//			CP : 고객을 예약리스트에서 삭제	(CP name flight_number)
//				 ->대기리스트의 첫번째 사람 예약자 리스트에 추가
//
//		2) 인쇄
//			PA : 비행기편의 순서에 따라 예약된 고객(이름순), 대기자 명단(큐에 도착순) 인쇄
//					(PA)
//			PF : 비행기편 번호순으로 비행기편의 정보 인쇄	(PF)
//			PR : 특정 비행기편의 PA를 행함	(PA flight_number)
//				  -> 비행기 편이 없다면 Error
//			pp : 지정된 고객의 비행 계획을 비행기편 번호 순으로 인쇄	(PP name)
//				 -> 나타낼 비행기편(출발지, 도착지, 예약ok?여부)
//------------------------------------------------------------------------------------------

#include "Flight.h"
#include "Client.h"
#include "InfoReserv.h"

using namespace std;

int main() {

	// 중복이 안되게 고객을 리스트안에 넣는 리스트는 클래스안에 구현
	List<Client>* c_list = new List<Client>;	// 전체 고객 리스트(중복허용)
	List<Flight>* f_list = new List<Flight>;	// 전체 비행기편 리스트(중복허용)

	ifstream openfile("samplein.p1.txt");
	ofstream write_file("OUTFILE.P1.txt");
	string token;
	string temp;
	int flag = 0;
	int length = 0;

	// 파일이 잘 열리는 지 확인
	if (openfile.is_open()) {
		// EOF나올 때 가지 반복
		while (!openfile.eof()) {

			// 한 줄씩 token에 입력
			getline(openfile, token, '\n');

			// 명령어 추출
			string cmd = token.substr(0, 2);

			//IF: 새로운 비행기편 추가(IF flight_number from_city to_city capacity)
			if (cmd == "IF") {
				Flight* newflight = new Flight;
				cout << token << endl;	// 명령 출력
				write_file << token << endl;
				token = token.substr(3);	// 명령 이후의 string token에 입력

				length = token.length();	// 길이입력

				// Flight객체 노드에 정보 입력
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

				// 비행기가 이미 존재 하면 비행기를 넣지 않는다.
				int flag2 = 0;
				f_list->gotoBeginning();

				while (flag2 != 1) {
					if (f_list->isEmpty()) {	// 비행기 리스트가 비어있음 -> 존재x
						flag2++;
						break;
					}
					if (temp == f_list->getCursor().return_number())	// 존재할 때
						break;

					// cursor로 다음 노드를 검사하기 때문에 마지막 노드 검사 후
					// flag2에 1일 더해져 한번 더 이곳에 도착하면 break;
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

			//DF : 비행기편을 리스트에서 삭제	(DF flight_number)
			else if (cmd == "DF") {

				cout << token << endl;
				write_file << token << endl;
				token = token.substr(3);	// 명령 이후의 string token에 입력

				length = token.length();	// 길이입력

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
					// cursor로 다음 노드를 검사하기 때문에 마지막 노드 검사 후
					// flag2에 1일 더해져 한번 더 이곳에 도착하면 break;
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
					
					// 고객의 예약/대기 리스트에도 삭제
					int flag3 = 0;
					c_list->gotoBeginning();

					while (flag3 != 2) {

						if(c_list->getCursor().return_myf_reserv_list() != nullptr)
						c_list->getCursor().delete_my_reserv_flight(&delete_soon_flight);

						if(c_list->getCursor().return_myf_standby_list() != nullptr)
						c_list->getCursor().delete_my_standby_flight(&delete_soon_flight);

						// cursor로 다음 노드를 검사하기 때문에 마지막 노드 검사 후
						// flag2에 1일 더해져 한번 더 이곳에 도착하면 break;
						if (c_list->get_cursor_next_node() == nullptr) {
							if (flag3++) {
								break;
							}
						}
						else c_list->gotoNext();
					}
				}
			}

			//RP : 고객을 비행기편에 예약		(RP name flight_number)
			else if (cmd == "RP") {

				Client* newclient = new Client;

				cout << token << endl;
				write_file << token << endl;
				token = token.substr(3);	// 명령 이후의 string token에 입력

				length = token.length();	// 길이입력

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

							// cursor로 다음 노드를 검사하기 때문에 마지막 노드 검사 후
							// flag3에 1일 더해져 한번 더 이곳에 도착하면 break;
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

							// cursor로 다음 노드를 검사하기 때문에 마지막 노드 검사 후
							// flag2에 1일 더해져 한번 더 이곳에 도착하면 break;
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


			//	CP : 고객을 예약리스트에서 삭제	(CP name flight_number)
			//			->대기리스트의 첫번째 사람 예약자 리스트에 추가
			else if (cmd == "CP") {

				Client* newclient = new Client;
				cout << token << endl;
				write_file << token << endl;
				token = token.substr(3);	// 명령 이후의 string token에 입력

				length = token.length();	// 길이입력

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
							// cursor로 다음 노드를 검사하기 때문에 마지막 노드 검사 후
							// flag2에 1일 더해져 한번 더 이곳에 도착하면 break;
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

			//	PA : 비행기편의 순서에따라 예약된 고객(이름순), 대기자 명단(큐에 도착순) 인쇄
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

					// cursor로 다음 노드를 검사하기 때문에 마지막 노드 검사 후
					// flag2에 1일 더해져 한번 더 이곳에 도착하면 break;
					if (f_list->get_cursor_next_node() == nullptr && flag2++) {
						cout << endl;
						break;
					}
					else f_list->gotoNext();
				}
			}
			//	PF : 비행기편 번호순으로 비행기편의 정보 인쇄	(PF)

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

					// cursor로 다음 노드를 검사하기 때문에 마지막 노드 검사 후
					// flag2에 1일 더해져 한번 더 이곳에 도착하면 break;
					if (f_list->get_cursor_next_node() == nullptr && flag2++) {
						cout << endl;
						write_file << endl;
						break;
					}
					else f_list->gotoNext();
				}
			}
			//PR : 특정 비행기편의 PA를 행함	(PA flight_number)
			//		  -> 비행기 편이 없다면 Error
			else if (cmd == "PR") {
				cout << token << endl;
				write_file << endl << token << endl;
				

				token = token.substr(3);	// 명령 이후의 string token에 입력

				length = token.length();	// 길이입력

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

						// cursor로 다음 노드를 검사하기 때문에 마지막 노드 검사 후
						// flag에 1일 더해져 한번 더 이곳에 도착하면 break;
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
			//pp : 지정된 고객의 비행 계획을 비행기편 번호 순으로 인쇄	(PP name)
			//		 -> 나타낼 비행기편(출발지, 도착지, 예약ok?여부)
			else if (cmd == "PP") {
				InfoReserv* info_client = new InfoReserv(c_list, f_list);
			
				cout << token << endl;
				write_file << token << endl;
				token = token.substr(3);	// 명령 이후의 string token에 입력

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