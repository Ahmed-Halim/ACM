#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define EPS 1e-9
#define MOD 1e9+7
#define SET(a) memset(a , 0 , sizeof(a))
#define Fast ios_base::sync_with_stdio(false)

class DisjointSet {
private:
    vector <int> parent , rank , setsize;
    int sets;
public:
    DisjointSet (int N) {
        sets = N;
        parent = vector <int> (N);
        rank = vector <int> (N);
        setsize = vector <int> (N);
        for (int i = 0; i < N; i++) {
            parent[i] = i; setsize[i] = 1 , rank[i] = 0;
        }
    }
    
    int getParent (int x){
        if (x == parent[x]) return x;
        return parent[x] = getParent (parent[x]);
    }
    
    bool isSameSet (int x , int y){
        return getParent(x) == getParent(y);
    }
    void Union (int x , int y) {
        if (isSameSet(x , y)) return;
        sets--;
        int xp = getParent(x);
        int yp = getParent(y);
        if (rank[xp] > rank[yp]) {
            parent[yp] = xp; setsize[xp] += setsize[yp];
        } else {
            if (rank[xp] == rank[yp]) {
                rank[yp]++;
                parent[xp] = yp; setsize[yp] += setsize[xp];
            } else {
                parent[xp] = yp; setsize[yp] += setsize[xp];
            }
        }
        
    }
    int numDisjointSets() {
        return sets;
    }
    int getSetSize(int x){
        return setsize[getParent(x)];
    }
};

int main() {
    Fast;
    
    int T;
    cin >> T;
    
    while (T--) {
        int Max = 100000;
        vector <int> div[Max+1];
        int n;
        cin >> n;
        int temp;
        for(int i = 0 ; i < n ; ++i) {
            cin >> temp;
            div[temp].push_back(i);
        }
        DisjointSet DS(n);
        long long ans = 0;
        for (int i = Max; i >= 1; i--) {
            int lead = -1;
            for (int j = i; j <= Max ; j += i ) {
                if (div[j].size() > 0 && lead == -1) {
                    lead = div[j][0];
                }
                if (lead != -1) {
                    for (auto x : div[j]) {
                        if (!DS.isSameSet(lead , x)) {
                            DS.Union(lead , x);
                            ans += i;
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}
