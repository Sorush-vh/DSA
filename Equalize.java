import java.util.ArrayList;
import java.util.Scanner;

public class Equalize{

public static int MAX_SIZE=200009;

static class Node{
    public boolean isInHeapMax;
    final int value;
    int index;

    public Node(int value){
        this.value=value;
    }
}

static class Heap{
    
        private boolean is_heap_max;
        private long heap_sum=0;
        private ArrayList <Node> nodes=new ArrayList<>();
        private int nodeCount;
        
        public Heap(boolean heap_type){
            this.is_heap_max=heap_type;
            this.heap_sum=0;
            this.nodeCount=0;
        }

        public long get_sum(){
            return this.heap_sum;
        }

        public int getParentIndex(int childIndex){
            return (int)Math.ceil((double)childIndex/2)-1;
        }

        public int getParentValue(int childIndex){
            return nodes.get(getParentIndex(childIndex)).value;
        }

        public boolean doesChildExist(int parentIndex, int childNumber){
            if(nodeCount>parentIndex*2+childNumber)
                return true;
            return false;
        }

        public int getChildIndex(int parentIndex, int childNumber){
            return 2*parentIndex+childNumber;
        }

        public int getChildValue(int parentIndex, int childNumber){
            if(!doesChildExist(parentIndex, childNumber))
                return -1;
            return nodes.get(getChildIndex(parentIndex, childNumber)).value;
        }
        
        public Node get_root(){
            if(nodes.size()==0)
                return null;
            return nodes.get(0);
        }

        public int getNodeCount(){
            return nodeCount;
        }

        //BASED ON FIRST NODE ARGUMENT
        public boolean isNodeBigger(int nodeIndex, int comparatorIndex){
            if(getNodeVal(nodeIndex)>getNodeVal(comparatorIndex))
                return true;
            
            return false;
        }

        public int getBiggerChildIndex(int parentIndex){
            int firstInd=getChildIndex(parentIndex, 1);
            int secondInd=getChildIndex(parentIndex, 2);
            int firstVal=getChildValue(parentIndex, 1);
            int secondVal=getChildValue(parentIndex, 2);

            if(firstVal==-1 &&secondVal==-1)
                return -1;
            if(secondVal==-1)
                return firstInd;
            if(secondVal>firstVal)
                return secondInd;
            else return firstInd;
        }

        public int getSmallerChildIndex(int parentIndex){
            int firstInd=getChildIndex(parentIndex, 1);
            int secondInd=getChildIndex(parentIndex, 2);
            int firstVal=getChildValue(parentIndex, 1);
            int secondVal=getChildValue(parentIndex, 2);

            if(firstVal==-1 &&secondVal==-1)
                return -1;
            if(secondVal==-1)
                return firstInd;
            if(secondVal<firstVal)
                return secondInd;
            else return firstInd;
        }

        public int getNodeVal(int index){
            return nodes.get(index).value;
        }

        public Node getNode(int index){
            return nodes.get(index);
        }

        void add_node_to_heap(Node node){
            int value=node.value;
            nodes.add(node);
            node.isInHeapMax=this.is_heap_max;
            node.index=nodeCount;
            nodeCount++;
            move_object_up_heap(node);
            heap_sum+=value;
        }

        void swap(int nodeIndex1,int nodeIndex2){
            //HAM ARRAYLIST TARTIBESH DOROSTE,, HAM NODE HA INDEXASHOON DOROSTE
            Node Node1=getNode(nodeIndex1);
            Node Node2=getNode(nodeIndex2);
            int tempIndex=Node1.index;
            Node1.index=Node2.index;
            Node2.index=tempIndex;
            nodes.set(nodeIndex1, Node2);
            nodes.set(nodeIndex2, Node1);
        }

        void move_object_up_heap(Node node){
            
            int parentIndex,nodeIndex;
            while (true)
            {
                parentIndex=getParentIndex(node.index);
                nodeIndex=node.index;
                if(parentIndex==-1)
                    return;

               
                if(isNodeBigger(node.index, parentIndex)&& is_heap_max ||
                    !isNodeBigger(node.index, parentIndex) && !is_heap_max){

                    swap(nodeIndex, parentIndex);
                }
                else return;
            }
        }

    void remove_from_heap(Node node){

            int value=node.value;
            int checkNodeIndex=node.index,swappingChild;

            while (true)
            {
                if(is_heap_max)
                    swappingChild=getBiggerChildIndex(checkNodeIndex);
                else
                    swappingChild=getSmallerChildIndex(checkNodeIndex);

                if(swappingChild==-1)
                    break; 
                
                swap(checkNodeIndex, swappingChild);
                checkNodeIndex=swappingChild;
            }
            nodeCount--;
            
            swap(checkNodeIndex, nodeCount);
            nodes.remove(nodeCount);
            if(checkNodeIndex<nodeCount)
                move_object_up_heap(getNode(checkNodeIndex));
            heap_sum-=value;
        }
}

public static int n,k;
public static ArrayList <Integer> elements=new ArrayList<>();
public static ArrayList <Node> nodes=new ArrayList<>();
public static Heap max_heap;
public static Heap min_heap;
public static Scanner scanner=new Scanner(System.in);

public static void get_inputs(){
    n=scanner.nextInt();
    k=scanner.nextInt();

    int temp;
    for (int i = 0; i < n; i++)
    {
        temp=scanner.nextInt();
        elements.add(temp);
        nodes.add(new Node(temp));
    }
}

public static  Node[] get_first_sorted_nodes(){

    Node[] sorted_nodes= new Node[k];
        for (int i = 0; i<k; i++) 
           sorted_nodes[i]=nodes.get(i);

    mergeSort(sorted_nodes);
    return sorted_nodes;
}

public static void mergeSort(Node[] array) {
    if (array == null || array.length <= 1) {
        return;
    }

    int mid = array.length / 2;
    Node[] leftArray = new Node[mid];
    Node[] rightArray = new Node[array.length - mid];

    System.arraycopy(array, 0, leftArray, 0, mid);

    if (array.length - mid >= 0)
        System.arraycopy(array, mid, rightArray,
                          0, array.length - mid);

    mergeSort(leftArray);
    mergeSort(rightArray);
    merge(leftArray, rightArray, array);
}

private static void merge(Node[] leftArray,
                          Node[] rightArray, Node[] array) {
    int i = 0, j = 0, k = 0;
    while (i < leftArray.length && j < rightArray.length) {
        if (leftArray[i].value <= rightArray[j].value) {
            array[k++] = leftArray[i++];
        } else {
            array[k++] = rightArray[j++];
        }
    }
    while (i < leftArray.length) {
        array[k++] = leftArray[i++];
    }
    while (j < rightArray.length) {
        array[k++] = rightArray[j++];
    }
}

public static void initialize_hips(){

    Node[] first_sorteds=get_first_sorted_nodes();
    max_heap=new Heap(true);
    min_heap=new Heap(false);
    for (int i = 0; i < k/2; i++)
        max_heap.add_node_to_heap(first_sorteds[i]);
    
    for (int i = k/2; i < k; i++)
        min_heap.add_node_to_heap(first_sorteds[i]);
}

public static void edit_heaps(int step){
    //END CHECK
    if(step==n-k)
        return;
    
        //ADD
    Node incoming_node=nodes.get(k+step);
    if (incoming_node.value <= max_heap.get_root().value)
        max_heap.add_node_to_heap(incoming_node);
    else
        min_heap.add_node_to_heap(incoming_node);

        //REMOVE
    Node removal_node=nodes.get(step);
    if(removal_node.isInHeapMax)
        max_heap.remove_from_heap(removal_node);
    else 
        min_heap.remove_from_heap(removal_node);
    
        //BALANCE THE HEAPS
    Node balancing_node;
    if(max_heap.getNodeCount()==k/2+1){
        balancing_node=max_heap.get_root();
        max_heap.remove_from_heap(balancing_node);
        min_heap.add_node_to_heap(balancing_node);
    }
    else if(max_heap.getNodeCount()==k/2-1){
        balancing_node=min_heap.get_root();
        min_heap.remove_from_heap(balancing_node);
        max_heap.add_node_to_heap(balancing_node);
    }
}

public static void get_answer(int i){
    //az i ta i+k-1
    long operations_count;

    operations_count= -max_heap.get_sum() + min_heap.get_sum();
    if(k%2==1)
        operations_count-=min_heap.get_root().value;

    System.out.print(""+operations_count+" ");
    edit_heaps(i);
}

public static void main(String args[]){
    
    get_inputs();

    initialize_hips();
    for (int i = 0; i < n-k+1; i++)
        get_answer(i);
    
    
}
}