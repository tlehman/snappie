function see() {
    request("GET", "/see");
}

function move(direction) {
    request("PUT", "/move/" + direction);
}

function speed(change) {
    request("PUT", "/speed/" + change);
}

function stop() {
    request("PUT", "/stop");
}

function request(verb, path) {
    var xhr = new XMLHttpRequest();
    xhr.open(verb, path);
    xhr.send();
    xhr.onreadystatechange = function() {
        eyes = document.getElementById("eyes");
        eyes.src = xhr.responseText;
    }
}

function main() {
    see();
    window.setInterval(see, 1000);
}

main();
