#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
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






int main() {

}
