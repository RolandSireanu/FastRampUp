let p1 = new Promise(function(resolve,reject){
    console.log("Executing first promise");
    resolve("Everything is ok ! ");
});

let p2 = new Promise(function(resolve,reject){
    console.log("Executing second promise");
    resolve("Now is really ok ! ");
});

Promise.all([p1, p2]).then(function(){
    console.log("all promises resolved !");
});


// Promise.race([p1, p2]).then(function(){
//     console.log("one of the promise is resolved !");
// });