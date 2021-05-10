const uuid = require("uuid");

let dbRepository = require("../repository/dbRepository");

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
    adminList.push(newUser);
    dbRepository.writeJSONFileUsers(usersList);

    return newUser;
}

module.exports.changeLogged = (newLogged) => {
    dbRepository.writeJSONFileLogged(newLogged);
    return newLogged;
}