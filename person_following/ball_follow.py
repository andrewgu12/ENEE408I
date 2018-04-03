import cv2
import sys
import numpy as np
from skimage.morphology import dilation
# import serial
# from Adafruit_IO import Client
# ser = serial.Serial('COM4', 9600, timeout=0)
# aio = Client('285ffbe7f2f14f9ab047842600bd13c8')

# Set up capture device
cap = cv2.VideoCapture(1)
cap.set(6,10) # Set frame rate (set to 10)

# Set up windows with sliders
cv2.namedWindow('image')
cv2.namedWindow('mask')

found = 0; recent = 'R'; alexa = 0; check = 0; help = 0; hcheck = 0; followcount = 0; stopcount = 0; command = '0'; commandCount = 0; turncount = 0;
while True:
    # Image
    re, img = cap.read()
    
    # Convert image to HSV
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # Threshold hsv image within hue range
    minHue = 27
    maxHue = 37 
    minSaturation = 110
    maxSaturation = 255
    minValue = 110
    maxValue = 255
    mask = 255 * (
                    (hsv[:,:,0] > minHue) & (hsv[:,:,0] < maxHue) \
                  & (hsv[:,:,1] > minSaturation) & (hsv[:,:,1] < maxSaturation) \
                  & (hsv[:,:,2] > minValue) & (hsv[:,:,2] < maxValue) \
                 ).astype(np.uint8)

    # Dilate mask to remove holes from noise
    mask = dilation(mask, np.ones((3, 3)))
    cv2.imshow('mask', mask) # display mask here because findContours modifies it

    # Find contours in image
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    try:
        largestContourIdx = np.argmax([len(c) for c in contours])
        #cv2.drawContours(img, contours, largestContourIdx, (0,255,0), 3)
        (x,y),radius = cv2.minEnclosingCircle(contours[largestContourIdx])
        center = (int(x),int(y))
        #print(center)
        radius = int(radius)
        if radius >= 9:
            cv2.circle(img,center,radius,(0,255,0),2)
            cv2.circle(img,center,2,(0,255,0),0)
            found = 1;
        pass
    except:
        found = 0;
        pass

    
    # Display images
    cv2.imshow('image', img)

    # Exit if q is pressed
    if cv2.waitKey(1) == ord('q'):
        serial.write('H'.encode('ascii'))
        sys.exit(0)
        break
    
    # # Get instruction from Adafruit_IO (Echo Dot)
    # if(check == 0):
    #     check = 20
    #     alexa = aio.receive('408i-robot-control.robot-drive').value
    #     command = alexa[:1]
    #     #print(alexa.value)
    # check = check - 1
    # if(hcheck == 0):
    #     hcheck = 120
    #     help = aio.receive('408i-robot-control.help').value
    #     if help == '0':
    #         ser.write('N'.encode('ascii'))
    #     elif help == '1':
    #         ser.write('E'.encode('ascii'))
    #         print("HELP")
    # hcheck = hcheck - 1;
    # # Determine if command should be reversed
    # if alexa == "11":
    #     followcount = followcount + 1;
    #     stopcount = 0
    #     print("Follow command detected, followcount = %d" % followcount)
    #     alexa = "10"
    #     aio.send('408i-robot-control.robot-drive', '10')
    # if alexa == "01":
    #     stopcount = stopcount + 1;
    #     followcount = 0
    #     print("Stop command detected, stopcount = %d" % stopcount)
    #     alexa = "00"
    #     aio.send('408i-robot-control.robot-drive', '00')
    
    # if followcount > 4:
    #     followcount = 0
    #     print('TOO MANY FOLLOW REQUESTS, RUNNING STOP')
    #     aio.send('408i-robot-control.robot-drive','00')
    # if stopcount > 4:
    #     stopcount = 0;
    #     print('TOO MANY STOP REQUESTS, RUNNING FOLLOW')
    #     aio.send('408i-robot-control.robot-drive','10')
    
    # if(found):
    #     if commandCount > 200:
    #         if help == '1':
    #             aio.send('408i-robot-control.help', '0')
    #             help = '0'
    #     commandCount = 0
    # else:
    #     commandCount = commandCount + 1
    #     if commandCount > 200:
    #         if help == '0':
    #             aio.send('408i-robot-control.help', '1')
    #             help = '1'
    
    # # Send Directions to Arduino
    # if command == '0':
    #     #print('HOLD')
    #     ser.write('H'.encode('ascii'))
    # elif command == '1':
    #     commandCount = 0;
    #     #print('FOLLOW')
    #     if(found):
    #         xloc = int(x)
    #         if xloc < 200: #Left
    #             ser.write('L'.encode('ascii'))
    #             recent = 'L'
    #             #print('L')
    #         elif xloc > 400: #Right
    #             ser.write('R'.encode('ascii'))
    #             recent = 'R'
    #             #print('R')
    #         else: #Forward
    #             ser.write('F'.encode('ascii'))
    #             #print('F')
    #     else:
    #         if recent == 'L': #Search Left
    #             ser.write('Y'.encode('ascii'))
    #             #print('Y')
    #         elif recent == 'R': #Search Right
    #             ser.write('X'.encode('ascii'))
    #             #print('X')
    # elif command == '2':
    #     turncount = turncount + 1
    #     if turncount < 100:
    #         ser.write('X'.encode('ascii'))
    #     else:
    #         ser.write('H'.encode('ascii'))
    # elif command == '3':
    #     commandCount = 20
    #     while commandCount > 0:
    #         commandCount = commandCount - 1
    #         ser.write('E'.encode('ascii'))
    #     commandCount = 10
    #     while commandCount > 0:
    #         commandCount = commandCount - 1
    #         ser.write('N'.encode('ascii'))
    #     commandCount = 20
    #     while commandCount > 0:
    #         commandCount = commandCount - 1
    #         ser.write('E'.encode('ascii'))
    #     commandCount = 10
    #     while commandCount > 0:
    #         commandCount = commandCount - 1
    #         ser.write('N'.encode('ascii'))
    #     commandCount = 40
    #     while commandCount > 0:
    #         commandCount = commandCount - 1
    #         ser.write('E'.encode('ascii'))
    #     ser.write('N'.encode('ascii'))
    #     commandCount = 40
    #     while commandCount > 0:
    #         commandCount = commandCount - 1
    #         ser.write('R'.encode('ascii'))
    #     commandCount = 80
    #     while commandCount > 0:
    #         commandCount = commandCount - 1
    #         ser.write('L'.encode('ascii'))
    #     commandCount = 400
    #     while commandCount > 0:
    #         commandCount = commandCount - 1
    #         ser.write('R'.encode('ascii'))
    #     ser.write('H'.encode('ascii'))
    #     command == '0'
    #     sys.exit(0)
