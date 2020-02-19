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
	
	if (!m_head)
	{
		temp->prev = m_tail;
		m_tail->next = temp;
		m_tail = temp;
	}
	else
	{
		temp->next = nullptr;
		m_head = m_tail = temp;
	}
}

void List::show()
{
     Node *m_temp = m_tail;
 
     while (!m_temp)              
     {
         cout << m_temp->x << " ";       
         m_temp = m_temp->prev;            
     }
     cout << "\n";
 
     m_temp = m_head;
     while (!m_temp)  
     {
         cout << m_temp->x << " ";  
         m_temp = m_temp->next;             
     }
     cout << "\n";
}