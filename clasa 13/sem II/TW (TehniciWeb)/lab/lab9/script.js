function fetchDogs(){
    let body = document.getElementsByTagName("body")[0];
    let p = document.createElement("p");
    p.innerText = "Loading...";

    p.setAttribute("id","loading");
    body.appendChild(p)
    fetch('http://localhost:3000/dogs',{
        method:'get'
    }).then((response)=>{
        response.json().then((data)=>{
            if (data.length){
                body.removeChild(p);
            }
            for(let i = 0;i<data.length;i++){
                let image = document.createElement("img");
                image.setAttribute("src",data[i].img);
                body.appendChild(image);

                let h2 = document.createElement("h2");
                h2.innerText = data[i].name;
                body.appendChild(h2);
            }
        })
    })
}

fetchDogs();