#include<bits/stdc++.h>
using namespace std;
/* The functions which
builds the segment tree */
void build(int st[], int arr[], int ind, int low, int high){
    if(low == high){
        st[ind] = arr[low];
        return;
    }

    int mid = low + ((high - low) >> 1);

    build(st, arr, 2*ind+1, low, mid);
    build(st, arr, 2*ind+2, mid+1, high);

    st[ind] = min(st[2*ind+1], st[2*ind+2]);
}

int* constructST(int arr[], int n) {

    int* st = new int[4*n + 1];

    fill(st, st + 4*n + 1, INT_MAX);

    build(st, arr, 0, 0, n-1);

    return st;
}
/* The functions returns the
 min element in the range
 from a and b */
int query(int tree[],int ti,int tl,int tr,int rl,int rr){
            //no overlap
            if(rr<tl||tr<rl)return INT32_MAX;
            //compelete overlap
            if(rl<=tl&&rr>=tr){
                return tree[ti];
            }
            //partial overlap
            int mid = tl +((tr-tl)>>1);
            int leftq = query(tree,2*ti+1,tl,mid,rl,rr);
            int rightq = query(tree,2*ti+2,mid+1,tr,rl,rr);
            return min(leftq,rightq);
        }
int RMQ(int st[], int n, int a, int b) {
    return query(st,0,0,n-1,a,b);
}