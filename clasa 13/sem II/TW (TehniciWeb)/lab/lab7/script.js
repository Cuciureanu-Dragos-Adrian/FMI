function ChangeStyle ()
{
    let stil = document.getElementsByTagName ("body");
    stil[0].style.fontFamily = "Arial, sans-serif";
}

function getSpan ()
{
    let span1 = document.getElementById ("nickname");
    let span2 = document.getElementById ("favorites");
    let span3 = document.getElementById ("hometown");
    span1.innerText = "/";
    span2.innerText = ".";
    span3.innerText = "/";

}

function getLi ()
{
    let ceva = document.getElementsByTagName ("li");
    for (let i =0; i < ceva.length; i++)
    {
        ceva[i].classList.add("list-item");
    }
}

function putImage ()
{
    let img = document.createElement ("img");
    img.setAttribute ("src", "poza.jpg");
    let body = document.getElementsByTagName ("body");
    body[0].appendChild(img);
}

window.onload = function ()
{
    ChangeStyle();
    getSpan ();
    getLi ();
    putImage ();
}