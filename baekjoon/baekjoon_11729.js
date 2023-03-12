const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
let input = Number(fs.readFileSync(filePath).toString());
const hanoiAns = [];

const hanoi = (start , temp , end , n) => {
    if(n === 1){
        hanoiAns.push(`${start} ${end}`);
    }
    else if (n > 1){
        hanoi(start , end, temp , n-1);
        // hanoi(start , temp , end , 1);
        hanoiAns.push(`${start} ${end}`);
        hanoi(temp , start , end , n-1);
    }
}

hanoi(1,2,3, input);

console.log(hanoiAns.length);
// hanoiAns.forEach((obj) => {const values = Object.values(obj); console.log(values[0] , values[1])});
console.log(hanoiAns.join("\n"));

