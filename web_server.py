#!/usr/bin/env python
# by tlehman
# Web server to enable manual control of GoPiGo robot
from flask import Flask
import cv2
#import gopigo
import base64
app = Flask(__name__)

# GET /
#    returns the static page remote control
@app.route("/")
def control():
    return open('static/control.html').read()

def current_img():
    cap = cv2.VideoCapture(0)
    cap.set* 1
    success, frame = cap.read()
    cap.release()
    return frame

# Return the current image as a base64-encoded png
def current_img_b64():
    b64 = None
    frame = current_img()
    if frame != None:
        png = cv2.imencode('.png', frame)[1]
        b64 = base64.encodestring(png)
    return b64

# GET /see
#    returns the current image
@app.route("/see")
def see():
    enc = current_img_b64()
    html = None

    if enc == None:
        html = "Could not capture image"
    else:
        html = "data:image/png;base64,%s" % enc
    return html

# PUT /move/{forward, backward, left, right}
@app.route("/move/<direction>", methods=['PUT'])
def move(direction):
    message = "Move %s\n" % direction
    print message
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
    print message
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
    print "Stopped"
    return "Stopped\n"

if __name__ == "__main__":
    app.run(host='0.0.0.0')
