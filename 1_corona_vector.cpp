#include<iostream>
#include<string>

using namespace std;

class corona_world {
public:
	corona_world(string name = "empty", int definedNum = 0, int deadNum = 0);
	void printInfo();

	string m_name;
	int m_definedNum;
	int m_deadNum;
	double m_rateOfDeath;
};

template<class T>
class DLLNode {
public:
	DLLNode()
	{
		next = prev = NULL;
	}
	DLLNode(const T& el, DLLNode* n = NULL, DLLNode* p = NULL) {
		info = el;
		next = n;
		prev = p;
	}
	T info;
	DLLNode* next, * prev;
};

template<class T>
class DLL{
public:
	DLL()
	{
		head = NULL;
	}
	~DLL()
	{
		for (DLLNode<T> *p=NULL; p != NULL ; )
		{
			p = head->next;
			delete head;
			head = p;
		}
	}
	void AddtoDLLSorted(const T& el);
	void DeleteDLLSorted(const string& name);
	void PrintDLLSorted();

private:
	DLLNode<T>* head;
};

corona_world::corona_world(string name, int definedNum, int deadNum)
{
	m_name = name;
	m_definedNum = definedNum;
	m_deadNum = deadNum;
	m_rateOfDeath = ((double)m_deadNum / m_definedNum) * 100;
}

void corona_world::printInfo()
{
	cout.width(10);
	cout << m_name;
	cout.width(10);
	cout << m_definedNum;
	cout.width(10);
	cout << m_deadNum;
	cout.width(10);
	cout << m_rateOfDeath << endl;
}

template<class T> void DLL<T>::AddtoDLLSorted(const T& el) {
	DLLNode<T>* temp = new DLLNode<T>;//새 노드 생성한다
	DLLNode<T>* pt = head; //추가되어야 할 부분을 알려주는 위치
	temp->info = el; //노드에 넣을 원소를 info로 초기화(info에 넣어준다)
	
	//1)노드가 비어있을 때 노드에 첫 내용 추가
	if (head == NULL) {
		head = temp;
		temp->prev = NULL;
		temp->next = NULL;
	}
	//2)info가 들어있는 노드일 때
	else {
		while (el.m_name > pt->info.m_name) { //국가명 탐색-추가 되는 위치를 찾아주는 역할
			if (pt->next == NULL)//마지막까지 돈다면
				break;//멈추기
			pt = pt->next;// 추가할 위치를 다음으로 넘긴다.
		}
		//_1. 처음 부분에 추가 된다면
		if (pt == head) {
			head = temp;
			pt->prev = temp;
			temp->prev = NULL; //처음에 추가되었기 때문에 앞 부분은 NULL
			temp->next = pt;
		}
		//_2. 마지막 부분에 추가 된다면
		else if (pt->next == NULL) {
			pt->next = temp;
			temp->prev = pt;
			temp->next = NULL;
		}
		//_3. 중간 부분에 추가 된다면
		else {
			pt->prev->next = temp; //temp 노드의 자리 지정
			temp->prev = pt->prev; //temp의 전 노드를 pt의 전전노드로 가리킴
			temp->next = pt; //temp의 다음은 pt노드로
			pt->prev = temp; //pt의 전 노드를 temp로 지정
			
		}
	}
}

template<class T>void DLL<T>::DeleteDLLSorted(const string& name) {
	DLLNode<T>* key = head; //임시 포인터에 헤드의 주소값으로 초기화
	if (key == NULL) //데이터가 없으면 반환한다
		return;
	while (key != NULL) {// 임시 포인터의 주소값이 NULL이 될 때까지 반복
		if (key->info.m_name == name) { //국가 찾기
			if (key == head) { //맨 앞 노드를 지우는 경우
				head = key->next;
				key->next->prev = NULL;
				delete key; //삭제
				break;
			}
			else if (key->next == NULL) { //마지막 노드를 지우는 경우
				key->prev->next = NULL;
				delete key;
				break;
			}
			else {//중간 노드를 삭제하는 경우
				key->prev->next = key->next;
				key->next->prev = key->prev;
				delete key;
				break;
			}
		}
		key = key->next;
	}
}

template<class T> void DLL<T>::PrintDLLSorted() {
	DLLNode<T>* printPt = head; //임시 포인터를 생성하고 이 포인터에 헤드의 주소값을 대입
	if (printPt == NULL) // 데이터가 들어있지 않다면 그냥 반환한다
		return;
	 else { //데이터가 하나 이상 들어있다면
		while (printPt != NULL) { //NULL이 될 때까지 반복한다
			printPt->info.printInfo(); //데이터를 출력하며
			printPt = printPt->next; //다음 포인터의 값을 부른다
		}
	}
}

int main()
{
	DLL<corona_world> DLLdata;
	DLLdata.AddtoDLLSorted(corona_world("USA", 387547, 12291));
	DLLdata.AddtoDLLSorted(corona_world("Spain", 140510, 13798));
	DLLdata.AddtoDLLSorted(corona_world("Italy", 135586, 17127));
	DLLdata.AddtoDLLSorted(corona_world("Germany", 107591, 2012));
	DLLdata.AddtoDLLSorted(corona_world("China", 81802, 3333));
	DLLdata.AddtoDLLSorted(corona_world("France", 78167, 10328));
	DLLdata.AddtoDLLSorted(corona_world("Iran", 62589, 3872));
	DLLdata.AddtoDLLSorted(corona_world("U.K", 55242, 6159));

	DLLdata.PrintDLLSorted(); //기본적으로 입력되어 있는 정보 추가 및 정렬

	while (true) {
		cout << "정보를 추가하거나 삭제할 수 있습니다." << endl;
		cout << "[정보를 추가]는 1, [국가 삭제]는 2, [종료]는 3을 입력하세요." << endl;
		int num = 0;
		cin >> num;

		if (num == 1) { //1 입력하면 정보 추가
			string addNation;
			int addDefinedNum = 0;
			int addDeadNum = 0;
			cout << "추가할 국가의 이름을 입력하세요(첫 글자는 대문자로 입력하세요): " << endl;
			cin >> addNation;
			cout << "코로나 확진자 수를 입력하세요: " << endl;
			cin >> addDefinedNum;
			cout << "사망자 수를 입력하세요: " << endl;
			cin >> addDeadNum;

			DLLdata.AddtoDLLSorted(corona_world(addNation, addDefinedNum, addDeadNum)); //추가할 정보를 함수에 넣는다

			DLLdata.PrintDLLSorted();//추가된 나라 출력
		}
		else if (num == 2) {
			cout << "삭제할 국가를 입력하세요(첫 글자는 대문자로 입력하세요): ";

			string temp;
			cin >> temp;

			DLLdata.DeleteDLLSorted(temp);

			DLLdata.PrintDLLSorted();
		}
		else if (num == 3) {
			cout << "정보 추가 및 삭제를 종료합니다." << endl;
			break;
		}
		else
			cout << "잘못 입력하였습니다." << endl;
		break;
	}
}
