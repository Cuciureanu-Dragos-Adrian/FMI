const fs = require("fs");

function readJSONFileAnimals()
{
    return JSON.parse(fs.readFileSync("db.json"))["animals"];
}

module.exports.readJSONFileAnimals = () => {
    return JSON.parse(fs.readFileSync("db.json"))["animals"];
}

function readJSONFileUsers()
{
    return JSON.parse(fs.readFileSync("db.json"))["users"];
}

module.exports.readJSONFileUsers = () => {
    return JSON.parse(fs.readFileSync("db.json"))["users"];
}

function readJSONFileLogged()
{
    return JSON.parse(fs.readFileSync("db.json"))["logged"];
}

module.exports.readJSONFileLogged = () => {
    return JSON.parse(fs.readFileSync("db.json"))["logged"];
}

module.exports.writeJSONFileAnimals = (animal) => {
    let user = readJSONFileUsers();
    let log = readJSONFileLogged();

    fs.writeFileSync(
        "db.json",
        JSON.stringify({animals: animal, users: user, logged: log}, null, 4),
        "utf8",
        err => {
            if(err) {
                console.log(err);
            }
        }
    )
}

module.exports.writeJSONFileUsers = (user) => {
    let animal = readJSONFileAnimals();
    let log = readJSONFileLogged();

    fs.writeFileSync(
        "db.json",
        JSON.stringify({animals: animal, users: user, logged: log}, null, 4),
        "utf8",
        err => {
            if(err) {
                console.log(err);
            }
        }
    )
}

module.exports.writeJSONFileLogged = (log) => {
    let user = readJSONFileUsers();
    let animal = readJSONFileAnimals();
    
    fs.writeFileSync(
        "db.json",
        JSON.stringify({animals: animal, users: user, logged: log}, null, 4),
        "utf8",
        err => {
            if(err) {
                console.log(err);
            }
        }
    )
}