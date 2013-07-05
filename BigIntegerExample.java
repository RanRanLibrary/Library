import java.math.BigInteger;
import java.util.Scanner;

class Main{ //submitするときはMainにしとかないとエラー出るかもしれない。それ以外はファイル名と統一
        public static void main(String[] args){
                BigInteger[] a=new BigInteger[1004];
                int i,j;

                a[0]=a[1]=BigInteger.ONE; //1で初期化
                a[1]=BigInteger.ZERO; //0で初期化
                a[1]=BigInteger.TEN; //10で初期化
                a[1]=new BigInteger("1234");//任意の数字で初期化するときは文字列で渡す
                a[0]=a[0].add(a[1]); //+
                a[0]=a[0].subtract(a[1]); //-
                a[0]=a[0].multiply(a[1]); //掛け算
                a[0]=a[0].divide(a[1]); //割り算
                a[0]=a[0].remainder(a[1]);//%
                
                a[1]=a[1].add( BigInteger.valueOf(3) ); //引数はBigInteger型である必要があるためこうする

                

                Scanner s=new Scanner(System.in);
                while(s.hasNextInt()){
                        int n=s.nextInt(); //次の整数、Doubleもあるよ
                        String str=s.nextLine(); //改行まで読み込む、改行文字は捨てられる
                        System.out.println("入力値+2は"+(n+2)); //末尾に改行を自動で挿入
                        System.out.print("こっちは改行挿入されない");
                }

        }

}
