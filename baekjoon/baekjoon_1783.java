import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.util.StringTokenizer;

public class baekjoon_1783 {
    public static void main(String[] args) throws Exception {
        int N , M;
        int result;
        // Scanner sc = new Scanner(System.in);
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        if(N == 1){
            result = 1;
        }
        else if(N == 2){
            result = (M-1) / 2 + 1;
            if(result > 4) result = 4;
        }
        else if(M < 4){
            result = M;
        }
        else if(M < 7){
            result = 4;
        }
        else{
            result = M - 2;
        }

        System.out.println(result);
    }
}
