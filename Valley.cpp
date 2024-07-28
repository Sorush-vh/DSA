#include <iostream>
#include <vector> 
using namespace std;

#define MAX_NUMBER 1000000007

vector <int> inputs;
int n;
long total_5_tuples=0;

void read_inputs(){

    cin >> n;
    inputs.reserve(n+1);
    int temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        inputs.push_back(temp);
    }
}

void initialize_inner_arrays(vector<int>& full_array,vector<int>& xv,vector<int>& yv,
                             vector<int>& zv,vector<int>& wv,vector<int>& tv){
    int size=full_array.size();
    xv.reserve(4+size/5);
    yv.reserve(4+size/5);
    zv.reserve(4+size/5);
    wv.reserve(4+size/5);
    tv.reserve(4+size/5);

    for (int i = 0; i < size/5; i++)
        xv.push_back(full_array.at(i));

    for (int i = size/5; i< 2*size/5 ; i++)
        yv.push_back(full_array.at(i));

    for (int i = 2*size/5; i < 3*size/5; i++)
        zv.push_back(full_array.at(i));
    
    for (int i = 3*size/5; i < 4*size/5; i++)
        wv.push_back(full_array.at(i));
     
    for (int i = 4*size/5; i < 5*size/5; i++)
        tv.push_back(full_array.at(i)); 
}

void copy(vector <int>& v1, vector <int>& v2source){
    v1.clear();
    v1.reserve(v2source.size());
    for (int i = 0; i < v2source.size(); i++)
        v1.push_back(v2source.at(i));
}

int get_emplacemed_pairs( vector <int>& v1, vector <int>& v2){

    int k1=0,k2=0,size1=v1.size(),size2=v2.size();
    int total_size=size1+size2,pairCount=0;

    for (int i = 0; i < total_size; i++)
        if(k2==size2 || k1==size1)
            return pairCount;
        else if(v1.at(k1)<v2.at(k2)){
            pairCount+=size2-k2;
            k1++;
        }
        else
            k2++;
    
    return pairCount;
    //each passed k1 element has its thing completely settled and those 
    //that are not passed are yet to affect the count
}

int get_val(vector <int>& vec, int index){
    if(vec.size()==index)
        return -1;
    return vec.at(index);
}

int get_min(int a1 ,int a2 ,int a3 ,int a4 ,int a5){
    int min=a1;
    if(a2<min||min==-1)
        min=a2;
    if(a3<min||min==-1)
        min=a3;
    if(a4<min||min==-1)
        min=a4;
    if(a5<min||min==-1)
        min=a5;
    return min;
}

//ALSO UPDATES TUPLE COUNT WITH INSIDE TOUPLES;
vector <int> get_sorted_array(vector <int>& full_array){
    int size=full_array.size();

    if(size<5){
        //just bubble sort it and give it back:
        int temp;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size-1; j++)
                if(full_array.at(j+1)<full_array.at(j)){
                    temp=full_array.at(j);
                    full_array.at(j)=full_array.at(j+1);
                    full_array.at(j+1)=temp;
                } 
        return full_array;
    }

    vector <int> xv,yv,zv,wv,tv;
    initialize_inner_arrays(full_array,xv,yv,zv,wv,tv);
 


    get_sorted_array(xv);
    get_sorted_array(yv);
    get_sorted_array(zv);
    get_sorted_array(wv);
    get_sorted_array(tv);

    vector <int> temp;
    //FROM NOW ON:
    //WE SHOULD TREAT X,Y IN REVERSE TO USE imp instead of disp
    copy(temp,xv);
    copy(xv,yv);
    copy(yv,temp);
    
    int emp_count_1=get_emplacemed_pairs(xv,yv);
    int emp_count_2=get_emplacemed_pairs(wv,tv);

    int ax,ay,az,aw,at,min;
    int kx=0,ky=0,kz=0,kw=0,kt=0;
    int size1=xv.size(),size2=yv.size(),size3=zv.size(),size4=wv.size(),size5=tv.size();
    for (int i = 0; i < size; i++)
    {
        //CHECK FOR END: har kodom beresan be tah, tamome va faqat sortesho bede
        ax=get_val(xv,kx);ay=get_val(yv,ky);az=get_val(zv,kz);aw=get_val(wv,kw);at=get_val(tv,kt);
        min=get_min(ax,ay,aw,az,at);
        full_array.at(i)=min;

        if(min==ax){
            emp_count_1-=size2-ky;
            kx++;
        }
        else if(min==ay)
            ky++;
        else if(min==at)
            kt++;
        else if(min==aw){
            emp_count_2-=size5-kt;
            kw++;
        }   else{
            //TIME TO ADD TO 5TUPLE COUNTS
            long int temp1=(size2-ky)*(size1-kx)-emp_count_1;
            long int temp2=(size4-kw)*(size5-kt)-emp_count_2;
            long int mode=temp1*temp2%MAX_NUMBER;
            total_5_tuples=(mode+total_5_tuples)%MAX_NUMBER;
            kz++;
        }
    }
    
    return full_array;
}


int main(){

    read_inputs();

    get_sorted_array(inputs);

    cout << total_5_tuples;

    return 0;
}