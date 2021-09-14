#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template<class T, int capacity = 30> //범용적인 stack을 만들기 위해서 templat사용
class Stack {
public:
	Stack() {
		pool.reserve(capacity);
	}
	void clear() {
		pool.clear();
	}
	bool isEmpty() const {
		return pool.empty();
	}
	T& topEL() {
		return pool.back();
	}
	T pop() {
		T el = pool.back();
		pool.pop_back();
		return el;
	}
	void push(const T& el) {
		pool.push_back(el);
	}
private:
	vector<T> pool; //데이터 공간 만들어 놓음
};

int main()
{
	vector <int>v1; //입력받은 x의 자릿수 저장
	vector <int>v2; //입력받은 y의 자릿수 저장
	stack <int>s1; //x의 자릿수 거꾸로 스택에 저장
	stack <int>s2; //y의 자릿수 거꾸로 스택에 저장
	stack <int>result; //더한 숫자를 스택에 저장

	int x, y; //입력받을 두 수
	cout << "덧셈을 할 숫자를 스페이스바로 구분하여 입력하세요." << endl;
	cin >> x >> y;
	cout << x << " + " << y << " = ";

	int num1 = 0; //x의 자릿수
	while (x != 0) { //x의 자릿수 나누고 벡터 v1에 저장
		num1 = x % 10;
		v1.push_back(num1);
		x = x / 10;
	}
	for (int i = 0; ; i++) { //벡터 v1의 끝부터 스택 s1에 저장
		s1.push(v1.back());
		v1.pop_back();
		if (v1.empty()) //v1이 비면 스택에 저장 멈춘다
			break;
	}

	int num2 = 0; //y의 자릿수
	while (y != 0) { //y의 자릿수 나누고 벡터 v2에 저장
		num2 = y % 10;
		v2.push_back(num2);
		y = y / 10;
	}
	for (int i = v2.back(); ; i++) { //벡터 v2의 끝부터 스택 s2에 저장
		s2.push(v2.back());
		v2.pop_back();
		if (v2.empty()) //v2가 비면 스택에 저장 멈춘다
			break;
	}
	int sum;
	while (!s1.empty() && !s2.empty()) { //두 스택이 비어있지 않을 때까지 반복
		if (s1.top() + s2.top() < 10) { //두 스택의 합이 10 미만일 때
			sum = s1.top() + s2.top(); //자리수가 같은 경우 여기만 실행
			result.push(sum);
			s1.pop();
			s2.pop();
			//자리수가 다른 경우
			if (!s1.empty() && s2.empty()) { //스택1이 비어있지 않았을 때
				while (!s1.empty()) { //스택1이 빌 때까지
					result.push(s1.top());
					s1.pop();
				}
			}
			else if (s1.empty() && !s2.empty()) { //스택2가 비어있지 않을 때
				while (!s2.empty()) { //스택 2가 빌 때까지
					result.push(s2.top());
					s2.pop();
				}
			}
		}
		else if(s1.top() + s2.top() >= 10) { //두 스택의 합이 10 이상일 때
				sum = s1.top() + s2.top();
				sum -= 10;
				result.push(sum);
				s1.pop();
				s2.pop();
				
				while (true) {
				if (!s1.empty() && s2.empty()) { //스택1이 비어있지 않을 때
						s1.top() += 1;
						while (true) { //합이 10 이상일 때
						if (s1.size() == 1) {
							result.push(s1.top());
							s1.pop();
							break;
						}
						if (s1.top() >= 10) {
							result.push(s1.top() - 10);
							s1.pop();
							result.push(s1.top() + 1);
							s1.pop();
							if (s1.empty()) //비면 멈춘다
								break;
						}
						else if (s1.top() < 10) {
							result.push(s1.top());
							s1.pop();
							if (s1.empty()) //비면 멈춘다
								break;
						}	
					}
				}
				else if (s1.empty() && !s2.empty()) { //스택 2가 비어있지 않을 때
					s2.top() += 1;
					while (true) { //합이 10 이상일 때
						if (s2.size() == 1) {
							result.push(s2.top());
							s2.pop();
							break;
						}
						if (s2.top() >= 10) {
							result.push(s2.top() - 10);
							s2.pop();
							result.push(s2.top() + 1);
							s2.pop();
							if (s2.empty()) //비면 멈춘다
								break;
						}
						else if (s2.top() < 10) {
							result.push(s2.top());
							s2.pop();
							if (s2.empty()) //비면 멈춘다
								break;
						}
					}
				}
				else if (s1.empty() && s2.empty()) { //두 스택이 비어있으면
					result.push(1);
				}
				else { //두 스택에 값이 있으면
					sum = s1.top() + s2.top() + 1;
					s1.pop();
					s2.pop();
					if (sum >= 10) {
						sum -= 10;
						result.push(sum);
						
						while (true) {
							if (!s1.empty() && s2.empty()) {
								if (s1.top() + 1 < 10) {
									result.push(s1.top() + 1);
									s1.pop();
								}
								else {
									result.push(s1.top() + 1 - 10);
									s1.pop();
									result.push(s1.top() + 1);
									s1.pop();
								}
								while (!s1.empty()) {
									result.push(s1.top());
									s1.pop();
								 }
							}
							else if (s1.empty() && !s2.empty()) {
								if (s2.top() + 1 < 10) {
									result.push(s2.top() + 1);
									s2.pop();
								}
								else {
									result.push(s2.top() + 1 - 10);
									s2.pop();
									result.push(s2.top() + 1);
									s2.pop();
								}
								while (!s2.empty()) {
									result.push(s2.top());
									s2.pop();
								}
							}
							else if (!s1.empty() && !s2.empty()) {
								sum = s1.top() + s2.top() + 1;
								s1.pop();
								s2.pop();
								while (true) {
									if (s1.empty() || s2.empty() || s1.empty() && s2.empty()) {
										if (s1.empty() || s2.empty()) {
											if (sum < 10)
												result.push(sum);
											else if (sum >= 10)
												result.push(sum);
										}
										break;
									}
									if (sum >= 10) {
										result.push(sum - 10);
									}
									else if (sum < 10) {
										result.push(sum);
									}
									sum = s1.top() + s2.top();
									s1.pop();
									s2.pop();
								}
							}
							else {
								result.push(1);
							}
							break;
						}
					}
					else if (sum < 10) {
						result.push(sum);
						if (!s1.empty()&&s2.empty()) {
							while (true) {
								result.push(s1.top());
								s1.pop();
								if (s1.empty())
									break;
							}
						}
						else if (s1.empty() && !s2.empty()) {
							while (true) {
								result.push(s2.top());
								s2.pop();
								if (s2.empty())
									break;
							}
						}
						else if (!s1.empty() && !s2.empty()) {
							while (true) {
								result.push(s1.top() + s2.top());
								s1.pop();
								s2.pop();
								if (s1.empty() || s2.empty())
								break;
							}
						}
					}
				}
				if (s1.empty() && s2.empty())
					break;
			}
		}
	if (s1.empty() && s2.empty())
		break;
	}

	for (int i = 0;; i++) {
		cout << result.top();
		result.pop();
		if (result.empty())
			break;
	}
	cout << "입니다." << endl;

	cin.get();
}
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template<class T, int capacity = 30> //범용적인 stack을 만들기 위해서 templat사용
class Stack {
public:
	Stack() {
		pool.reserve(capacity);
	}
	void clear() {
		pool.clear();
	}
	bool isEmpty() const {
		return pool.empty();
	}
	T& topEL() {
		return pool.back();
	}
	T pop() {
		T el = pool.back();
		pool.pop_back();
		return el;
	}
	void push(const T& el) {
		pool.push_back(el);
	}
private:
	vector<T> pool; //데이터 공간 만들어 놓음
};

int main()
{
	vector <int>v1; //입력받은 x의 자릿수 저장
	vector <int>v2; //입력받은 y의 자릿수 저장
	stack <int>s1; //x의 자릿수 거꾸로 스택에 저장
	stack <int>s2; //y의 자릿수 거꾸로 스택에 저장
	stack <int>result; //더한 숫자를 스택에 저장

	int x, y; //입력받을 두 수
	cout << "덧셈을 할 숫자를 스페이스바로 구분하여 입력하세요." << endl;
	cin >> x >> y;
	cout << x << " + " << y << " = ";

	int num1 = 0; //x의 자릿수
	while (x != 0) { //x의 자릿수 나누고 벡터 v1에 저장
		num1 = x % 10;
		v1.push_back(num1);
		x = x / 10;
	}
	for (int i = 0; ; i++) { //벡터 v1의 끝부터 스택 s1에 저장
		s1.push(v1.back());
		v1.pop_back();
		if (v1.empty()) //v1이 비면 스택에 저장 멈춘다
			break;
	}

	int num2 = 0; //y의 자릿수
	while (y != 0) { //y의 자릿수 나누고 벡터 v2에 저장
		num2 = y % 10;
		v2.push_back(num2);
		y = y / 10;
	}
	for (int i = v2.back(); ; i++) { //벡터 v2의 끝부터 스택 s2에 저장
		s2.push(v2.back());
		v2.pop_back();
		if (v2.empty()) //v2가 비면 스택에 저장 멈춘다
			break;
	}
	int sum;
	while (!s1.empty() && !s2.empty()) { //두 스택이 비어있지 않을 때까지 반복
		if (s1.top() + s2.top() < 10) { //두 스택의 합이 10 미만일 때
			sum = s1.top() + s2.top(); //자리수가 같은 경우 여기만 실행
			result.push(sum);
			s1.pop();
			s2.pop();
			//자리수가 다른 경우
			if (!s1.empty() && s2.empty()) { //스택1이 비어있지 않았을 때
				while (!s1.empty()) { //스택1이 빌 때까지
					result.push(s1.top());
					s1.pop();
				}
			}
			else if (s1.empty() && !s2.empty()) { //스택2가 비어있지 않을 때
				while (!s2.empty()) { //스택 2가 빌 때까지
					result.push(s2.top());
					s2.pop();
				}
			}
		}
		else if(s1.top() + s2.top() >= 10) { //두 스택의 합이 10 이상일 때
				sum = s1.top() + s2.top();
				sum -= 10;
				result.push(sum);
				s1.pop();
				s2.pop();
				
				while (true) {
				if (!s1.empty() && s2.empty()) { //스택1이 비어있지 않을 때
						while (true) { //합이 10 이상일 때
						if (s1.size() == 1) {
							result.push(s1.top());
							s1.pop();
							break;
						}
						s1.top() += 1;
						if (s1.top() >= 10) {
							result.push(s1.top() - 10);
							s1.pop();
							result.push(s1.top() + 1);
							s1.pop();
							if (s1.empty()) //비면 멈춘다
								break;
						}
						else if (s1.top() < 10) {
							result.push(s1.top());
							s1.pop();
							if (s1.size() == 1) {
								result.push(s1.top());
								s1.pop();
								break;
							}
							if (s1.empty()) //비면 멈춘다
								break;
						}	
					}
				}
				else if (s1.empty() && !s2.empty()) { //스택 2가 비어있지 않을 때
					s2.top() += 1;
					while (true) { //합이 10 이상일 때
						if (s2.size() == 1) {
							result.push(s2.top());
							s2.pop();
							break;
						}
						if (s2.top() >= 10) {
							result.push(s2.top() - 10);
							s2.pop();
							result.push(s2.top() + 1);
							s2.pop();
							if (s2.empty()) //비면 멈춘다
								break;
						}
						else if (s2.top() < 10) {
							result.push(s2.top());
							s2.pop();
							if (s2.empty()) //비면 멈춘다
								break;
						}
					}
				}
				else if (s1.empty() && s2.empty()) { //두 스택이 비어있으면
					result.push(1);
				}
				else { //두 스택에 값이 있으면
					sum = s1.top() + s2.top() + 1;
					s1.pop();
					s2.pop();
					if (sum >= 10) {
						sum -= 10;
						result.push(sum);
						
						while (true) {
							if (!s1.empty() && s2.empty()) {
								if (s1.top() + 1 < 10) {
									result.push(s1.top() + 1);
									s1.pop();
								}
								else {
									result.push(s1.top() + 1 - 10);
									s1.pop();
									result.push(s1.top() + 1);
									s1.pop();
								}
								while (!s1.empty()) {
									result.push(s1.top());
									s1.pop();
								 }
							}
							else if (s1.empty() && !s2.empty()) {
								if (s2.top() + 1 < 10) {
									result.push(s2.top() + 1);
									s2.pop();
								}
								else {
									result.push(s2.top() + 1 - 10);
									s2.pop();
									result.push(s2.top() + 1);
									s2.pop();
								}
								while (!s2.empty()) {
									result.push(s2.top());
									s2.pop();
								}
							}
							else if (!s1.empty() && !s2.empty()) {
								sum = s1.top() + s2.top() + 1;
								s1.pop();
								s2.pop();
								while (true) {
									if (!s1.empty() && s2.empty()) {
										if (sum < 10)
											result.push(sum);
										else if (sum >= 10) {
											result.push(sum - 10);
											result.push(s1.top() + 1);
											s1.pop();
										}
									}
									else if (s1.empty() && !s2.empty()) {
										if (sum < 10)
											result.push(sum);
										else if (sum >= 10) {
											result.push(sum - 10);
											result.push(s2.top() + 1);
											s2.pop();
										}
									}
									else if (s1.empty() && s2.empty()) {
										if (sum < 10)
											result.push(sum);
										else if (sum >= 10) {
											result.push(sum);
										}
									}
									else {
										sum = s1.top() + s2.top();
										while (true) {
											if (sum = s1.top()+s2.top() < 10) {
												result.push(sum);
												s1.pop();
												s2.pop();
											}
											else {
												if (s1.empty()) {
													result.push(s1.top() + 1);
													s1.pop();
												}
												else if (s2.empty()) {
													result.push(s2.top() + 1);
													s2.pop();
												}
												else if (!s1.empty() && !s2.empty()) {
													result.push(sum - 10);
													sum = s1.top() + s2.top() + 1;
												}
												if (s1.empty() && s2.empty())
													break;
											}
										}
									}
									break;
									if (sum >= 10) {
										result.push(sum - 10);
									}
									else if (sum < 10) {
										result.push(sum);
									}
									sum = s1.top() + s2.top();
									s1.pop();
									s2.pop();
								}
							}
							else {
								result.push(1);
							}
							break;
						}
					}
					else if (sum < 10) {
						result.push(sum);
						if (!s1.empty()&&s2.empty()) {
							while (true) {
								result.push(s1.top());
								s1.pop();
								if (s1.empty())
									break;
							}
						}
						else if (s1.empty() && !s2.empty()) {
							while (true) {
								result.push(s2.top());
								s2.pop();
								if (s2.empty())
									break;
							}
						}
						else if (!s1.empty() && !s2.empty()) {
							while (true) {
								result.push(s1.top() + s2.top());
								s1.pop();
								s2.pop();
								if (s1.empty() || s2.empty())
								break;
							}
						}
					}
				}
				if (s1.empty() && s2.empty())
					break;
			}
		}
	if (s1.empty() && s2.empty())
		break;
	}

	for (int i = 0;; i++) {
		cout << result.top();
		result.pop();
		if (result.empty())
			break;
	}
	cout << "입니다." << endl;

	cin.get();
}
기본 틀
//
/*
int sum;
	while (!s1.empty() && !s2.empty()) {
		sum = s1.top() + s2.top();
		if (sum < 10) {
			result.push(sum);
			s1.pop();
			s2.pop();
		}
		else {
			while (sum >= 10) {
				sum = s1.top() + s2.top();
				sum -= 10;
				result.push(sum);
				s1.pop();
				s2.pop();

				if (!s1.empty() && s2.empty()) {
					s1.top() += 1;
				}
				else if (s1.empty() && !s2.empty()) {
					s2.top() += 1;
				}
				else if (s1.empty() && s2.empty()) {
					result.push(1);
				}
				else {
					sum = s1.top() + s2.top() + 1;
				}
				if (sum < 10)
					break;
			}
		}
	if (s1.empty() && s2.empty())
		break;
	}
*/
/*
while (!s1.empty() && !s2.empty()) {
		if (s1.top() + s2.top() < 10) { //두 스택의 합이 10 미만일 때
			sum = s1.top() + s2.top();
			result.push(sum);
			s1.pop();
			s2.pop();

			if (!s1.empty() && s2.empty()) {
				result.push(s1.top());
				s1.top();
			}
			else if (s1.empty() && !s2.empty()) {
				result.push(s2.top());
				s2.pop();
			}
		}
		else { //두 스택의 합이 10 이상일 때
			while (s1.top() + s2.top() >= 10) {
				sum = s1.top() + s2.top();
				sum -= 10;
				result.push(sum);
				s1.pop();
				s2.pop();

				if (!s1.empty() && s2.empty()) {
					s1.top() += 1;
					/*if (s1.top() >= 10) {
						result.push(s1.top() - 10);
						s1.pop();
						s1.top() += 1;
						result.push(s1.top());
					}
					else if(s1.top() < 10) {
						result.push(s1.top());
					}
					s1.pop();*/
				/*}
				else if (s1.empty() && !s2.empty()) {
				s2.top() += 1;
				result.push(s2.top());
				}
				else if (s1.empty() && s2.empty()) {
				result.push(1);
				}
				else {
				sum = s1.top() + s2.top() + 1;
				s1.pop();
				s2.pop();
				while (sum >= 10) {
					sum -= 10;
					result.push(sum);
				}
				if (sum < 10) {
					result.push(sum);
				}
				}
				if (s1.empty() && s2.empty())
					break;
			}
		}
		if (s1.empty() && s2.empty())
			break;
	}
*/
