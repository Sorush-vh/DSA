#include <iostream>
#include <vector> 
using namespace std;

#define MAX_SIZE 1000001

    int n,q;
    vector <int> treeIncidents[MAX_SIZE];
    int nodesRankInBranch[MAX_SIZE];
    int nodesLowerBound[MAX_SIZE];
    int nodesUpperBound[MAX_SIZE];
    int highestBranchNumber=1;
    void setAllVerticesBranchAndRank(int vertic,int parent);
    void sortTreeByParentalRelation();
    void getSartingData();
    void storeIncidentData();
    void answerQuestions();
    bool isTargetsBranchUnderVertic(int vertic, int targetChild);


    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        getSartingData();
                
        sortTreeByParentalRelation();

        answerQuestions();
    }

    void sortTreeByParentalRelation(){

        nodesRankInBranch[1]=0;
        nodesLowerBound[1]=1;
        setAllVerticesBranchAndRank(1,0);
    
    }

    void getSartingData(){

        cin >> n >> q;
        //in next int nist lozomanaaa
        for (int i = 0; i < n-1; i++) 
            storeIncidentData();

    }

    void storeIncidentData(){
        int a,b;
        cin >> a >> b;

        treeIncidents[a].push_back(b);

        treeIncidents[b].push_back(a);
    }

    void setAllVerticesBranchAndRank(int vertic,int parent){

        int recursionOccurence=0;

        for (int child : treeIncidents[vertic]){

            if(child==parent) continue;

            if(recursionOccurence==1) highestBranchNumber++;
            
            nodesRankInBranch[child]=nodesRankInBranch[vertic]+1;
            nodesLowerBound[child]=highestBranchNumber;

            setAllVerticesBranchAndRank(child, vertic);

            recursionOccurence=1;
        }

        nodesUpperBound[vertic]=highestBranchNumber;            
    }

    bool isVerticAParent(int vertic,int targetChild){
        
        if(vertic==targetChild) return true;

        return isTargetsBranchUnderVertic(vertic, targetChild);
    }

    bool isTargetsBranchUnderVertic(int vertic, int targetChild){

        if(nodesRankInBranch[vertic] >= nodesRankInBranch[targetChild]) return false;

        if(nodesLowerBound[vertic] > nodesLowerBound[targetChild]) return false;

        if(nodesUpperBound[vertic] < nodesUpperBound[targetChild]) return false;

        return true;
    }

    void answerQuestions(){

        int a,b;

        for (int i = 0; i < q; i++) {

          cin >> a >>b;

          if(isVerticAParent(a, b)) 
            cout<< "YES\n";
          else 
            cout << "NO\n";
        }
    }