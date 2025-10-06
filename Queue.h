#pragma once
#include<iostream>
#include<string>
using namespace std;
struct Request
{
	string friend_name;
	string status;
	Request* next;
	Request() {
		next = NULL;
	}
	Request(string friend_name, string st)
	{
		this->friend_name = friend_name;
		this->status = st;
		next = NULL;
	}
};
class Queue
{
	Request* front;
	Request* rear;
public:
	Queue()
	{
		front = NULL;
		rear = NULL;
	}
	bool isEmpty()
	{
		return (front == NULL);
	}
	void enqueRear(string nm, string st)
	{
		Request* newRequest = new Request(nm, st);
		if (isEmpty())
		{
			front = newRequest;
			rear = newRequest;
			return;
		}
		rear->next = newRequest;
		rear = newRequest;
	}
	void dequeFront()
	{
		if (isEmpty())
		{
			cout << "There is no Follow Request yet\n";
			return;
		}
		if (front == rear)
		{
			Request *temp = front;
			front = front->next;
			delete temp;
			temp = NULL;
			rear = NULL;
			return;
		}
		Request *temp = front;
		front = front->next;
		delete temp;
		temp = NULL;
	}
	bool searchQueue(string nm)
	{
		if (isEmpty())
		{
			return false;
		}
		Request* temp = front;
		while (temp)
		{
			if (temp->friend_name == nm)
			{
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	bool checkPending(string nm)
	{
		if (isEmpty())
		{
			return false;
		}
		Request* temp = front;
		while (temp)
		{
			if (temp->friend_name == nm)
			{
				if (temp->status == "Pending")
					return true;
				else
				{
					cout << "You already handled this follow request\n";
					return false;
				}
			}
			temp = temp->next;
		}
		return false;
	}
	void changeStatus(string nm, string st)
	{
		Request* temp = front;
		while (temp)
		{
			if (temp->friend_name == nm)
			{
				temp->status = st;
				return;
			}
			temp = temp->next;
		}
	}
	
	void display()
	{
		if (isEmpty())
		{
			cout << "There is no Follow Request yet\n";
			return;
		}
		Request* temp = front;
		while (temp)
		{
			if(temp->status=="Pending")
				cout << temp->friend_name << "\t " << temp->status << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	~Queue()
	{
		while (isEmpty())
		{
			dequeFront();
		}
	}
};
