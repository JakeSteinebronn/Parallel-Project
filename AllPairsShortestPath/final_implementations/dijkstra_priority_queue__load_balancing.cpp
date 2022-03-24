#include <bits/stdc++.h>
#include <thread>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

// template<class T, class U> istream& operator>>(istream &is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
// template<class T> istream& operator>>(istream& is, vector<T>& vec) { for(auto &x : vec) cin >> x; return is; } 
// template<class T, class U> ostream& operator<<(ostream &os, pair<T, U>& p) { os << "<" << p.first << "," << p.second << ">"; return os; }
// template<class T> ostream& operator<<(ostream& os, vector<T>& vec) { os << "["; for(auto x : vec) os << x << " "; os << "]"; return os; }

ll oo = ll(1e15);

const int MAXN = 5000;
ll adj[MAXN][MAXN];
ll res[MAXN][MAXN];

int n;
typedef pair<ll, int> st;
typedef priority_queue<st, vector<st>, greater<st>> dpq;

void dijkstra(int st) {
    rep(i, 0, n) res[st][i] = oo;
    res[st][st] = 0;
    dpq pq;
    pq.emplace(0, st);
    
    while(pq.size()) {
        auto [d, u] = pq.top(); pq.pop();
        if(d > res[st][u]) continue;
        rep(v, 0, n) {
            if(v != u && res[st][v] > d + adj[u][v]) {
                res[st][v] = d + adj[u][v];
                pq.emplace(res[st][v], v);
            }
        }
    }
}

int num_threads = 12;

int main(int argc, char *argv[]){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    if(argc > 1) num_threads = stoi(argv[1]);

    cin >> n;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> adj[i][j];

    // APSP HERE
    
    int curi = 0;
    mutex curiLock;

    auto threadEx = [&](int tnum) -> void {
        while(true){
            curiLock.lock();
            int me = curi;
            curi += 1;
            curiLock.unlock();
            if(me >= n) break;
            dijkstra(me);
        }
    };

    vector<thread*> threads;
    rep(i, 0, num_threads) threads.push_back(new thread(threadEx, i));
    for(auto th : threads) th->join();


    // END APSP HERE
    cout << n << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) cout << res[i][j] << " ";
        cout << "\n";
    } 

    return 0;
}
