#include <bits/stdc++.h>
using namespace std;




int main()
{
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; i++)
    {
        cin >> numbers.at(i);
    }

    sort(numbers.begin(), numbers.end());


    int maxDiff,diff;
    int firstval=numbers[0],lastVal=numbers[1];
    maxDiff=numbers[1]-numbers[0];

    for (int i = 2; i < n; i++)
    {
        //update_max:
        diff = numbers[i] - firstval;
        if(maxDiff < diff){
            maxDiff=diff;
        }
        diff=numbers[i]-lastVal;
        if(maxDiff < diff){
            maxDiff=diff;
        }
        
        //if its an odd stage, flip
        if(i%2==0){
            firstval=numbers[i];
        }
        else{ //otherwise, place at end
            lastVal=numbers[i];
        }
    }
    
    cout << maxDiff;

    return 0;
}