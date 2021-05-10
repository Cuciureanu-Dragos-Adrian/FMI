var body = document.getElementsByTagName("body")[0];

    window.onload = function (){
    var logTab = document.createElement("div");
    logTab.classList.add("logTab");
    logTab.id = "logTab";
    
    body.appendChild(logTab);

      
    fetch('http://localhost:3000/logged', {
        method: 'get'
    }).then((response)=> {
        response.json().then((logged)=>{
            if(logged.state==0){
            console.log("aici");

            logTab.style.left="82%";
            logTab.style.width = "15%";
            logTab.style.height = "auto";

            let userLabel= document.createElement("label");
            userLabel.setAttribute("for", "userInput");
            userLabel.innerText="User: ";

            let passwordLabel= document.createElement("label");
            passwordLabel.setAttribute("for", "passwordInput");
            passwordLabel.innerText="Password: ";

            let roleLabel= document.createElement("label");
            roleLabel.setAttribute("for", "roleInput");
            roleLabel.innerText="Role: ";
            
            let userInput= document.createElement("input");
            userInput.setAttribute("type","text");
            userInput.id="User";
            userInput.style.width = "100%";
            userInput.placeholder = "Username";

            let passwordInput= document.createElement("input");
            passwordInput.setAttribute("type","password");
            passwordInput.id="Password";
            passwordInput.style.width = "100%";
            passwordInput.placeholder = "Password";

            let roleInput= document.createElement("input");
            roleInput.setAttribute("type","text");
            roleInput.id="Role";
            roleInput.style.width = "100%";
            roleInput.placeholder = "Role (complete only if you want to sign up)";

            let addButton= document.createElement("button");
            addButton.classList.add("button");
            addButton.innerText="Sign up";
            addButton.setAttribute("onClick","addUser()");
            addButton.onclick = function(){addUser()};

            let loginButton= document.createElement("button");
            loginButton.classList.add("button");
            loginButton.innerText="Log in";
            loginButton.onclick = function(){tryLogin()};

            logTab.appendChild(userLabel);
            logTab.appendChild(userInput);
            logTab.appendChild(passwordLabel);
            logTab.appendChild(passwordInput);
            logTab.appendChild(roleLabel);
            logTab.appendChild(roleInput);
            logTab.appendChild(loginButton);
            logTab.appendChild(addButton);

            document.addEventListener('keypress', function(enter)
            {
                if(enter.key === 'Enter')
                {
                    tryLogin();
                }
            })
            
            }

            else if(logged.state== 1 && logged.rol == "admin"){
            //
            console.log("aici");

            logTab.style.left="82%";
            logTab.style.width = "15%";
            logTab.style.height = "6%";
            logTab.style.padding = "0.5%";
            logTab.style.justifyContent = "space-between";

            let welcomeText = document.createElement("p");
            welcomeText.innerText="Logged in as an " + logged.rol + ", " + logged.name+ "!";
            welcomeText.style.margin = "0";

            let logoutButton= document.createElement("button");
            logoutButton.classList.add("button");
            logoutButton.innerText="Log out";
            logoutButton.onclick = function(){logOut()};

            logTab.appendChild(welcomeText);
            logTab.appendChild(logoutButton);

            //

            let insertMenu = document.createElement("div");
            insertMenu.classList.add("insertMenu");

            let name = document.createElement("label");
            name.innerText="Insert";
            name.style.marginLeft = "35%";
            
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
            addButton.innerText="Insert";
            addButton.onclick = function(){add_animal()};
            addButton.style.width = "104.4%";
            
            insertMenu.appendChild(name);
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

            // celalalt meniu

            let alterMeniu = document.createElement("div");
            alterMeniu.classList.add("alterMeniu");

            let name1 = document.createElement("label");
            name1.innerText="Alter";
            name1.style.marginLeft = "35%";
            
            let nameLabel1 = document.createElement("label");
            nameLabel1.setAttribute("for", "nameAlter");
            nameLabel1.innerText="Name: ";

            let imgLabel1= document.createElement("label");
            imgLabel1.setAttribute("for", "imgAlter");
            imgLabel1.innerText="Link image: ";

            let descriptionLabel1= document.createElement("label");
            descriptionLabel1.setAttribute("for", "descriptionAlter");
            descriptionLabel1.innerText="Description: ";
            
            let rateLabel1= document.createElement("label");
            rateLabel1.setAttribute("for", "rateAlter");
            rateLabel1.innerText="Rate: ";
            
            let nameInput1= document.createElement("input");
            nameInput1.setAttribute("type","text");
            nameInput1.id="nameAlter";
            nameInput1.style.width="100%";

            let imgInput1= document.createElement("input");
            imgInput1.setAttribute("type","text");
            imgInput1.id="imgAlter";
            imgInput1.style.width="100%";

            let descriptionInput1= document.createElement("input");
            descriptionInput1.setAttribute("type","text");
            descriptionInput1.id="descriptionAlter";
            descriptionInput1.style.width="100%";

            let rateInput1= document.createElement("input");
            rateInput1.setAttribute("type","text");
            rateInput1.id="rateAlter";
            rateInput1.style.width="100%";
            
            alterMeniu.appendChild(name1);
            alterMeniu.appendChild(nameLabel1);
            alterMeniu.appendChild(nameInput1);
            alterMeniu.appendChild(imgLabel1);
            alterMeniu.appendChild(imgInput1);
            alterMeniu.appendChild(descriptionLabel1);
            alterMeniu.appendChild(descriptionInput1);
            alterMeniu.appendChild(rateLabel1);
            alterMeniu.appendChild(rateInput1);

            body.append(alterMeniu);
            }
            else if(logged.state== 1){
                //
                console.log("aici");
    
                logTab.style.left="81%";
                logTab.style.width = "15%";
                logTab.style.padding = "1%";
                logTab.style.justifyContent = "space-between";
    
                let welcomeText = document.createElement("p");
                welcomeText.innerText="Logged in as an " + logged.rol + ", " + logged.name+ "!";
                welcomeText.style.margin = "0";
    
                let logoutButton= document.createElement("button");
                logoutButton.classList.add("button");
                logoutButton.innerText="Log out";
                logoutButton.onclick = function(){logOut()};

                logTab.appendChild(welcomeText);
                logTab.appendChild(logoutButton);

                console.log("acolo");
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
            window.alert("User can't be empty!");
        }
        else if(password.length==0){
            window.alert("Password can't be empty!");
        }
        else if(role.length==0){
            window.alert("Role can't be empty!");
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
                            window.alert("Username already exists!");
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
                            window.alert("User created!");
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
                        window.alert("Wrong password!");
                        }
                        else{
                            logUser(item.name, item.rol);
                        }
                    }
                }
                
                if(OK==0)
                window.alert("User does not exist!");
            })
        })
    
    }