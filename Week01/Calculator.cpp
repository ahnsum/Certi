

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


template <typename T> class Stack { // ���� ���� Ŭ����
private:
	int top;
	T* ch;
public:
	Stack();
	T peek(); // top �� ���
	void push(T); // item ����
	T pop(); // item ��ȯ �� ����
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



class Calculator { // ���� Ŭ����

private:
	Stack<char> stack;
	char* str;
public:
	Calculator() { str = NULL; };
	int priority(char); // �켱����
	void postfix(char*); // ����ǥ���
	void run(); // ���
	~Calculator() {}
};


int Calculator::priority(char ch) { // �켱����
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

void Calculator::postfix(char* ch) { // ����ǥ��� ��ȯ �ڡڡ�
	
	int len = strlen(ch);
	int index = 0;
	char* pos = new char[len+1]; // '\0'�� �Էµ� ���� ����
	
	for (int i = 0; i < len; i++) 
	{
		if (ch[i] >= '0' && ch[i] <= '9') { // �ǿ����� ���
			
			pos[index++] = ch[i];
		}
		else if (ch[i] == RIGHT_PAREN) { // ')'�� ������ '('�� ���� ������ ���
			
			while (stack.peek() != LEFT_PAREN)
			{
				pos[index++] = stack.peek();
				stack.pop();
			}
			stack.pop(); // '(' ������
		}
		else { // ������

			while (!stack.isEmpty() && ch[i] != LEFT_PAREN && (priority(ch[i]) <= priority(stack.peek())) )
			{ // !st.isEmpty() : ���� ó���� �����ڴ� �ٷ� push && (+,-) < (*,/) && <= : / �� * �� �켱������ ����
				pos[index++] = stack.peek();
				stack.pop();
			}
			stack.push(ch[i]);
		}
	}

	while (!stack.isEmpty()) { // stack�� push�� item ���� ���
		pos[index++] = stack.peek();
		stack.pop();
		//pos[index++] = stack.pop();
	}

	pos[index] = '\0'; // �迭 �Է� ���� �ڡڡ�
	
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
	char expression[50]; // �� �ڸ����� �Է� ����
	char exit;

	cout << "================================================" << endl;
	cout << "================== Calculator ==================" << endl;
	cout << "================================================" << endl;
	
	while (1) {

		cout << "Enter the expression >> ";
		cin >> expression;

		calc.postfix(expression);
		calc.run();

		cout << "�����Ϸ��� q�� �������� => ";
		
		cin >> exit;
		if (exit == 'q') {
			break;
		}
		cout << "================================================" << endl;
	}

	return 0;
}