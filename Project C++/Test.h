#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

class EmployeeList
{
public:
	class Node;

private:
	Node* head;
	Node* tail;
	int count;

public:
	class Node
	{
	public:
		string Name;
		int Age;
		int YearsOfWork;
		Node* next;

		Node(string Name, int Age, int YearsOfWork, Node* next)
		{
			this->Name = Name;
			this->Age = Age;
			this->YearsOfWork = YearsOfWork;
			this->next = next;
		}
	};
	
	EmployeeList()
	{
		this->head = NULL;
		this->tail = NULL;
		this->count = 0;
	}

	~EmployeeList()
	{
		while (this->head != NULL) del(this->head->Name);
	}

	bool append(const string& n, int a, int workYear)
	{
		Node* tmp = new Node(n, a, workYear, NULL);
		if (this->head == NULL)
		{
			this->head = tmp;
			this->tail = tmp;
		}
		else
		{
			this->tail->next = tmp;
			this->tail = tmp;
		}
		++this->count;
		return true;
	}

	bool del(const string& n)
	{
		if (this->head == NULL) return false;
		else
		{
			Node* current = this->head->next;
			Node* precurrent = this->head;
			if (precurrent->Name == n)
			{
				if (this->count == 1) this->tail = NULL;
				this->head = precurrent->next;
				precurrent->next = NULL;
				delete precurrent;
				--this->count;
				cout << "Destructor of Employee" << endl;
				return true;
			}
			else
			{
				while (current != NULL)
				{
					if (current->Name == n)
					{
						if (this->tail == current)
						{
							this->tail = precurrent;
						}
						precurrent->next = current->next;
						current->next = NULL;
						delete current;
						--this->count;
						cout << "Destructor of Employee" << endl;
						return true;
					}
					current = current->next;
					precurrent = precurrent->next;
				}
			}
			return false;
		}
	}

	void print()
	{
		Node* current = this->head;
		while (current != NULL)
		{
			cout << "Name: " << current->Name << ", Age: " << current->Age << ", Year Of Work: " << current->YearsOfWork << endl;
			current = current->next;
		}
	}
};

template <class T>
class SLinkedList {
public:
	class Node; // Forward declaration
	class Iterator;
protected:
	Node* head;
	Node* tail;
	int count;
public:
	SLinkedList() : head(NULL), tail(NULL), count(0) {};
	~SLinkedList() { this->clear(); };
	void    add(const T& e);
	void    add(int index, const T& e);
	int     size();
	bool    empty();
	void    clear();
	T       get(int index);
	void    set(int index, const T& e);
	int     indexOf(const T& item);
	bool    contains(const T& item);
	T       removeAt(int index);
	bool    removeItem(const T& removeItem);
	Iterator begin();
	Iterator end();

	string  toString() {
		stringstream ss;
		ss << "[";
		Node* ptr = head;
		while (ptr != tail) {
			ss << ptr->data << ",";
			ptr = ptr->next;
		}

		if (count > 0)
			ss << ptr->data << "]";
		else
			ss << "]";
		return ss.str();
	}

public:
	class Node {
	private:
		T data;
		Node* next;
		friend class SLinkedList<T>;
	public:
		Node() {
			next = 0;
		}
		Node(Node* next) {
			this->next = next;
		}
		Node(T data, Node* next = NULL) {
			this->data = data;
			this->next = next;
		}
	};

	class Iterator
	{
	private:
		SLinkedList<T>* pList;
		Node* current;
		int index;

	public:
		Iterator(SLinkedList<T>* pList = NULL, bool begin = true);
		Iterator& operator=(const Iterator& iterator);
		void remove();
		void set(const T& e);
		T& operator*();
		bool operator!=(const Iterator& iterator);
		Iterator& operator++();
		Iterator operator++(int);
	};
};

template <class T>
void SLinkedList<T>::add(const T& e) {
	/* Insert an element into the end of the list. */
	SLinkedList<T>::Node* tmp = new SLinkedList<T>::Node(e, NULL);
	if (this->head == NULL)
	{
		this->head = tmp;
		this->tail = tmp;
	}
	else
	{
		this->tail->next = tmp;
		this->tail = tmp;
	}
	++this->count;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
	/* Insert an element into the list at given index. */
	if (index >= 0 && index <= this->count)
	{
		if (index == 0)
		{
			if (this->count == 0)
			{
				SLinkedList<T>::Node* tmp = new SLinkedList<T>::Node(e, NULL);
				this->head = tmp;
				this->tail = tmp;
			}
			else
			{
				SLinkedList<T>::Node* tmp = new SLinkedList<T>::Node(e, this->head);
				this->head = tmp;
			}
		}
		else if (index == this->count)
		{
			SLinkedList<T>::Node* tmp = new SLinkedList<T>::Node(e, NULL);
			this->tail->next = tmp;
			this->tail = tmp;
		}
		else
		{
			int currIndex = 0;
			SLinkedList<T>::Node* current = this->head;
			while (current != NULL)
			{
				if (currIndex == index - 1)
				{
					SLinkedList<T>::Node* tmp = new SLinkedList<T>::Node(e, current->next);
					current->next = tmp;
					break;
				}
				++currIndex;
				current = current->next;
			}
		}
		++this->count;
	}
}

template<class T>
int SLinkedList<T>::size() {
	/* Return the length (size) of list */
	return this->count;
}

template<class T>
T SLinkedList<T>::get(int index) {
	/* Give the data of the element at given index in the list. */
	T failed = this->head->data;
	if (index >= 0 && index <= this->count - 1)
	{
		int currIndex = 0;
		SLinkedList<T>::Node* current = this->head;
		while (currIndex != index)
		{
			++currIndex;
			current = current->next;
		}
		return current->data;
	}
	return failed;
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
	/* Assign new value for element at given index in the list */
	if (index >= 0 && index <= this->count - 1)
	{
		int currIndex = 0;
		SLinkedList<T>::Node* current = this->head;
		while (currIndex != index)
		{
			++currIndex;
			current = current->next;
		}
		current->data = e;
	}
}

template<class T>
bool SLinkedList<T>::empty() {
	/* Check if the list is empty or not. */
	if (this->count == 0) return true;
	return false;
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
	/* Return the first index wheter item appears in list, otherwise return -1 */
	int currIndex = 0;
	SLinkedList<T>::Node* current = this->head;
	while (current != NULL)
	{
		if (current->data == item) return currIndex;
		++currIndex;
		current = current->next;
	}
	return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
	/* Check if item appears in the list */
	SLinkedList<T>::Node* current = this->head;
	while (current != NULL)
	{
		if (current->data == item) return true;
		current = current->next;
	}
	return false;
}

template <class T>
T SLinkedList<T>::removeAt(int index)
{
	/* Remove element at index and return removed value */
	T failed = this->head->data;
	if (index >= 0 && index <= this->count - 1)
	{
		SLinkedList<T>::Node* current = this->head;
		T result;
		if (index == 0)
		{
			result = current->data;
			this->head = this->head->next;
			if (this->head == NULL)
				this->tail = NULL;
			current->next = NULL;
			delete current;
			--this->count;
			return result;
		}
		int currIndex = 0;
		while (current != NULL)
		{
			if (currIndex == index - 1) break;
			++currIndex;
			current = current->next;
		}
		if (current->next == this->tail) this->tail = current;
		SLinkedList<T>::Node* tmp = current->next;
		result = tmp->data;
		current->next = tmp->next;
		tmp->next = NULL;
		delete tmp;
		--this->count;
		return result;
	}
	return failed;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
	/* Remove the first apperance of item in list and return true, otherwise return false */
	SLinkedList<T>::Node* current = this->head;
	int currIndex = 0;
	while (current != NULL)
	{
		if (current->data == item)
		{
			removeAt(currIndex);
			return true;
		}
		++currIndex;
		current = current->next;
	}
	return false;
}

template<class T>
void SLinkedList<T>::clear() {
	/* Remove all elements in list */
	int size = this->count;
	for (int i = 0; i < size; ++i) removeAt(0);
}

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
	/*
		Constructor of iterator
		* Set pList to pList
		* begin = true:
		* * Set current (index = 0) to pList's head if pList is not NULL
		* * Otherwise set to NULL (index = -1)
		* begin = false:
		* * Always set current to NULL
		* * Set index to pList's size if pList is not NULL, otherwise 0
	*/
	this->pList = pList;
	if (begin == true)
	{
		if (this->pList != NULL)
		{
			this->current = this->pList->head;
			this->index = 0;
		}
		else
		{
			this->current = NULL;
			this->index = -1;
		}
	}
	else
	{
		this->current = NULL;
		if (this->pList != NULL) this->index = this->pList->size();
		else this->index = 0;
	}
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
	/*
		Assignment operator
		* Set this current, index, pList to iterator corresponding elements.
	*/
	this->pList = iterator.pList;
	this->current = iterator.current;
	this->index = iterator.index;
	return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
	/*
		Remove a node which is pointed by current
		* After remove current points to the previous node of this position (or node with index - 1)
		* If remove at front, current points to previous "node" of head (current = NULL, index = -1)
		* Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
	*/
	if (this->current == NULL) throw out_of_range("Segmentation fault!");
	if (this->current == this->pList->head)
	{
		this->pList->removeAt(this->index);
		this->current = NULL;
		this->index = -1;
	}
	else
	{
		this->pList->removeAt(this->index);
		--this->index;
		this->current = this->pList->head;
		int currIndex = 0;
		while (currIndex != index)
		{
			++currIndex;
			this->current = this->current->next;
		}
	}
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
	/*
		Set the new value for current node
		* Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
	*/
	if (this->current == NULL) throw out_of_range("Segmentation fault!");
	else
	{
		this->current->data = e;
	}
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
	/*
		Get data stored in current node
		* Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
	*/
	if (this->current == NULL) throw out_of_range("Segmentation fault!");
	else
	{
		return this->current->data;
	}
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
	/*
		Operator not equals
		* Returns true if two iterators points the same node and index
	*/
	if (this->current == iterator.current && this->index == iterator.index) return false;
	return true;
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
	/*
		Prefix ++ overload
		* Set current to the next node
		* If iterator corresponds to the previous "node" of head, set it to head
		* Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
	*/
	if (this->index == -1)
	{
		this->current = this->pList->head;
		++this->index;
		return *this;
	}
	if (this->index == this->pList->size())
	{
		throw out_of_range("Segmentation fault!");
	}
	this->current = this->current->next;
	++this->index;
	return *this;
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
	/*
		Postfix ++ overload
		* Set current to the next node
		* If iterator corresponds to the previous "node" of head, set it to head
		* Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
	*/
	if (this->index == -1)
	{
		SLinkedList<T>::Iterator tmp = *this;
		this->current = this->pList->head;
		++this->index;
		return tmp;
	}
	if (this->index == this->pList->size())
	{
		throw out_of_range("Segmentation fault!");
	}
	SLinkedList<T>::Iterator tmp = *this;
	this->current = this->current->next;
	++this->index;
	return tmp;
}

template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::begin()
{
	Iterator iterator = Iterator(this, true);
	return iterator;
}

template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::end()
{
	Iterator iterator = Iterator(this, false);
	return iterator;
}

class Term {
private:
	double coeff;
	int exp;
	friend class Polynomial;

public:
	Term(double coeff = 0.0, int exp = 0) {
		this->coeff = coeff;
		this->exp = exp;
	}

	bool operator==(const Term& rhs) const {
		return this->coeff == rhs.coeff && this->exp == rhs.exp;
	}

	friend ostream& operator<<(ostream& os, const Term& term) {
		cout << endl;
		cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
		return os;
	}
};

class Polynomial {
private:
	SLinkedList<Term>* terms;

public:
	Polynomial() {
		this->terms = new SLinkedList<Term>();
	}

	~Polynomial() {
		this->terms->clear();
	}

	void insertTerm(const Term& term);
	void insertTerm(double coeff, int exp);
	// Polynomial operator+(const Polynomial& rhs);

	void print() {
		SLinkedList<Term>::Iterator it;
		cout << "[";
		for (it = this->terms->begin(); it != this->terms->end(); it++) {
			cout << (*it);
		}
		cout << endl << "]";
	}
};

void Polynomial::insertTerm(const Term& term) {
	// STUDENT ANSWER
	if (this->terms->size() == 0) this->terms->add(term);
	else
	{
		int currIndex = 0;
		Term tmp = this->terms->get(currIndex);
		while (currIndex != this->terms->size())
		{
			if (term.exp >= tmp.exp) break;
			++currIndex;
			if (currIndex != this->terms->size()) 
				tmp = this->terms->get(currIndex);
		}
		if (term.exp == tmp.exp)
		{
			tmp.coeff += term.coeff;
			if (tmp.coeff == 0)
				this->terms->removeAt(currIndex);
			else
				this->terms->set(currIndex, tmp);
		}
		else this->terms->add(currIndex, term);
	}
}

void Polynomial::insertTerm(double coeff, int exp) {
	// STUDENT ANSWER
	Term tmp = Term(coeff, exp);
	insertTerm(tmp);
}

template <class T>
class DLinkedList {
public:
	class Node; // Forward declaration
	class Iterator;

protected:
	Node* head;
	Node* tail;
	int count;
public:
	DLinkedList() : head(NULL), tail(NULL), count(0) {};
	~DLinkedList() {};
	void    add(const T& e);
	void    add(int index, const T& e);
	int     size();
	T		get(int index);
	void	set(int index, const T& e);
	bool	empty();
	int		indexOf(const T& item);
	bool	contains(const T& item);
	T		removeAt(int index);
	bool	removeItem(const T& item);
	void	clear();
	Iterator begin()
	{
		return Iterator(this, true);
	}
	Iterator end()
	{
		return Iterator(this, false);
	}


public:
	class Node
	{
	private:
		T data;
		Node* next;
		Node* previous;
		friend class DLinkedList<T>;

	public:
		Node()
		{
			this->previous = NULL;
			this->next = NULL;
		}

		Node(const T& data)
		{
			this->data = data;
			this->previous = NULL;
			this->next = NULL;
		}
	};

	string toString()
	{
		stringstream ss;
		ss << "[";
		Node* ptr = head;
		while (ptr != tail)
		{
			ss << ptr->data << ",";
			ptr = ptr->next;
		}

		if (count > 0)
			ss << ptr->data << "]";
		else
			ss << "]";
		return ss.str();
	}

	class Iterator
	{
	private:
		DLinkedList<T>* pList;
		Node* current;
		int index; // is the index of current in pList
	public:
		Iterator(DLinkedList<T>* pList, bool begin);
		Iterator& operator=(const Iterator& iterator);
		void set(const T& e);
		T& operator*();
		bool operator!=(const Iterator& iterator);
		void remove();

		// Prefix ++ overload
		Iterator& operator++();

		// Postfix ++ overload
		Iterator operator++(int);
	};
};

template <class T>
void DLinkedList<T>::add(const T& e) {
	/* Insert an element into the end of the list. */
	Node* tmp = new Node(e);
	if (this->count == 0)
	{
		this->head = tmp;
		this->tail = tmp;
	}
	else
	{
		this->tail->next = tmp;
		tmp->previous = this->tail;
		this->tail = tmp;
	}
	++this->count;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
	/* Insert an element into the list at given index. */
	Node* tmp = new Node(e);
	if (index >= 0 && index <= this->count)
	{
		if (this->count == 0) this->add(e);
		else
		{
			if (index == 0)
			{
				this->head->previous = tmp;
				tmp->next = this->head;
				this->head = tmp;
				++this->count;
			}
			else
			{
				if (index == this->count) this->add(e);
				else
				{
					int currIndex = 0;
					Node* current = this->head;
					while (currIndex != index)
					{
						++currIndex;
						current = current->next;
					}
					current->previous->next = tmp;
					tmp->previous = current->previous;
					current->previous = tmp;
					tmp->next = current;
					++this->count;
				}
			}
		}
	}
}

template<class T>
int DLinkedList<T>::size() {
	/* Return the length (size) of list */
	return this->count;
}

template<class T>
T DLinkedList<T>::get(int index) {
	/* Give the data of the element at given index in the list. */
	T failed = this->head->data;
	if (index >= 0 && index <= this->count - 1)
	{
		int currIndex = 0;
		Node* current = this->head;
		while (currIndex != index)
		{
			++currIndex;
			current = current->next;
		}
		return current->data;
	}
	return failed;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
	/* Assign new value for element at given index in the list */
	if (index >= 0 && index <= this->count - 1)
	{
		int currIndex = 0;
		Node* current = this->head;
		while (currIndex != index)
		{
			++currIndex;
			current = current->next;
		}
		current->data = e;
	}
}

template<class T>
bool DLinkedList<T>::empty() {
	/* Check if the list is empty or not. */
	if (this->count == 0) return true;
	return false;
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
	/* Return the first index wheter item appears in list, otherwise return -1 */
	int currIndex = 0;
	Node* current = this->head;
	while (current != NULL)
	{
		if (current->data == item) return currIndex;
		++currIndex;
		current = current->next;
	}
	return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
	/* Check if item appears in the list */
	Node* current = this->head;
	while (current != NULL)
	{
		if (current->data == item) return true;
		current = current->next;
	}
	return false;
}

template <class T>
T DLinkedList<T>::removeAt(int index)
{
	/* Remove element at index and return removed value */
	T failed = this->head->data;
	if (index >= 0 && index <= this->count - 1)
	{
		Node* current = this->head;
		T result;
		if (index == 0)
		{
			result = current->data;
			this->head = this->head->next;
			if (this->head != NULL)
				this->head->previous = NULL;
			else
				this->tail = NULL;
			current->next = NULL;
			delete current;
			--this->count;
			return result;
		}
		int currIndex = 0;
		while (current != NULL)
		{
			if (currIndex == index) break;
			++currIndex;
			current = current->next;
		}
		result = current->data;
		current->previous->next = current->next;
		if (index == this->count - 1) this->tail = current->previous;
		else current->next->previous = current->previous;
		current->next = NULL;
		current->previous = NULL;
		delete current;
		--this->count;
		return result;
	}
	return failed;
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item)
{
	/* Remove the first apperance of item in list and return true, otherwise return false */
	Node* current = this->head;
	int currIndex = 0;
	while (current != NULL)
	{
		if (current->data == item)
		{
			this->removeAt(currIndex);
			return true;
		}
		++currIndex;
		current = current->next;
	}
	return false;
}

template<class T>
void DLinkedList<T>::clear() {
	/* Remove all elements in list */
	int size = this->count;
	for (int i = 0; i < size; ++i) this->removeAt(0);
}

/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T>* pList, bool begin)
{
	this->pList = pList;
	if (begin == true)
	{
		if (this->pList != NULL)
		{
			this->current = this->pList->head;
			this->index = 0;
		}
		else
		{
			this->current = NULL;
			this->index = -1;
		}
	}
	else
	{
		this->current = NULL;
		if (this->pList != NULL) this->index = this->pList->size();
		else this->index = 0;
	}
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator& iterator)
{
	this->pList = iterator.pList;
	this->current = iterator.current;
	this->index = iterator.index;
	return *this;
}

template <class T>
void DLinkedList<T>::Iterator::set(const T& e)
{
	if (this->current == NULL) throw out_of_range("Segmentation fault!");
	else
	{
		this->current->data = e;
	}
}

template<class T>
T& DLinkedList<T>::Iterator::operator*()
{
	if (this->current == NULL) throw out_of_range("Segmentation fault!");
	else
	{
		return this->current->data;
	}
}

template<class T>
void DLinkedList<T>::Iterator::remove()
{
	/*
	* TODO: delete Node in pList which Node* current point to.
	*       After that, Node* current point to the node before the node just deleted.
	*       If we remove first node of pList, Node* current point to nullptr.
	*       Then we use operator ++, Node* current will point to the head of pList.
	*/
	if (this->current == NULL) throw out_of_range("Segmentation fault!");
	if (this->current == this->pList->head)
	{
		this->pList->removeAt(this->index);
		this->current = NULL;
		this->index = -1;
	}
	else
	{
		this->current = this->current->previous;
		this->pList->removeAt(this->index);
		--this->index;
	}
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator& iterator)
{
	if (this->current == iterator.current && this->index == iterator.index) return false;
	return true;
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++()
{
	if (this->index == -1)
	{
		this->current = this->pList->head;
		++this->index;
		return *this;
	}
	if (this->index == this->pList->size())
	{
		throw out_of_range("Segmentation fault!");
	}
	this->current = this->current->next;
	++this->index;
	return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)
{
	if (this->index == -1)
	{
		DLinkedList<T>::Iterator tmp = *this;
		this->current = this->pList->head;
		++this->index;
		return tmp;
	}
	if (this->index == this->pList->size())
	{
		throw out_of_range("Segmentation fault!");
	}
	DLinkedList<T>::Iterator tmp = *this;
	this->current = this->current->next;
	++this->index;
	return tmp;
}

template<class T>
class Stack {
protected:
	DLinkedList<T> list;
public:
	Stack() {}
	void push(T item)
	{
		this->list.add(0, item);
	}
	T pop()
	{
		return this->list.removeAt(0);
	}
	T top()
	{
		return this->list.get(0);
	}
	bool empty()
	{
		return this->list.empty();
	}
	int size()
	{
		return this->list.size();
	}
	void clear()
	{
		this->list.clear();
	}
};

template<class T>
class Queue {
protected:
	DLinkedList<T> list;
public:
	Queue() {}
	void push(T item)
	{
		this->list.add(0, item);
	}
	T pop()
	{
		return this->list.removeAt(this->list.size() - 1);
	}
	T top()
	{
		return this->list.get(this->list.size() - 1);
	}
	bool empty()
	{
		return this->list.empty();
	}
	int size()
	{
		return this->list.size();
	}
	void clear()
	{
		return this->list.clear();
	}
};

bool isValidParentheses(string s) {
	stack<char> container;
	char tmp;
	for (int i = 0; i < s.length(); ++i)
	{
		if (s[i] == '[' || s[i] == '(' || s[i] == '{')
		{
			container.push(s[i]);
			tmp = container.top();
		}
		if ((s[i] == ']' && tmp == '[') ||
			(s[i] == ')' && tmp == '(') ||
			(s[i] == '}' && tmp == '{'))
		{
			container.pop();
			if (!container.empty()) tmp = container.top();
		}
	}
	if (container.empty()) return true;
	return false;
}

int baseballScore(string ops) {
	stack<int> container;
	int tmp1, tmp2, sum;
	for (int i = 0; i < ops.length(); ++i)
	{
		//cout << i << " ";
		if (ops[i] == '1' ||
			ops[i] == '2' ||
			ops[i] == '3' ||
			ops[i] == '4' ||
			ops[i] == '5' ||
			ops[i] == '6' ||
			ops[i] == '7' ||
			ops[i] == '8' ||
			ops[i] == '9' ||
			ops[i] == '0')
		{
			container.push(int(ops[i] - '0'));
			//cout << "Pushed" << " ";
		}
		else if (ops[i] == 'D')
		{
			container.push(container.top() * 2);
			//cout << "Pushed Doubled" << " ";
		}
		else if (ops[i] == 'C')
		{
			container.pop();
			//cout << "Deleted" << " ";
		}
		else if (ops[i] == '+')
		{
			tmp1 = container.top();
			container.pop();
			tmp2 = container.top();
			container.pop();
			sum = tmp1 + tmp2;
			container.push(tmp2);
			container.push(tmp1);
			container.push(sum);
			//cout << "Pushed Plus" << " ";
		}
		//cout << container.top() << endl;
	}
	tmp1 = 0;
	sum = 0;
	while (!container.empty())
	{
		sum += container.top();
		container.pop();
		//cout << tmp1 << " " << sum << endl;
	}
	return sum;
}

string removeDuplicates(string S) {
	stack<char> container;
	for (int i = 0; i < S.length(); ++i)
	{
		if (container.empty() || S[i] != container.top())
		{
			container.push(S[i]);
		}
		else
		{
			container.pop();
		}
	}
	if (container.empty()) return "";
	else
	{
		stack<char> reverse;
		string result;
		while (!container.empty())
		{
			reverse.push(container.top());
			container.pop();
		}
		while (!reverse.empty())
		{
			result += reverse.top();
			reverse.pop();
		}
		return result;
	}
}

void bfs(vector<vector<int>> graph, int start) {
	int size = graph.size();
	queue<int> bfs;
	bool* visited = new bool[size];

	for (int i = 0; i < size; ++i) visited[i] = false;
	bfs.push(start);
	visited[start] = true;

	while (!bfs.empty())
	{
		start = bfs.front();
		bfs.pop();
		cout << start << " ";
		for (vector<int>::iterator it = graph[start].begin(); it != graph[start].end(); ++it)
		{
			if (!visited[*it])
			{
				visited[*it] = true;
				bfs.push(*it);
			}
		}
	}
}

bool isBipartite(vector<vector<int>> graph) {
	queue<int> bfs;
	int size = graph.size();
	bool* visited = new bool[size] {false};
	int* color = new int[size] {-1};
	int start = 0;

	bfs.push(start);
	visited[start] = true;
	color[start] = 1;

	while (!bfs.empty())
	{
		start = bfs.front();
		bfs.pop();
		for (vector<int>::iterator it = graph[start].begin(); it != graph[start].end(); ++it)
		{
			if (visited[*it] == false && color[*it] == -1)
			{
				visited[*it] = true;
				color[*it] = 1 - color[start];
				bfs.push(*it);
			}
			else if (visited[*it] == false && color[*it] == color[start])
				return false;
		}
	}
	return true;
}

//Kahn's algorithm
vector<int> topologicalSorting(vector<vector<int>> graph) 
{
	queue<int> bfs;
	int* indegree = new int[graph.size()]{ 0 };
	vector<int> result;

	//Count indegree of all vertices
	for (int i = 0; i < graph.size(); ++i)
	{
		for (int j = 0; j < graph[i].size(); ++j)
			++indegree[graph[i][j]];
	}

	// Push vertex with indegree = 0 into queue
	for (int i = 0; i < graph.size(); ++i)
	{
		if (indegree[i] == 0)
			bfs.push(i);
	}

	while (!bfs.empty())
	{
		int currVertex = bfs.front();
		bfs.pop();
		result.push_back(currVertex);
		/*-1 indegree of all currVertex's adjacent vertices,
		push into queue if it's indegree = 0 after -1.*/
		for (vector<int>::iterator it = graph[currVertex].begin(); it != graph[currVertex].end(); ++it)
		{
			--indegree[*it];
			if (indegree[*it] == 0)
				bfs.push(*it);
		}
	}
	return result;
}
