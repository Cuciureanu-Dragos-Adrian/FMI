const express = require("express");
const app = express();

app.get('/cuvinte',function(req, res){
  
    dictionar = [
        {
            cuvant:"carte", traducere:"book"
        }, 
        {
            cuvant:"floare", traducere:"flower"
        }, 
        {
            cuvant:"tablou", traducere:"picture"
        }, 
        {
            cuvant:"film", traducere:"movie"
    }]
  
  let cuvant = req.query.cuvant;
  var traducere = [];
  var ok = 0;
  
  for(var c of dictionar){
    if (c.cuvant == cuvant){
        traducere.push(c.traducere);
        ok = 1;
    }
  }
  
  if(ok == 0){
      res.send("Nu exista cuvantul cautat");
  }
  else{
    res.send(traducere);
  }
});

app.listen(5000, ()=>{
  console.log("Server pornit la portul 5000");
})
