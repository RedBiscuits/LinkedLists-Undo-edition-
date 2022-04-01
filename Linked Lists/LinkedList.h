#pragma once
#include<iostream>
#include<stack>

using namespace std;
template <class T>
class Node
{
	public:
	Node<T>* next;
	T value;

	Node();
	Node(T val);
};

//History Class to keep track of operations made and their values and indeces
template <class T>
class History {
public:
	stack<string> operations;
	stack<T> values;
	stack<int> indeces;
};

template <class T>
class LinkedList
{
	int count;
	Node<T>* head;
	Node<T>* tail;
	//History required elements
	History<T> history;
	void removeHistoryLastElement();
	void addHistoryElement(string op, int index, T value);
public:
	LinkedList();
	int Length();
	T At(int);
	void InsertAt(int,T);
	void Append(T);
	void DeleteAt(int);
	//Undo decleration
	void Undo();
	~LinkedList(void);
};

