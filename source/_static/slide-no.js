$().ready(function() {
    var articles = $("#slide_container article.slide")
    var i = 0;
    while (i < articles.length) {
        var div = document.createElement("div");
        div.className += " slide-no";
        div.textContent = "" + (i+1) + "/" + articles.length;
        articles[i].appendChild(div);
        i += 1;
    }
})
