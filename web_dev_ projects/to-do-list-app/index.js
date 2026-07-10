const newTaskButton= document.getElementById("newTaskButton");
const tasksContainer = document.getElementById("tasksContainer");

newTaskButton.addEventListener("click", addTask);

let noOfTasks=0;

function addTask(){
    //creates a new div, appends it to the div id=tasksContainer. and then creates the inner children of the individual tak div and appends them inside it.
    noOfTasks+=1;
    //get the value of new task
    let taskText = document.getElementById("newTask").value;
    if (taskText.trim() === "") {
        alert("Please enter a task!");
        return;
    }

    //container with all tasks=tasksContainer
    //individualtaskcontainer=taskN
    //task name=taskName

    //create new element div(task container)
    const taskN= document.createElement("div");
    taskN.classList.add("taskN");
    //append it to the div id=tasksContainer
    tasksContainer.appendChild(taskN);

    //create inner parts of the div
    const checkbox = document.createElement("input");
    checkbox.type = "checkbox";
    checkbox.classList.add("checkBox");
    let del= document.createElement("button");
   // const edit= document.createElement("button");
    const taskName=document.createElement("div");
    //add the task to the inner div
    taskName.textContent=taskText;
    taskName.classList.add("taskName");
    del.classList.add("delButton");
     
    del.textContent = "Delete";
   // edit.textContent = "Edit";

    //append the elements as children of the individual div
    taskN.appendChild(checkbox);
    taskN.appendChild(taskName);
    taskN.appendChild(del);
del.setAttribute("src", "recycle-bin-icon.svg");
  del.setAttribute("height", "75%");
  del.setAttribute("width", "35px");
  del.setAttribute("alt", "Delete Button");
   // taskN.appendChild(edit);
  

    document.getElementById("newTask").value = "";

    del.addEventListener("click", function () {
        task.remove(); // Remove the parent task div
    });

}

/*
function editTask(){

}

function Progress(){

}

function isCompleted(){//check if all tasks are checked off

}
*/