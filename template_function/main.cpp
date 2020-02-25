#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <list>

using namespace std;

template<typename Iterator, typename Stream>
void showContainer(Iterator begin, Iterator end, Stream& stream)
{
    auto it = begin;
    int counter = 1;
    while (it != end)
    {
        stream << "Item " << counter << ": " << *it << std::endl;
        ++it;
        ++counter;
    }
}


int main()
{
    vector<string> v1{"43658","345877y","87t4387","eryt8","ertuiy","er8ytf987"};
    array<int, 9> a1{1,2,3,4,5,6,7,8,9};
    list<double> l1{0.435,4.23,3.32,4.3,5.3,6.1};


//    cout << "intercalate: "<< showContainer << endl;
    showContainer(v1.begin(), v1.end(), std::cout);
    showContainer(a1.begin(), a1.end(), std::cout);
    showContainer(l1.begin(), l1.end(), std::cout);
    system("pause");
    return 0;
}
