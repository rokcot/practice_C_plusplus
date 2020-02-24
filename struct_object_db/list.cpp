#include <iostream>
#include <stdlib.h>
#include "list.h"

using namespace std;

struct Node
{
    double x = 0.0;
    Node *next = nullptr;
    Node *prev = nullptr;
};

List::List()
{
    m_head = m_tail = new Node;
}

List::~List()
{
    while(m_head != m_tail)
    {
        auto temp = m_head->next;
        temp->prev = nullptr;
        delete m_head;
        m_head = temp;
	}
    delete m_tail;
}

void List::add(double x)
{
	Node *temp = new Node;
	temp->next = nullptr;
	temp->x = x;
	
    if (m_head != m_tail)
	{
        auto prev = m_tail->prev;
        prev->next = temp;
        m_tail->prev = temp;
        temp->prev = prev;
        temp->next = m_tail;
	}
	else
	{
        m_head = temp;
        m_head->next = m_tail;
        m_tail->prev = m_head;
	}
}

void List::del(int index)
{
    Node *temp = m_head;
	int counter=0;
    while(temp != m_tail)
	{
        if (counter == index)
        {
            Node *next = temp->next;
            Node *prev = temp->prev;

            if (prev)
            {
                prev->next = next;
                next->prev = prev;
            }
            else
            {
                m_head = next;
                m_head->prev = nullptr;
            }
			
            delete temp;
            return;
		}
        temp = temp->next;
		counter++;
	}
}

int List::quantity() const
{
    Node *temp = m_head;
	int counter=0;
    while (temp != m_tail)
	{
		counter++;
        temp = temp->next;
    }
    return counter;
}

double &List::operator[](int index)
{
    Node *temp = m_head;
    int counter=0;
    while (temp != m_tail)
    {
        if(counter == index)
        {
            return temp->x;
        }
        counter++;
        temp = temp->next;
    }
    return temp->x;
}

double List::getValue(int index) const
{
    Node *temp = m_head;
	int counter=0;
    while (temp != m_tail)
	{
		if(index == counter)
        {
            return temp->x;
		}
		counter++;
        temp = temp->next;
	} 
	return 0;
}

void List::setValue(int index, double value)
{
    Node *temp = m_head;
	int counter=0;
    while (temp != m_tail)
	{
		if(index == counter)
		{
          temp->x = value;
		  break;
		}
		counter++;
        temp = temp->next;
	} 
}

void List::show()
{
     Node *temp = m_head;
    while (temp != m_tail)
	{
        cout << temp->x << " ";
        temp = temp->next;
	}
	cout << "\n";
 
    temp = m_tail;
    while (temp != m_head)
    {
        temp = temp->prev;
        cout << temp->x << " ";
	}
     cout << "\n";

}


ListIterator::ListIterator() : m_node(nullptr)
{
}

ListIterator::ListIterator(const ListIterator &other) : m_node(other.m_node)
{
}

ListIterator::ListIterator(ListIterator &&other) noexcept : m_node(std::move(other.m_node))
{
}

ListIterator &ListIterator::operator++()
{
    m_node = m_node->next;
    return *this;
}

ListIterator ListIterator::operator++(int)
{
    ListIterator temp(*this);
    ++(*this);
    return temp;
}

ListIterator &ListIterator::operator--()
{
    m_node = m_node->prev;
    return *this;
}

ListIterator ListIterator::operator--(int)
{
    ListIterator temp(*this);
    --(*this);
    return temp;
}

double ListIterator::operator*() const
{
    return m_node->x;
}

bool ListIterator::operator==(const ListIterator &other) const
{
    return m_node == other.m_node;
}

bool ListIterator::operator!=(const ListIterator &other) const
{
    return m_node != other.m_node;
}

ListIterator &ListIterator::operator=(const ListIterator &other)
{
    m_node = other.m_node;
    return *this;
}

ListIterator ListIterator::operator()() const
{
    return ListIterator(*this);
}

ListIterator::ListIterator(Node *node) : m_node(node)
{
}

ListIterator List::begin()
{
    return ListIterator(m_head);
}

ListIterator List::begin() const
{
    return ListIterator(m_head);
}

ListIterator List::end()
{
    return ListIterator(m_tail);
}

ListIterator List::end() const
{
    return ListIterator(m_tail);
}
