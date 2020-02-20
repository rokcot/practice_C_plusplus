#include <iostream>
#include <stdlib.h>
#include "list.h"

using namespace std;

struct Node
{
	double x;
	Node *next;
	Node *prev;
};

List::~List()
{
	while(m_head)
	{
		m_tail = m_head->next;
		delete m_head;
		m_head = m_tail;
	}
}

void List::add(double x)
{
	Node *temp = new Node;
	temp->next = nullptr;
	temp->x = x;
	
	if (m_head)
	{
		temp->prev = m_tail;
		m_tail->next = temp;
		m_tail = temp;
	}
	else
	{
		temp->prev = nullptr;
		m_head = m_tail = temp;
	}
}

void List::del(int index)
{
	Node *m_temp = m_head;
	Node *m_temp_next;
	Node *m_temp_prev;
	int counter=0;
	while(m_temp)
	{
		if(counter == index)
		{
			m_temp_next = m_temp->next;
			m_temp_prev = m_temp->prev;
			
			m_temp_next->prev = m_temp_prev;
			m_temp_prev->next = m_temp_next;
			
			delete m_temp;
		}
		m_temp = m_temp->next;
		counter++;
	}
}

int List::quantity()
{
	Node *m_temp = m_head;
	int counter=0;
	while (m_temp)  
	{
		counter++;
		m_temp = m_temp->next;             
	} 
	return counter; 
}

int List::getValue(int index)
{
	Node *m_temp = m_tail;
	int counter=0;
	while (m_temp)  
	{
		if(index == counter)
		{
			return m_temp->x;  
		}
		counter++;
		m_temp = m_temp->prev;             
	} 
	return 0;
}

void List::setValue(int index, double value)
{
	Node *m_temp = m_tail;
	int counter=0;
	while (m_temp)  
	{
		if(index == counter)
		{
		  m_temp->x = value;
		  break;
		}
		counter++;
		m_temp = m_temp->prev;             
	} 
}

void List::show()
{
     Node *m_temp = m_tail;
	while (m_temp)              
	{
		cout << m_temp->x << " ";       
		m_temp = m_temp->prev;            
	}
	cout << "\n";
 
	m_temp = m_head;
	while (m_temp)  
	{
		cout << m_temp->x << " ";  
		m_temp = m_temp->next;             
	}
     cout << "\n";
	 
}