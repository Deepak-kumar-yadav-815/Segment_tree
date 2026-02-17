//(h.k)
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL)
#define test(t) int t;cin>>t;while(t--)
#define all(x) begin(x),end(x)
class SegmentTree{
    public:
        int n;
        vector<int>tree;
        vector<int>nums;
        SegmentTree(vector<int>&nums){
            this->n = nums.size();
            tree.resize(4*n,0);
            this->nums = nums;
        }
        void build(int ind,int left ,int right){
            if(left==right){
                tree[ind] = nums[left];
                return;
            }
            int mid = left + ((right-left)>>1);
            build(2*ind+1,left,mid);
            build(2*ind+2,mid+1,right);
            tree[ind] = tree[2*ind + 1]+tree[2*ind + 2];
        }
        int query(int ind, int left, int right, int l, int r) {
            if (right < l || left > r)
                return 0;

            if (left >= l && right <= r)
                return tree[ind];
            int mid = left + (right - left) / 2;

            int leftSum  = query(2*ind + 1, left, mid, l, r);
            int rightSum = query(2*ind + 2, mid+1, right, l, r);

            return leftSum + rightSum;
        }
        void update(int ind,int val,int i,int l,int r){
            if(l==r){
                tree[i] = val;
                nums[ind] = val;
                return;
            }
            int mid = l + ((r-l)>>1);
            if(ind<=mid){
                update(ind,val,2*i+1,l,mid);
            }
            else{
                update(ind,val,2*i+2,mid+1,r);
            }
            tree[i] = tree[2*i+1]+tree[2*i+2];
        }
};
signed main() {
  fast;
  int n,q;cin>>n>>q;
  vector<int>nums(n);
  for(int i=0;i<n;i++)cin>>nums[i];
  SegmentTree sum(nums);
  sum.build(0,0,n-1);
  while(q--){
    int t,a,b;cin>>t>>a>>b;
    if(t==1){
        sum.update(a-1,b,0,0,n-1);
    }
    else{
        cout<<sum.query(0,0,n-1,a-1,b-1)<<endl;
    }
  }
}
