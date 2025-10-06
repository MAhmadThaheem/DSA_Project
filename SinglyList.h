#pragma once
template<typename T>
class List
{
public:
	T *head;
	T *tail;
	int count = 0;
	List()
	{
		head = NULL;
		tail = NULL;
	}
	void insertAtFirst(T*& newUser)
	{
		if (head == NULL)
		{
			head = new T;
			head = newUser;
			tail = head;
			return;
		}

		T *newT = new T;
		newT = newUser;
		newT->next = head;
		head = newT;
		return;
	}
	void insertAtlast(T*& newUser)
	{
		if (tail == NULL)
		{
			head = new T;
			head = newUser;
			tail = head;
			head->next = NULL;
			return;
		}
		T *newT = new T;
		newT = newUser;
		tail->next = newT;
		tail = newT;
		tail->next = NULL;
		return;
	}
	//delete T at first
	void deleteAtFirst()
	{
		if (head == NULL)
		{
			return;
		}
		T *newT = head;
		head = head->next;
		delete newT;
		newT = NULL;
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
			delete head;
			head = NULL;
			tail = NULL;
			return;
		}
		T *current = head;
		while (current->next != tail)
		{
			current = current->next;
		}
		delete tail;
		tail = current;
		tail->next = NULL;
		return;
	}
	//display name of list
	void display()
	{
		if (head == NULL)
		{
			cout << "Please create list first " << endl;
			return;
		}
		T *temp = new T;
		temp = head;
		while (temp != NULL)
		{
			cout << temp->name << "\t\t" << temp->lastLogin << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	~List()
	{
		while (head)
		{
			deleteAtFirst();
		}
	}
};
