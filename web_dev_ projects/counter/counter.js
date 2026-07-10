const decreaseVal = document.getElementById("decrease");
const increaseVal = document.getElementById("increase");
const resetVal = document.getElementById("reset");
const count= document.getElementById("countLabel");

let counter=0;

increase.onclick= function(){
    counter++;
    countLabel.textContent=counter;
}

decrease.onclick= function(){
    counter--;
    countLabel.textContent=counter;
}

reset.onclick= function(){
    counter=0;
    countLabel.textContent=counter;
}