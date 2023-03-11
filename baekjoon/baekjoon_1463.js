const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
const input = Number(fs.readFileSync(filePath).toString());

let dp = new Array(input+1).fill(0);
// console.log(dp.length);
dp[1] = 0;
dp[2] = 1;
dp[3] = 1;

for(let i = 4 ; i <= input+1; ++i){
    
    let divideThree = Number.POSITIVE_INFINITY;
    let divideTwo = Number.POSITIVE_INFINITY;
    if(i%3 === 0){
        divideThree = dp[Math.floor(i /3)] + 1;
    }
    if(i%2 === 0){
        
        divideTwo = dp[Math.floor(i / 2)] + 1;
    }
    const subOne = dp[Math.floor(i-1)] + 1;

    dp[i]= Math.min(divideThree , divideTwo , subOne);

}

console.log(dp[input])

