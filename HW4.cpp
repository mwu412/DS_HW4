#include <iostream>
#include <stack>
using namespace std;

#define MAX 1000	//represent: infinity

class Graph {
private:
	int n;	//number of vertices
	int **a; //array of cost
	int **pre; //array of predecessor
	void PrintPath(int i, int j) {
		stack<int> s; //path
		int previous = j;
		while (previous != i) {
			previous = pre[i][previous];
			s.push(previous);
		}
		while (!s.empty()) {
			cout << s.top() << "->";
			s.pop();
		}
		cout << j;
		cout << endl;
	}
	bool PreviousPath(int i, int j, int k) {
		stack<int> s1;
		stack<int> s2;
		int p = j;
		while (p != i) {	//j~i
			p = pre[i][p];
			s1.push(p);
		}
		p = j;
		while (p != k) {	//j~k
			p = pre[i][p];
			s2.push(p);
		}
		p = k;
		while (p != i) {	//k~i
			p = pre[i][p];
			s2.push(p);
		}
		while (!(s1.empty() || s2.empty())) {
			if (s1.top() < s2.top()) return false;
			else if (s2.top() < s1.top()) return true;
			s1.pop();
			s2.pop();
		}
	}
public:
	void MakeMatrix() {
		cin >> n;
		a = new int *[n];
		for (int i = 0; i < n; i++)
			a[i] = new int[n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
				if (a[i][j] == 0) a[i][j] = MAX;
			}
		}
		pre = new int *[n];
		for (int i = 0; i < n; i++)
			pre[i] = new int[n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if(a[i][j] == MAX) pre[i][j] = -1;
				else pre[i][j] = i;
			}
		}
	}
	void Floyd() {
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if ((a[i][k] + a[k][j]) < a[i][j]) {
						a[i][j] = a[i][k] + a[k][j];
						pre[i][j] = k;
					}
					else if ((a[i][k] + a[k][j]) == a[i][j]) {
						if (PreviousPath(i, j, k)) {
							pre[i][j] = k;
						}
					}
				}
			}
		}
	}
	void PrintResult() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (a[i][j] != MAX && i!=j) {
					cout << "Path(" << i << ',' << j << "):";
					PrintPath(i, j);
					cout << "Cost:" << a[i][j] << endl;
				}
			}
		}
	}
};

int main() {
	Graph g;
	g.MakeMatrix();
	g.Floyd();
	g.PrintResult();
	system("pause");
	return 0;
}
