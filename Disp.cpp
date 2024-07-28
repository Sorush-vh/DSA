#include <iostream>
#include <vector>

using namespace std;

#define MAX_NUMBER 1000000007

class FenwickTree {
private:
    vector<long long int> bit;

public:

    FenwickTree(int size) : bit(size + 1, 0) {}

    void update(int index, int delta) {
        while (index < bit.size()) {
            bit[index] += delta;
            index += index & -index;
        }
    }

    long long int query(int index) {
        long long int sum = 0;
        while (index > 0) {
            sum += bit[index];
            index -= index & -index;
        }
        return sum;
    }

    long long int getRangeSum(int left, int right) {
        return query(right) - query(left - 1);
    }
};

int n,tuple_counts=0;
vector <int> indexes;

void read_input(vector <int>& vect){

    cin >> n;

    vect.resize(n+1);

    int temp;
    for (int i = 1; i < n+1; i++)
    {
        cin >> temp;
        vect.at(temp)=i;
    }
    vect.at(0)=0;
}

int get_index_of(int i){
    return indexes.at(i);
}

//ENTEKHABE 2 AZ C
long long int get_pairs_combination_count(int c){
    return (long)c*(c-1)/2;
}


void add_Ith_effect(int i,FenwickTree* mainF, FenwickTree* left_sum,FenwickTree* right_sum){
    int index=get_index_of(i);

    int r_index_sum=mainF->getRangeSum(index+1,n);
    int l_index_sum=mainF->getRangeSum(1,index-1);
    long long int r_correct_combs=get_pairs_combination_count(r_index_sum)-right_sum->getRangeSum(index+1,n);
    long long int l_correct_combs=get_pairs_combination_count(l_index_sum)-left_sum->getRangeSum(1,index-1);
    
    r_correct_combs=r_correct_combs%MAX_NUMBER;
    l_correct_combs=l_correct_combs%MAX_NUMBER;
    tuple_counts=(tuple_counts+((r_correct_combs*l_correct_combs)%MAX_NUMBER))%MAX_NUMBER;

    right_sum->update(index,r_index_sum);
    left_sum->update(index,l_index_sum);
    mainF->update(index,1);
    
}

int main() {

    read_input(indexes);

    FenwickTree right_sum(n),left_sum(n),mainF(n);

    for (size_t i = n; i > 0; i--)
        add_Ith_effect(i,&mainF,&left_sum,&right_sum);
    
    cout << tuple_counts;



    // // Example usage:
    // int size = 10; // Adjust the size as needed
    // FenwickTree fenwickTree(size);

    // // Modify operations
    // fenwickTree.update(3, 5); // Change value at index 3 to 5
    // fenwickTree.update(5, 2); // Change value at index 5 to 2
    // fenwickTree.update(3,1);

    // // Reading sum of range [l, r]
    // int left = 2, right = 7;
    // int rangeSum = fenwickTree.getRangeSum(left, right);

    // cout << "Sum of range [" << left << ", " << right << "]: " << rangeSum << endl;

    return 0;
}
