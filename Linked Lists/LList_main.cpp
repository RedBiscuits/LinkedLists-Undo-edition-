#include <iostream>
#include "LinkedList.cpp"

using namespace std;

int main()
{
	LinkedList<int> L;
	L.Append(9);
	//9
	L.Append(10);
	//9 10
	L.Append(11);
	//9 10 11
	L.InsertAt(1,100);
	//9 100 10 11
	L.DeleteAt(1);
	//9 10 11
	L.Undo();//Cancels Delete
	//9 100 10 11
	L.Undo();//Cancels InsertAt
	//9 10 11
	L.Undo();//Cancels Append(11)
	//9 10
	L.Undo();//Cancels Append(10)
	//9
	L.Undo();//Cancels Append(9)
	//(empty)

	//L.Undo(); //it gets assertion error

	for(int i=0;i<L.Length();i++)
		cout<<L.At(i)<<endl;
	return 0;
}