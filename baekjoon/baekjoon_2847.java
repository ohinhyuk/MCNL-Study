
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class baekjoon_2847{
    public static void main(String[] args) throws Exception {
        int N;
        int result = 0;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        N = Integer.parseInt(br.readLine());
        int[] arr = new int [N];
        for(int i = 0 ; i < N ; ++i){
            arr[i] = Integer.parseInt(br.readLine());
        }

        for(int i = N-1 ; i > 0 ; --i){
            if(arr[i] <= arr[i-1]){
                result += (arr[i-1] - arr[i] + 1);
                arr[i-1] = arr[i] - 1;
            }
        }

        System.out.println(result);
    }
}