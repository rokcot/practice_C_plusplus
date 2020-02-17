#include <iostream>
#include <string>

using namespace std;

int calculateMin(string array[], int leng, bool is_min, int &result)
{
	result = array[0].size();
	for (int i = 0; i < leng; ++i)
	{
		if (is_min)
		{
			if (result > array[i].size())
			{
				result = array[i].size();
			}
		}
		else
		{
			if (result < array[i].size())
			{
				result = array[i].size();
			}
		}
	}
}



int main()
{
	const int N = 20;
	setlocale(0, "");
	int len_min = 0, len_max = 0;
	string temp;
	string town[] = { "Miami","Houston","Atlanta","Boston","New York","Dayton","Chicago","Seattle","Mesa","Tucson","Dallas","Amarillo",
					"Bozeman","Butte","Casper","Linciln","Onaha","Fargo","Peoria","Toledo","Detroit","London","Hamilton","Ottawa" };
	string *town_point = town;
	int length_array = sizeof(town) / sizeof(*town);
	string min_lenS;
	string max_lenS;

	calculateMin(town, length_array, true, len_min);
	calculateMin(town, length_array, false, len_max);

	cout << "Короткие:" << endl;
	cout << "===========================" << endl;
	for (int i = 0; i < N; ++i)
	{
		if (len_min == (i+town_point)->size())
		{
			len_min = (*(i + town_point)).size();
			min_lenS = (*(i + town_point));
			cout << " " << min_lenS << endl;
		}
	}
	cout << "===========================" << endl;

	cout << "Длинные:" << endl;
	cout << "===========================" << endl;
	for (int i = 0; i < N; ++i)
	{
		if (len_max == (*(i+town_point)).size())
		{
			len_max = (*(i+town_point)).size();
			max_lenS = (*(i+town_point));
			cout << " " << max_lenS << endl;
		}
	}
	cout << "===========================" << endl;

	cout << "Сортировка по длине и алфавиту:" << endl;
	cout << "===========================" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - i; j++) {
			if ((*(j+town_point)).size() > (*((j+1)+town_point)).size() ||
				((*(j+town_point)).size() == (*((j+1)+town_point)).size() &&
					(*(j+town_point)) > (*((j+1)+town_point)))) {
				temp = (*(j+town_point));
				(*(j+town_point)) = (*((j+1)+town_point));
				(*((j+1)+town_point)) = temp;
			}
		}
	}
	for (int i = 0; i < N; ++i)
	{
		cout << town[i] << endl;
	}
	cout << "===========================" << endl;
	system("pause");
	return 0;
}
