#include <iostream>

using namespace std;


struct nod
{
	int val;
	nod* urm;

	nod(int x) : val(x), urm(0) {}
};

class Queue
{
private:
	nod* s;
	nod* d;
	int size;

public:
	Queue(): s(0), d(0), size(0) {}

	int get_size()
	{
		return size;
	}

	void push(int);
	int pop();
};

void Queue::push(int x)
{
	size++;
	nod* aux;
	aux = new nod(x);
	if (d != NULL)
	{
		d->urm = aux;
	}
	else
	{
		s = aux;
	}
	d = aux;
}

int Queue::pop()
{
	if (s == NULL)
	{
		return -1;
	}
	size--;
	int afis = s->val;
	nod* aux = s;
	s = s->urm;
	delete aux;
	if (s == NULL)
		d = NULL;
	return afis;
}


class Stiva1
{
private:
	Queue q1, q2;
public:
	Stiva1 () {}

	void push(int);
	int pop();
};

void Stiva1::push(int x)
{
	q2.push(x);
	while (q1.get_size() != 0)
	{
		q2.push(q1.pop());
	}
	Queue q = q1;
	q1 = q2;
	q2 = q;
}

int Stiva1::pop()
{
	return q1.pop();
}


class Stiva2
{
private:
	Queue q3, q4;
public:
	Stiva2() {}

	void push(int);
	int pop();
};

void Stiva2::push(int x)
{
	q3.push(x);
}

int Stiva2::pop()
{
	if (q3.get_size() == 0)
		return -1;
	else 
	{
		while (q3.get_size() != 1)
		{
			q4.push(q3.pop());
		}
		Queue q = q3;
		q3 = q4;
		q4 = q;
		return q4.pop();
	}
}

int main()
{
	Stiva1 a;
	a.push(1);
	a.push(2);
	cout << a.pop() << " ";
	cout << a.pop() << " ";
	cout << a.pop() << " ";
	a.push(1);
	a.push(1);
	a.push(1);
	cout << a.pop() << " ";
	a.push(2);
	a.push(3);
	cout << a.pop() << " ";
	cout << a.pop() << " ";
	cout << a.pop() << " ";
	cout << a.pop() << " ";
	cout << a.pop() << " ";

	cout << "\n";

	Stiva2 b;
	b.push(1);
	b.push(2);
	cout << b.pop() << " ";
	cout << b.pop() << " ";
	cout << b.pop() << " ";
	b.push(1);
	b.push(1);
	b.push(1);
	cout << b.pop() << " ";
	b.push(2);
	b.push(3);
	cout << b.pop() << " ";
	cout << b.pop() << " ";
	cout << b.pop() << " ";
	cout << b.pop() << " ";
	cout << b.pop() << " ";
	return 0;
}