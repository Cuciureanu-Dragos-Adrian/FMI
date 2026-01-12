const uuid = require("uuid");

let dbRepository = require("../repository/dbRepository");

//get

module.exports.getAllAnimals = () => {
    const animalsList = dbRepository.readJSONFileAnimals();
    return animalsList;
}

module.exports.getAllUsers = () => {
    const usersList = dbRepository.readJSONFileUsers();
    return usersList;
}

module.exports.getLogged = () => {
    const logged = dbRepository.readJSONFileLogged();
    return logged;
}

//add

module.exports.addAnimal = (newAnimal) => {
    const animalsList = dbRepository.readJSONFileAnimals();
    newAnimal.id = uuid.v4.apply();
    animalsList.push(newAnimal);
    dbRepository.writeJSONFileAnimals(animalsList);

    return newAnimal;
}

module.exports.addUser = (newUser) => {
    const usersList = dbRepository.readJSONFileUsers();
    newUser.id = uuid.v4.apply();
    usersList.push(newUser);
    dbRepository.writeJSONFileUsers(usersList);

    return newUser;
}

//change

module.exports.changeLogged = (newLogged) => {
    dbRepository.writeJSONFileLogged(newLogged);
    return newLogged;
}