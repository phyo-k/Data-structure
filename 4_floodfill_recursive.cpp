#include <iostream>

using namespace std;

int ans[10];

//재귀함수
void WBconvert(int block[10][10], int x, int y, int count)
{
	if ((x== 0) || (y == 0) || (x == 9) || (y == 9)) // 제일 바깥 쪽은 0으로 채운다.
		block[x][y] = 0;

	if (block[x][y] != 1) //0이면 그대로 반환한다.
		return;
	else {
		block[x][y] = 0;//색깔 흰색->검정색(번호1->0 바꾸기)
		ans[count]++; //영역 세기
		WBconvert(block, x + 1, y, count); //위
		WBconvert(block, x - 1, y, count); //오른쪽
		WBconvert(block, x, y + 1, count); //아래
		WBconvert(block, x, y - 1, count); //왼쪽
	}
}

int main()
{
	int block[10][10]; //10x10 배열 선언
	int b = 0, w = 0; //b=black=0, w=white=1
	int cnt = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if ((i==0)||(j==0)||(i==9)||(j==9)) //가장 큰 테두리는 0으로
				block[i][j] = 0;
			else { //안 쪽 배열은 난수 생성
				block[i][j] = rand() % 2;
				if (block[i][j] % 2 == 0)
					block[i][j] = 0; //2로 나누어 떨어지면 b(검정)
				else
					block[i][j] = 1; //그렇지 않으면 w(흰색)
			}
			cout << block[i][j] << " ";
		}
	cout << endl;
	}
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (block[i][j] == 1) { //원소가 1인 경우 0으로 바꿔준다.
				WBconvert(block, i, j, cnt);
				cnt++; //바뀌어지는 개수 세기
			}
		}
	}
	cout << endl;

	cout << cnt << " white(=1) areas of "; 
	for (int i = 0; i < cnt; i++) {
		if (i < cnt - 1)
			cout << ans[i] << ", ";
		else
			cout << "and " << ans[i] << " cells." << endl;
	}
		
	cout << endl;
	
	return 0;
}