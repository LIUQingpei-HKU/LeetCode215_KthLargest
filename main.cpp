#include <iostream>
#include <vector>

using namespace std;

//Time out
class SolutionMe {
private:
    int __partition(vector<int> arr, int l, int r){
        swap(arr[l],arr[rand()%(r-l+1)+l]);
        int v = arr[l];

        //arr[l+1...j]>v;arr[j+1...i)<=v
        int j=l;
        for(int i=l+1;i<=r;i++){
            if(arr[i]>v){
                swap(arr[j+1],arr[i]);
                j++;
            }
        }
        swap(arr[l],arr[j]);
        return j;
    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        int l = 0;
        int r = nums.size()-1;
        int index = __partition(nums,l,r);
        while(index!=k){
            if(index>k){
                r = index;
                index = __partition(nums,l,r);
            }else{//index<k
                l = index;
                index = __partition(nums,l,r);
            }
        }
        return nums[index];

    }
};

//62.03% 9ms
//O(n)
//O(1)
class Solution {
private:
    int __partition(vector<int>& arr, int l, int r){  //注意要用引用

        swap(arr[l],arr[rand()%(r-l+1)+l]);
        int v = arr[l];

        //arr[l+1...j]>v;arr[j+1...i)<=v
        int j=l;
        for(int i=l+1;i<=r;i++){
            if(arr[i]>v){
                swap(arr[j+1],arr[i]);
                j++;
            }
        }
        swap(arr[l],arr[j]);
        return j;
    }

    //[l...r]
    int __findKthLargest(vector<int>& nums, int l, int r, int k){ //注意要用引用
        if(l==r)
            return nums[l];

        int index = __partition(nums, l, r);
        if(index==k)
            return nums[index];
        else if(index>k)
            return __findKthLargest(nums,l,index-1,k);
        else  //index < k
            return __findKthLargest(nums,index+1,r,k);

    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        //srand(time(NULL));
        return __findKthLargest(nums, 0, nums.size() - 1, k - 1);
    }
};


class Solution2 {
public:
    int findKthLargest(vector<int>& nums, int k) {

        srand(time(NULL));
        return __findKthLargest(nums, 0, nums.size()-1 , k - 1 );
    }

private:
    int __findKthLargest( vector<int>& nums, int l, int r, int k ){

        if( l == r )
            return nums[l];

        int p = partition( nums, l, r );

        if( p == k )
            return nums[p];
        else if( k < p )
            return __findKthLargest( nums, l, p-1, k);
        else // k > p
            return __findKthLargest( nums, p+1 , r, k );
    }

    int partition( vector<int>& nums, int l, int r ){

        int p = rand()%(r-l+1) + l;
        swap( nums[l] , nums[p] );

        int lt = l + 1; //[l+1...lt) > p ; [lt..i) < p
        for( int i = l + 1 ; i <= r ; i ++ )
            if( nums[i] > nums[l] )
                swap(nums[i], nums[lt++]);

        swap(nums[l], nums[lt-1]);

        return lt-1;
    }
};

class Solution3 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if (nums.empty()) return -1;
        return quickSelect(nums, 0, nums.size() - 1, k);
    }

    int quickSelect(vector<int>& nums, int st, int ed, int k) {
        if (st == ed) return nums[st];

        int l = st, r = ed;
        int pivot = nums[(l + r) / 2];

        while (l <= r) {
            while (l <= r && nums[l] > pivot) {
                l++;
            }
            while (l <= r && nums[r] < pivot) {
                r--;
            }

            if (l <= r) {
                swap(nums[l], nums[r]);
                l++;
                r--;
            }
        }

        if (st + k - 1 <= r) {
            return quickSelect(nums, st, r, k);
        }

        if (st + k - 1 >= l) {
            return quickSelect(nums, l, ed, k - (l - st));
        }

        return nums[r + 1];
    }
};



int main() {
    int nums1[] = {3, 2, 1, 5, 6, 4,7,8,3,3,2};
    vector<int> vec1(nums1, nums1 + sizeof(nums1)/sizeof(int));

    cout<<Solution().findKthLargest( vec1, 2 )<<endl;
    for(int i=0;i<vec1.size();i++){
        cout<<vec1[i]<<" ";
    }
    cout<<endl;


    int nums2[] = {3, 1, 2, 4};
    vector<int> vec2(nums2, nums2 + sizeof(nums2)/sizeof(int));

    cout<<Solution().findKthLargest( vec2, 2 )<<endl;


    int nums3[] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
    vector<int> vec3(nums3, nums3 + sizeof(nums3)/sizeof(int));

    cout<<Solution().findKthLargest( vec3, 8 )<<endl;
    return 0;
}