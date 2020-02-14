#include <iostream>
#include <string>

using namespace std;

int calculateMin(string array[], bool is_min)
{
	int result = array[0].size();
	for (int i = 0; i < 20; ++i)
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
	return result;
}



int main()
{
	const int N = 20; //Длина массива
	setlocale(0, "");
	int len_min = 0, len_max = 0;
	string temp;
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
		if (len_min == town[i].size())
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
		if (len_max == town[i].size())
		{
			len_max = town[i].size();
			max_lenS = town[i];
			cout << " " << max_lenS << endl;
		}
	}
	cout << "===========================" << endl;

	cout << "Сортировка по длине и алфавиту:" << endl;
	cout << "===========================" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - i; j++) {
			if (town[j].size() > town[j + 1].size() || (town[j].size() == town[j + 1].size() && town[j] > town[j + 1])) {
				// меняем элементы местами
				temp = town[j];
				town[j] = town[j + 1];
				town[j + 1] = temp;
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
