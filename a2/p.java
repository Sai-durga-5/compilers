import java.util.Scanner;

public class p{
    static class student{
        String name;
        int age;
        student(String n,int a){
            name=n;age=a;
        }
        void dispaly(){
            System.out.println(name+" "+age);
        }
    }
    public static float add(int a ,float b){
        return (float)a+b;
    }
    public static void main(String[] args){
        System.out.println("hello man !");
        int a=0;
        double b=3.14;
        char c='A';
        boolean flag=true;
        String name="sai";
        System.out.println(name);
        long x=56;
        Scanner sc=new Scanner(System.in);
        int x1=sc.nextInt();
        float x2=sc.nextFloat();
        System.out.println(add(x1,x2));
        student c1=new student("sai",20);
        c1.dispaly();
    }
}