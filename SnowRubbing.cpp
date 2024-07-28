#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#define MAX_SIZE 510

using namespace std;

class BFS_detail{
    public:
    int distance;
    pair <int , int> parent;

    BFS_detail(int dist, pair<int, int> prnt):
        distance(dist), parent(prnt) {}
};

class enque_nodes{
    public:
        pair <int, int> coords;
        BFS_detail* bfs_detail;
        enque_nodes* next;
        enque_nodes* previous;

        enque_nodes(pair <int , int> crd, BFS_detail* bfs_det, enque_nodes* nxt, enque_nodes* prv) :
            coords(crd),  bfs_detail(bfs_det), next(nxt), previous(prv) {}
};

class enque{
    public:
    bool is_finished;
    enque_nodes* first_node;
    enque_nodes* last_node;

    enque_nodes* pop(){
        if(first_node==nullptr)
            return nullptr;

        if(!first_node->next){
            enque_nodes* temp=first_node;
            first_node=nullptr;
            last_node=nullptr;
            return temp;
        }

        first_node->next->previous=nullptr;
        enque_nodes* old_first=first_node;
        first_node=old_first->next;
        return old_first;
    }

    void insert(enque_nodes* node){
        if(first_node==nullptr){
            first_node=node;
            last_node=node;
            return;
        }
            
        first_node->previous=node;
        node->next=first_node;
        first_node=node;
    }

    void push(enque_nodes* node){
        if(first_node==nullptr){
            first_node=node;
            last_node=node;
            return;
        }

        last_node->next=node;
        node->previous=last_node;
        last_node=node;
    }

    enque(enque_nodes* starting_node){
        is_finished=false;
        first_node=starting_node;
        last_node=starting_node;
    }

    void empty(){
        first_node=nullptr;
        last_node=nullptr;
    }
};

int n,m;
char map[MAX_SIZE][MAX_SIZE];
bool visits[MAX_SIZE][MAX_SIZE][3];
int best_distance=0;
vector <BFS_detail*> bfs_details[MAX_SIZE][MAX_SIZE];
int special_spots[3][2]; //jacks house , grandma and grandpa
vector <pair<int,int>> neighbors[4];


void read_map(){
cin >> n >> m;
getchar();
char c;
for (int i = 0; i < n; i++)
    for (int j= 0; j < m; j++)
    {

        for (int k = 0; k < 3; k++)
            visits[i][j][k]=false;
        
        cin >>c;
        map[i][j]=c;
        if(c=='A'){
            special_spots[0][1]=j;
            special_spots[0][0]=i;
        }
        if(c=='B'){
            special_spots[1][1]=j;
            special_spots[1][0]=i;
        }
        if(c=='C'){
            special_spots[2][1]=j;
            special_spots[2][0]=i;
        }
    }
    getchar();
}

bool is_visited(int x, int y, int step){
    return visits[x][y][step-1];
}

void set_viable_neighbors(pair <int , int> location, int visit_step){
    int x=location.first, y=location.second;
    pair<int,int> temp;
    if(x-1>-1)
        if(!is_visited(x-1,y,visit_step) && map[x-1][y] !='#'){
            temp.first=x-1;
            temp.second=y;
            neighbors->push_back(temp);
        }
    
    if(x+1<n)
        if(!is_visited(x+1,y,visit_step) && map[x+1][y] !='#'){
            temp.first=x+1;
            temp.second=y;
            neighbors->push_back(temp);
        }

    if(y+1<m)
        if(!is_visited(x,y+1,visit_step) && map[x][y+1] !='#'){
            temp.first=x;
            temp.second=y+1;
            neighbors->push_back(temp);
        }

    if(y-1>-1)
        if(!is_visited(x,y-1,visit_step) && map[x][y-1] !='#'){
            temp.first=x;
            temp.second=y-1;
            neighbors->push_back(temp);
        }
}

bool is_node_special(int x, int y){
    return( x==special_spots[1][0]&&y==special_spots[1][1] || 
        x==special_spots[2][0]&&y==special_spots[2][1]) ? true : false;

}

int get_total_distance(int x, int y){
    vector <BFS_detail*> node_details=bfs_details[x][y];
    if(node_details.size()!=3 || is_node_special(x,y))
        return -1;

    int ans= node_details.at(0)->distance+node_details.at(1)->distance+node_details.at(2)->distance;
    if(map[x][y] == '*')
        ans-=2;
    return ans;
}

pair<int, int> get_best_node(){
    pair <int , int> best_node;
    best_node.first=-1;
    best_node.second=-1;

    int minimum_total_dist=1000000000, temp_dist;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            temp_dist=get_total_distance(i,j);
            if(temp_dist==-1)
                continue;
            if(temp_dist<minimum_total_dist){
                minimum_total_dist=temp_dist;
                best_node.first=i;
                best_node.second=j;
            }
        }
    
    return best_node;
}

void BFS(enque_nodes* current_node, enque* enque, int start_mode){
    
    int x=current_node->coords.first, y=current_node->coords.second,
    node_distance=current_node->bfs_detail->distance;

    if(is_visited(x,y,start_mode)){
        enque_nodes* next=enque->pop();
        if(next==nullptr)
            return ;
        BFS(next,enque,start_mode);
        return;
    }
    
    bfs_details[x][y].push_back(current_node->bfs_detail);
    visits[x][y][start_mode-1]=true;

    pair <int , int> tempcrd;
    set_viable_neighbors(current_node->coords,start_mode);
    for (int i = 0; i < neighbors->size(); i++)
    {
        tempcrd=neighbors->at(i);
        BFS_detail* next_detail=new BFS_detail(node_distance,current_node->coords);

        if(map[tempcrd.first][tempcrd.second] == '.' || map[tempcrd.first][tempcrd.second] == 'A'){
            enque->insert(new enque_nodes(tempcrd, next_detail,nullptr,nullptr));
        }
        else {
            if(map[tempcrd.first][tempcrd.second] != '*')
                continue;
            
            
            next_detail->distance++;
            enque->push(new enque_nodes(tempcrd, next_detail,nullptr,nullptr));
        }
    }
    
    neighbors->clear();
    enque_nodes* next=enque->pop();
    if(next==nullptr)
        return ;
    BFS(next,enque,start_mode);
}

void start_bfs(){

    pair <int, int> jack;
    jack.first=special_spots[0][0], jack.second=special_spots[0][1];
    BFS_detail* jack_house_detail=new BFS_detail(0,jack);
    enque_nodes* jack_house_node=new enque_nodes(jack, jack_house_detail, nullptr, nullptr);
    enque* jack_enque=new enque(jack_house_node);
    jack_enque->pop();
    BFS(jack_house_node,jack_enque,1);

    pair <int, int> grandma;
    grandma.first=special_spots[1][0], grandma.second=special_spots[1][1];
    BFS_detail* grandma_house_detail=new BFS_detail(0,grandma);
    enque_nodes* grandma_house_node=new enque_nodes(grandma, grandma_house_detail, nullptr, nullptr);
    enque* grandma_enque=new enque(grandma_house_node);
    grandma_enque->pop();
    BFS(grandma_house_node,grandma_enque,2);

    pair <int, int> grandpa;
    grandpa.first=special_spots[2][0], grandpa.second=special_spots[2][1];
    BFS_detail* grandpa_house_detail=new BFS_detail(0,grandpa);
    enque_nodes* grandpa_house_node=new enque_nodes(grandpa, grandpa_house_detail, nullptr, nullptr);
    enque* grandpa_enque=new enque(grandpa_house_node);
    grandpa_enque->pop();
    BFS(grandpa_house_node,grandpa_enque,3);
}

bool are_coords_equal(pair <int, int> crd1 , pair <int, int> crd2){
    return(crd1.first==crd2.first && crd1.second==crd2.second) ? true : false;
}

void modify_optimal_map(pair<int, int> best_node_coords,int step_zb, pair<int, int> start_loc){
    pair <int , int> parentcrd; 
    pair <int,int> nodecrd;
    nodecrd=best_node_coords;
    parentcrd=bfs_details[nodecrd.first][nodecrd.second].at(step_zb)->parent;
    while (true)
    {
        if(map[nodecrd.first][nodecrd.second] == '*'){
            map[nodecrd.first][nodecrd.second]='o';
            best_distance++;
        }
        if(are_coords_equal(start_loc,parentcrd))
            break;
        nodecrd=parentcrd;
        parentcrd=bfs_details[nodecrd.first][nodecrd.second].at(step_zb)->parent;
    }
}

void print_output(int distance){

    cout << distance << "\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << map[i][j];
        }
        cout <<"\n";
    }
}

int main(){

    read_map();

    //run bfs 3 times:
    start_bfs();

    pair<int, int> best_node=get_best_node();
    if(best_node.first==-1){
        cout << "CHRISTMAS RUINED!";
        return -1;
    }

    pair<int , int> start_loc;

    start_loc.first=special_spots[0][0];
    start_loc.second=special_spots[0][1];
    modify_optimal_map(best_node,0,start_loc);


    start_loc.first=special_spots[1][0];
    start_loc.second=special_spots[1][1];
    modify_optimal_map(best_node,1,start_loc);

    start_loc.first=special_spots[2][0];
    start_loc.second=special_spots[2][1];
    modify_optimal_map(best_node,2,start_loc);

    print_output(best_distance);
}
