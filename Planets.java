import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class Planets{


    public static int n;
    
    public static Integer[][] planetsData;
    public static Integer[][] planetsXSorted;
    public static double fastestCollision=-1;
    public static Scanner scanner=new Scanner(System.in);
    public static void main(String[] args) {
        
        readInputPlanets();

        //momkene bug bendaze
        planetsXSorted=sortPlanetsByXCoordinate(0,n);

        getFatestCollision();

        getAnswer();

    }

    public static void getAnswer(){
         DecimalFormat df = new DecimalFormat("#.00");
        if(fastestCollision==-1) System.out.println("Collision-Free System");
        else  System.out.print(df.format(fastestCollision));
    }

    public static void readInputPlanets(){

        n=scanner.nextInt();
        planetsData= new Integer[n][3];

        for (int i = 0; i < n; i++) {
            planetsData[i][0]=scanner.nextInt();
            planetsData[i][1]=scanner.nextInt();
            planetsData[i][2]=scanner.nextInt();
        }
    }

    public static Integer[][] sortPlanetsByXCoordinate(int lowerBound, int UpperBound){

        Arrays.sort(planetsData, new Comparator<Integer[]>() {
            @Override
            public int compare(final Integer[] entry1, final Integer[] entry2) {
                final Integer time1 = entry1[2];
                final Integer time2 = entry2[2];
                return time1.compareTo(time2);
            }
        });

        return planetsData;
    }

    public static void getFatestCollision(){

        double temp;
        for (int i = 0; i < n-1; i++) {
            temp=getPlanetsFastestCollision(i);
            if(temp>-1) {
                if(fastestCollision==-1) fastestCollision=temp;
                else if(fastestCollision>temp) fastestCollision=temp;
            };
        }
    }

    public static double getPlanetsFastestCollision(int planetNumber){
        double temp,min=-1;
        for (int i = 1; i < 1000; i++) {
            temp=doesPlanetsCollide(planetNumber, planetNumber+i);
            if(temp==0)
                return 0;
            if(temp==-1) continue;
            temp=getCollisionTime(planetNumber, planetNumber+i);
            if(min==-1) min=temp;
            else if(temp<min) min=temp;
        }
        return min;
    }

    public static int doesPlanetsCollide(int firstPlanet,int secondPlanet){
        if(secondPlanet>n-1) 
            return -1;

        
        if(getCollisionDistance(firstPlanet,secondPlanet)>=getStartingDistance(firstPlanet, secondPlanet))
            return 0;
        
        if(getRelativeVelocity(firstPlanet, secondPlanet)<=0)
            return -1;

        return 1;
    }

    public static int getRelativeVelocity(int firstPlanet, int secondPlanet){
        return planetsXSorted[firstPlanet][1]-planetsXSorted[secondPlanet][1];
    }

    public static double getCollisionDistance(int firstPlanet, int secondPlanet){

        double DistanceY=planetsXSorted[secondPlanet][0]-planetsXSorted[firstPlanet][0];

        double totalCollisionDistance=planetsXSorted[firstPlanet][0]+planetsXSorted[secondPlanet][0];
        return Math.sqrt(totalCollisionDistance*totalCollisionDistance
                                            -DistanceY*DistanceY);
    }

    public static double getStartingDistance(int firstPlanet, int secondPlanet){
         double DistanceY=planetsXSorted[secondPlanet][0]-planetsXSorted[firstPlanet][0];
         double DistanceX=planetsXSorted[secondPlanet][2]-planetsXSorted[firstPlanet][2];     

         return Math.sqrt(DistanceX*DistanceX+DistanceY*DistanceY);
    }

    public static double getCollisionTime(int firstPlanet, int secondPlanet){

        double DistanceX=planetsXSorted[secondPlanet][2]-planetsXSorted[firstPlanet][2];        
        double CollisionDistanceX=getCollisionDistance(firstPlanet, secondPlanet);
        
        double effectiveTravelX=DistanceX-CollisionDistanceX;

        return effectiveTravelX/getRelativeVelocity(firstPlanet, secondPlanet);
    }

}