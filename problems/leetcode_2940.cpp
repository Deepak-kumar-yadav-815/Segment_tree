//(h.k)
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL)
#define test(t) int t;cin>>t;while(t--)
#define all(x) begin(x),end(x)
class SegmentTree
{
public:
    // max_index
    int n;
    vector<int> tree;
    SegmentTree(vector<int> &arr, int n)
    {
        this->n = n;
        tree.resize(4 * n, INT_MIN);
        build(arr, 0, 0, n - 1);
    }
    void build(vector<int> &arr, int ind, int low, int high)
    {
        if (low == high)
        {
            tree[ind] = low;
            return;
        }
        int mid = low + ((high - low) >> 1);
        build(arr, 2 * ind + 1, low, mid);
        build(arr, 2 * ind + 2, mid + 1, high);
        tree[ind] = (arr[tree[2 * ind + 1]] > arr[tree[2 * ind + 2]]) ? tree[2 * ind + 1] : tree[2 * ind + 2];
    }
    int rmiq(const vector<int> &arr, int ti, int tl, int tr, int rl, int rr)
    {

        if (rr < tl || tr < rl)
            return -1;

        if (rl <= tl && tr <= rr)
            return tree[ti];

        int mid = tl + ((tr - tl) >> 1);

        int leftq = rmiq(arr, 2 * ti + 1, tl, mid, rl, rr);
        int rightq = rmiq(arr, 2 * ti + 2, mid + 1, tr, rl, rr);

        if (leftq == -1)
            return rightq;
        if (rightq == -1)
            return leftq;

        return arr[leftq] > arr[rightq] ? leftq : rightq;
    }
    int rmiq2(int a,int b,vector<int>&arr,int n){
        if(a==b||arr[a]<arr[b])return b;
        int left = b+1,right = n-1;
        int pans =-1;
        while(left<=right){
            int mid = left+((right-left)>>1);
            int ans = rmiq(arr,0,0,n-1,left,mid);
            if(ans!=-1&&arr[ans]>max({arr[a],arr[b]})){
                pans=ans;
                right=mid-1;
            }
            else{
                left=mid+1;
            }
        }
        return pans;
    }
};
class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int n = heights.size();
        SegmentTree st(heights,n);
        int q = queries.size();
        vector<int>ans(q,0);
        for(int i=0;i<q;i++){
            sort(begin(queries[i]),end(queries[i]));
            ans[i]=st.rmiq2(queries[i][0],queries[i][1],heights,n);
        }
        return ans;
    }
};