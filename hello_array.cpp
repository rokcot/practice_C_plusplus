#include <iostream>
#include <string>

using namespace std;

int calculateMax(string * array)
{
	return 0;
}

int calculateMin(string * array,bool min_max)
{
	int len_min = array[0].size(), len_max = array[0].size();
	string min_lenS = array[0];
	string max_lenS = array[0];
	for (int i = 0; i < 20; ++i)
	{
		if (len_min > array[i].size())
		{
			len_min = array[i].size();
			min_lenS = array[i];
		}
		if (len_max < array[i].size())
		{
			len_max = array[i].size();
			max_lenS = array[i];
		}
	}
	if(min_max == true)
	return len_min;
	else return len_max;
}

int main()
{
	const int N = 20; //Длина массива

	setlocale(0, "");
	int len_min = 0, len_max = 0;
	string town[] = { "Miami","Houston","Atlanta","Boston","New York","Dayton","Chicago","Seattle","Mesa","Tucson","Dallas","Amarillo",
					"Bozeman","Butte","Casper","Linciln","Onaha","Fargo","Peoria","Toledo","Detroit","London","Hamilton","Ottawa" };

	string min_lenS;
	string max_lenS;

	len_min = calculateMin(town, true);
	len_max = calculateMin(town, false);

	cout << "Короткие:" << endl;
	cout << "===========================" << endl;
	for (int i = 0; i < N; ++i)
	{
		if (len_min >= town[i].size())
		{
			len_min = town[i].size();
			min_lenS = town[i];
			cout << " " << min_lenS << endl;
		}
	}
	cout << "===========================" << endl;

	cout << "Длинные:" << endl;
	cout << "===========================" << endl;
	for (int i = 0; i < N; ++i)
	{
		if (len_max <= town[i].size())
		{
			len_max = town[i].size();
			max_lenS = town[i];
			cout << " " << max_lenS << endl;
		}
	}
	cout << "===========================" << endl;

	cout << "Сортировка по длине:" << endl;
	cout << "===========================" << endl;
	for (int i = 0; i < N; ++i)
	{
		if (len_min < town[i].size())
		{
			len_min = town[i].size();
			min_lenS = town[i];

			for (int j = 0; j < N; ++j) {
				if (len_min == town[j].size())
				{
					len_min = town[j].size();
					min_lenS = town[j];
					cout << " " << min_lenS << endl;
				}
			}
		}
	}
	cout << "===========================" << endl;
	system("pause");
	return 0;
}
