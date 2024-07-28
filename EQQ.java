import java.util.ArrayList;
import java.util.Scanner;

public class EQQ {
    static class AVLNode {
        long totalValue;
        int key, height, numNodes;
        AVLNode left, right;

        public AVLNode(int key) {
            this.key = key;
            this.totalValue = key;
            this.numNodes = 1;
            this.height = 1;
            this.left = this.right = null;
        }
    }

    public static class AVLTree {
        private AVLNode root;
        private boolean isKEven;

        public AVLTree(boolean isKEven){
            this.isKEven=isKEven;
        }

        private int height(AVLNode node) {
            if (node == null)
                return 0;
            return node.height;
        }

        private int max(int a, int b) {
            if (a > b)
                return a;
            return b;
        }

        private int size(AVLNode node) {
            if (node == null)
                return 0;
            return node.numNodes;
        }

        private long sumValues(AVLNode node) {
            if (node == null)
                return 0;
            else
                return node.totalValue;
        }

        private AVLNode rotateRight(AVLNode y) {
            AVLNode x = y.left;
            AVLNode T2 = x.right;

            x.right = y;
            y.left = T2;

            updateNode(y);
            updateNode(x);

            return x;
        }

        private AVLNode rotateLeft(AVLNode x) {
            AVLNode y = x.right;
            AVLNode T2 = y.left;

            y.left = x;
            x.right = T2;

            updateNode(x);
            updateNode(y);

            return y;
        }

        private int balanceFactor(AVLNode node) {
            return height(node.left) - height(node.right);
        }

        private AVLNode balance(AVLNode node) {
            updateNode(node);

            int balance = balanceFactor(node);

            // Left Heavy
            if (balance > 1) {
                if (balanceFactor(node.left) < 0) {
                    node.left = rotateLeft(node.left);
                }
                return rotateRight(node);
            }

            // Right Heavy
            if (balance < -1) {
                if (balanceFactor(node.right) > 0) {
                    node.right = rotateRight(node.right);
                }
                return rotateLeft(node);
            }

            return node;
        }

        private void updateNode(AVLNode node) {
            if (node == null)
                return;
            node.height = 1 + max(height(node.left), height(node.right));
            node.numNodes = 1 + size(node.left) + size(node.right);
            node.totalValue = node.key + sumValues(node.left) + sumValues(node.right);
        }

        public void insert(int key) {
            root = insertNode(root, key);
        }

        private AVLNode insertNode(AVLNode root, int key) {
            if (root == null) {
                return new AVLNode(key);
            }
            root.totalValue += key;
            root.numNodes += 1;
            if (key < root.key) {
                root.left = insertNode(root.left, key);
            } else {
                root.right = insertNode(root.right, key);
            }

            return balance(root);
        }

        public void delete(int key) {
            root = deleteNode(root, key);
        }

        private AVLNode deleteNode(AVLNode root, int key) {
            if (root == null) {
                return root;
            }
            root.numNodes--;
            root.totalValue-=key;
            if (key < root.key) {
                root.left = deleteNode(root.left, key);
            } else if (key > root.key) {
                root.right = deleteNode(root.right, key);
            } else {
                if (root.left == null) {
                    return root.right;
                } else if (root.right == null) {
                    return root.left;
                }

                AVLNode temp = findMin(root.right);
                root.key = temp.key;
                root.right = deleteNode(root.right, temp.key);
            }

            return balance(root);
        }

        private AVLNode findMin(AVLNode root) {
            while (root.left != null) {
                root = root.left;
            }
            return root;
        }

        public AVLNode search(int key) {
            return searchNode(root, key);
        }

        private AVLNode searchNode(AVLNode root, int key) {
            if (root == null || root.key == key) {
                return root;
            }
            if (key < root.key)
                return searchNode(root.left, key);

            return searchNode(root.right, key);
        }

        private int getTotalNodes() {
            return this.root.numNodes;
        }

        private long getDistanceFromNode(long smallerSum, long biggerSum, AVLNode root, int remainedIndex) {
            
            AVLNode newRoot;
            if(size(root.left)==remainedIndex ){
                smallerSum+=sumValues(root.left);
                biggerSum+=sumValues(root.right);

                if(isKEven)
                    biggerSum+=root.key;

                return getDifFromMedian(smallerSum, biggerSum);
            }

            else if(size(root.left)==0)
                return getDistanceFromNode(smallerSum+root.key, biggerSum, root.right, remainedIndex-1);

            else if(size(root.right)==0)
                return getDistanceFromNode(smallerSum, biggerSum+root.key, root.left, remainedIndex);
            
            else if (size(root.left) < remainedIndex) {
                remainedIndex -= root.left.numNodes+1;
                smallerSum += sumValues(root.left)+root.key;
                newRoot = root.right;
                return getDistanceFromNode(smallerSum, biggerSum, newRoot, remainedIndex);
            }

            else {
                biggerSum+= sumValues(root.right)+root.key;
                newRoot=root.left;
                return getDistanceFromNode(smallerSum,biggerSum,newRoot,remainedIndex);
            }

        }

        private long getDifFromMedian(long smallerSum,long biggerSum){
            int temp=(int)biggerSum-(int)smallerSum;
            answers2.add(temp);
            return biggerSum-smallerSum;
        }

        public long getDistanceFromMedian() {
            return getDistanceFromNode(0, 0, this.root, getTotalNodes() / 2);
        }

    }

    public static int k, n;
    public static Scanner scanner = new Scanner(System.in);
    public static ArrayList<Integer> elements = new ArrayList<>();
    public static ArrayList<Integer> answers=new ArrayList<>();
     public static ArrayList<Integer> answers2=new ArrayList<>();
    public static AVLTree avlTree;

    public static void get_inputs() {
        n = scanner.nextInt();
        k = scanner.nextInt();

        int temp;
        for (int i = 0; i < n; i++) {
            temp = scanner.nextInt();
            elements.add(temp);
        }
    }

    public static void main(String[] args) {

        get_inputs();

        initializeTree();

        for (int i = 0; i < n-k+1; i++)
        get_answer(i);
    }

    public static void initializeTree() {
        avlTree = new AVLTree(k%2==0);
        for (int i = 0; i < k; i++) 
            avlTree.insert(elements.get(i));
    }

    public static void get_answer(int i) {
        long operations_count = avlTree.getDistanceFromMedian();
        System.out.print("" + operations_count + " ");
        edit_tree(i);
    }

    public static void edit_tree(int step) {
        if(step==n-k)
        return;
        avlTree.delete(elements.get(step));
        avlTree.insert(elements.get(step + k));
    }

}