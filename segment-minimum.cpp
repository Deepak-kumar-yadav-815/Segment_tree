#include<bits/stdc++.h>
using namespace std;

class SegmentMin{
    public:
        int n;
        vector<int>nums;
        vector<int>tree;
        SegmentMin(int n,vector<int>&nums){
            this->nums = nums;
            this->n = n;
            tree.resize(4*n,INT32_MAX);
        }
        void build(int ind,int low,int high){
            if(low==high){
                tree[ind] = nums[low];
                return;
            }
            int mid = low + ((high-low)>>1);
            build(2*ind+1,low,mid);
            build(2*ind+2,mid+1,high);
            tree[ind] = min(tree[2*ind+1],tree[2*ind+2]);
        }
        void update(int ind,int val,int ti,int low,int high){
            if(low==high){
                tree[ti] = val;
                nums[ind] = val;
                return;
            }
            int mid = low +((high-low)>>1);
            if(ind<=mid){
                update(ind,val,2*ti+1,low,mid);
            }
            else update(ind,val,2*ti+2,mid+1,high);
            tree[ti] = min(tree[2*ti+1],tree[2*ti+2]);
        }
        int query(int ti,int tl,int tr,int rl,int rr){
            //no overlap
            if(rr<tl||tr<rl)return INT32_MAX;
            //compelete overlap
            if(rl<=tl&&rr>=tr){
                return tree[ti];
            }
            //partial overlap
            int mid = tl +((tr-tl)>>1);
            int leftq = query(2*ti+1,tl,mid,rl,rr);
            int rightq = query(2*ti+2,mid+1,tr,rl,rr);
            return min(leftq,rightq);
        }
};

signed main() {

}
