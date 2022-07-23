import cv2
from cvzone.HandTrackingModule import HandDetector
import serial
import time

# Definimos la camara con el tamaño de la ventana
cap = cv2.VideoCapture(0)
cap.set(3, 1280)
cap.set(4, 720)

# detector es el detector de dedos, con un margen de 80% de confiabilidad
detector = HandDetector(detectionCon=0.8, maxHands=1)

# definimos el puerto serial
mySerial = serial.Serial("COM4", 9600)

while True:
    # Obtenemos la imagen de la camara, es decir un frame
    success, img = cap.read()

    # Espejar camara
    camara_espejada = cv2.flip(img,1)
    
    # Busca la mano y los puntos de referencia
    camara_espejada = detector.findHands(camara_espejada)
    lmList, bboxInfo = detector.findPosition(camara_espejada)
    
    # Si encontro una mano en la imagen
    if lmList:
        # fingers es el array de dedos levantados y lo printeamos por consola
        fingers = detector.fingersUp()
        #print(f"Python: {fingers}")

        dedos = f"{fingers}"
        #print(dedos)

        mySerial.write(dedos.encode('ascii'))
        #time.sleep(1)

        rawString = mySerial.readline()
        print(f"Arduino {rawString}")

        #Esto hace un cuadrado mostrando el array de los dedos
        bbox = bboxInfo['bbox']
        cv2.putText(camara_espejada, f'{fingers}', (bbox[0] + 200, bbox[1] - 30), cv2.FONT_HERSHEY_PLAIN, 2, (0, 255, 0), 2)
    
    # Abre ventana con el output de la camara
    cv2.imshow("Camara cuantica 4k", camara_espejada) 
    
    # Esto cierra el programa con la q
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Esto cierra el programa
cap.release()
cv2.destroyAllWindows()
#cerramos el puerto serial
mySerial.close()
