const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
const input = Number(fs.readFileSync(filePath).toString());

let cnt = 0;
let answer = 666;

const check = (num) => {
    const numString = num + "";
    for(let i = 0 ; i < numString.length-2 ; ++i){
        if(numString[i] === '6' && numString[i+1] === '6' && numString[i+2] === '6'){
            return true;
        }
    }
    return false;
}

while(cnt !== input){
    if(check(answer)){
        cnt++;
    }
    answer+=1;
}

console.log(answer-1);