#pragma once
#include<iostream>
#include<string>
using namespace std;
struct myMessage
{
	string msg;
	string time;
	myMessage* next;
	myMessage() {
		next = NULL;
	}
	myMessage(string msg, string time)
	{
		this->msg = msg;
		this->time = time;
		next = NULL;
	}
};
class Stack
{
private:
	string emp_msg="Stack is Empty";
	myMessage* top;
public:

	Stack()
	{
		top = NULL;
	}
	Stack(string emp_msg)
	{
		top = NULL;
		this->emp_msg = emp_msg;
	}
	bool isEmpty()
	{
		return (top == NULL);
	}
	void push(string msg, string time)
	{
		myMessage* newmyMessage = new myMessage(msg, time);
		newmyMessage->next = top;
		top = newmyMessage;
	}
	void pushT(myMessage* t)
	{
		t->next = top;
		top = t;
	}
	void pop()
	{
		if (isEmpty())
		{
			cout << emp_msg << endl;
			return;
		}
		myMessage* tp = top;
		top = top->next;
		delete tp;
		tp = NULL;
	}
	pair<string,string> peek()
	{
		pair<string, string> tk;
		if (isEmpty())
		{
			cout << emp_msg << endl;
			tk.first = "";
			tk.second = "";
			return tk;
		}
		tk.first = top->msg;
		tk.second = top->time;
		return tk;
	}

	void display()
	{
		if (isEmpty())
		{
			cout << "\t"<<emp_msg << endl;
			return;
		}
		myMessage* temp = top;
		while (temp != nullptr)
		{
			cout << temp->msg << "\t\t " << temp->time << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	~Stack()
	{
		while (!isEmpty())
		{
			pop();
		}
	}
};
