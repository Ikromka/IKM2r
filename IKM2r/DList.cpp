#include "DList.h"
#include <string>
using namespace std;

//DList
	//Iterator
		//public
DList::Iterator::Iterator() : _List(nullptr), _Node(nullptr) {}
DList::Iterator::Iterator(DList* List, PNode Node) : _List(List), _Node(Node) {}
DList::Iterator& DList::Iterator::operator++() {
	_Node = _Node->Next;
	return *this;
}
DList::Iterator& DList::Iterator::operator--() {
	_Node = _Node->Prev;
	return *this;
}
wstring& DList::Iterator::operator*() {
	return _Node->Data;
}
bool DList::Iterator::operator==(Iterator Other) {
	return _Node == Other._Node;
}
bool DList::Iterator::operator!=(Iterator Other) {
	return _Node != Other._Node;
}
DList::Iterator DList::Iterator::operator+(int Shift) {
	Iterator Result = *this;
	if (Shift > 0) {
		for (int i = 0; i < Shift; i++) {
			++Result;
		}
	}
	else {
		for (int i = 0; i < -Shift; i++) {
			--Result;
		}
	}
	return Result;
}
DList::Iterator DList::Iterator::operator-(int Shift) {
	Iterator Result = *this;
	if (Shift > 0) {
		for (int i = 0; i < Shift; i++) {
			--Result;
		}
	}
	else {
		for (int i = 0; i < -Shift; i++) {
			++Result;
		}
	}
	return Result;
}
//Местод ставит MovedNode слева от AnchorNode
void DList::Iterator::Pull(Iterator Other) {
	const PNode MovedNode = Other._Node;
	const PNode AnchorNode = this->_Node;
	if (MovedNode == AnchorNode) {							//Двигаем узел к самому себе
		return;
	}
	if (MovedNode == nullptr) {								//Узел "после" крайнего правого
		return;
	}
	bool NodeIsHead = MovedNode->Prev == nullptr;
	bool NodeIsTail = MovedNode->Next == nullptr;

	if (NodeIsHead && NodeIsTail) {							//Единсивенный узел
		Other._List->_Head = nullptr;
	}
	else {
		if (NodeIsHead) {									//Крайний левый узел
			Other._List->_Head = MovedNode->Next;
			MovedNode->Next->Prev = nullptr;
		}
		else {												//Не крайний левый узел
			MovedNode->Prev->Next = MovedNode->Next;
		}
		if (NodeIsTail) {									//Крайний правый узел
			Other._List->_Tail = MovedNode->Prev;
			MovedNode->Prev->Next = nullptr;
		}
		else {												//Не крайний правый узел
			MovedNode->Next->Prev = MovedNode->Prev;
		}
	}
	if (AnchorNode == nullptr) {							//Двигаем в самый конец

		if (this->_List->_Head == nullptr) {				//Двигаем в пустой список
			this->_List->_Head = MovedNode;
			MovedNode->Prev = nullptr;
		}
		else {												//Двигаем в конец не пустого спска
			this->_List->_Tail->Next = MovedNode;
			MovedNode->Prev = this->_List->_Tail;
		}
		this->_List->_Tail = MovedNode;
		MovedNode->Next = nullptr;
	}
	else {													//Двигаем не в конец
		bool AnchorIsHead = AnchorNode->Prev == nullptr;
		if (AnchorIsHead) {									//Двигаем в начало
			AnchorNode->Prev = MovedNode;
			MovedNode->Next = AnchorNode;
			this->_List->_Head = MovedNode;
			MovedNode->Prev = nullptr;
		}
		else {												//Двигаем в середину
			AnchorNode->Prev->Next = MovedNode;
			MovedNode->Prev = AnchorNode->Prev;
			AnchorNode->Prev = MovedNode;
			MovedNode->Next = AnchorNode;
		}
	}
}
//Местод ставит подсписок из узлов от Begin до End включительно слева от AnchorNode
void DList::Iterator::Pull(Iterator Front, Iterator Back) {
	const PNode LeftNode = Front._Node;
	const PNode RightNode = Back._Node;
	const PNode AnchorNode = this->_Node;
	if (RightNode == AnchorNode || LeftNode == AnchorNode) {							//Двигаем узлы в тоже самое место
		return;
	}
	if (RightNode == nullptr) {								//Узел "после" крайнего правого
		return;
	}
	bool NodeIsHead = LeftNode->Prev == nullptr;
	bool NodeIsTail = RightNode->Next == nullptr;

	if (NodeIsHead && NodeIsTail) {							//Двигаем все узлы
		Front._List->_Head = nullptr;
	}
	else {
		if (NodeIsHead) {									//Узлы содержат Head
			Front._List->_Head = RightNode->Next;
			RightNode->Next->Prev = nullptr;
		}
		else {												//Узлы не содержат Head
			LeftNode->Prev->Next = RightNode->Next;
		}
		if (NodeIsTail) {									//Узлы содержат Tail
			Front._List->_Tail = LeftNode->Prev;
			LeftNode->Prev->Next = nullptr;
		}
		else {												//Узлы не содержат Tail
			RightNode->Next->Prev = LeftNode->Prev;
		}
	}
	if (AnchorNode == nullptr) {							//Двигаем в самый конец

		if (this->_List->_Head == nullptr) {				//Двигаем в пустой список
			this->_List->_Head = LeftNode;
			LeftNode->Prev = nullptr;
		}
		else {												//Двигаем в конец не пустого спска
			this->_List->_Tail->Next = LeftNode;
			LeftNode->Prev = this->_List->_Tail;
		}
		this->_List->_Tail = RightNode;
		RightNode->Next = nullptr;
	}
	else {													//Двигаем не в конец
		bool AnchorIsHead = AnchorNode->Prev == nullptr;
		if (AnchorIsHead) {									//Двигаем в начало
			AnchorNode->Prev = RightNode;
			RightNode->Next = AnchorNode;
			this->_List->_Head = LeftNode;
			LeftNode->Prev = nullptr;
		}
		else {												//Двигаем в середину
			AnchorNode->Prev->Next = LeftNode;
			LeftNode->Prev = AnchorNode->Prev;
			AnchorNode->Prev = RightNode;
			RightNode->Next = AnchorNode;
		}
	}
}

		//private

	//Ne Itetator
	//public
DList::Iterator DList::begin() {
	return DList::Iterator(this, _Head);
}
DList::Iterator DList::end() {
	return DList::Iterator(this, nullptr);
}
//Итератор на последний элемент
DList::Iterator DList::Back() {
	return Iterator(this, _Tail);
}

DList::DList() : _Head(nullptr), _Tail(nullptr) {}
DList::~DList() {
	Clear();
}
void DList::PushBack(wstring NewData) {
	PNode NewNode = new Node;
	NewNode->Data = NewData;
	if (_Head == nullptr) {
		_Head = _Tail = NewNode;
		_Head->Prev = nullptr;
	}
	else {
		_Tail->Next = NewNode;
		NewNode->Prev = _Tail;
		_Tail = NewNode;
	}
	_Tail->Next = nullptr;
}
void DList::Clear() {
	if (_Head == nullptr) {
		return;
	}
	while (_Head->Next != nullptr) {
		_Head = _Head->Next;
		delete _Head->Prev;
	}
	delete _Head;
	_Head = _Tail = nullptr;
}
bool DList::IsEmpty() {
	return _Head == nullptr;
}

	//private
