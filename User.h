#pragma once
#include"Queue.h"
#include"Stack.h"
#include<iostream>
#include<Windows.h>
#include<vector>
#include<map>
using namespace std;
class Node
{
public:
	string name;
	string password;
	string city;
	string lastLogin;
	int followers;
	int following_count;
	int req_count;
	int noti_count;
	int post_count;
	Node* next;
	vector<Node*> Followers;
	vector<Node*> following;
	Queue Requests;
	Stack Notification;
	Stack Posts;
	Stack NewsFeed;
	Stack *Message;
	map<string, Stack*> Messages;
	Node* listHead;
	Node()
	{
		listHead = NULL;
		this->followers = 0;
		this->req_count = 0;
		this->noti_count = 0;
		this->post_count = 0;
		this->following_count = 0;
	}
	Node(string name, string password, string city)
	{
		this->name = name;
		this->password = password;
		this->city = city;
		listHead = NULL;
		this->followers = 0;
		this->req_count = 0;
		this->noti_count = 0;
		this->post_count = 0;
		this->following_count = 0;
	}
	void saveAllUsers(vector<Node*>& allUsers)
	{
		
		for (int i = 0; i < allUsers.size(); i++)
		{
			Message = new Stack("No Messaging yet");
			Messages[allUsers[i]->name] = Message;
		}
	}
	void newFrinedRequest(string name, string st)
	{
		this->Requests.enqueRear(name, st);
	}
	void searchFollower(Node*& otherUser, string otherUserName)
	{
		for (int i = 0; i < Followers.size(); i++)
		{
			if (Followers[i]->name == otherUserName)
			{
				otherUser = Followers[i];
				return;
			}
		}
	}
	void NodeMenu()
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h, 71);
		puts("*-----------------------*");
		puts("|       My Account      |");
		puts("|=======================|");
		puts("|                       |");
		puts("|1. Send Follow Request |");
		puts("|2. Handle Requests     |");
		puts("|3. Upload Post         |");
		puts("|4. Notifications       |");
		puts("|5. Messaging           |");
		puts("|6. Search Users        |");
		puts("|7. Followers List      |");
		puts("|8. Newsfeed            |");
		puts("|9. Logout              |");
		puts("*-----------------------*");
		SetConsoleTextAttribute(h, 87);
	}
	void addFollowers(Node*& folower_user)
	{
		this->Followers.push_back(folower_user);
		followers++;
	}
	void addNewUser(Node*& newUser, int index)
	{
		Message = new Stack("No Messaging yet");
		Messages[newUser->name] = Message;
	}
	void displayFollowers()
	{
		for (int i = 0; i < this->Followers.size(); i++)
		{
			this->Followers[i]->displayNode();
		}
	}
	void displayNewsFeed()
	{
		this->NewsFeed.display();
	}
	void displayRequests()
	{
		if (req_count == 0)
		{
			cout << "There is no request to handle yet\n";
			return;
		}
		this->Requests.display();
	}
	void displayNode()
	{
		cout << this->name << "\t\t " << this->lastLogin << endl;
	}
};
