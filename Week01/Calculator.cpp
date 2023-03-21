

#include <iostream>
#include <stdlib.h>

using namespace std;

enum symbol { 
	LEFT_PAREN = '(',
	RIGHT_PAREN = ')',
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	DIVIDE = '/'
};


template <typename T> class Stack { // 스택 구현 클래스
private:
	int top;
	T* ch;
public:
	Stack();
	T peek(); // top 값 출력
	void push(T); // item 삽입
	T pop(); // item 반환 후 삭제
	int size() { return top + 1; }
	bool isEmpty() { return (top == -1); }
};

template <typename T>
Stack<T>::Stack() {
	top = -1;
	ch = new T[10];
}

template <typename T>
T Stack<T>::peek() {
	if (isEmpty()) {
		return NULL;
	}

	return ch[top];
}

template <typename T>
void Stack<T>::push(T newItem) {
	
	ch[++top] = newItem;
}

template <typename T>
T Stack<T>::pop() {
	if (isEmpty()) {
		return NULL;
	}
	
	T item = ch[top];
	ch[top--] = NULL;

	return item;
}



class Calculator { // 계산기 클래스

private:
	Stack<char> stack;
	char* str;
public:
	Calculator() { str = NULL; };
	int priority(char); // 우선순위
	void postfix(char*); // 후위표기법
	void run(); // 계산
	~Calculator() {}
};


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
	
	int len = strlen(ch);
	int index = 0;
	char* pos = new char[len+1]; // '\0'가 입력될 여유 공간
	
	for (int i = 0; i < len; i++) 
	{
		if (ch[i] >= '0' && ch[i] <= '9') { // 피연산자 출력
			
			pos[index++] = ch[i];
		}
		else if (ch[i] == RIGHT_PAREN) { // ')'가 나오면 '('가 나올 때까지 출력
			
			while (stack.peek() != LEFT_PAREN)
			{
				pos[index++] = stack.peek();
				stack.pop();
			}
			stack.pop(); // '(' 버리기
		}
		else { // 연산자

			while (!stack.isEmpty() && ch[i] != LEFT_PAREN && (priority(ch[i]) <= priority(stack.peek())) )
			{ // !st.isEmpty() : 가장 처음의 연산자는 바로 push && (+,-) < (*,/) && <= : / 와 * 는 우선순위가 동일
				pos[index++] = stack.peek();
				stack.pop();
			}
			stack.push(ch[i]);
		}
	}

	while (!stack.isEmpty()) { // stack에 push한 item 전부 출력
		pos[index++] = stack.peek();
		stack.pop();
		//pos[index++] = stack.pop();
	}

	pos[index] = '\0'; // 배열 입력 종료 ★★★
	
	str = pos;

	cout << "Postfix ::: " << str << endl;
}


void Calculator::run() {
	
	Stack<int> stk;
	int size = strlen(str);
	int value, num1, num2;
	char ch;

	for (int i = 0; i < size; i++)
	{
		ch = str[i];

		if (ch >= '0' && ch <= '9') {
			value = ch - '0';
			stk.push(value);
		}
		else {
			num2 = stk.pop();
			num1 = stk.pop();

			switch (ch) {
			case PLUS: stk.push(num1 + num2); break;
			case MINUS: stk.push(num1 - num2); break;
			case MULTIPLY: stk.push(num1 * num2); break;
			case DIVIDE: stk.push(num1 / num2); break;
			}
		}
		
	}
	cout << "Result :::: " << stk.pop() << endl;
}



int main()
{
	Calculator calc;
	char expression[50]; // 한 자릿수만 입력 가능
	char exit;

	cout << "================================================" << endl;
	cout << "================== Calculator ==================" << endl;
	cout << "================================================" << endl;
	
	while (1) {

		cout << "Enter the expression >> ";
		cin >> expression;

		calc.postfix(expression);
		calc.run();

		cout << "종료하려면 q를 누르세요 => ";
		
		cin >> exit;
		if (exit == 'q') {
			break;
		}
		cout << "================================================" << endl;
	}

	return 0;
}