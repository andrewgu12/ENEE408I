from Adafruit_IO import Client
aio = Client('37dae49e09e64368b034e523c2bce404')
import pdb

check = 0
while True:
    if (check == 0):
        check = 20
        alexa = aio.receive('RobotInput')
        command = alexa[:1]
        print alexa.value

