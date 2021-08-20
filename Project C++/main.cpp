#include <SearchingMethods.h>
#include <SortingMethods.h>
#include <Test.h>

using namespace std;

int main()
{
	list<adjVertex>* adj = new list<adjVertex>[5];
	adjVertex *x = new adjVertex;
	x->cost = 5;
	x->des_vertex = 5;

	adj[4].push_back(*x);
	delete x;

	list<adjVertex>::iterator it = adj[4].begin();
	adjVertex test = *it;
	cout << test.cost << endl;

	adj->resize(2);
	list<adjVertex>::iterator it2 = adj[4].begin();
	adjVertex test2 = *it2;
	cout << test2.cost << endl;
}