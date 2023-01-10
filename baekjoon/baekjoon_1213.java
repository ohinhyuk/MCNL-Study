package baekjoon_programming;

import java.util.Scanner;
import java.util.Stack;
import java.util.TreeMap;
import java.util.Map.Entry;

import javax.swing.text.html.parser.Entity;

public class baekjoon_1213{
    public static void main(String[] args) {
        TreeMap<Character, Integer> map = new TreeMap<Character,Integer>();
        Stack<Character> stack = new Stack<>();

        Scanner sc = new Scanner(System.in);

        String text = sc.nextLine();
        String result = "";

        for(int i = 0 ; i < text.length() ; ++i){
            char key = text.charAt(i);
            if(map.containsKey(key) == true) map.replace(key, map.get(key)+1);
            else map.put(key,1);
        }
        if(text.length() % 2 == 0){
            for(Entry< Character, Integer> entry : map.entrySet()){
                if(entry.getValue() % 2 == 1){
                    System.out.println("I'm Sorry Hansoo");
                    System.exit(0);
                }
                
                for(int i = 0 ; i < entry.getValue()/2 ; ++i){
                    stack.push(entry.getKey());
                    result+=entry.getKey();
                } 
            }
        }
        else{
            char first=' ';
            int cnt = 0 ;
            for(Entry<Character,Integer> entry : map.entrySet()){
                if(entry.getValue() % 2 == 1){
                    if(cnt == 1){
                        System.out.println("I'm Sorry Hansoo");
                        System.exit(0);
                    }
                    first = entry.getKey();
                    cnt++;
                }

                for(int i = 0 ; i < entry.getValue()/2 ; ++i){
                    stack.push(entry.getKey());
                    result+=entry.getKey();
                }
            }
            result += first;
        }

        // for(int i = 0 ; i < stack.size() ; ++i) result += stack.pop();
        
        while(!stack.empty()){
            result += stack.pop();
        }

        System.out.println(result);
    }
}