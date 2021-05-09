var body = document.getElementsByTagName("body")[0];

    window.onload = function pageLoad(){
    var logTab = document.createElement("div");
    logTab.classList.add("logTab");
    logTab.id = "logTab";
    
    body.appendChild(logTab);

      
    fetch('http:/localhost:3000/logged', {
        method: 'get'
    }).then((response)=> {
        response.json().then((logged)=>{
            if(logged.state==0){
            logTab.style.left="65.5%";

            let br = document.createElement("br");

            let userLabel= document.createElement("label");
            userLabel.setAttribute("for", "userInput");
            userLabel.innerText="User: ";

            let passwordLabel= document.createElement("label");
            passwordLabel.setAttribute("for", "passwordInput");
            passwordLabel.innerText="Password: ";
            passwordLabel.style.marginLeft="2%";

            let roleLabel= document.createElement("label");
            roleLabel.setAttribute("for", "roleInput");
            roleLabel.innerText="Role: ";
            roleLabel.style.marginLeft="1%";
            
            let userInput= document.createElement("input");
            userInput.setAttribute("type","text");
            userInput.id="User";

            let passwordInput= document.createElement("input");
            passwordInput.setAttribute("type","password");
            passwordInput.id="Password";

            let roleInput= document.createElement("input");
            roleInput.setAttribute("type","text");
            roleInput.id="Role";

            let addButton= document.createElement("button");
            addButton.classList.add("button");
            addButton.classList.add("add");
            addButton.innerText="Sign up";
            addButton.setAttribute("onClick","addUser()");
            addButton.onclick = function(){addUser()};


            let loginButton= document.createElement("button");
            loginButton.classList.add("button");
            loginButton.classList.add("login");
            loginButton.innerText="Log in";
            loginButton.onclick = function(){tryLogin()};

            logTab.appendChild(userLabel);
            logTab.appendChild(userInput);
            logTab.appendChild(passwordLabel);
            logTab.appendChild(passwordInput);
            logTab.appendChild(roleLabel);
            logTab.appendChild(roleInput);
            logTab.appendChild(addButton);
            logTab.appendChild(loginButton);

            document.addEventListener('keypress', function(e){
                console.log(e.key);

                if(e.key === 'Enter'){
                    tryLogin();
                    }
            })
            
            }

            else if(logged.state==0 && logged.rol == "admin"){
            //

            logTab.style.left="78%";
            logTab.style.width = "15%";
            logTab.style.padding = "1%";
            logTab.style.justifyContent = "space-between";

            let welcomeText = document.createElement("p");
            welcomeText.innerText="Logged in as an " + logged.rol + ", " + logged.name+ "!";
            welcomeText.style.margin = "0";

            let logoutButton = document.createElement("img");
            logoutButton.setAttribute("src","Images/logout.png");
            logoutButton.onclick=function(){logOut()};
            logoutButton.classList.add("logoutButton");

            logTab.appendChild(welcomeText);
            logTab.appendChild(logoutButton);

            //

            let insertMenu = document.createElement("div");
            insertMenu.classList.add("insertMenu");

            let nameLabel= document.createElement("label");
            nameLabel.setAttribute("for", "nameInput");
            nameLabel.innerText="Name: ";

            let imgLabel= document.createElement("label");
            imgLabel.setAttribute("for", "imgInput");
            imgLabel.innerText="Link image: ";

            let descriptionLabel= document.createElement("label");
            descriptionLabel.setAttribute("for", "descriptionInput");
            descriptionLabel.innerText="Description: ";
            
            let rateLabel= document.createElement("label");
            rateLabel.setAttribute("for", "rateInput");
            rateLabel.innerText="Rate: ";
            
            let nameInput= document.createElement("input");
            nameInput.setAttribute("type","text");
            nameInput.id="nameInput";
            nameInput.style.width="100%";

            let imgInput= document.createElement("input");
            imgInput.setAttribute("type","text");
            imgInput.id="imgInput";
            imgInput.style.width="100%";

            let descriptionInput= document.createElement("input");
            descriptionInput.setAttribute("type","text");
            descriptionInput.id="descriptionInput";
            descriptionInput.style.width="100%";

            let rateInput= document.createElement("input");
            rateInput.setAttribute("type","text");
            rateInput.id="rateInput";
            rateInput.style.width="100%";

            let addButton= document.createElement("button");
            addButton.classList.add("button");
            addButton.classList.add("add");
            addButton.innerText="Inserare";
            addButton.onclick=function(){addCar()};
            
            insertMenu.appendChild(nameLabel);
            insertMenu.appendChild(nameInput);
            insertMenu.appendChild(imgLabel);
            insertMenu.appendChild(imgInput);
            insertMenu.appendChild(descriptionLabel);
            insertMenu.appendChild(descriptionInput);
            insertMenu.appendChild(rateLabel);
            insertMenu.appendChild(rateInput);
            insertMenu.appendChild(addButton);

            body.append(insertMenu);
            }
        })
    
    })


    }
  
    function logUser(item1, item2){
        var loggedState = {
            state: 1,
            name : item1,
            rol: item2
        }
        fetch('http:/localhost:3000/logged', {
            method: 'put',
            headers: {
                'content-type': 'application/json'
            },
            body: JSON.stringify(loggedState)
        }).then(function(response) {
            window.location.reload();
        })
    }

    function logOut(){
        var loggedState = {
            state: 0,
            name: "None"
        }
        fetch('http:/localhost:3000/logged', {
            method: 'put',
            headers: {
                'content-type': 'application/json'
            },
            body: JSON.stringify(loggedState)
        }).then(function(response) {
            window.location.reload();
        })
    }

    function addUser(){
        let user = document.getElementById("User").value;
        let password = document.getElementById("Password").value;
        let role = document.getElementById("Role").value;
    
        console.log(user);
    
        if(user.length==0){
            window.alert("Campul user nu poate fi gol!");
        }
        else if(password.length==0){
            window.alert("Campul parola nu poate fi gol!");
        }
        else if(role.length==0){
            window.alert("Campul role nu poate fi gol!");
        }
        else{
            var newUser={
                name: user,
                pass: password,
                rol: role
            }
            console.log(newUser);
    
            let OK=1;
            fetch('http:/localhost:3000/users', {
                method: 'get'
            }).then((response) =>{
                response.json().then((users) => {
        
                    users.forEach(search);
                    
                    function search(item){
                        if(item.name==newUser.name&&OK!=0){
                            window.alert("Username deja existent!");
                            OK=0;
                        }
                    }
    
                    if(OK==1){    
                        fetch("http:/localhost:3000/users", {
                            method: 'post',
                            headers: {
                                'Content-Type': 'application/json'
                            },
                            body: JSON.stringify(newUser)
                        }).then(function(response){
                            console.log(response);
                            window.alert("User creat cu succes!");
                        })
                    }
                })
            })
    
        }
    }
    
    function tryLogin(){
        let user = document.getElementById("User").value;
        let password = document.getElementById("Password").value;

        fetch('http:/localhost:3000/users', {
            method: 'get'
        }).then((response) =>{
            response.json().then((users) => {
    
                let OK=0;
    
                users.forEach(search);
                
                function search(item){
                    if(item.name==user&&OK==0){
                        OK=1;
                        
                        if(item.pass!=password){
                        window.alert("Parola incorecta!");
                        }
                        else{
                            logUser(item.name, item.rol);
                        }
                    }
                }
                
                if(OK==0)
                window.alert("User inexistent!");
            })
        })
    
    }