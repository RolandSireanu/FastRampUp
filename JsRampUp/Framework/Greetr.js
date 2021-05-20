(function (windowObject, jqueryObject){
    console.log("IIFE from Greater library !");

    // ======= Private to object ==========
    // ==== Not exposed to the outside word ====
    // === working due to closure =======
    var supportedLanguages = ["en","es"];

    var greetings = {
        en:"Hello",
        es:"Holla"
    };

    var formalGreetings = {
        en:"Greeting",
        es:"Saludos"
    };

    var logMessage = {
        en:"Logged in",
        es:"Inicio sesion"
    };

    // =========================================

    var Greetr = function (firstName, lastName, language) {
        return new Greetr.init(firstName, lastName, language);
    }

    Greetr.prototype = {
        whoAmI: function() {
            console.log("Firstname:"+this.firstName);
            console.log("LastName:"+this.lastName);
            console.log("Language:"+this.language);
            return this;
        },

        validate : function () {
            if(supportedLanguages.includes(this.language) === false) {
                throw "Language not supported !";
            }

            return this;
        },

        greeting: function (formal) {
            if(formal) {
                return formalGreetings[this.language] + ", "+this.firstName; 
            }
            else {
                return greetings[this.language] + ", "+this.firstName; 
            }
        },

        HTMLGreeting: function(selector, formal) {
            if(!$) {
                throw "Jquerry not included !";
            }

            if(!selector) {
                throw "Selector is null ";
            }

            var msg = this.greeting(formal);
            jqueryObject(selector).html(msg);

            return this;
        },

        setLanguage: function(lang) {
            this.language = lang;
            this.validate()
            return this;
        }
    };
    

    Greetr.init = function (firstName="John", lastName="Doe", language="ES") {
        this.firstName = firstName;
        this.lastName = lastName;
        this.language = language;
    }

    Greetr.init.prototype = Greetr.prototype;

    windowObject.$G = Greetr;

    var obj = Greetr();


})(window,jQuery);