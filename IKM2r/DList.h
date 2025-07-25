#pragma once
#include <string>

using namespace std;

struct Node;

using PNode = Node*;

struct Node {
	PNode Prev;
	wstring Data;
	PNode Next;
};

class DList {
public:
	class Iterator {
	public:
		Iterator();
		Iterator(DList* List, PNode Node);
		Iterator& operator++();
		Iterator& operator--();
		wstring& operator*();
		bool operator==(Iterator Other);
		bool operator!=(Iterator Other);
		Iterator operator+(int Shift);
		Iterator operator-(int Shift);
		void Pull(Iterator Other);
		void Pull(Iterator Begin, Iterator End);


	private:
		DList* _List;
		PNode _Node;
	};
	Iterator begin();
	Iterator end();
	Iterator Back();
	
	DList();
	~DList();
	void PushBack(wstring NewData);
	void Clear();
	bool IsEmpty();

private:
	PNode _Head;
	PNode _Tail;
};

using Iter = DList::Iterator;