#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cstring> 

using namespace std;

#define MAX_SIZE 100007

class explosion{
    public:
    int node;
    int size;
    int color;
    explosion (int a1, int a2, int a3): node(a1), size(a2), color(a3){}
};

class bfs_info{
    public:
    int node_number;
    int bfs_mode;
    int dist;
    bfs_info (int a0, int a1, int a2): bfs_mode(a1), dist(a2), node_number(a0){}
};


class node_state{
    public:
    int node_number;
    int highest_0_bfs;
    int highest_1_bfs;
    int color;
    node_state (int a0, int a1, int a2, int a3):
        highest_0_bfs(a1), highest_1_bfs(a2), color(a3), node_number(a0){}
};

int n,m,q;
vector <int> node_incidents[MAX_SIZE];
vector <explosion*> queries;
vector <node_state*> node_details;

void get_input(){
    cin >> n >> m;
    int a,b,c;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        node_incidents[a].push_back(b);
        node_incidents[b].push_back(a);
    }
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> a >> b >>c;
        explosion* temp=new explosion(a,b,c);
        queries.push_back(temp);
    }

    node_details.push_back(nullptr);
    for (int i = 1; i < n+1; i++)
    {
        node_details.push_back(new node_state(i,-1,-1,-1));
    }
}

void handle_query(explosion* query){
    //GOING FOR BFS if it is not useless
    queue<bfs_info*> qiu;

    // Initialize the source node and visited array
    node_state* source=node_details.at(query->node);

    if(query->size  > source->highest_0_bfs){
        bfs_info* first=new bfs_info(query->node,0,query->size);
        qiu.push(first);
    }

    // Perform BFS
    int w,num;
    bfs_info* current;
    while (!qiu.empty()) {
        current = qiu.front();
        qiu.pop();
        w=current->bfs_mode;
        num=current->node_number;

        if (!w) 
            if( node_details.at(num)->highest_0_bfs >= current->dist)
                continue;
            else{
                node_details.at(num)->highest_0_bfs=current->dist;
            }
        
        else
            if( node_details.at(num)->highest_1_bfs >= current->dist)
                continue;
            else{
                node_details.at(num)->highest_1_bfs=current->dist;
            }

        if(node_details.at(num)->color == -1 && !w)
            node_details.at(num)->color=query->color;
        w=(w+1)%2;



        for (int neighbor : node_incidents[current->node_number]) {
            bfs_info* next=new bfs_info(neighbor, w , current->dist-1);
            qiu.push(next);
        }
        
    }
}


int main(){

    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    get_input();
    for (int i = q-1; i > -1; i--)
    {
        handle_query(queries.at(i));
    }
    
    for (int i = 1; i < n+1; i++)
    {
        if(node_details.at(i)->color==-1)
            node_details.at(i)->color=0;
       cout << node_details.at(i)->color << "\n";
    }


}