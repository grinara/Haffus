#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
using namespace std;
class Uzel {
public:
	int a;
	char c;
	Uzel* left, * right;
	Uzel() {
		left = right = NULL;
	}
	Uzel(Uzel* L, Uzel* R)
	{
		left = L;
		right = R;
		a = L->a + R->a;
	}

};
struct MyCompare
{
	bool operator()(const Uzel* l, const Uzel* r) const { return l->a < r->a; }
};
void Print(Uzel* root, unsigned k = 0) {
	if (root != NULL) {
		Print(root->left, k + 3);
		for (unsigned i = 0; i < k; i++) {
			cout << " ";
		}
		if (root->c) {
			cout << root->a << " (" << root->c << ")" << endl;
		}
		else {
			cout << root->a << endl;
			Print(root->right, k + 3);
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	string s1="Welcome to hell";
	map<char, int>  m;
	for (int ix = 0; ix < s1.length(); ix++) {
		char c = s1[ix];
		m[c]++;
	}

	list<Uzel*> da;

	map<char, int>::iterator i;

	for (i = m.begin(); i != m.end(); ++i) {
		Uzel* k = new Uzel;
		k->c = i->first; // char в map 
		k->a = i->second; // int в map
		da.push_back(k); // добовляем указатель в list
	}
	while (da.size() != 1) // пока не останеться один элемент
	{
		da.sort(MyCompare()); //сортировка по MyCompare

		Uzel* SonL = da.front(); // создаём левого потомка берём первый элемент из list 
		da.pop_front(); // удаляем элемент
		Uzel* SonR = da.front(); // создаём правого потомка берём первый(после удаления другого) элемент из list 
		da.pop_front(); // удаляем элемент

		Uzel* parent = new Uzel(SonL, SonR); // создаём узел 
		da.push_back(parent); // добавляем его в list
	}
	Uzel* root = da.front(); // указатель на корень дерева
	Print(root);
}
