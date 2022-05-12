#include <bits/stdc++.h>
using namespace std;

string curve(int n) {
	if (n == 1) return "F+F+F";
	string r = curve(n-1), l = r;
	
	for (char &x : l) {
		if (x == '+') x = '-'; else
		if (x == '-') x = '+';
	}
	return "+" + l + "+F" + r + "-F-" + r + "F+" + l + "+";
}

int main(int argc, char** argv) {

	int n = atoi(argv[1]), l = atoi(argv[2]), sqw = 1;
	int w = (l-1)*((1 << n)-1)+(1 << n) + 2;
	string s = curve(n), light = "  ", dark = "[]";

	if (argc == 4) {
		sqw = atoi(argv[3]);
		light = "255 255 255\n";
		dark = "0 0 0\n";
		cout << "P3\n" << w*sqw << " " <<  w*sqw << "\n256\n";
	}
	
	bool mx[w][w];
	{
		for (int i = 0; i < w*w; i++)
			mx[0][i] = false;
		mx[1][1] = true;

		int x = 1, y = 1, dir = 0;
		int deltax[] = {0, 1, 0, -1};
		int deltay[] = {1, 0, -1, 0};	

		for (char c : s) {
			if (c == '+') dir+=1; else
			if (c == '-') dir+=3; else
			for (int i = 0; i < l; i++) {
				x += deltax[dir];
				y += deltay[dir];
				mx[x][y] = true;
			}
			dir %= 4;
		}
	}
	
	for (int i = 0; i < w*sqw; i++) {
		for (int j = 0; j < w*sqw; j++) {
			if (mx[j/sqw][w-i/sqw-1]) cout << dark; 
			else cout << light;
		}
		cout << "\n";
	}
}
