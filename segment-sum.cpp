#include<bits/stdc++.h>
using namespace std;

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
        int rmiq(int ind, int left, int right, int l, int r) {
            if (right < l || left > r)
                return 0;

            if (left >= l && right <= r)
                return tree[ind];
            int mid = left + (right - left) / 2;

            int leftSum  = rmiq(2*ind + 1, left, mid, l, r);
            int rightSum = rmiq(2*ind + 2, mid+1, right, l, r);

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
    int n ;cin>>n;
    vector<int>nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    SegmentTree sum(nums);
    sum.build(0,0,n-1);
    for(int i=0;i<(4*n);i++){
        cout<<sum.tree[i]<<" ";
    }
}
