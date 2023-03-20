
//#define _CRT_SECURE_NO_WARNINGS

//#include <stdio.h>
#include <iostream>
#include <stdlib.h>
//#include <stack>

using namespace std;

enum symbol {
	LEFT_PAREN = '(',
	RIGHT_PAREN = ')',
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	DIVIDE = '/'
};

class Stack { // 스택 구현 클래스
private:
	int top = -1;
	char* ch;
public:
	Stack();
	char peek(); // top 값 출력
	void push(char c); // item 삽입
	char pop(); // item 반환 후 삭제
	int size() { return top + 1; }
	bool isEmpty() { return (top == -1); }
	void resize(int i);
};

Stack::Stack() {
	top = -1;
	ch = new char[1];
}

char Stack::peek() {
	if (isEmpty()) {
		return;
	}

	return ch[top];
}

void Stack::push(char newItem) {
	/*if (size() == sizeof(ch)) {
		resize(2 * sizeof(ch));
		cout << "배열 사이즈 : " << 2 * sizeof(ch) << endl;
	}*/

	ch[++top] = newItem;
}

char Stack::pop() {
	if (isEmpty()) {
		return;
	}

	char item = ch[top];
	ch[top--] = '\0';

	/*if (size() > 0 && size() == sizeof(ch) / 4) {
		resize(int(sizeof(ch) / 2));
		cout << "배열 사이즈 : " << int(sizeof(ch) / 2) << endl;
	}*/

	return item;
}

/*void Stack::resize(int newSize) {
	char* temp;
	temp = new char[newSize];

	for (int i = 0; i < sizeof(ch); i++) {
		temp[i] = ch[i];
	}

	ch = temp;
}*/



class Calculator { // 계산기 클래스

private:
	Stack stack;
	char* str;
public:
	Calculator() { str = new char[50]; };
	void input(); // 입력
	int priority(char ch); // 우선순위
	void postfix(char* ch); // 후위표기법
	//void run(); // 계산
	~Calculator() {}
};
/*
void Calculator::input() {
	char ch;
	int i = 0;

	while ((ch = getchar()) != EOF)
	{
		str[i] = getchar();

		if (str[i++] == '\n') {
			str[i - 1] = '\n';
			break;
		}
	}

	printf("ch : %s\n", str);
}*/

int Calculator::priority(char ch) { // 우선순위
	if (ch == LEFT_PAREN) {
		return 0;
	}
	else if (ch == PLUS || ch == MINUS) {
		return 1;
	}
	else if (ch == MULTIPLY || ch == DIVIDE) {
		return 2;
	}
	else
		return -1;
}

void Calculator::postfix(char* ch) { // 후위표기법 변환 ★★★
	
	Stack st;
	int len = sizeof(ch);
	int index = 0;
	char* pos = new char[len];

	for (int i = 0; i < len; i++) 
	{
		if (ch[i] >= '0' && ch[i] <= '9') { // 피연산자 출력
			
			pos[index++] = ch[i];
		}
		else if (ch[i] == RIGHT_PAREN) { // ')'가 나오면 '('가 나올 때까지 출력
			
			while (st.peek() != LEFT_PAREN)
			{
				pos[index++] = st.peek();
				st.pop();
			}
			st.pop(); // '(' 버리기
		}
		else { // 연산자

			while (!st.isEmpty() && ch[i] != LEFT_PAREN && (priority(ch[i]) <= priority(st.peek())) )
			{ // !st.isEmpty() : 가장 처음의 연산자는 바로 push && (+,-) < (*,/)
				pos[index++] = st.peek();
				st.pop();
			}
			st.push(ch[i]);
		}
	}

	while (!st.isEmpty()) { // stack에 push한 item 전부 출력
		pos[index++] = st.peek();
		st.pop();
	}
	
	printf("%s\n", pos);
}
/*
void Calculator::run() {
	// atoi() 함수
	int size = strlen(str);

	for (int i = 0; i < size; i++)
	{
		if (str[i] >= '0' && str[i] <= '9') {
			s=st
		}
	}
}*/



int main()
{
	Calculator calc;
	char expression[50];

	cout << "================== Calculator ==================" << endl;
	cout << "================================================" << endl;
	cout << "Enter the expression >> ";
	cin >> expression;
	
	calc.postfix(expression);


	return 0;
}