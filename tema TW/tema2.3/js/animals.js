var body = document.getElementsByTagName("body")[0];


fetch('http://localhost:3000/animals', {
    method: 'get'
}).then((response) => {
    response.json().then((animals)=>{

        let container = document.getElementById("animal_container");
        
        fetch('http://localhost:3000/logged', {
        method: 'get'
    }).then((response)=> {
        response.json().then((logged)=>{
            if(logged.state==1 && logged.rol == "admin")
            {
                for(let i = 0 ; i < animals.length ; i++)
                {
                    let animal_id = animals[i].id;

                    let animal_div = document.createElement("div");
                    animal_div.classList.add("animal");

                    let image = document.createElement("img");
                    image.setAttribute("src", animals[i].img);
                    image.className = "image";

                    let animal_image = document.createElement("div");
                    animal_image.classList.add("poze");
                    // animal_image.style.backgroundImage=`url("${animals[i].img}")`;
                    animal_image.appendChild(image);
                    
                    let animal_name = document.createElement("p");
                    animal_name.classList.add("scris");
                    animal_name.innerText = "Name: " + animals[i].name;
                    
                    let animal_description = document.createElement("p");
                    animal_description.classList.add("scris");
                    animal_description.innerText = animals[i].description;
                    
                    let animal_rate = document.createElement("p");
                    animal_rate.classList.add("scris");
                    animal_rate.innerText="Rating: " + animals[i].rate;

                    let deleteButton= document.createElement("button");
                    deleteButton.classList.add("button");
                    deleteButton.innerText="Delete this one!!!";
                    deleteButton.onclick = function(){delete_animal(animal_id)};

                    let editButton= document.createElement("button");
                    editButton.classList.add("button");
                    editButton.innerText="Editer time!!!";
                    editButton.onclick = function(){edit_animal(animal_id)};

                    container.appendChild(animal_div);

                    animal_div.appendChild(animal_image);
                    animal_div.appendChild(animal_name);
                    animal_div.appendChild(animal_description);
                    animal_div.appendChild(animal_rate);
                    animal_div.appendChild(deleteButton);
                    animal_div.appendChild(editButton);
                }
            }
            else if(logged.state==1)
            {
                console.log("asd");
                for(let i = 0 ; i < animals.length ; i++)
                {
                    let animal_div = document.createElement("div");
                    animal_div.classList.add("animal");

                    let animal_image = document.createElement("div");
                    animal_image.classList.add("poze");
                    animal_image.style.backgroundImage=`url("${animals[i].img}")`;
                        
                    let animal_name = document.createElement("p");
                    animal_name.classList.add("scris");
                    animal_name.innerText = "Name: " + animals[i].name;
                        
                    let animal_description = document.createElement("p");
                    animal_description.classList.add("scris");
                    animal_description.innerText = animals[i].description;
                        
                    let animal_rate = document.createElement("p");
                    animal_rate.classList.add("scris");
                    animal_rate.innerText="Rating: " + animals[i].rate;

                    container.appendChild(animal_div);

                    animal_div.appendChild(animal_image);
                    animal_div.appendChild(animal_name);
                    animal_div.appendChild(animal_description);
                    animal_div.appendChild(animal_rate);
                }
            }
            })
        })
    })
})

function add_animal(){

    let i = document.getElementById("imgInput").value;
    let n = document.getElementById("nameInput").value;
    let d = document.getElementById("descriptionInput").value;
    let r = document.getElementById("rateInput").value;
    
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

function delete_animal(animal_id)
{
    fetch('http://localhost:3000/animals/' + animal_id, {
        method: 'delete',
        headers:{
            'Content-Type': 'application/json'
        }
    }).then(function(response) 
    {
        window.location.reload();
    })
}

function edit_animal(animal_id){
    
    let i = document.getElementById("imgAlter").value;
    let n = document.getElementById("nameAlter").value;
    let d = document.getElementById("descriptionAlter").value;
    let r = document.getElementById("rateAlter").value;
    
    fetch('http://localhost:3000/animals', {
        method: 'get'
    }).then((response) => {
        response.json().then((animals)=>{
            for(let j=0 ; j < animals.length ; j++)
            {
                console.log(n);
                if(animals[j].id == animal_id) 
                { 
                    if (i === "")
                    {
                        i = animals[j].img;
                    }
                    if (n === "")
                    {
                        n = animals[j].name;
                    }
                    if (d === "")
                    {
                        d = animals[j].description;
                    }
                    if (r === "")
                    {
                        r = animals[j].rate;
                    }
                }
            }
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
        })
    })
}