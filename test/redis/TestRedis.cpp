
#include "TestRedis.h"
#include "Redis.h"
#include <memory>
#include <string_view>
#include <iostream>
#include <thread>

using namespace std;
using namespace yedis;


class RedisWorker {
    public:
        void operator()() const {
             Redis r;
            const string_view addr("192.168.1.179");
            auto port = 6379;
            auto ret = r.connect(addr,port);

            if (ret) {

                auto result = r.execCommand("RPUSH mylist \"Hello\"");
                cout<<"result "<<result.get()<<endl;
            }
            // while (ret) {
            //     sleep(1);
            // }
            
        }
};

TEST_F(TestRedis,test_connect) {
   thread t{RedisWorker()};
   
   t.join();
}


class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        
        std::sort(nums.begin(),nums.end());
        int n = nums.size();
        vector<vector<int>> ans;

        for (int j = 0; j < n; j++) {
            for(int i = j + 1; i < n; i++) {
                int left = i + 1;
                int right = n - 1;
                while (left < right) {
                    int sum =  nums[left] + nums[right] + nums[i];
                    if (sum + nums[j] < target) left++;
                    else  if (sum + nums[j] > target) right--;
                    else ans.push_back({nums[left],nums[right],nums[i],nums[j]});
                
                    while(left < n - 1 && nums[left] == nums[left + 1]) left++;
                    while(right >= 0 && nums[right] == nums[right - 1]) right--;
                }
            }
        }

        

        return ans;
    }
};