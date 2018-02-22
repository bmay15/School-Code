
var Ones = {
    name: "Ones:",
    divId: "onesOutput",
    value: 0,
    score: function(array){
        for(var i = 0; i < array.length; i++){
            if(Number(array[i]) === 1){
                this.value = this.value + 1;
            }
        }
    }
};

var Twos = {
    name: "Twos:",
    divId: "twosOutput",
    value: 0,
    score: function(array){
        for(var i = 0; i < array.length; i++){
            if(Number(array[i]) === 2){
                this.value = this.value + 2;
            }
        }
    }
};

var Threes = {
    name: "Threes:",
    divId: "threesOutput",
    value: 0,
    score: function(array){
        for(var i = 0; i < array.length; i++){
            if(Number(array[i]) === 3){
                this.value = this.value + 3;
            }
        }
    }
};

var Fours = {
    name: "Fours:",
    divId: "foursOutput",
    value: 0,
    score: function(array){
        for(var i = 0; i < array.length; i++) {
            if (Number(array[i]) === 4) {
                this.value = this.value + 4;
            }
        }
    }
};

var Fives = {
    name: "Fives:",
    divId: "fivesOutput",
    value: 0,
    score: function(array){
        for(var i = 0; i < array.length; i++){
            if(Number(array[i]) === 5){
                this.value = this.value + 5;
            }
        }
    }
};

var Sixes = {
    name: "Sixes:",
    divId: "sixesOutput",
    value: 0,
    score: function(array){
        for(var i = 0; i < array.length; i++){
            if(Number(array[i]) === 6){
                this.value = this.value + 6;
            }
        }
    }
};

var ThreeKind = {
    name: "Three of A Kind:",
    divId: "threeKindOutput",
    value: 0,
    sum: 0,
    1: 0,
    2: 0,
    3: 0,
    4: 0,
    5: 0,
    6: 0,
    score: function (array) {
        for (var i = 0; i < array.length; i++) {
            this.sum = this.sum + Number(array[i]);
        }

        for (var j = 0; j < array.length; j++){
            this[array[j]] = this[array[j]] + 1;

            if(this[array[j]] === 3){
                this.value = this.sum;
            }
        }
    }
};

var FourKind = {
    name: "Four of A Kind:",
    divId: "fourKindOutput",
    value: 0,
    sum: 0,
    1: 0,
    2: 0,
    3: 0,
    4: 0,
    5: 0,
    6: 0,
    score: function (array) {
        for (var i = 0; i < array.length; i++) {
            this.sum = this.sum + Number(array[i]);
        }

        for (var j = 0; j < array.length; j++){
            this[array[j]] = this[array[j]] + 1;

            if(this[array[j]] === 4){
                this.value = this.sum;
            }
        }
    }
};

var FiveKind = {
    name: "Five of A Kind:",
    divId: "fiveKindOutput",
    value: 0,
    1: 0,
    2: 0,
    3: 0,
    4: 0,
    5: 0,
    6: 0,
    score: function (array) {
        for (var i = 0; i < array.length; i++){
            this[array[i]] = this[array[i]] + 1;

            if(this[array[i]] === 5){
                this.value = 50;
            }
        }
    }
};

var Random = {
    name: "Random:",
    divId: "ranOutput",
    value: 0,
    score: function(array){
        for(var i = 0; i < array.length; i++){
            this.value = this.value + Number(array[i]);
        }
    }
};

var categoryArr = [Ones, Twos, Threes, Fours, Fives, Sixes, ThreeKind, FourKind, FiveKind, Random];

var doScoreBtn = function(){
    var diceInput = getInput("userInput");
    var diceArr = diceInput.split(" ");

    for(var j = 0; j < categoryArr.length; j++){
        categoryArr[j].score(diceArr);
    }

    var addElement = function(){
        var newDiv = document.createElement("div");
        var newText = document.createTextNode(categoryArr[i].name + categoryArr[i].value);
        newDiv.appendChild(newText);
        newDiv.Id = categoryArr[i].divId;

        var currentDiv = document.getElementById("Outputs");
        document.body.insertBefore(newDiv, currentDiv);
    };

    for(var i = 0; i < categoryArr.length; i++){
        addElement();
    }

};

setClickHandler("scoreBtn", doScoreBtn);
