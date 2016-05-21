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
    var xhr = new XMLHttpRequest("PUT", "http://robot.local:5000");
    xhr.open(verb, path)
}
