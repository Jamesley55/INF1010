#include "iostream"
using namespace std;

class Toto
{
public:
	Toto() {}
	Toto(const Toto &t) { cout << "Copie!" << endl; }
	~Toto() { cout << "Detruit!" << endl; }
};

void f1(Toto t1)
{
	Toto t2 = t1;
}

Toto f2(Toto &t1)
{
	Toto t2 = t1;
	return t1;
}

int main()
{

	Toto t1 = Toto();
	Toto t2(t1);

	f1(t2);

	Toto t3 = f2(t1);
}
