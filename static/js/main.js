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
    xhr.open(verb, path)
}
