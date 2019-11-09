#define mod 998244353
#define MAXN 100100
#define MAXE 400400
#define eps 1e-8
#define INF 1e8
#define X first
#define Y second

#include <set>
#include <map>
#include <list>
#include <stack>
#include <cmath>
#include <ctime>
#include <queue>
#include <deque>
#include <array>
#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <random>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef double db;
typedef pair<int, int> pii;

default_random_engine dre(time(NULL));
uniform_int_distribution<LL> d(0, (1LL << 50));

int n, m, N;
double Ans = 1e50, far[40][40];
double Px[40], Py[40];

double F(vector<int> a) {
    double ret = 0;
    for(int i = 0; i < n - 1; i++) {
        ret += far[a[i]][a[i + 1]];
    }
    ret += far[a[n - 1]][a[0]];
    return ret;
}

void maintain(vector<int> &a, vector<int> &b) {
    int nn = (int) a.size();
    map<int, int> ap; ap.clear();
    vector<int> ra, rb; ra.clear(), rb.clear();
    for(int i = 0; i < nn; i++) {
        if(!ap.count(a[i])) ap[a[i]] = 1;
        else ra.push_back(a[i]);
    }

    ap.clear();

    for(int i = 0; i < nn; i++) {
        if(!ap.count(b[i])) ap[b[i]] = 1;
        else rb.push_back(b[i]);
    }

    nn = (int) ra.size();
    
    for(int i = 0; i < nn; i++) {
    	for(int j = 0; j < (int) a.size(); j++) {
    		if(a[j] == ra[i]) {
    			a[j] = rb[i];
    			break;
			}
		}
		
		for(int j = 0; j < (int) a.size(); j++) {
    		if(b[j] == rb[i]) {
    			b[j] = ra[i];
    			break;
			}
		}
    }

    nn = (int) a.size();
}

vector<vector<int> > v;
double sum[MAXN], val[MAXN];

bool cmp(vector<int> a, vector<int> b) {
    return F(a) < F(b);
}

void init() {
    N = 500;
    v.clear();
	
	srand((unsigned) time(NULL)); 
    vector<int> tmp;
    tmp.clear();
    for(int i = 1; i <= n; i++) tmp.push_back(i);
    for(int i = 0; i < N; i++) {
        random_shuffle(tmp.begin(), tmp.end());
        v.push_back(tmp);
    }
}

void evolve() {
	N = (int) v.size();
    srand((unsigned) (time(NULL)));
    sort(v.begin(), v.end(), cmp); 
	
    for(int i = 0; i < (int) v.size(); i++) {   
		val[i] = F(v[i]);
    }
    
    if(Ans > F(v[0]) + eps) {
    	Ans = F(v[0]);
	} 
	
	vector<int> x, y;
	if(n >= 4) v[v.size() - 1] = v[0]; v[v.size() - 2] = v[1];

    for(int i = 2; i + 1 < N; i += 2) {
    	if((db) rand() / RAND_MAX < 0.85) {
    		x = v[i], y = v[i + 1];
    		int pos_begin = (int) (d(dre) % n), pos_end = (int) (d(dre) % n);
    		if(pos_begin > pos_end) 
				swap(pos_end, pos_begin);
    		for(int j = pos_begin; j <= pos_end; j++) {
    				swap(v[i][j], v[i + 1][j]);
			} 
    		maintain(v[i], v[i + 1]);
    		
    		if(F(v[i]) > val[i] + eps || F(v[i + 1]) > val[i + 1] + eps) {
    			pos_begin = (int) (d(dre) % n), pos_end = (int) (d(dre) % n);
    			if(pos_begin > pos_end) 
					swap(pos_end, pos_begin);
    			for(int j = 0; j <= pos_begin; j++) {
    				swap(v[i][j], v[i + 1][j]);
				} 
    			maintain(v[i], v[i + 1]);
			}
			
			if(F(v[i]) > val[i] + eps || F(v[i + 1]) > val[i + 1] + eps) {
				v[i] = x; v[i + 1] = y;
			}
		}
	}
    int pos_begin, pos_end;
    for(int i = 2; i < N; i++) {
    	if(rand() / RAND_MAX < 0.09) {
    		pos_begin = (int) (d(dre) % n), pos_end = (int) (d(dre) % n);
        	while(pos_begin == pos_end) pos_end = (int) (d(dre) % n);
        	swap(v[i][pos_begin], v[i][pos_end]);
        	
        	if(val[i] < F(v[i])) {
        		pos_begin = (int) (d(dre) % n), pos_end = (int) (d(dre) % n);
        		while(pos_begin == pos_end) pos_end = (int) (d(dre) % n);
        		swap(v[i][pos_begin], v[i][pos_end]);
			}
		}
	}
}

inline void calc() {
    init();
    int T = 2000;
    while(T --) evolve();
    cout << Ans << " ";
}

signed main() {
	freopen("data.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    for(int i = 1; i <= 38; i++) {
        for(int j = 1; j <= 38; j++) {
            far[i][j] = INF;
        }
    }
    
	cin >> n;
    for(int i = 1; i <= n; i++) {
        int a;
		cin >> a >> Px[i] >> Py[i];
    }
    
    for(int i = 1; i <= n; i++) {
    	for(int j = i; j <= n; j++) {
    		far[i][j] = far[j][i] = 
			sqrt((Px[i] - Px[j]) * (Px[i] - Px[j]) + (Py[i] - Py[j]) * (Py[i] - Py[j]));
		}
	}

    Ans = INF;
    calc();
    fclose(stdin);
	return 0;
}
/*
38 
1 11003.611100 42102.500000
2 11108.611100 42373.888900
3 11133.333300 42885.833300
4 11155.833300 42712.500000
5 11183.333300 42933.333300
6 11297.500000 42853.333300
7 11310.277800 42929.444400
8 11416.666700 42983.333300
9 11423.888900 43000.277800
10 11438.333300 42057.222200
11 11461.111100 43252.777800
12 11485.555600 43187.222200
13 11503.055600 42855.277800
14 11511.388900 42106.388900
15 11522.222200 42841.944400
16 11569.444400 43136.666700
17 11583.333300 43150.000000
18 11595.000000 43148.055600
19 11600.000000 43150.000000
20 11690.555600 42686.666700
21 11715.833300 41836.111100
22 11751.111100 42814.444400
23 11770.277800 42651.944400
24 11785.277800 42884.444400
25 11822.777800 42673.611100
26 11846.944400 42660.555600
27 11963.055600 43290.555600
28 11973.055600 43026.111100
29 12058.333300 42195.555600
30 12149.444400 42477.500000
31 12286.944400 43355.555600
32 12300.000000 42433.333300
33 12355.833300 43156.388900
34 12363.333300 43189.166700
35 12372.777800 42711.388900
36 12386.666700 43334.722200
37 12421.666700 42895.555600
38 12645.000000 42973.333300

*/
