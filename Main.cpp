#include"Queue.h"
#include"Stack.h"
#include"SinglyList.h"
#include"AVL.h"
#include"Hash.h"
#include<Windows.h>
#include<unordered_map>
using namespace std;
class Instagram
{
private:
	void getName(string& name)
	{
		bool flag;
		do
		{
			flag = false;
			cout << "Enter Name: ";
			getline(cin, name);
			if (name.size() != 0)
			{
				for (auto i : name)
				{
					if (i == ' ')
					{
						flag = true;
						cout << "Spaces are not allowed\n";
						break;
					}
				}
			}
			else
			{
				cout << "Please fill this info\n";
				flag = true;
			}
		} while (flag);
	}
public:
	int count = 0;
	unordered_map<Node*, List<Node>*> graph;
	AVL tree;
	vector<Node*> allUsers;
	Node* currentUser;
	hashTable HObj;
	Instagram()
	{
		currentUser = NULL;
	}
	void setPassword(string &password)
	{
		bool flag = true;
		while (flag)
		{
			cout << "Enter Password: ";
			getline(cin, password);
			if (password.size() >= 8)
			{
				flag = false;
			}
			else
				cout << "Password must include at least 8 characters!\n";
		}
	}
	void Sign_Up()						// Sign Up
	{
		string name, password, city;
		bool flag = true;
		while (flag)
		{
			getName(name);
			Node* check = NULL;
			tree.searchNode(tree.root, check, name);
			if (!check)
			{
				flag = false;
				setPassword(password);
				do
				{
					cout << "Enter City: ";
					getline(cin, city);
					if (city.size() != 0)
						break;
					cout << "Please fill this info\n";
				} while (true);
				HObj.insert(name, password);
				Node* newUser = new Node(name, password, city);
				newUser->lastLogin = getTime();
				List<Node> *followersList = new List<Node>;
				graph[newUser] = followersList;
				tree.root = tree.insertB(tree.root, newUser);		
				if (count == 0)
				{
					allUsers.push_back(newUser);
					newUser->saveAllUsers(allUsers);
					count++;
				}
				else
				{
					newUser->saveAllUsers(allUsers);
					allUsers.push_back(newUser);
					count++;
					for (int i = 0; i < count; i++)
					{
						allUsers[i]->addNewUser(newUser, allUsers.size() - 1);
					}
				}
			}
			else
				cout << "This name is already taken!\n";
		}
	}
	void SendFollowReq()				// Send Request Function
	{
		string name;
		cout << "Enter User Name: ";
		getline(cin, name);
		if (currentUser->name == name)
		{
			cout << "You cannot follow yourself\n";
			return;
		}
		Node* otherUser = NULL;
		tree.searchNode(tree.root, otherUser, name);
		if (!otherUser)
		{
			cout << "Sorry this user Not Found\n";
			return;
		}
		else
		{
			bool flag = true;
			for (int i = 0; i < currentUser->following_count; i++)
			{
				if (name == currentUser->following[i]->name)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				if (!otherUser->Requests.searchQueue(currentUser->name))
					sendReq(otherUser);
				else
					cout << "You already sent follow request to " << name << endl;
			}
			else
				cout << "You already followed " << name << endl;
		}
	}
	void sendReq(Node*& otherUser)
	{
		otherUser->newFrinedRequest(currentUser->name, "Pending");
		otherUser->Notification.push(currentUser->name + " sent you a follow request ", getTime());
		otherUser->noti_count++;
		cout << "You successfully send follow request to " << otherUser->name << endl;
		otherUser->req_count++;

	}
	void handleRequests()				// handle Request Function
	{
		
		if (!currentUser->Requests.isEmpty() && currentUser->req_count!=0)
		{
			currentUser->displayRequests();
			string user;
			cout << "Enter User Name you want to deal request of: ";
			getline(cin, user);
			if (currentUser->Requests.searchQueue(user) && currentUser->Requests.checkPending(user))
			{
				Node* otherUser = NULL;
				tree.searchNode(tree.root, otherUser, user);
				string choice;
				string currentTime = getTime();
				cout << "\n1. Accept Request\n";
				cout << "2. Reject Request\n";
				cout << "3. Exit\n";
				checkOption(choice, "123");
				switch (choice[0])
				{
				case '1':
				{
					currentUser->addFollowers(otherUser);
					graph[currentUser]->insertAtlast(otherUser);
					cout << "Follow Request of " << otherUser->name << " is accepted\n";
					currentUser->Requests.changeStatus(otherUser->name, "Accepted");
					string str = currentUser->name + " accepted your Follow Request";
					otherUser->Notification.push(str, currentTime);
					otherUser->noti_count++;
					otherUser->following.push_back(currentUser);
					otherUser->following_count++;
					currentUser->req_count--;
					break;
				}
				case '2':
				{
					cout << "Follow Request of " << otherUser->name << " is rejected\n";
					currentUser->Requests.changeStatus(otherUser->name, "Rejected");
					string str = currentUser->name + " rejected your Follow Request\t\t" + currentTime;
					otherUser->Notification.push(str, currentTime);
					otherUser->noti_count++;
					currentUser->req_count--;
					break;
				}
				case '3':
					break;
				}
			}
			else
				cout << "This user did not send follow request to you\n";
		}
		else
			cout << "There is no follow request yet\n";
	}
	void Posts()						// Posts Function
	{
		string post;
		cout << "Type your Post: ";
		getline(cin, post);
		string currentTime = getTime();
		currentUser->Posts.push(post, currentTime);
		currentUser->post_count++;
		string str = currentUser->name + "\t\t " + currentTime;
		for (int i = 0; i < currentUser->Followers.size(); i++)
		{
			currentUser->Followers[i]->NewsFeed.push(post, str);
		}
	}
	string getTime()
	{
		time_t ct = time(0);
		string currentTime = ctime(&ct);
		return currentTime;
	}
	void Messages()				//	Messages
	{
		string otherUserName;
		Node* otherUser = NULL;
		for (int i = 0; i < currentUser->following_count; i++)
		{
			cout << currentUser->following[i]->name << "\t\t" << currentUser->following[i]->lastLogin << endl;
		}
		cout << "\nEnter name you want to Message: ";
		getline(cin, otherUserName);
		tree.searchNode(tree.root, otherUser, otherUserName);
		if (!otherUser)
		{
			cout << "This User not found\n";
			return;
		}
		else
		{
			writeMessage(otherUser);
		}
	}
	void writeMessage(Node*& otherUser)		//write message
	{
		string message, currentTime;
		currentUser->Messages[otherUser->name]->display();
		cout << "You: ";
		getline(cin, message);
		currentTime = getTime();
		currentUser->Messages[otherUser->name]->push("You:\t" + message, currentTime);
		otherUser->Messages[currentUser->name]->push(currentUser->name + ":\t" + message, currentTime);
		otherUser->Notification.push(currentUser->name + " sent you a message", currentTime);
		otherUser->noti_count++;
	}
	void displayUserFollowers()
	{
		graph[currentUser]->display();
	}
	void searchUser()		//search user
	{
		string user;
		Node* otherUser = NULL;
		cout << "Enter user name you want to search: ";
		getline(cin, user);
		tree.searchNode(tree.root, otherUser, user);
		if(!otherUser)
		{
			cout << "This user not exits\n";
			return;
		}
		else
		{
			string choice;
			cout << "User Found\n\n";
			otherUser->displayNode();
			cout << "1. Send Follow Request\n";
			cout << "2. Message\n";
			cout << "3. Exit\n";
			checkOption(choice, "123");
			switch (choice[0])
			{
			case '1':
				if (!otherUser)
				{
					cout << "Sorry this user Not Found\n";
					return;
				}
				else
				{
					bool flag = true;
					for (int i = 0; i < currentUser->following_count; i++)
					{
						if (user == currentUser->following[i]->name)
						{
							flag = false;
							break;
						}
					}
					if (flag)
					{
						if (!otherUser->Requests.searchQueue(currentUser->name))
							sendReq(otherUser);
						else
							cout << "You already sent follow request to " << user << endl;
					}
					else
						cout << "You already followed " << user << endl;
				}
				break;
			case '2':
				writeMessage(otherUser);
				break;
			case '3':
				break;
			}
		}
	}
	void NewsFeed()		//newsfeed
	{
		string choice;
		cout << "1. View Own Posts\n";
		cout << "2. NewsFeed\n";
		cout << "3. Exit\n";
		checkOption(choice, "123");
		switch (choice[0])
		{
		case '1':
			currentUser->Posts.display();
			break;
		case '2':
			currentUser->NewsFeed.display();
			break;
		case '3':
			break;
		}
	}
	void login()					// Login Function
	{
		if (count == 0)
		{
			cout << "There is no User exists on Instagram yet!\n";
			Sleep(1500);
			return;
		}
		string name, password;
		cout << "Enter Name: ";
		getline(cin, name);
		tree.searchNode(tree.root, currentUser, name);
		if (!currentUser)
		{
			cout << "This User not exists!\n";
			Sleep(1000);
			return;
		}
		else
		{
			bool flag = true;
			while (flag)
			{
				cout << "Enter Password: ";
				getline(cin, password);
				if (password==HObj.getN(name))
				{
					flag = false;
					currentUser->lastLogin = getTime();
					system("cls");
					string choice;
					bool flag = true;
					do
					{
						currentUser->NodeMenu();
						checkOption(choice, "123456789");
						switch (choice[0])
						{
						case '1':
							cout << "\n   <=== Send Follow request ===>\n\n";
							SendFollowReq();
							system("pause");
							system("cls");
							break;
						case '2':
							cout << "\n   <=== Follow Requests ===>\n\n";
							handleRequests();
							system("pause");
							system("cls");
							break;
						case '3':
							cout << "\n   <=== Upload Post ===>\n\n";
							Posts();
							system("pause");
							system("cls");
							break;
						case '4':
							cout << "\n   <=== Notification ===>\n\n";
							currentUser->Notification.display();
							system("pause");
							system("cls");
							break;
						case '5':
							cout << "\n   <=== Messaging ===>\n\n";
							Messages();
							system("pause");
							system("cls");
							break;
						case '6':
							cout << "\n   <=== Search User ===>\n\n";
							searchUser();
							system("pause");
							system("cls");
							break;
						case '7':
							cout << "\n   <=== Followers ===>\n\n";
							displayUserFollowers();
							system("pause");
							system("cls");
							break;
						case '8':
							cout << "\n   <=== NewsFeed ===>\n\n";
							NewsFeed();
							system("pause");
							system("cls");
							break;
						case '9':
							currentUser = NULL;
							cout << "Please wait";
							for (int i = 0; i < 3; i++)
							{
								cout << ".";
								Sleep(500);
							}
							flag = false;
							break;
						}
					} while (currentUser);
				}
				else
				{
					cout << "Wrong Password!\n";
				}
			}
		}
		cin.ignore();
	}
	void checkOption(string &choice, string check)
	{
		bool flag = true;
		while (flag)
		{
			getline(cin, choice);
			for (int i = 0; i < check.size(); i++)
			{
				if (choice[0] == check[i] && choice[1] == '\0')
					return;
			}
			cout << "Invalid Input!\n";
		}
	}
	~Instagram()
	{
		for (int i = 0; i < allUsers.size(); i++)
		{
			for (int j=0; j < allUsers[i]->followers; j++)
			{
				graph[allUsers[i]]->deleteAtlast();
			}
		}
	}
};
void mainMenu()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 71);
	puts("*-------------------*");
	puts("|     Instagram     |");
	puts("|===================|");
	puts("|                   |");
	puts("|1. Sign Up         |");
	puts("|2. Login           |");
	puts("|3. Exit            |");
	puts("|                   |");
	puts("*-------------------*");
	SetConsoleTextAttribute(h, 87);
}

int main()
{
	Instagram Obj;
	bool flag = true;
	string choice;
	system("color 57");
	do
	{
		mainMenu();
		Obj.checkOption(choice, "123");
		switch (choice[0])
		{
		case '1':
			cout << "\n   <=== Sign Up ===>\n\n";
			Obj.Sign_Up();
			cout << "Congratulations! You successfully Signed Up\n";
			Sleep(1200);
			system("cls");
			break;
		case '2':
			cout << "\n   <=== Login ===>\n\n";
			Obj.login();
			system("cls");
			break;
		case '3':
			cout << "Please wait";
			for (int i = 0; i < 3; i++)
			{
				cout << ".";
				Sleep(500);
			}
			system("cls");
			flag = false;
			break;
		}
		
	} while (flag);
}
