class A
{
public:
	A(int x) {}
};

int main()
{
	A a;
}
// ce code ne compile pas puisqu'il n'y a
// pas de constructeur par parametre;

class A
{
public:
	A(int x) {}

private:
	int x = 1;
};

int main()
{
	A a;
}

// ce code compile puisque on a initialiser x=1;
