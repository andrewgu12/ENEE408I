import numpy as np
import cv2
from skimage.morphology import dilation

cap = cv2.VideoCapture(1)

while(True):
    # capture frame by frame
    ret, frame = cap.read()
    print(ret)
    print(frame)
    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Display the resulting frame
    cv2.imshow('frame', gray)
    # quit by pressing q
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
