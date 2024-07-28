#include <bits/stdc++.h>

using namespace std;

const int BASE = 50003;  // Base for polynomial rolling hash
const int MOD = 1e9 + 9;  // Large prime modulus to avoid collisions
int n, m;
vector<string> type1;
vector<string> type2;
vector <vector< long long>> type1_hashes;
vector <vector< long long>> type2_hashes;
vector<long long> power;

// Function to compute rolling hash value of a string
vector<long long> computeStringHash(const string& s) {
    vector<long long> hashes(m + 1, 0);

    // Compute hash values for all substrings of s
    for (int i = 0; i < m; ++i) {
        hashes[i + 1] = (hashes[i] * BASE + (s[i] - 'A' + 1)+ MOD) % MOD;
    }
    return hashes;
}

long long getPartialHash(const vector<long long>& hashvals, int l, int r) {
    // Length of substring
    int len = r - l + 1;
   
    // Compute hash value using polynomial rolling hash formula
    long long hash_value = (hashvals[r] - (hashvals[l-1] * power[len] % MOD) + MOD) % MOD;
   
    return hash_value;
}


bool is_right_bound_working(int l, int r)
{
    // Check for all lengths from 1 to m
    set <int> st;
    for (int i = 0; i < n; i++)
        st.insert(getPartialHash(type1_hashes[i],l,r));
   
    for (int i = 0; i < n; i++)
    {
        if(st.find(getPartialHash(type2_hashes[i],l,r)) != st.end())
            return false;
    }
    return true;
}

int bs_right_bound(int l){
int d = l - 1, up = m + 1;

    if(!is_right_bound_working(l,m))
        return -1;

    while (up - d > 1)
    {
int mid = (up + d) >> 1;
        if(is_right_bound_working(l, mid))
{
up = mid;
}
else
{
d = mid;
}
    }
    return up;
}



int min_distinguishing_length() {
   
    vector<long long> interval_hashes;
    int ans=m;
    // Check for all lengths from 1 to m
    for (int l = 1; l <= m; l++) {
        int r=bs_right_bound(l);
        if(r!=-1)
{
ans = min(ans, r - l + 1);
}
    }
    return ans;  // In the worst case, we need to check the entire length of the strings
}

void get_input(){
    cin >> n >> m;
    power.resize(m + 2, 0);
    type1.resize(n+2);
    type2.resize(n+2);
    type1_hashes.resize(n+2);
    type2_hashes.resize(n+2);
    // Read type1 strings
    for (int i = 0; i < n; ++i) {
        cin >> type1[i];
    }
   
    // Read type2 strings
    for (int i = 0; i < n; ++i) {
        cin >> type2[i];
    }

power[0] = 1;
    for (int i = 1; i <= m; ++i) {
        power[i] = (power[i - 1] * BASE) % MOD;
    }
}

void calculate_hashes(){
    for (int i = 0; i < n; i++)
    {
        type1_hashes[i]=computeStringHash(type1[i]);
        type2_hashes[i]=computeStringHash(type2[i]);
    }
}




int main() {

    get_input();    
    calculate_hashes();
   
    // Call the function and print the result
    cout << min_distinguishing_length() << endl;
   
    return 0;
}