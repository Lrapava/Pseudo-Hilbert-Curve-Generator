#include <bits/stdc++.h>
using namespace std;

typedef struct {
	double r; // ∈ [0, 1]
	double g; // ∈ [0, 1]
	double b; // ∈ [0, 1]
} rgb;

typedef struct {
	double h; // ∈ [0, 360]
	double s; // ∈ [0, 1]
	double v; // ∈ [0, 1]
} hsv;

void help(int x);
void error();
pair <string, string> parse(string s);
string genCurve(int n);
rgb hsv2rgb(hsv HSV);

int main(int argc, char** argv) {
	// 0123456
	// hacgirz

	bool options[7]{false};
	string background="", curve="";
	int weight = -1, padding = -1, order = atoi(argv[argc-1]);

	for (int i = 1; i < argc; i++) {

		string opt = parse(argv[i]).first, val = parse(argv[i]).second;
		// cout << i << ": " << opt << ", " << val << ";\n";

		if (i != argc-1 && (opt.size() < 2 || opt[0] != '-')) error();
		
		if (opt == "--help" )        options[0] = true;      else
		if (opt == "--ascii")        options[1] = true;      else
		if (opt == "--color")        options[2] = true;      else
		if (opt == "--grey" )        options[3] = true;      else
		if (opt == "--instructions") options[4] = true;      else
		if (opt == "--rainbow")      options[5] = true;      else
		if (opt == "--zero")         options[6] = true;       else
		if (opt == "--weight=")      weight     = stoi(val); else
		if (opt == "--padding=")     padding    = stoi(val); else
		if (opt == "--background=")  background = val;       else
		if (opt == "--curve=")       curve      = val;       else
		if (opt[0] == '-') {
			for (int i = 1, len = opt.size(); i < len; i++) {
				switch (opt[i]) {
					case 'h': options[0] = true; break;
					case 'a': options[1] = true; break;
					case 'c': options[2] = true; break;
					case 'g': options[3] = true; break;
					case 'i': options[4] = true; break;
					case 'r': options[5] = true; break;
					case 'z': options[6] = true; break;
					default: error();
				}
			}
		}
	}


	if (options[1] + options[2] + options[3] != 1 || (options[1] && options[5])) error();
	
	if (options[0]) help(0);

	if (background == "") {
		if (options[1]) background = "  "; else
		if (options[2]) background = "255 255 255"; else
		if (options[3]) background = "255";
	}

	if (curve == "") {
		if (options[1]) curve = "[]"; else
		if (options[2]) curve = "0 0 0"; else
		if (options[3]) curve = "0";
	}

	if (padding < 0) {
		if (options[1]) padding = 1; else padding = 10;
	}

	if (weight < 0) {
		if (options[1]) weight = 1; else weight = 10;
	}

	if (options[6]) weight = 1, padding = 0;

	auto s = genCurve(order);
	if (options[4]) cout << s << "\n";

	int w = (weight+padding-1)*((1 << order)-1)+(1 << order) + weight + 2*padding - 1;
	int len = ((1<<order)*(1<<order)-1)*(weight+padding)+1;

	
	int mx[w][w];
	// cout << order << " " << w << "\n";
	{
		for (int i = 0; i < w*w; i++)
			mx[0][i] = 0;
		
		for (int i = 0; i < weight; i++)
		for (int j = 0; j < weight; j++) {

			int x = i+padding, y = j+padding, dir = 0;
			int deltax[] = {0, 1, 0, -1};
			int deltay[] = {1, 0, -1, 0};
			
			mx[x][y] = 1;
			int px = 1;

			for (char c : s) {
				if (c == '+') dir+=1; else
				if (c == '-') dir+=3; else
				for (int i = 0; i < (weight+padding); i++) {
					px += options[5];
					x += deltax[dir];
					y += deltay[dir];
					mx[x][y] = px;
				}
				dir %= 4;
			}
		}
	}


	if (options[2]) cout << "P3\n" << w << " " << w << "\n255\n";
	if (options[3]) cout << "P2\n" << w << " " << w << "\n255\n";

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			if (mx[j][w-i-1]) { 
				if (options[2] && options[5]) {
					hsv hsvColor;
					hsvColor.h = 360.0 * mx[j][w-i-1] / len;
					hsvColor.s = hsvColor.v = 1;
					rgb rgbColor = hsv2rgb(hsvColor);
					cout << round(255*rgbColor.r) << " " << round(255*rgbColor.g) << " " << round(255*rgbColor.b);
				} else
				if (options[3] && options[5]) cout << round(255.0*mx[j][w-i-1]/len); else
				cout << curve;
			} else cout << background;
			if (!options[1]) cout << "\n";
		}
		if (options[1]) cout << "\n";
	}
	
}

void help(int x) {
	cout 
	<< "Lrapava/hcurve is a simple command-line utility for generating pseudo Hilbert curves' visualizations.\n"
	<< "You can view source-code at https://github.com/Lrapava/hcurve\n"
	<< "For more informatiob about Hilbert curve view https://youtu.be/3s7h2MHQtxc\n\n"
	<< "Usage:\n"
	<< "hcurve [OPTION..] ORDER\n\n"
	<< "Options:\n"
	<< "--help         | -h   displays this message\n"
	<< "--ascii        | -a   visualizes the curve in form of ascii art\n"
	<< "--color        | -c   visualizes the curve in form of ppm\n"
	<< "--grey         | -g   visualizes the curve in form of pgm\n"
	<< "--instructions | -i   outputs \"instructions\" for building the curve (F - move forward, + - rotate right by 90 degrees, - - rotate left by 90 degrees)\n"
	<< "--rainbow      | -r   the color (if used with -c) or the brightness (if used with -g) of the curve changes depending on the length of the curve\n"
	<< "--zero         | -z   sets padding to 0 and weight to 1\n"
	<< "--weight=X            sets width of the curve to X\n"
	<< "--padding=X           sets padding to X\n"
	<< "--background=X        fills the background with X\n"
	<< "--curve=X             fills the curve with X\n\n";
	exit(x);
}

void error() {
	cout << "Syntax error. Hopefully you'll find this message useful:\n\n";
	help(-1);
}

pair <string, string> parse(string s) {
	string option, value;
	bool eq = false;
	for (char c : s) {
		if (eq) value += c; else option += c;
		eq = max(eq, (c == '='));
	}
	return { option, value };
}

string genCurve(int n) {

	if (n <  1) error();
	if (n == 1) return "F+F+F";
	string r = genCurve(n-1), l = r;
	
	for (char &x : l) {
		if (x == '+') x = '-'; else
		if (x == '-') x = '+';
	}
	return "+" + l + "+F" + r + "-F-" + r + "F+" + l + "+";
}


rgb hsv2rgb(hsv HSV) {
    rgb RGB;
    double H = HSV.h, S = HSV.s, V = HSV.v,
            P, Q, T,
            fract;

    (H == 360.)?(H = 0.):(H /= 60.);
    fract = H - floor(H);

    P = V*(1. - S);
    Q = V*(1. - S*fract);
    T = V*(1. - S*(1. - fract));

    if      (0. <= H && H < 1.)
        RGB = (rgb){.r = V, .g = T, .b = P};
    else if (1. <= H && H < 2.)
        RGB = (rgb){.r = Q, .g = V, .b = P};
    else if (2. <= H && H < 3.)
        RGB = (rgb){.r = P, .g = V, .b = T};
    else if (3. <= H && H < 4.)
        RGB = (rgb){.r = P, .g = Q, .b = V};
    else if (4. <= H && H < 5.)
        RGB = (rgb){.r = T, .g = P, .b = V};
    else if (5. <= H && H < 6.)
        RGB = (rgb){.r = V, .g = P, .b = Q};
    else
        RGB = (rgb){.r = 0., .g = 0., .b = 0.};

    return RGB;
}
