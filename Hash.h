#pragma once
#include<iostream>
#include<string>
using namespace std;
struct p
{
	pair<string, string> node;
	p* next;
	p()
	{
		next = NULL;
	}
};
class ListH
{
public:
	p *head;
	p *tail;
	int count = 0;
	ListH()
	{
		head = NULL;
		tail = NULL;
	}
	void insertAtlast(pair<string, string> newUser)
	{
		count++;
		if (tail == NULL)
		{
			head = new p;
			head->node = newUser;
			tail = head;
			head->next = NULL;
			return;
		}
		p *newT = new p;
		newT->node = newUser;
		tail->next = newT;
		tail = newT;
		tail->next = NULL;
		return;
	}
	//delete at last by traversing till tail
	void deleteAtlast()
	{
		if (tail == NULL)
		{
			return;
		}
		if (head == tail)
		{
			count--;
			delete head;
			head = NULL;
			tail = NULL;
			return;
		}
		p* current = head;
		int count1 = 1;
		while (current->next != tail)
		{
			count1++;
			current = current->next;
		}
		delete tail;
		tail = current;
		tail->next = NULL;
		return;
	}
	string searcH(string name)
	{
		p* temp = head;
		while (temp)
		{
			if (temp->node.first == name)
			{
				return temp->node.second;
			}
			temp = temp->next;
		}
		return "";
	}
	int size()
	{
		return count;
	}
	~ListH()
	{
		while (head)
		{
			deleteAtlast();
		}
	}
};
class hashTable
{
private:
	static const int total = 10;
	ListH hash[total];
public:
	int hashkey(string name);
	void insert(string name, string password);
	string getN(string name);
};

int hashTable::hashkey(string name)
{
	int sum = 0;
	for (char ch : name)
	{
		sum += ch;
	}
	return sum % total;
}
void hashTable::insert(string name, string password)
{
	int hashValue = hashkey(name);
	pair<string, string> m;
	m.first = name;
	m.second = password;
	hash[hashValue].insertAtlast(m);
}
string hashTable::getN(string name)
{
	int hashValue = hashkey(name);
	return hash[hashValue].searcH(name);
}
