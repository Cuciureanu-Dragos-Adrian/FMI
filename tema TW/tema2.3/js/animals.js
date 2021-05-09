var body = document.getElementsByTagName("body")[0];

// let deleted = document.getElementById("deleted");
// deleted.classList.remove("title");
// deleted.removeAttribute("onclick");
// deleted.parentNode.removeChild(deleted);


fetch('http:/localhost:3000/animals', {
    method: 'get'
}).then((response) => {
    response.json().then((animals)=>{

        let container = document.getElementById("animal_container");
        
        for(let i=0 ; i < animals.length ; i++){
            
                let animal_id = animals[i].id;
                console.log(animal_id);

                let animal_div = document.createElement("div");
                animal_div.classList.add("animal");
                container.appendChild(animal_div);

                let animal_image = document.createElement("div");
                animal_image.classList.add("animal-image");
                animal_image.style.backgroundImage="url("+animals[i].img+")";
                animal_div.appendChild(animal_image);

                let animal_name = document.createElement("p");
                animal_name.classList.add("animal-name");
                animal_name.innerText = "Name: " + animals[i].name;
                animal_div.appendChild(animal_name);

                let animal_description = document.createElement("p");
                animal_description.classList.add("animal-content");
                animal_description.innerText = animals[i].description;
                animal_div.appendChild(animal_description);

                let animal_rate = document.createElement("p");
                animal_rate.classList.add("animal-content");
                animal_rate.innerText="Rate: " + animals[i].rate;
                animal_div.appendChild(animal_rate);

                 
                let delete_button = document.createElement("img");
                delete_button.setAttribute("src","Images/delete.png");
                delete_button.addEventListener("click", function(){delete_animal(animal_id)});
                delete_button.classList.add("delete_button");
                animal_div.appendChild(delete_button);

                let edit_button = document.createElement("img");
                edit_button.setAttribute("src", "Images/edit.png");       
                edit_button.addEventListener("click", function(){edit_animal(animal_id)});
                edit_button.classList.add("edit_button");
                animal_div.appendChild(edit_button);

        }
    })
})

function add_animal(){

    let i = document.getElementById("img_input").value;
    let n = document.getElementById("name_input").value;
    let d = document.getElementById("description_input").value;
    let r = document.getElementById("rate_input").value;
    
    let new_animal = {
        img: i,
        name: n,
        description: d,
        rate: r
    }

    fetch('http://localhost:3000/animals', {
        method: 'post',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(new_animal)
    }).then(function(response) {
       window.location.reload();
    })

    console.log(new_animal);
}

function delete_animal(animal_id){
    fetch('http://localhost:3000/animals/' + animal_id, {
        method: 'delete',
        headers:{
            'Content-Type': 'application/json'
        }
    }).then(function(response) {
        window.location.reload();
    })

}

function edit_animal(animal_id){
    
    let i = document.getElementById("img_input").value;
    let n = document.getElementById("name_input").value;
    let d = document.getElementById("description_input").value;
    let r = document.getElementById("rate_input").value;
    
    let new_animal = {
        img: i,
        name: n,
        description: d,
        rate: r
    }

    fetch('http://localhost:3000/animals/' + animal_id, {
        method: 'put',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(new_animal)
    }).then(function(response) {
        window.location.reload();
    })

}

