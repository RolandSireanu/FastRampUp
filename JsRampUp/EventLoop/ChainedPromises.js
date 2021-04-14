let cleanRoom = function(){
    return new Promise(function(resolve,reject){
        resolve("I cleaned my room !");
    });
}

let removeGarbage = function(msg){
    return new Promise(function (resolve, reject){
        return resolve(msg + " I threw away the garbage");
    });
}

let eatIcecream = function(msg){
    return new Promise(function(resolve,reject){
        resolve(msg + ", now I want icecream !");
    });
}

cleanRoom().then(function (message){
    return removeGarbage(message);
}).then(function (message){
    return eatIcecream(message)
}).then(function (message){
    console.log(message);
}).catch(function (message){
    console.log(message);
})