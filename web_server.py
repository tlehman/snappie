#!/usr/bin/env python
# by tlehman
# Web server to enable manual control of GoPiGo robot
from flask import Flask
import gopigo
app = Flask(__name__)

# GET /
#    returns the static page remote control
@app.route("/")
def control():
    return open('static/control.html').read()

# GET /css/*
#    returns the static page remote control
@app.route("/css/<stylesheet>")
def static_css(stylesheet):
    return open('static/css/%s' % stylesheet).read()

# GET /js/*
#    returns the static page remote control
@app.route("/js/<javascript>")
def static_js(javascript):
    return open("static/js/%s" % javascript).read()

# GET /*.(png.ico)
#    returns the static page remote control
@app.route("/<img>")
def static_img(img):
    if img == "static/gerty.png":
        return open(img).read()
    elif img == "static/favicon.ico":
        return open(img).read()


# PUT /move/{forward, backward, left, right}
@app.route("/move/<direction>", methods=['PUT'])
def move(direction):
    message = "Move %s\n" % direction
    if direction == 'forward':
        gopigo.fwd()
    elif direction == 'backward':
        gopigo.bwd()
    elif direction == 'left':
        gopigo.left()
    elif direction == 'right':
        gopigo.right()
    else:
        message = "Error: '%s' is not a valid direction" % direction
    return message

# PUT /speed/{up, down}
@app.route("/speed/<change>", methods=['PUT'])
def speed(change):
    message = "Speed %s\n" % change
    if change == "up":
        gopigo.increase_speed()
    elif change == "down":
        gopigo.decrease_speed()
    else:
        message = "Error: '%s' is not a valid change in speed" % change

    return message

# PUT /stop
@app.route("/stop", methods=['PUT'])
def stop():
    gopigo.stop()
    return "Stopped\n"

if __name__ == "__main__":
    app.run(host='0.0.0.0')
