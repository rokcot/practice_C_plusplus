#include <iostream>
#include <stdlib.h>
#include "list.h"


int main()
{
	setlocale(0,"");
	List lst;
	lst.add(100);
	lst.add(200);
	
	lst.show();
	system("pause");
	return 0;
}