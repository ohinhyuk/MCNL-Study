const fs = require("fs");
const { exit } = require("process");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
const input = fs.readFileSync(filePath).toString().split("\n");
const N = Number(input[0].split(" ")[0]);
const M = Number(input[0].split(" ")[1]);

let inputArr = new Array(N);
let outputArr = new Array(N);

let minCnt = 0;



// function


const BFS = (arr) => {
    let cnt = 0;
    // console.log(i,j);
    
    // if(i === N-2){
        
    //     for(let row = 0 ; row < M ; ++row){
    //         if(JSON.stringify(arr[row]) !== JSON.stringify(outputArr[row])){
    //             console.log("debug");
                
    //         }
    //     }
    //     return Math.min(cnt, minCnt);
    // }
        
    // if(j === M-3){
    //     BFS(arr , cnt , i+1, 0);
    //     // convert 필요
    //     convert(arr,i,j);
    //     BFS(arr,cnt+1 , i+1,0); 
    // } 
    // else{
    //     BFS(arr , cnt , i , j+1);
    //     // convert 필요.
    //     convert(arr,i,j);
    //     console.log("B");
    //     BFS(arr, cnt+1, i,j+1 );
    // }


    
    for(let i = 0 ; i < N-2 ; ++i){
        for(let j = 0 ; j < M-2; ++j){
            if(outputArr[i][j] !== arr[i][j]){
                cnt++;
                
                convert(arr,i,j);
                
            }
        }
    }
    

    
    for(let row = 0 ; row < M ; ++row){
        if(JSON.stringify(arr[row]) !== JSON.stringify(outputArr[row])){
            cnt = -1;   
        }
    }
    
    console.log(cnt);
    
}

const convert = (arr , i , j) => {

    for(let a = i ; a < i+3 ; ++a){
        for(let b = j ; b < j+3 ; ++b){
            if(arr[a][b] === '0'){
                arr[a][b] ='1';
            } 
            else if(arr[a][b] === '1') arr[a][b] ='0';
        }
    }
    
}


const check = (a , b) => {
    for(let row = 0 ; row < M ; ++row){
        if(JSON.stringify(a[row]) !== JSON.stringify(b[row])){
            return false;
        }
    }
    return true;
}

for( let i = 0 ; i < inputArr.length ; ++i){
    inputArr[i] = new Array(M);
    outputArr[i] = new Array(M);
}

for(let i = 0 ; i < N ; ++i){
    for(let j = 0 ; j < M ; ++j){
        inputArr[i][j] = input[i+1][j];
        outputArr[i][j] = input[i+1+N][j];
    }
}

if(check(inputArr,outputArr)) console.log(0);
else BFS(inputArr);




// if(minCnt === 0) console.log(-1);
