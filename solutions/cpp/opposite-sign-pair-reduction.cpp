class Solution {
  public:
    vector<int> asteroidCollision(int N, vector<int> &asteroids) {
        // code here
        
        stack<int> st;
        
        for(int i = 0; i < N; i++){
            if(st.empty() || asteroids[i] > 0){
                st.push(asteroids[i]);
            }else{
                while(!st.empty() && st.top() > 0 && st.top() < abs(asteroids[i])){
                    st.pop();
                }

                if(!st.empty() && st.top() == abs(asteroids[i])){
                    st.pop();
                }else{
                    if(st.empty() || st.top() < 0){
                        st.push(asteroids[i]);
                    }
                } 
            }
        } 
     vector<int> ans(st.size(), 0); 
     int size = st.size();
        while(!st.empty()){
            ans[--size] = st.top();
            st.pop();
        }
     return ans;
    }
};