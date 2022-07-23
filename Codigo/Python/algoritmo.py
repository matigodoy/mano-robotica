import cv2
from cvzone.HandTrackingModule import HandDetector
import serial
import re

# Definimos la camara con el tamaño de la ventana
camara = cv2.VideoCapture(0)
camara.set(3, 1280)
camara.set(4, 720)

# Definimos el detector de dedos, con un margen de 80% de confiabilidad
detector = HandDetector(detectionCon=0.8, maxHands=1)

# Definimos valiables para esperar un cierto tiempo antes de mandar al arduino
dedosAnteriores = []
contador = 0

# definimos el puerto serial
mySerial = serial.Serial("COM4", 9600)

while True:
    # Obtenemos la imagen de la camara, es decir un frame
    success, imagen = camara.read()

    # Espejar camara
    camara_espejada = cv2.flip(imagen,1)
    
    # Busca la mano y los puntos de referencia
    camara_espejada = detector.findHands(camara_espejada)
    lmList, bboxInfo = detector.findPosition(camara_espejada)
    
    # Si encontro una mano en la imagen
    if lmList:
        # dedos es el array de dedos levantados
        dedos = detector.fingersUp()

        # Esto en general lo que hace es comparar los dedos leidos con los dedos anteriores para verificar si son iguales.
        # Si son iguales va a esperar x repeticiones para mandarle el comando al arduino.
        # Cada vez que se cambian los dedos, se resetea la lista dedosAnteriores y el contador.
        if(dedos == dedosAnteriores):
            contador += 1
            if(contador == 100): # valor del tiempo de espera
                print(f"Valores: {dedosAnteriores}")
                contador = 0
                dedosArduino = f"{dedos}" # Convierte la lista de dedos en un string
                dedosArduino = re.sub("\[|\,|\ |\]","",dedosArduino) # Elimina los corchetes, espacios y comas que hay en el string
                mySerial.write(dedosArduino.encode()) # Le mandamos los dedos al arduino
        else:
            dedosAnteriores = dedos.copy()
            contador = 0

        # Hace un cuadrado mostrando el array de los dedos
        bbox = bboxInfo['bbox']
        cv2.putText(camara_espejada, f'{dedos}', (bbox[0] + 200, bbox[1] - 30), cv2.FONT_HERSHEY_PLAIN, 2, (0, 255, 0), 2)
    
    # Abre la ventana con el output de la camara
    cv2.imshow("Mano Robotica", camara_espejada) 
    
    # Sale del while infinito con la 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Antes de cerrar el programa ponemos todos los dedos en 1
mySerial.write("11111".encode()) 

# Cierra el programa
camara.release()
cv2.destroyAllWindows()
# Cerramos el puerto serial
mySerial.close()