#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;
#define MAX_SIZE 64 


int n,k,bound;
int ans=0;

int last_index=0;
int combination_table [MAX_SIZE]; 

void fill_table(int n, int bound, int k){
    int sum=0,digit_value, number_copy;
    for (int i = 0; i < bound; i++)
    {
        //check:
        number_copy=i;
        for (int j = 0; j < n; j++)
        {
            digit_value=number_copy%2;
            number_copy/=2;
            if(digit_value==1)
                sum++;
        }

        if(sum==k){
            combination_table[last_index]=i;
            last_index++;
        }
        sum=0;
    }
    
}



void brute_force(int step, vector<int> current_column_sum,int encoded_row ){

    int digit_value;
    for (int i = 0; i < n; i++){
        digit_value=encoded_row%2;
        encoded_row/=2;
        
        if(digit_value==1){
            current_column_sum.at(i)+=1;
        }
    }

    for (int i = 0; i < n; i++)
        if(current_column_sum.at(i)>k)
            return;
    

    if(step==n){
        ans++;
        return;
    }
    
    //FINDING COMBINARTIONS WICH FILL ROWS CORRECTLY, THEN CHECKING IF..
    //..COLUMNS END UP FINE
    for (int i = 0; i < last_index; i++)
        brute_force(step+1,current_column_sum,combination_table[i]);
    
}


int main(){

    double cosign=1;
    double tanval=1;
    for (int i = 0; i < 15; i++)
    {
        cosign*=(cos(atan(tanval)));
        tanval/=2;
    }
    cout << ((double)1/tanval) << "\n";
    

    cin >> n >> k;

    vector <int> column_sum;
    vector<int> row;
    bound=int(pow(2,n));
    column_sum.resize(n);
    row.resize(n);

    for (int i = 0; i < n; i++){
        column_sum.at(i)=0;
        row.at(i)=0;
    }

    fill_table(n,bound,k);    

    for (int i = 0; i < last_index; i++)
        brute_force(1,column_sum,combination_table[i]);
    cout << ans;


}





