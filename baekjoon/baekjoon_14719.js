const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
let input = fs.readFileSync(filePath).toString().split("\n");
const H = Number(input[0].split(" ")[0]);
const W = Number(input[0].split(" ")[1]);

const blocks = input[1].split(" ");

let total = 0;

let stdHeight;
for(let i = 1 ; i < W ; ++i){

    let left = -1;
    let right = -1;

for(let j = i ; j >= 0; --j){
    left = Math.max(blocks[j],left);
}
for(let j = i ; j < W ; ++j){
    right = Math.max(blocks[j] , right);
}

stdHeight = Math.min(left , right);
total += stdHeight - blocks[i];


}
console.log(total);