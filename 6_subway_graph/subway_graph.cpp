#include "subway_graph.h"

int main(){
	MatrixWGraph g;
	char s1[4], s2[4];
	char line1, line2;
	int num1, num2;

	cout << "[지하철 노선도 프로그램입니다.]" << endl;
	cout << endl;
	cout << "1호선(a): 서울역(a1)  시청(a2)       종각(a3)       종로3가(a4)       종로5가(a5)      동대문(a6)" << endl;
	cout << endl;
	cout << "2호선(b): 시청(b1)    을지로3가(b2)  을지로4가(b3)  동대문운동장(b4)  신당(b5)         상왕십리(b6)" << endl;
	cout << "          왕십리(b7)  한양대(b8)     뚝섬(b9)       성수(b10)         건대입구(b11)    구의(b12)" << endl;
	cout << "          강변(b13)   잠실나루(b14)  잠실(b15)      잠실새내(b16)     종합운동장(b17)  삼성(b18)" << endl;
	cout << "          선릉(b19)   역삼(b20)      강남(b21)      교대(b22)         서초(b23)" << endl;
	cout << endl;
	cout << "3호선(c): 경복궁(c1)  안국(c2)       종로3가(c3)    을지로3가(c4)     충무로(c5)       약수(c6)" << endl;
	cout << "          금호(c7)    옥수(c8)       압구정(c9)     신사(c10)         잠원(c11)        고속버스터미널(c12)" << endl;
	cout << "          교대(c13)   남부터미널(c14)" << endl;
	cout << endl;
	cout << "※ 위와 같이 알파벳과 숫자로 써주시면 됩니다. 예)서울역은 a1, 잠실은 b15" << endl;
	cout << "출발역 : ";
	cin >> s1;
	cout << "도착역 : ";
	cin >> s2;
	
	line1 = s1[0];
	if (!s1[2])
		num1 = (int)(s1[1] - 48);
	else
		num1 = (int)((s1[1] - 48) * 10 + (s1[2] - 48));

	line2 = s2[0];
	if (!s2[2])
		num2 = (int)(s2[1] - 48);
	else
		num2 = (int)((s2[1] - 48) * 10 + (s2[2] - 48));

	g.result(line1, num1, line2, num2);
	return 0;
}