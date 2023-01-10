package baekjoon_programming;

import java.util.Scanner;

public class baekjoon_2720{
public static void main(String[] argv){



Scanner sc = new Scanner(System.in);
int T = sc.nextInt();
int C;

for(int i = 0 ; i < T;++i){
    C = sc.nextInt();
    int q = 0,d = 0,n = 0,p = 0;
    while(C > 0){
        if(C >= 25){
            q++;
            C -=25;
        }
        else if(C >= 10){
            d++;
            C-=10;
        }
        else if(C >= 5){
            n++;
            C -= 5;
        }
        else if(C >= 1){
            p++;
            C-=1;
        }
    }

    System.out.println(q + " " + d + " " + n + " " + p);
}
}
}