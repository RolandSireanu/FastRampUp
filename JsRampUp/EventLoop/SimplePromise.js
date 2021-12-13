//Js is single threaded 
//A promise is an object that represents the eventual completion of
// an async operation and its value
//Promise has 3 states : pending , fulfilled , rejected
//Promise is a proxy for a value not necessary known when the promsie is created

//The async method returns a promise to supply the value at a later time
//The value return by a promise is value of arg passed to resolve , reject

var p = new Promise(function(resolve,reject){

    let worked = false;
    let obj = {
        name: "Roland",
        age: 28
    };

    if(worked){
        resolve(obj);
    }
    else{
        reject("It didn't work fine");
    }
});

//".then" function is executed only if p gets resolved
//Likewise , if p is rejected , .catch method will be executed
p.then(function (result){
    console.log(result)
}).catch(function (result){
    console.log("Rejectd:"+result);
});

//.then function can take 2 callback arguments, one for succesfully resolved promises ,
//and one for rejected promises
p.then((result) => {
    console.log("Promise resolved with success ");
},
        (result) => {
    console.log("Promise rejected ");
});


console.log("Hello world !");
