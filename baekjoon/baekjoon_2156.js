const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
let input = fs.readFileSync(filePath).toString().split("\n")  ;

let N = Number(input[0]);
input.splice(0,1);

const nums = input.map( elem => Number(elem));

// console.log(nums);

const dp = new Array(nums.length);


dp[0] = nums[0];

if(N >= 2) dp[1] = nums[0] + nums[1];

if(N >= 3) dp[2] = Math.max(nums[0]+ nums[1] , nums[1]+nums[2] , nums[0] + nums[2]);

for(let i = 3 ; i < nums.length ; ++i){
   dp[i] = Math.max(dp[i-3] +nums[i-2]+nums[i-1] , dp[i-2] + nums[i-1] , dp[i-1]);
}

console.log(dp[nums.length-1]);


