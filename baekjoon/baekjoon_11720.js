// let input = require('fs').readFileSync('/dev/stdin').toString().split('\n');

const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
let input = fs.readFileSync(filePath).toString().split("\n");

const INPUT_SIZE = +input[0];
let arr = input[1];
let sum = 0;

sum = arr.split("").reduce((acc , v) => {
    return acc += v * 1
} , 0)
console.log(sum);