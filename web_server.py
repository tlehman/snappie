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
