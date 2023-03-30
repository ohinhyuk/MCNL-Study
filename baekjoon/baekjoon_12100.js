const fs = require("fs");
const filePath = process.platform === "linux" ? "/dev/stdin" : "./input.txt";
// filePath = "/dev/stdin";
let input = fs.readFileSync(filePath).toString().split("\n");

let N = +input[0];



function create2DArray(rows , columns){
    let arr = new Array(rows);
    for(let i = 0 ; i < arr.length ; ++i){
        // arr[i] = new Array(columns);
        arr[i] = [ ...input[i+1].split(' ').map(elem => +elem)];
        console.log(arr[i])
    }
    return arr;
}

function print2DArray(arr,rows, columns){
    for(let i = 0 ; i < rows ; ++i){
        for(let j = 0 ; j < columns ; ++j){
            process.stdout.write(arr[i][j] + " ");
        }
        console.log("");
    }
}


let arr = create2DArray(N,N);

print2DArray(arr,N,N);


// l -> r 이라고 할때 r->l 
// 1) start , end 가 같을 때 -> 값 두배해서 list에 추가 , index : end -1 부터 시작
// 2) 다를 때, 끝날 때 -> start list에 추가 , index : end부터 시작,





const moveOneTime = (arr ,dir) => {
    
    // left
    if(dir === "left"){
        for(let i = 0 ; i < N ; ++i){
            let list = [];
            let cnt = 0;
            let j = 0;
            for(j = 0 ; j < N ; ++j){
                if(arr[i][j]!== 0) list.push(arr[i][j]);
            }
            for(j = 0; j < list.length ; ++j){
                if( j !== list.length-1 && list[j] === list[j+1]){
                    arr[i][cnt++] = list[j] * 2;
                    j++;
                }
                else {
                    arr[i][cnt++] = list[j];
                }
            }
            for(j = cnt ; j < N ; ++j){
                arr[i][j] = 0;
            }
        }
    }
    // right
    else if(dir === "right"){
        for(let i = 0 ; i < N ; ++i){
            let list = [];
            let cnt = N-1;
            let j = 0;
            for(j = 0 ; j < N ; ++j){
                if(arr[i][j]!== 0) list.push(arr[i][j]);
            }
            for(j = list.length -1; j >= 0 ; --j){
                if( j !== 0 && list[j] === list[j-1]){
                    arr[i][cnt--] = list[j] * 2;
                    j--;
                }
                else {
                    arr[i][cnt--] = list[j];
                }
            }
            for(j = cnt ; j >=0 ; --j){
                arr[i][j] = 0;
            }
        }
    }
    // top
    else if(dir === "top"){
        for(let i = 0 ; i < N ; ++i){
            let list = [];
            let cnt = 0;
            let j = 0;
            for(j = 0 ; j < N ; ++j){
                if(arr[j][i]!== 0) list.push(arr[j][i]);
            }
            for(j = 0; j < list.length ; ++j){
                if( j !== list.length-1 && list[j] === list[j+1]){
                    arr[cnt++][i] = list[j] * 2;
                    j++;
                }
                else {
                    arr[cnt++][i] = list[j];
                }
            }
            for(j = cnt ; j < N ; ++j){
                arr[j][i] = 0;
            }
        }
    }
    // bottom
    else if(dir === "bottom"){
        for(let i = 0 ; i < N ; ++i){
            let list = [];
            let cnt = N-1;
            let j = 0;
            for(j = 0 ; j < N ; ++j){
                if(arr[j][i]!== 0) list.push(arr[j][i]);
            }
            for(j = list.length -1; j >= 0 ; --j){
                if( j !== 0 && list[j] === list[j-1]){
                    arr[cnt--][i] = list[j] * 2;
                    j--;
                }
                else {
                    arr[cnt--][i] = list[j];
                }
            }
            for(j = cnt ; j >=0 ; --j){
                arr[j][i] = 0;
            }
        }
    }
    return arr;
}

arr = moveOneTime(arr , "bottom");
// arr = moveOneTime(arr , 1);
print2DArray(arr,4,4);
