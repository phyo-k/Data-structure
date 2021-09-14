#include <iostream>
#include <stack>

#define MAX 43 //44이상부터는 제대로 작동하지 않습니다..
#define INF 9999

using namespace std;

class Station{
private:
	char line; //노선
	int num; //역 이름
	int x, y; //좌표
public:
	Station(char l = 'a', int n = 1, int i = 0, int j = 0) :line(l), num(n), x(i), y(j)
	{}
	friend class MatrixWGraph;
	friend ostream& operator<<(ostream& os, Station& s);
};

ostream& operator<<(ostream& os, Station& s)
{
	cout << s.line << s.num << " ";
	return os;
}

class MatrixWGraph{
private:
	Station metroStation[MAX]; //a, b, c 노선의 모든 역
	double length[MAX][MAX]; //간선의 길이
	double dist[MAX]; //최단 경로
	bool s[MAX]; //최단 경로 찾았는지
	int path[MAX]; //시작점과 끝점 사이의 경로
public:
	MatrixWGraph(){
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				if (i == j)
					length[i][j] = 0;
				else
					length[i][j] = INF;
			}
		}
		Initialize();
	}

	int findIndex(char line, int num){
		int idx;
		int n = num;
		switch (line){
		case 'a'://1호선일 때
			idx = num - 1;
			break;
		case 'b'://2호선일 때
			idx = num + 5;
			break;
		case 'c'://3호선일 때
			idx = num + 28;
			break;
		}
		return idx;
	}

	void AddEdge(char line1, int num1, char line2, int num2, double weight) //가중치 간선 추가
	{
		int i, j;

		i = findIndex(line1, num1);
		j = findIndex(line2, num2);
		length[i][j] = weight;
		length[j][i] = weight;
	}

	void Initialize()
	{
		//a = 1호선
		metroStation[0] = Station('a', 1, 0, 8);//서울역
		metroStation[1] = Station('a', 2, 0, 9);//시청
		metroStation[2] = Station('a', 3, 0, 10);//종각
		metroStation[3] = Station('a', 4, 1, 10);//종로3가
		metroStation[4] = Station('a', 5, 2, 10);//종로5가
		metroStation[5] = Station('a', 6, 3, 10);//동대문

		//b = 2호선
		metroStation[6] = Station('b', 1, 0, 9);//시청
		metroStation[7] = Station('b', 2, 1, 9);//을지로3가
		metroStation[8] = Station('b', 3, 2, 9);//을지로4가
		metroStation[9] = Station('b', 4, 3, 9);//동대문운동장
		metroStation[10] = Station('b', 5, 4, 9);//신당
		metroStation[11] = Station('b', 6, 5, 9);//상왕십리
		metroStation[12] = Station('b', 7, 6, 9);//왕십리
		metroStation[13] = Station('b', 8, 7, 9);//한양대
		metroStation[14] = Station('b', 9, 8, 9);//뚝섬
		metroStation[15] = Station('b', 10, 8, 8);//성수
		metroStation[16] = Station('b', 11, 8, 7);//건대입구
		metroStation[17] = Station('b', 12, 8, 6);//구의
		metroStation[18] = Station('b', 13, 8, 5);//강변
		metroStation[19] = Station('b', 14, 8, 3);//잠실나루
		metroStation[20] = Station('b', 15, 8, 2);//잠실
		metroStation[21] = Station('b', 16, 8, 1);//잠실새내
		metroStation[22] = Station('b', 17, 7, 1);//종합운동장
		metroStation[23] = Station('b', 18, 6, 1);//삼성
		metroStation[24] = Station('b', 19, 5, 1);//선릉
		metroStation[25] = Station('b', 20, 4, 1);//역삼
		metroStation[26] = Station('b', 21, 3, 1);//강남
		metroStation[27] = Station('b', 22, 2, 1);//교대
		metroStation[28] = Station('b', 23, 1, 1);//서초
		
		//c = 3호선
		metroStation[29] = Station('c', 1, 0, 11);//경복궁
		metroStation[30] = Station('c', 2, 1, 11);//안국
		metroStation[31] = Station('c', 3, 1, 10);//종로3가
		metroStation[32] = Station('c', 4, 1, 9);//을지로3가
		metroStation[33] = Station('c', 5, 1, 8);//충무로
		metroStation[34] = Station('c', 6, 2, 8);//약수
		metroStation[35] = Station('c', 7, 2, 7);//금호
		metroStation[36] = Station('c', 8, 2, 6);//옥수
		metroStation[37] = Station('c', 9, 2, 5);//압구정
		metroStation[38] = Station('c', 10, 2, 4);//신사
		metroStation[39] = Station('c', 11, 2, 3);//잠원
		metroStation[40] = Station('c', 12, 2, 2);//고속버스터미널
		metroStation[41] = Station('c', 13, 2, 1);//교대
		metroStation[42] = Station('c', 14, 2, 0);//남부터미널

		//1호선끼리 시간-엑셀 데이터
		AddEdge('a', 1, 'a', 2, 2);
		AddEdge('a', 2, 'a', 3, 3);
		AddEdge('a', 3, 'a', 4, 1);
		AddEdge('a', 4, 'a', 5, 2);
		AddEdge('a', 5, 'a', 6, 2);

		//2호선끼리 시간-엑셀데이터
		AddEdge('b', 1, 'b', 2, 2);
		AddEdge('b', 2, 'b', 3, 1);
		AddEdge('b', 3, 'b', 4, 2);
		AddEdge('b', 4, 'b', 5, 2);
		AddEdge('b', 5, 'b', 6, 2);
		AddEdge('b', 6, 'b', 7, 1);
		AddEdge('b', 7, 'b', 8, 2);
		AddEdge('b', 8, 'b', 9, 2);
		AddEdge('b', 9, 'b', 10, 1);
		AddEdge('b', 10, 'b', 11, 2);
		AddEdge('b', 11, 'b', 12, 3);
		AddEdge('b', 12, 'b', 13, 1);
		AddEdge('b', 13, 'b', 14, 3);
		AddEdge('b', 14, 'b', 15, 2);
		AddEdge('b', 15, 'b', 16, 2);
		AddEdge('b', 16, 'b', 17, 2);
		AddEdge('b', 17, 'b', 18, 2);
		AddEdge('b', 18, 'b', 19, 2);
		AddEdge('b', 19, 'b', 20, 2);
		AddEdge('b', 20, 'b', 21, 1);
		AddEdge('b', 21, 'b', 22, 2);
		AddEdge('b', 22, 'b', 23, 2);

		//3호선끼리 시간-엑셀데이터
		AddEdge('c', 1, 'c', 2, 2);
		AddEdge('c', 2, 'c', 3, 2);
		AddEdge('c', 3, 'c', 4, 2);
		AddEdge('c', 4, 'c', 5, 1);
		AddEdge('c', 5, 'c', 6, 2);
		AddEdge('c', 6, 'c', 7, 1);
		AddEdge('c', 7, 'c', 8, 2);
		AddEdge('c', 8, 'c', 9, 2);
		AddEdge('c', 9, 'c', 10, 3);
		AddEdge('c', 10, 'c', 11, 2);
		AddEdge('c', 11, 'c', 12, 2);
		AddEdge('c', 12, 'c', 13, 2);
		AddEdge('c', 13, 'c', 14, 2);
		
		//환승역 소요시간 - 네이버지도 7월3일 21시20분 기준입니다.
		AddEdge('a', 4, 'c', 3, 3);//종로3가
		AddEdge('b', 2, 'c', 4, 3);//을지로3가
		AddEdge('a', 2, 'b', 1, 3);//시청
		AddEdge('b', 22, 'c', 13, 3);//교대
	}

	int Choose(int n) //s[w]가 0이고 dist[u]가 dist[w] 중 최소일 때 반환
	{
		int min = INF;
		int u = -1; //정점이 음수일 수는 없으므로 초기값을 -1

		for (int w = 0; w < n; w++) {
			if (!s[w] && dist[w] < min){
				min = dist[w];
				u = w;
			}
		}
		return u;
	}

	void ShortestPath(const int n, const int v)
	{//dist[j], 0<=j<n은 n개의 정점을 가진 방향 그래프 G에서 정점 v에서 정점 j까지의 최단 경로 길이로 설정됨
		for (int i = 0; i < n; i++){
			s[i] = false;
			path[i] = -1;
			dist[i] = length[v][i];
		}
		s[v] = true;
		dist[v] = 0;
		for (int i = 0; i < n - 2; i++) { //정점 v로부터 n-1개 경로를 결정
			int u = Choose(n); //s[w]가 0이고 dist[u]가 dist[w] 중 최소일 때 반환

			s[u] = true;

			for (int w = 0; w < n; w++) {
				if (!s[w] && dist[u] + length[u][w] < dist[w]) {
					path[w] = u; //바뀌기 전에 저장
					dist[w] = dist[u] + length[u][w];
				}
			}
		}
	}

	void result(char line1, int num1, char line2, int num2) {
		stack<int> s;
		int i, j, idx;

		i = findIndex(line1, num1);
		j = findIndex(line2, num2);
		ShortestPath(MAX, i);
		idx = j; //도착역이 바뀌면 안되기 때문에

		cout << metroStation[i].line << metroStation[i].num << " -> ";
		while (1) {//도착역 직전역부터 출발역 다음역까지 stack에 넣는다
			if (path[idx] == -1)
				break;

			s.push(path[idx]);
			idx = path[idx];
		}
		while (!s.empty()) {//스택이 빌 때까지 출력한다
			int v = s.top();

			s.pop();
			cout << metroStation[v].line << metroStation[v].num << " -> ";
		}
		cout << metroStation[j].line << metroStation[j].num << endl;
		double time = dist[j];
		double second = time - (int)time;

		cout << "소요시간은 : " << (int)time << "분입니다.";

		if (second)
			cout << "30초" << endl;
		else
			cout << endl;
	}
};
