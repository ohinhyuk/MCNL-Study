const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
let input = fs.readFileSync(filePath).toString().split("\n");

const heights = input.map(elem => Number(elem));
let answer = new Array(7);


const DFS = (i , total ,Nanjangs) => {
    
if(i === 9){
    if( Object.keys(Nanjangs).length === 7 && Object.keys(Nanjangs).reduce((acc , e) => acc + Number(e) , 0) === 100){
        console.log(total , Object.keys(Nanjangs));

        answer = Object.keys(Nanjangs).map(e => Number(e));
        
        return ;
    }
}

else if(i<9){
     DFS(i+1,total , Nanjangs);
// Nanjangs.push(heights[i]);
    Nanjangs[heights[i]] = heights[i];
    DFS(i+1 , total + heights[i] , Nanjangs);

}

}

let arr = {}
DFS(0 , 0 ,arr);

answer.sort( function(a,b) {
    if(a > b) return 1;
    if(a === b) return 0;
    if(a < b) return -1;
});
answer.forEach( elem => console.log(elem));