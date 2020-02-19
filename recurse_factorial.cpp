#include <iostream>

using std::cout;
using std::endl;

void recurse_factorial(int n, int &y)
{
	if (n > 1)
	{
		y *= n;
		recurse_factorial(n - 1, y);
	}
}

int main()
{
	int x;
	int y = 1;
	cout << "Input factorial value:" << endl;
	std::cin >> x;
	recurse_factorial(x, y);
	cout << "======" << endl;
	cout << "" << y << "" << endl;
	cout << "======" << endl;
	system("pause");
	return 0;
}
