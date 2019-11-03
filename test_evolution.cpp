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

const db muta_rate = 1e-9;
double A;
int N, Ans = -1000000, initial_val;
int sum[MAXN / 100 + 10], val[MAXN / 100 + 10]; 

vector<bitset < 160 > > v;
bitset < 160 > ans;
default_random_engine dre(time(NULL));
uniform_int_distribution<int> d(0, (1 << 30));

/*
 * check函数用于判断一个单位（基因）是否是有效的
 * F函数是计算适应度的（即该01串的总贡献）
 * default...是C++11自带的生成均匀随机数的引擎（?）
 * uniform...就是具体到生成一个随机数的函数
 * 事实上这属于上一个版本的遗留问题，不过已经基本解决
*/
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

/*
 * init()函数的作用是生成一个大小为N的种群
 * 不得不说bitset真是个好东西^_^
 * 可以直接用01串赋初值实在是省了很多麻烦
 * 
*/

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

//进化

void evolve() {
	int mx = -10000000, smx = -10000000;
	int mn = 10000000, smn = 10000000; 
	int px = 0, py = 0, ty = 0, tx = 0;
	sum[0] = 0;
	for(int i = 0; i < N; i++) {
		int res = 0;
		res = F(v[i]);
		if(res > mx) smx = mx, py = px, px = i, mx = res;
		else if(res > smx) smx = res, py = i; //记录适应度最大和次大的01串
		if(res < mn) smn = mn, ty = tx, tx = i, mn = res;
		else if(res < smn) smn = res, ty = i; //记录适应度最小和次小的01串
		val[i] = res + 800; // 保证非负
		if(i) sum[i] = sum[i - 1] + val[i];
		else sum[i] = val[i];
	}
	if(mx > Ans) {
		Ans = mx;
		ans = v[px];
	}
	v[tx] = v[px]; v[ty] = v[py]; //保留优秀基因，淘汰弱小个体，鉴于计算机内存和CPU算力有限，不敢扩大种群数量，只能执行末位淘汰
	sum[0] = (int) (val[0] * 1. / sum[N - 1] * 100.);
	for(int i = 1; i < N; i++) sum[i] = sum[i - 1] + (int) (val[i] * 1. / sum[N - 1] * 100.);
	uniform_int_distribution<int> GetPos(0, sum[N - 1] - 1);
	int p1 = GetPos(dre);
	px = (int) (upper_bound(sum, sum + N, p1) - sum);
	while(p1 >= sum[px - 1] && p1 < sum[px]) p1 = GetPos(dre);
	py = (int) (upper_bound(sum, sum + N, p1) - sum);

	/*
	 * 专门解释一下上面这段代码，它的作用类似于加权
	 * 根据适应度给每个01串分配一个权值，适应度越大权值越大
	 * 目前的权值计算方式并不是最优的，存在一定的问题
	 * 计算完成之后随机选择两个01串，这两个串将用于杂交，显然越优秀的个体越容易被选中
	 * 具体的实现方式是将权值映射到值域数轴上，随机生成一个数，判断属于哪个01串
	*/
	
	int pos = d(dre) % 160; //随机生成一个位置作为交叉互换的点
	for(int i = 0; i <= pos; i++) {
		int tmp_stat;
		tmp_stat = v[px].test(i);
		v[px][i] = v[py][i];
		v[py].set(i, tmp_stat); //交叉互换
	}
	for(int i = 0; i < N; i++) {
		if(pow((db) d(dre) / (1LL << 60), 2) < muta_rate) {
			pos = d(dre) % 160;
			v[i].flip(pos); 
			/*
			 * 每个个体在每次进化中存在一定的概率变异（高中生物又快忘了，可能不太符合逻辑）
			 * 变异的方式是将随机某一位取反
			*/
		}
	}
}

LL ev = 0, rn = 0;

void calc() {
	N = 50;
	init();
	int T = 100000;
	while(T --) {
		evolve();
	}
	int Tmp = Ans;
	
	T = 300000;
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
		calc();
	}
	if(ev > rn) cout << "Yeah!!!!    " << ev << " " << rn << endl;
	else cout << "Fuck!!!!     " << ev << " " << rn << endl;
	return 0;
}