#include <iostream>
#include <stdlib.h>
#include "list.h"

int main()
{
	setlocale(0,"");
	List lst;

    std::cout<<"======================="<<std::endl
             <<"=Использование списка:="<<std::endl
             <<"======================="<<std::endl;
	lst.add(10);
	lst.add(20);
	lst.add(30);
	lst.add(40);
	lst.add(50);
    std::cout<<"Создание элементов: "<<std::endl;
	lst.show();
	std::cout<<"Количество элементов: "<<lst.quantity()<<std::endl;
	lst.del(2);
    std::cout<<"Удалён третий элемент: "<<std::endl;
	lst.show();
	std::cout<<"Количество элементов: "<<lst.quantity()<<std::endl;
	const int size = lst.quantity();

	lst.setValue(2,800);
    std::cout<<"Третий элемент изменёт на 800: "<<std::endl;
	lst.show();
    std::cout<<"========================="<<std::endl
             <<"=Использование итератора:="<<std::endl
             <<"========================="<<std::endl;
    ListIterator iter = lst.begin();
    std::cout<<"Элемент 1 : "<<*iter<<std::endl;
    ++iter;
    std::cout<<"Элемент 2: "<<*iter<<std::endl;
    iter=lst.end();
    std::cout<<"Элемент default: "<<*iter<<std::endl;
    --iter;
    std::cout<<"Элемент 5: "<<*iter<<std::endl;
    auto i = iter();

    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        std::cout << ">> item: " << *it << std::endl;
    }

    std::cout<<"постфикс: "<<*(iter--)<<std::endl;
    std::cout<<"постфикс: "<<*iter<<std::endl;

    std::cout<<"======================================="<<std::endl
             <<"=Использование списка с оператором []:="<<std::endl
             <<"======================================="<<std::endl;

    std::cout<<"оператор[] 3 значение: "<<lst[2]<<std::endl;
    std::cout<<"оператор[] 2 значение: "<<lst[1]<<std::endl;
    lst[1] = 5;
    std::cout<<"оператор[] 2 значение изменено на 5: "<<lst[1]<<std::endl;
	system("pause");
	return 0;
}
