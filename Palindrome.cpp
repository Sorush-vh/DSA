#include <iostream>
#include <string.h>

#define ALPHABET_PRIME 31
#define HASH_PRIME2 1000000007
#define HASH_PRIME 1000000009
#define MAX_SIZE 200005
typedef unsigned long long ULL;

using namespace std;
ULL palindrome_degrees[MAX_SIZE];
ULL start_subs_hash[MAX_SIZE];
ULL offset_powers[MAX_SIZE];
ULL end_subs_hash[MAX_SIZE];//starts from the end of the string: end[0]=last char
ULL total_degree=0;
int length;

ULL get_substring_hash(int index, bool is_from_start){
    if(index==-1 || index==length)
        return 0;
    if(is_from_start)
        return start_subs_hash[index];
    else
        return end_subs_hash[index];
}

ULL get_partial_hash(int start, int end, bool is_from_start){
    if(is_from_start)
        return (get_substring_hash(end,true)-get_substring_hash(start-1,true)+HASH_PRIME)%HASH_PRIME;
    else
        return (get_substring_hash(start,false)-get_substring_hash(end+1,false)+HASH_PRIME)%HASH_PRIME;
}

ULL get_offset_power(int bound,bool for_reverse){
    if(for_reverse)
        return offset_powers[bound];
    else
        return offset_powers[length-1-bound];
}


bool is_string_palindrome(int start, int end, int strsize){

    int bound1=start+strsize/2-1;
    ULL start_reverse_partial=get_partial_hash(start,bound1,false);

    int bound2=strsize/2 +start;
    if(strsize%2 == 1)
        bound2+=1;
    ULL end_inorder_partial=get_partial_hash(bound2,end,true);


    start_reverse_partial=(start_reverse_partial*get_offset_power(bound2,true))%HASH_PRIME;
    end_inorder_partial=(end_inorder_partial*get_offset_power(bound1,false))%HASH_PRIME;

    return (end_inorder_partial==start_reverse_partial) ? true : false;
}

ULL get_string_palindrome_degree(int end){

    if(palindrome_degrees[end]!=-1)
        return palindrome_degrees[end];

    int strsize=end+1;
    if(strsize==1){
        palindrome_degrees[end]=1;
        return 1;
    }

    if(!is_string_palindrome(0,end,strsize)){
        palindrome_degrees[end]=0;
        return 0;
    }

    int bound=strsize/2 -1;

    ULL k1=get_string_palindrome_degree(bound);
    palindrome_degrees[end]=k1+1;
    return k1+1;
}


void calculate_substings(char input, ULL base_pow ,int step,bool is_from_start){
    
    ULL delta=(ULL) ((input-'a'+1) * base_pow) % HASH_PRIME;

    if(is_from_start){
        start_subs_hash[step]=(get_substring_hash(step-1,true)+delta)%HASH_PRIME;
    }
    else{
        end_subs_hash[step]=(get_substring_hash(step+1,false)+delta)%HASH_PRIME;
    }
}

int main(){
    string input;
    getline(cin,input);
    length=input.size();

    for (int i = 0; i < length; i++)
        palindrome_degrees[i]=-1;
    
    ULL base_pow=1;
    for (int i = 0; i < length; i++){
        calculate_substings(input.at(i), base_pow,i,true);
        offset_powers[i]=base_pow;
        base_pow=(base_pow * ALPHABET_PRIME) % HASH_PRIME;
    }

    base_pow=1;
    for (int i = length-1; i > -1; i--){
        calculate_substings(input.at(i), base_pow,i,false);
        base_pow=(base_pow * ALPHABET_PRIME) % HASH_PRIME;
    }

    for (int i = 0; i < length; i++){
       total_degree+=get_string_palindrome_degree(i);
    }


    cout << total_degree;
    return 0;
}