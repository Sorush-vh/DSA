#include <iostream>

using namespace std;




int main(){
    long int n;

    cin >> n;
    if( (n+5)%5==0 || (n+5)%5==2 )
        cout << "Yes";
    else 
        cout << "No";    

    return 0;
}