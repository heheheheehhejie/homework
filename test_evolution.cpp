#include <set>
#include <map>
#include <list>
#include <stack>
#include <cmath>
#include <ctime>
#include <queue>
#include <deque>
#include <array>
#include <random>
#include <bitset>
#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

#define o 1.000000
#define E_E 2.718281828
#define E_PI 3.1415926535
#define mod 998244353

#define INF 0x3f3f3f3f
#define X first
#define Y second

const int MAXN = 100100;
const int MAXE = 400400;

typedef long long LL;
typedef double db;
typedef pair<int, int> pii;

const db muta_rate = 1e-12;
double A;
int N, Ans = -1000000, initial_val;
int sum[MAXN / 100 + 10], val[MAXN / 100 + 10]; 

deque<bitset < 160 > > v;
bitset < 160 > ans;
default_random_engine dre(time(NULL));
uniform_int_distribution<int> d(0, (1 << 30));

bool check(int x) {
	if(x == 3) return 1;
	else return 0;
}

int F(bitset < 160 > x) {
	int ret = 0;
	for(int i = 0; i < 160; i += 2) {
		int tmp = 0;
		for(int j = i; j < i + 2 && j < 160; j++) {
			if(x.test(j)) tmp += (1 << (j - i));
		}
		if(check(tmp)) ret += 140;
		else ret -= 10;
	}
	return ret;
}

void init() {
	string s = "";
	for(int i = 0; i < N; i++) {
		s = "";
		for(int j = 0; j < 160; j++) {
			int t = d(dre);
			s += (char) ((t & 1) + '0');
		}
		bitset < 160 > tmp(s);
		v.push_back(tmp);
	}
}

void evolve() {
	int mx = -10000000, smx = -10000000;
	int mn = 10000000, smn = 10000000; 
	int px = 0, py = 0, ty = 0, tx = 0;
	sum[0] = 0;
	for(int i = 0; i < N; i++) {
		int res = 0;
		res = F(v[i]);
		if(res > mx) smx = mx, py = px, px = i, mx = res;
		else if(res > smx) smx = res, py = i; 
		if(res < mn) smn = mn, ty = tx, tx = i, mn = res;
		else if(res < smn) smn = res, ty = i; 
		val[i] = res + 800; 
		if(i) sum[i] = sum[i - 1] + val[i];
		else sum[i] = val[i];
	}
	if(mx > Ans) {
		Ans = mx;
		ans = v[px];
	}
	v[tx] = v[px]; v[ty] = v[py]; 
	sum[0] = (int) (val[0] * 1. / sum[N - 1] * 100.);
	for(int i = 1; i < N; i++) sum[i] = sum[i - 1] + (int) (val[i] * 1. / sum[N - 1] * 100.);
	uniform_int_distribution<int> GetPos(0, sum[N - 1] - 1);
	int p1 = GetPos(dre);
	px = (int) (upper_bound(sum, sum + N, p1) - sum);
	while(p1 >= sum[px - 1] && p1 < sum[px]) p1 = GetPos(dre);
	py = (int) (upper_bound(sum, sum + N, p1) - sum);
	
	
	int pos = d(dre) % 160; 
	for(int i = 0; i <= pos; i++) {
		int tmp_stat;
		tmp_stat = v[px].test(i);
		v[px][i] = v[py][i];
		v[py].set(i, tmp_stat); 
	}

	if(pow((db) d(dre) / (1LL << 60), 2) < muta_rate) {
		pos = d(dre) % 160;
		v[py].flip(pos); 
	}
	
	if(pow((db) d(dre) / (1LL << 60), 2) < muta_rate) {
		pos = d(dre) % 160;
		v[px].flip(pos); 
	}
}

LL ev = 0, rn = 0;

void calc() {
	N = 50;
	int T = 10000;
	init();
	while(T --) {
		evolve();
	}
	int Tmp = Ans;
	
	T = 500000;
	Ans = -100000000;
	while(T--) {
		string s = "";
		for(int j = 0; j < 160; j++) {
			int t = d(dre);
			s += (char) ((t & 1) + '0');
		}
		bitset < 160 > tmp(s);
		Ans = max(Ans, F(tmp));
	}
	ev += (Tmp > Ans);
	rn += (Tmp < Ans);
	cout << Tmp << " --- " << Ans << endl << endl; 
}

signed main() {
	int T = 0;
	cin >> T;
	while(T--) {
		Ans = -1000000;
		calc();
		while(!v.empty()) v.pop_back();
	}
	if(ev > rn) cout << "Yeah!!!!    " << ev << " " << rn << endl;
	else cout << "Fuck!!!!     " << ev << " " << rn << endl;
	return 0;
}
