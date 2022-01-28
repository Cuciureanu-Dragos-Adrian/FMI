var express = require('express');
var router = express.Router();

let dbService = require("../service/dbService");
let dbRepository = require("../repository/dbRepository");


//READ


router.get("/animals", (req, res) => {

    let animalList = dbService.getAllAnimals();
    if (animalList!= undefined && animalList.length !=0){
        res.status(200).send(animalList);
    }
    else {
        res.status(404).send("No animals found!");
    }
});


router.get("/users", (req, res) => {

    let usersList = dbService.getAllUsers();
    if (usersList!= undefined && usersList.length !=0){
        res.status(200).send(usersList);
    }
    else {
        res.status(404).send("No users found!");
    }
});


router.get("/logged", (req, res) => {

    let logged = dbService.getLogged();
    res.status(200).send(logged);
});


router.get("/animals/:id", (req,res) => {
    let animalsList = dbService.getAllAnimals();
    let id = req.params.id;
    let checkExists = false;

    animalsList.forEach(animal => {
        if(animal.id == id){
            checkExists = true;
            res.status(200).send(animal);
        }
    })

    if(checkExists === false) {
        res.status(404).send("No animal found!");
    }
});


router.get("/users/:id", (req,res) => {
    let usersList = dbService.getAllUsers();
    let id = req.params.id;
    let checkExists = false;

    usersList.forEach(user => {
        if(user.id == id){
            checkExists = true;
            res.status(200).send(user);
        }
    })

    if(checkExists === false) {
        res.status(404).send("No user found!");
    }
})


//CREATE


router.post("/users", (req,res) => {

    let newUser = dbService.addUser(req.body);
    res.status(200).send(newUser);

})

router.post("/animals", (req,res) => {
    console.log(req);
    let newAnimal = dbService.addAnimal(req.body);
    res.status(200).send(newAnimal);
});


//UPDATE


router.put("/animals/:id", (req,res) => {

    const animalsList = dbService.getAllAnimals();
    let id = req.params.id;
    let checkExists = false;

    for(let i = 0; i < animalsList.length; i++){
        if(animalsList[i].id == id) 
        {
            if(req.body.img)
            {
                animalsList[i].img = req.body.img;
            }

            if(req.body.name)
            {
                animalsList[i].name = req.body.name;
            }
            
            if(req.body.description)
            {
                animalsList[i].description = req.body.description;
            }

            if(req.body.rate)
            {
                animalsList[i].rate = req.body.rate;
            }

            checkExists = true;
        }
    }

    if(checkExists === true) {
        dbRepository.writeJSONFileAnimals(animalsList);
        res.status(200).send("Animal successfully updated!");
    }
    else {
        res.status(404).send("No animal found!");
    }
})

router.put("/logged", (req,res) => {
    let logStatus = dbService.changeLogged(req.body);
    res.status(200).send(logStatus);

})


//DELETE


router.delete("/animals/:id", (req, res) => {

    const animalsList = dbService.getAllAnimals();
    let id = req.params.id;
    let checkExists = false;

    for(let i = 0; i < animalsList.length; i++) 
    {
        if(animalsList[i].id == id) 
        {
            checkExists = true;
            animalsList.splice(i, 1);
        }
    }
  
    if(checkExists === true) 
    {
        dbRepository.writeJSONFileAnimals(animalsList);
        res.status(200).send("Animal deleted!");
    } else {
        res.status(404).send("Animal not found!");
    }
  });


module.exports = router;