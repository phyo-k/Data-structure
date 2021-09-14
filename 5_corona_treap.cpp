#include<iostream>
#include<string>

using namespace std;

typedef string KeyType; //value 저장
class TreapNode
{
public:
	KeyType value; //국가명
	double priority; // 노드가 갖는 우선 순위: 사망률
	int size; //노드를 루트로 하는 서브트립의 크기
	TreapNode* left;
	TreapNode* right;

	TreapNode(const KeyType _value)
		:value(_value), priority(rate()), size(1), left(NULL), right(NULL)
	{}
	double rate(void) {
		if ("USA")
			priority = 5.5;
		else if ("Spain")
			priority = 11.4;
		else if ("Italy")
			priority = 14.3;
		else if ("Germany")
			priority = 4.6;
		else if ("China")
			priority = 5.6;
		else if ("France")
			priority = 19.2;
		else if ("Mexico")
			priority = 11.1;
		else if ("Rumania")
			priority = 6.5;
		else if ("Ecuador")
			priority = 8.6;
		else if ("Korea")
			priority = 2.4;

		return priority;
	}
	void setLeft(TreapNode* newLeft) {
		left = newLeft;
		Size();
		return;
	}
	void setRight(TreapNode* newRight){
		right = newRight;
		Size();
		return;
	}
	void Size(void) {//노드를 루트로 하는 서브트립의 크기 계산
		size = 1;
		if (size = (left != NULL))
			size + left->size;
		else
			size;
		if (size = (right != NULL))
			size + right->size;
		else
			size;
		return;
	}
};

typedef pair<TreapNode*, TreapNode*> TreapNodePair; //split함수의 리턴 값 구조체

TreapNodePair split(TreapNode* root, KeyType value){//key값을 기준으로 노드 나눈다
	if (root == NULL) 
		return TreapNodePair(NULL, NULL);

	if (root->value < value) {
		TreapNodePair rs = split(root->right, value);
		root->setRight(rs.first);
		return TreapNodePair(root, rs.second);
	}
	else {
		TreapNodePair ls = split(root->left, value);
		root->setLeft(ls.second);
		return TreapNodePair(ls.first, root);
	}
	return TreapNodePair(NULL, NULL);
}

TreapNode* insertTreap(TreapNode* root, TreapNode* node){//우선순위 비교하며 트립 구성한다
	if (root == NULL)
		return node;
	
	if (root->priority > node->priority){
		if (root->value > node->value)
			root->setLeft(insertTreap(root->left, node));

		else
			root->setRight(insertTreap(root->right, node));
		
		return root;
	}
	else{
		TreapNodePair splited = split(root, node->value);
		node->setLeft(splited.first);
		node->setRight(splited.second);
		return node;
	}
	return NULL;
}

//두 트립의 루트 n1,n2가 주어지고 n1의 최대값이 n2의 최소값보다 작을 때 둘을 합쳐 새 루트를 반환
TreapNode* merge(TreapNode* n1,TreapNode* n2){ //max(t1)<max(t2)를 만족하는 한 서브트립, max(t1)<max(t2)를 만족하는 한 서브트립
	//두 트립중 하나가 NULL인 경우 남은 한 쪽을 반환
	if (n1 == NULL)
		return n2;
	if (n2 == NULL)
		return n1;
	//n2가 루트가 되어야하는 경우
	if (n1->priority < n2->priority){
		n2->setLeft(merge(n1, n2->left));
		return n2;
	}
	//n1이 루트가 되어야하는 경우
	else{
		n1->setRight(merge(n1->right, n2));
		return n1;
	}
	return NULL;
}

int cnt = 0;
TreapNode* searchNation(TreapNode* root, KeyType value) {//원하는 국가 검색
	while (root != 0) {
		cout << " -> " <<root->value;
		cnt++;
		if (root == NULL || root->value == value)
			return root;
		if (root->value < value)
			return searchNation(root->right, value);
		else
			return searchNation(root->left, value);
	}
}

TreapNode* deletedNode(TreapNode* root, KeyType value){
	if (root == NULL)
		return root;
	if (root->value == value){
		TreapNode* re = merge(root->left, root->right);
		delete root;
		return re;
	}
	else if (root->value > value){
		root->setLeft(deletedNode(root->left, value));
		return root;
	}
	else{
		root->setRight(deletedNode(root->right, value));
		return root;
	}
	return root;
}

void inorderNode(TreapNode* root){//inorder로 순회
	if (root != NULL){
		inorderNode(root->left);
		cout << root->value << ' ';
		inorderNode(root->right);
	}
	return;
}

int main(void)
{
	cout << "[코로나 발병 국가 정보]" << endl;
	cout << endl;
	cout << "발병 국가:   ";
	TreapNode* root = NULL; ///< 트립 선언
	root = insertTreap(root, new TreapNode("USA"));
	root = insertTreap(root, new TreapNode("Spain"));
	root = insertTreap(root, new TreapNode("Italy"));
	root = insertTreap(root, new TreapNode("Germany"));
	root = insertTreap(root, new TreapNode("China"));
	root = insertTreap(root, new TreapNode("France"));
	root = insertTreap(root, new TreapNode("Mexico"));
	root = insertTreap(root, new TreapNode("Rumania"));
	root = insertTreap(root, new TreapNode("Ecuador"));
	root = insertTreap(root, new TreapNode("Korea"));

	inorderNode(root);
	cout << endl;
	cout << endl;

	string nation;//검색할 국가
	int num = 0;
		cout << "1. 국가 탐색  2. 상위에 위치한 국가 삭제  3. 종료" << endl;
		cout << "입력 번호: ";
		cin >> num;
		cout << endl;
		if (num == 1) {
			cout << "[국가를 한 번 탐색합니다. 검색하고 싶은 나라를 입력하세요.]" << endl;
			cout << "검색할 나라: ";
			cin >> nation;
			root = searchNation(root, nation);
			cout << endl;
			cout << cnt-1 << "번의 탐색을 하였습니다." << endl;
		}
		else if (num == 2) {
			cout << "[상위에 위치한 국가를 삭제합니다.]" << endl;
			cout << " 현재 상위 국가는 France입니다. 이 국가를 삭제하겠습니다." << endl;
			root = deletedNode(root, "France");
			cout << "삭제한 결과:   ";
			inorderNode(root);
			cout << endl;
		}
		else if (num == 3)
			cout << "종료합니다." << endl;
	return 0;
}
