const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
let input = fs.readFileSync(filePath).toString().split("\n");
const N = +input[0];
const costReq = input[1].split(' ');
const total = +input[2];

const calTotal = (standard) => {
    let totalComp = 0;
    for(let i = 0 ; i < N ; ++i) {
        totalComp += (standard >= +costReq[i] ? Number(costReq[i]) : standard);
    }

    return totalComp;
}


let left = 1;
let right = 100000;
let maxMid = -1;

let a = -1;
let b = 0;
for(let j = 0; j < N ; ++j){
    b+=Number(costReq[j]);
    a = Math.max(a ,Number(costReq[j]));
}
if(total >= b){
    console.log(a);
    return;
}

while( left <= right){
    let mid = Math.floor((left+right)/2);

    let comp = calTotal(mid);
    // console.log(mid , comp);
    if(comp <= total){
        left = mid + 1;
        maxComp = Math.max(maxMid , mid);
    }
    else{
        right = mid - 1;
    }
}

console.log(maxComp);