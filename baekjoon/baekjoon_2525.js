const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
let input = fs.readFileSync(filePath).toString().split("\n");

let nowHours = Number(input[0].split(" ")[0]);
let nowMinutes = Number(input[0].split(" ")[1]);
let plusMinutes = Number(input[1]);
let afterMinutes = nowMinutes;
let afterHours = nowHours;


const addMinutes = (plusMinutes) => {
    afterMinutes += plusMinutes;
    if(afterMinutes >= 60){
        nowHours += afterMinutes / 60;
    }
    return afterMinutes % 60;
}

const checkHours = (afterHours) => {
    if(afterHours >= 24){
        afterHours -= 24;
    }
    return afterHours;
}

afterMinutes = Math.floor(addMinutes(plusMinutes));
afterHours = Math.floor(checkHours(nowHours));

console.log(afterHours , afterMinutes);
