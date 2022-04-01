#include "LinkedList.h"
#include <assert.h>
constexpr auto APPENDSTR = "append";
constexpr auto DELETESTR = "delete";
constexpr auto INSERTSTR = "insert";

template <class T>
Node<T>::Node()
{
	value=0;
	next=0;
}

template <class T>
Node<T>::Node(T val)
{
	value=val;
	next=0;
}

template <class T>
LinkedList<T>::LinkedList(void)
{
	head=tail=0;
	count=0;

}

template <class T>
int LinkedList<T>::Length()
{
	return count;
}

template <class T>
void LinkedList<T>::Append(T val)
{
	Node<T>* newNode=new Node<T>(val);
	if(head==0)
		head=tail=newNode;
	else
	{
		tail->next=newNode;
		tail=newNode;
	}
	count++;
	int tempPlaceHolder = count;
	addHistoryElement(APPENDSTR, tempPlaceHolder -1 , val);
}

template <class T>
T LinkedList<T>::At(int pos)
{
	assert(pos>=0&&pos<count);
	Node<T>* tmp=head;
	for(int i=0;i<pos;i++)
		tmp=tmp->next;
	return tmp->value;
}

template <class T>
void LinkedList<T>::InsertAt(int pos, T val)
{
	assert(pos>=0&&pos<count);
	Node<T>* tmp=head;
	Node<T>* newNode=new Node<T>(val);
	if(pos==0)
	{
		newNode->next=head;
		head=newNode;
	}
	else
	{
		for(int i=0;i<pos-1;i++)
			tmp=tmp->next;
	
		newNode->next=tmp->next;
		tmp->next=newNode;
	}
	count++;
	addHistoryElement(INSERTSTR, pos, val);
}

template <class T>
void LinkedList<T>::DeleteAt(int pos)
{
	assert(pos>=0&&pos<count);
	Node<T>* tmp = head;
	
	if(pos==0)
	{
		head=head->next;
		delete tmp;
	}
	else
	{
		for(int i=0;i<pos-1;i++)
			tmp=tmp->next;
		Node<T>* del=tmp->next;
		addHistoryElement(DELETESTR, pos, del->value);
		tmp->next=del->next;
		delete del;
		if(pos==count-1)
			tail=tmp;
	}
	count--;
}

template <class T>
LinkedList<T>::~LinkedList(void)
{
	while (count != 0)
		DeleteAt(0);
}


/// <summary>
/// idk what is this but you will find my implementations below Undo() , addHistoryElement and removeHistorElement
/// </summary>
/// <typeparam name="T"></typeparam>

template <class T>
void LinkedList<T>::Undo() {

	assert(!history.operations.empty());//Makes sure there was a previous operation
	
	//Checks which operation to reverse
	if (history.operations.top() == APPENDSTR) //if it was append then we delete the last element  
	{
		
		LinkedList<T>::DeleteAt(count-1);
		removeHistoryLastElement();
		if(history.operations.size() != 0)//as by default we add an element to history everytime
			removeHistoryLastElement(); //we delete so we have to delete twice

	}
	
	else if (history.operations.top() == DELETESTR)//if it is delete we just insert again using saved valuse and index
	{
	
		if (history.indeces.top() >= count) //if the last element was deleted wo do this
		{
			Append(history.values.top());
			removeHistoryLastElement();		
			if (history.operations.size() != 0)
				removeHistoryLastElement();

		}
		
		else //or do this if it's not the last element
		{
			LinkedList<T>::InsertAt(history.indeces.top(), history.values.top());
			removeHistoryLastElement();
			if (history.operations.size() != 0)
				removeHistoryLastElement();

		}
	}
	
	else //base case it was an InsertAt operation so we delete at the same index again
	{
		
		LinkedList<T>::DeleteAt(history.indeces.top());
		removeHistoryLastElement();
		if (history.operations.size() != 0)
			removeHistoryLastElement();
	}
}

//addHistoryElement : applying clean code to get raid of duplicated code as much we can 
template <class T>
void LinkedList<T>::addHistoryElement(string op, int index, T value) //pushes last operation type , index and value
{
	history.operations.push(op);
	history.values.push(value);
	history.indeces.push(index);
}

//removeHistoryLastElement : applying clean code to get raid of duplicated code as much we can 
template <class T>
void LinkedList<T>::removeHistoryLastElement()//pops last operation so we dont stuck at infinity loop of Undoes
{
	history.operations.pop();
	history.values.pop();
	history.indeces.pop();
}