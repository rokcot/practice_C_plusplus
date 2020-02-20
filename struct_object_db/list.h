#ifndef LIST_H
#define LIST_H

struct Node;

class List
{
	Node *m_head, *m_tail;
public:
	List():m_head(NULL),m_tail(NULL){};
	~List();
	
	void show();
	void add(double x);
	void del(int index);
	
	int getValue(int index);
	void setValue(int index, double value);
	
	int quantity();
};

#endif // LIST_H