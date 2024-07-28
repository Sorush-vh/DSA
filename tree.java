import java.util.ArrayList;
import java.util.Scanner;

public class tree{

    public static Scanner scanner= new Scanner(System.in);
    public static int n,q;
    public static ArrayList<Integer> treeIncidents[];
    public static int[] nodesRankInBranch;
    public static int[] nodesLowerBound;
    public static int[] nodesUpperBound;
    public static int highestBranchNumber=1;
    // public static ArrayList<Integer> incidentQuestions[];

    public static void main(String[] args) {
        
        getSartingData();
                
        sortTreeByParentalRelation();

        answerQuestions();
    }

    public static void getSartingData(){

        n=scanner.nextInt();
        q=scanner.nextInt();
        treeIncidents= (ArrayList<Integer>[]) new ArrayList[n+1];

        for (int i = 0; i < n-1; i++) 
            storeIncidentData();

    }

    private static void storeIncidentData(){
        int a,b;
        a=scanner.nextInt(); b=scanner.nextInt();

        if(treeIncidents[a] != null) treeIncidents[a].add(b);
        else{
            treeIncidents[a]= new ArrayList<Integer>();
            treeIncidents[a].add(b);
        }

        if(treeIncidents[b] != null) treeIncidents[b].add(a);
        else{
            treeIncidents[b]= new ArrayList<Integer>();
            treeIncidents[b].add(a);
        }
    }

    public static void sortTreeByParentalRelation(){
        nodesRankInBranch=new int[n+1];
        nodesLowerBound=new int[n+1];
        nodesUpperBound=new int[n+1];

        nodesRankInBranch[1]=0;
        nodesLowerBound[1]=1;
        setAllVerticesBranchAndRank(1,0);
    }

    private static void setAllVerticesBranchAndRank(int vertic,int parent){

        int recursionOccurence=0;

        for (Integer child : treeIncidents[vertic]){

            if(child==parent) continue;

            if(recursionOccurence==1) highestBranchNumber++;
            
            nodesRankInBranch[child]=nodesRankInBranch[vertic]+1;
            nodesLowerBound[child]=highestBranchNumber;

            setAllVerticesBranchAndRank(child, vertic);

            recursionOccurence=1;
        }

        nodesUpperBound[vertic]=highestBranchNumber;            
    }

    private static boolean isVerticAParent(int vertic,int targetChild){
        
        if(vertic==targetChild) return true;

        return isTargetsBranchUnderVertic(vertic, targetChild);
    }

    private static boolean isTargetsBranchUnderVertic(int vertic, int targetChild){

        if(nodesRankInBranch[vertic] >= nodesRankInBranch[targetChild]) return false;

        if(nodesLowerBound[vertic] > nodesLowerBound[targetChild]) return false;

        if(nodesUpperBound[vertic] < nodesUpperBound[targetChild]) return false;

        return true;
    }

    public static void answerQuestions(){

        int a,b;

        for (int i = 0; i < q; i++) {

          a=scanner.nextInt(); b=scanner.nextInt();

          if(isVerticAParent(a, b)) System.out.println("YES");
          else System.out.println("NO");
        }
    }

}