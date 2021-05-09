#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

ifstream fin("citire.in");
ofstream fout("afisare.out");

// minime pe lvl pare (0, 2, 4,...)
// maxime pe lvl impare (1, 3, 5...)



int det_lvl(int i)
{
	int idx = 0;
	while (i)
	{
		i /= 2;
		idx++;
	}

	return (idx + 1) % 2;
}

int small(vector <int>& v, int i)
{
	int minim = i * 2;

	if (i * 2 + 1 < v.size() && v[minim] > v[i * 2 + 1])
		minim = i * 2 + 1;
	if (i * 4 < v.size() && v[minim] > v[i * 4])
		minim = i * 4;
	if (i * 4 + 1 < v.size() && v[minim] > v[i * 4 + 1])
		minim = i * 4 + 1;
	if (i * 4 + 2 < v.size() && v[minim] > v[i * 4 + 2])
		minim = i * 4 + 2;
	if (i * 4 + 3 < v.size() && v[minim] > v[i * 4 + 3])
		minim = i * 4 + 3;

	return minim;
}

int big(vector <int>& v, int i)
{
	int maxim = i * 2;

	if (i * 2 + 1 < v.size() && v[maxim] < v[i * 2 + 1])
		maxim = i * 2 + 1;
	if (i * 4 < v.size() && v[maxim] < v[i * 4])
		maxim = i * 4;
	if (i * 4 + 1 < v.size() && v[maxim] < v[i * 4 + 1])
		maxim = i * 4 + 1;
	if (i * 4 + 2 < v.size() && v[maxim] < v[i * 4 + 2])
		maxim = i * 4 + 2;
	if (i * 4 + 3 < v.size() && v[maxim] < v[i * 4 + 3])
		maxim = i * 4 + 3;

	return maxim;
}

void heapify_min(vector <int>& v, int i)
{
	if (i * 2 < v.size())
	{
		int m = small(v, i);

		if (m / 4 == i)
		{
			if (v[m] < v[i])
			{
				swap(v[m], v[i]);

				if (v[m] > v[m / 2])
				{
					swap(v[m], v[m / 2]);
				}

				heapify_min(v, m);
			}
		}
		else
		{
			if (v[m] < v[i])
			{
				swap(v[m], v[i]);
			}
		}
	}
}

void heapify_max(vector <int>& v, int i)
{
	if (i * 2 < v.size())
	{
		int m = big(v, i);

		if (m / 4 == i)
		{
			if (v[m] > v[i])
			{
				swap(v[m], v[i]);

				if (v[m] < v[m / 2])
				{
					swap(v[m], v[m / 2]);
				}

				heapify_max(v, m);
			}
		}
		else
		{
			if (v[m] > v[i])
			{
				swap(v[m], v[i]);
			}
		}
	}
}

void heapify(vector <int>& v, int i)
{
	if (det_lvl(i) == 0)
		heapify_min(v, i);
	else
		heapify_max(v, i);
}

void build(vector <int>& v)
{
	for (int i = (v.size() - 1) / 2; i >= 1; i--)
	{
		heapify(v, i);
	}
}



void insert_min(vector <int>& v, int i)
{
	if (i / 4 != 0 && v[i] < v[i / 4])
	{
		swap(v[i], v[i / 4]);
		insert_min(v, i / 4);
	}
}

void insert_max(vector <int>& v, int i)
{
	if (i / 4 != 0 && v[i] > v[i / 4])
	{
		swap(v[i], v[i / 4]);
		insert_max(v, i / 4);
	}
}

void insert(vector <int>& v, int i)
{
	if (i != 1)
	{
		if (det_lvl(0) == 0)
		{
			if (v[i] > v[i / 2])
			{
				swap(v[i], v[i / 2]);
				insert_max(v, i / 2);
			}
			else
			{
				insert_min(v, i);
			}
		}
		else
		{
			if (v[i] < v[i / 2])
			{
				swap(v[i], v[i / 2]);
				insert_min(v, i / 2);
			}
			else
			{
				insert_max(v, i);
			}
		}
	}
}



void afisare_min(vector <int>& v)
{
	fout << "minim: " << v[1] << "\n";
}

void afisare_max(vector <int>& v)
{
	if (v[2] > v[3])
		fout << "maxim: " << v[2] << "\n";
	else
		fout << "maxim: " << v[3] << "\n";
}

void delete_min(vector <int>& v)
{
	v[1] = v[v.size() - 1];
	v.erase(v.end() - 1);
	heapify_min(v, 1);
}

void delete_max(vector <int>& v)
{
	if (v[2] > v[3])
	{
		v[2] = v[v.size() - 1];
		v.erase(v.end() - 1);
		heapify_max(v, 2);
	}
	else
	{
		v[3] = v[v.size() - 1];
		v.erase(v.end() - 1);
		heapify_max(v, 3);
	}
}


void afisare(vector <int>& v)
{
	int nr = v.size() - 1;
	int idx = 0;
	while (nr)
	{
		nr /= 2;
		idx++;
	}
	nr = 1;
	while (idx > 1)
	{
		for (int i = nr; i < nr * 2; i++)
			fout << v[i] << " ";
		fout << "\n";
		nr *= 2;
		idx--;
	}
	for (int i = nr; i < v.size(); i++)
		fout << v[i] << " ";
	fout << "\n\n";
}

void meniu ()
{
	vector <int> mmh;
	int nr_optiuni;
	fin >> nr_optiuni;

	for (int i = 0; i < nr_optiuni; i++)
	{
		int optiune;
		fin >> optiune;

		switch (optiune)
		{
		case 1:
		{
			int x;
			fin >> x;
			mmh.push_back(x);
			insert(mmh, mmh.size() - 1);
			break;
		}
		case 2:
		{
			delete_min(mmh);
			break;
		}
		case 3:
		{
			delete_max(mmh);
			break;
		}
		case 4:
		{
			afisare_min(mmh);
			break;
		}
		case 5:
		{
			afisare_max(mmh);
			break;
		}
		case 6:
		{
			int n;
			fin >> n;

			mmh.assign(n+1, 0);

			for (int i = 1; i <= n; i++)
			{	
				fin >> mmh[i];
			}

			build(mmh);
			break;
		}
		case 7:
		{
			afisare(mmh);
		}
		}

	}
}

int main()
{
	meniu();
	return 0;
}