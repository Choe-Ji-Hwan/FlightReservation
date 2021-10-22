# Flight Reservation

2020-1학기 자료구조및실습 중간고사 대체

비행기 예약 시스템

(링크드 리스트와 큐 등 이용한 예약, 정의되어 있는 라이브러리가 아닌 자기가 구현한 자료구조이용)

```
  자료구조및실습01 최지환 midterm project
	Flight Reservation System


	*주의 : 1. 대기 리스트는 한 비행편의 대기 리스트(Queue)를 사용한다.
	*주의 : 2. 예약 리스트는 예약한 것이고, 또 다른 리스트이다.
				(비행기에 예약(이름순) -> capacity가 넘으면 대기 리스트로 보낸다.)
				(Dubly Linked List) 사용
	*주의 : 3. 고객은 여러 대의 비행기를 예약 가능하다(여러 나라를 여행할 예정이다.)


	어떻게 돌아가는 지 간단한 설명
	명령문 : 명령설명		(명령형태)
		1) 입력/삭제 (입력은 파일을 읽어 입력받는다. 한줄씩 명령이 적혀있다)
					(만약 명령어가 해당되지 않는 명령어면 Error)
			IF : 새로운 비행기편 추가			(IF flight_number from_city to_city capacity)
			DF : 비행기편을 리스트에서 삭제	(DF flight_number)
			RP : 고객을 비행기편에 예약		(RP name flight_number)
			CP : 고객을 예약리스트에서 삭제	(CP name flight_number)
				 ->대기리스트의 첫번째 사람 예약자 리스트에 추가

		2) 인쇄
			PA : 비행기편의 순서에 따라 예약된 고객(이름순), 대기자 명단(큐에 도착순) 인쇄
					(PA)
			PF : 비행기편 번호순으로 비행기편의 정보 인쇄	(PF)
			PR : 특정 비행기편의 PA를 행함	(PA flight_number)
				  -> 비행기 편이 없다면 Error
			pp : 지정된 고객의 비행 계획을 비행기편 번호 순으로 인쇄	(PP name)
				 -> 나타낼 비행기편(출발지, 도착지, 예약ok?여부)
```
# input(samplein.p1.txt)
```
IF 0056 Lafayette Detroit 004
IF 1234 Chicago Baltimore 006
IF 0196 Dayton Indianapolis 003
PA
RP Smith 0056
RP Hubbard 0196
RP Jones 0056
RP Churchill 0056
RP Sauvage 0056
RP Smith 0196
RP Smith 0056
RP Smith 1234
RP Jones 0196
RP Hubbard 0056
PF
PR 0056
PP Smith
CP Churchill 0056
RP Churchill 0196
RP Wiley 0196
PA
CP Smith 0
PR 0196
DF 0196
PA
```
# output(OUTFILE.p1.txt)
```
IF 0056 Lafayette Detroit 004
IF 1234 Chicago Baltimore 006
IF 0196 Dayton Indianapolis 003
PA
-----------------------------
Flight-number	: 0056
From-city 	: Lafayette
to-city		: Detroit
capacity		: 4
reserved-number	: 0
empty reservation list
empty stand-by list
-----------------------------

-----------------------------
Flight-number	: 0196
From-city 	: Dayton
to-city		: Indianapolis
capacity		: 3
reserved-number	: 0
empty reservation list
empty stand-by list
-----------------------------

-----------------------------
Flight-number	: 1234
From-city 	: Chicago
to-city		: Baltimore
capacity		: 6
reserved-number	: 0
empty reservation list
empty stand-by list
-----------------------------

RP Smith 0056
RP Hubbard 0196
RP Jones 0056
RP Churchill 0056
RP Sauvage 0056
RP Smith 0196
RP Smith 0056
Smith is already exist in reservation list
RP Smith 1234
RP Jones 0196
RP Hubbard 0056
PF
-----------------------------
Flight-number	: 0056
From-city 	: Lafayette
to-city		: Detroit
capacity		: 4
reserved-number	: 4

-----------------------------
Flight-number	: 0196
From-city 	: Dayton
to-city		: Indianapolis
capacity		: 3
reserved-number	: 3

-----------------------------
Flight-number	: 1234
From-city 	: Chicago
to-city		: Baltimore
capacity		: 6
reserved-number	: 1


PR 0056
-----------------------------
Flight-number	: 0056
From-city 	: Lafayette
to-city		: Detroit
capacity		: 4
reserved-number	: 4

PP Smith
-----------------------------
Flight-number	: 0056
From-city		: Lafayette
to-city		: Detroit
(status)->reservation ok 

Flight-number	: 0196
From-city		: Dayton
to-city		: Indianapolis
(status)->reservation ok 

Flight-number	: 1234
From-city		: Chicago
to-city		: Baltimore
(status)->reservation ok 

-----------------------------

CP Churchill 0056
RP Churchill 0196
RP Wiley 0196
PA
-----------------------------
Flight-number	: 0056
From-city 	: Lafayette
to-city		: Detroit
capacity		: 4
reserved-number	: 4
reservation list: (Hubbard) (Jones) (Sauvage) (Smith) 
empty stand-by list
-----------------------------

-----------------------------
Flight-number	: 0196
From-city 	: Dayton
to-city		: Indianapolis
capacity		: 3
reserved-number	: 3
reservation list: (Hubbard) (Jones) (Smith) 
stand-by list   : (Churchill) (Wiley) 
-----------------------------

-----------------------------
Flight-number	: 1234
From-city 	: Chicago
to-city		: Baltimore
capacity		: 6
reserved-number	: 1
reservation list: (Smith) 
empty stand-by list
-----------------------------

CP Smith 0
Can't find flight!


PR 0196
-----------------------------
Flight-number	: 0196
From-city 	: Dayton
to-city		: Indianapolis
capacity		: 3
reserved-number	: 3

DF 0196
PA
-----------------------------
Flight-number	: 0056
From-city 	: Lafayette
to-city		: Detroit
capacity		: 4
reserved-number	: 4
reservation list: (Hubbard) (Jones) (Sauvage) (Smith) 
empty stand-by list
-----------------------------

-----------------------------
Flight-number	: 1234
From-city 	: Chicago
to-city		: Baltimore
capacity		: 6
reserved-number	: 1
reservation list: (Smith) 
empty stand-by list
-----------------------------
```
