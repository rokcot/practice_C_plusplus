#ifndef LIST_H
#define LIST_H

struct Node;
class List;

class ListIterator
{
public:
    ListIterator();
    ListIterator(const ListIterator& other);
    explicit ListIterator(ListIterator&& other) noexcept;

    ListIterator& operator++();
    ListIterator operator++(int);
    ListIterator& operator--();
    ListIterator operator--(int);

	double operator*() const;
	bool operator==(const ListIterator& other) const;
	bool operator!=(const ListIterator& other) const;
	ListIterator& operator=(const ListIterator& other);
    ListIterator operator()() const;
	
private:
    friend class List;
    explicit ListIterator(Node* node);

private:
	Node* m_node = nullptr;
};

class List
{
public:
    List();;
	~List();
	
	void show();
	void add(double x);
	void del(int index);
	
    double getValue(int index) const;
	void setValue(int index, double value);
	
    int quantity() const;

    double& operator[](int index);
	
	ListIterator begin();
	ListIterator begin() const;
	ListIterator end();
	ListIterator end() const;
	
private:
	friend class ListIterator;
    Node *m_head;
    Node *m_tail;
};

#endif // LIST_H
