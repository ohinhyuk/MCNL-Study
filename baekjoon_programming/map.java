package baekjoon_programming;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;
import java.util.Map.Entry;

import javax.naming.ldap.SortKey;


public class map {
    public static void main(String[] args) {
        TreeSet<Integer> result = new TreeSet<>();
        int A,B,C;
        Scanner sc = new Scanner(System.in);
        
        A = sc.nextInt();
        B = sc.nextInt();
        C = sc.nextInt();

        if(A >= C && B >= C){
            result.add(C);
        }
        else{
            if(A < C && B < C && A+B < C ){
                result.add(C);
                result.add(C-A);
                result.add(C-B);
                result.add(C-A-B);
                
            }
            else if(A < C && B < C){
                result.add(A);
                result.add(B);
                result.add(C);
                result.add(C-A);
                result.add(C-B);
            }
            else{
                if(A < B){
                    result.add(C);
                    result.add(A);
                    while(C-A > 0){
                        C -=A;
                        result.add(C);
                    }
                }
                else{
                    result.add(C);
                    result.add(B);
    
                    while(C-B > 0){
                        C -=B;
                        result.add(C);
                    }
                }
        }
        
        }
        
        for(Integer element : result){
            System.out.println(element);
        }

    }
}

