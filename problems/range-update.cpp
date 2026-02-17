//(h.k)
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL)
#define test(t) int t;cin>>t;while(t--)
#define all(x) begin(x),end(x)
class LazySegmentTree {
public:
    int n;
    vector<long long> tree;
    vector<long long> lazy;

    LazySegmentTree(vector<long long>& arr) {
        n = arr.size();
        tree.resize(4*n);
        lazy.resize(4*n, 0);
        build(0, 0, n-1, arr);
    }

    // Build
    void build(int ind, int low, int high, vector<long long>& arr) {
        if (low == high) {
            tree[ind] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);

        tree[ind] = tree[2*ind+1] + tree[2*ind+2];
    }

    // Push lazy value
    void push(int ind, int low, int high) {
        if (lazy[ind] != 0) {
            tree[ind] += (high - low + 1) * lazy[ind];

            if (low != high) {
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }

            lazy[ind] = 0;
        }
    }

    // Range Update (add val to [l, r])
    void update(int ind, int low, int high, int l, int r, long long val) {

        push(ind, low, high);

        // No overlap
        if (high < l || r < low)
            return;

        // Complete overlap
        if (l <= low && high <= r) {
            lazy[ind] += val;
            push(ind, low, high);
            return;
        }

        // Partial overlap
        int mid = (low + high) / 2;
        update(2*ind+1, low, mid, l, r, val);
        update(2*ind+2, mid+1, high, l, r, val);

        tree[ind] = tree[2*ind+1] + tree[2*ind+2];
    }

    // Range Query (sum of [l, r])
    long long query(int ind, int low, int high, int l, int r) {

        push(ind, low, high);

        // No overlap
        if (high < l || r < low)
            return 0;

        // Complete overlap
        if (l <= low && high <= r)
            return tree[ind];

        // Partial overlap
        int mid = (low + high) / 2;

        return query(2*ind+1, low, mid, l, r)
             + query(2*ind+2, mid+1, high, l, r);
    }
};

signed main(){
    int n,q;cin>>n>>q;
    vector<int>nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    LazySegmentTree range(nums);
    range.build(0,0,n-1,nums);
    while(q--){
        int t;cin>>t;
        if(t==1){
            int a,b,u;cin>>a>>b>>u;
            range.update(0,0,n-1,a-1,b-1,u);
        }
        else{
            int k;cin>>k;
            cout<<range.query(0,0,n-1,k-1,k-1)<<endl;
        }
    }
}