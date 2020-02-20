#include <iostream>
#include <stdlib.h>
#include "list.h"


int main()
{
	setlocale(0,"");
	List lst;
	std::cout<<"Количество элементов: "<<lst.quantity()<<std::endl;
	lst.add(10);
	lst.add(20);
	lst.add(30);
	lst.add(40);
	lst.add(50);
	lst.show();
	std::cout<<"Количество элементов: "<<lst.quantity()<<std::endl;
	lst.del(2);
	lst.show();
	std::cout<<"Количество элементов: "<<lst.quantity()<<std::endl;
	const int size = lst.quantity();
	int index = 2;
	
	if (0 <= index && size > index)
	{
		std::cout<<"Элемент №2: "<<lst.getValue(index)<<std::endl;
	}
	
	lst.setValue(2,800);
	lst.show();
	system("pause");
	return 0;
}