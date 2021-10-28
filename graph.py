import serial 
import time 
import collections
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.lines import Line2D
import numpy as np 



def getSerialData(self,Samples,numData,serialConnection, lines):
    for i in range(numData):
        value =int(serialConnection.readline().strip()) #Leer sensor
        data[i].append(value) #Guarda lectura en la ultima posicion
        lines[i].set_data(range(Samples),data[i]) #Dibujar nueva linea

serialPort = 'COM14' #Puerto serial Arduino
baudRate = 9600 #Baudios

serialConnection = serial.Serial(serialPort, baudRate)

try: 
    serialConnection = serial.Serial(serialPort, baudRate) #Instancias objeto serial
    
except: 
    print ('Cannot conect to the port')

Samples = 100 #Muestras
sampleTime = 200 #Tiempo de muestreo
numData = 3 #Numero de sensores 

#Limites de los ejes

xmin = 0 
xmax = Samples
ymin = [0, 0, 0, 0]
ymax = [400, 400, 400, 400]
lines = []
data = []

for i in range(numData): 
    data.append(collections.deque([0] * Samples, maxlen=Samples))
    lines.append(Line2D([], [], color = 'red'))

fig = plt.figure () #Crea una uneva figura
ax1 = fig.add_subplot(2, 2, 1,xlim=(xmin, xmax), ylim=(ymin[0], ymax[0]))
ax1.title.set_text('Sensor Ultrasonico')
#ax1.set_xlabel("Samples")
ax1.set_ylabel("Centimetros")
ax1.add_line(lines[0])


ax2 = fig.add_subplot(2, 2, 2,xlim=(xmin, xmax), ylim=(ymin[1], ymax[1]))
ax2.title.set_text('RPM rueda derecha')
ax2.set_xlabel("Samples")
ax2.set_ylabel("RPM")
ax2.add_line(lines[1])


ax3 = fig.add_subplot(2, 2, 3,xlim=(xmin, xmax), ylim=(ymin[2], ymax[2]))
ax3.title.set_text('RPM rueda izquierda')
ax3.set_xlabel("Samples")
ax3.set_ylabel("RPM")
ax3.add_line(lines[2])

#ax4 = fig.add_subplot(2, 2, 1,xlim=(xmin, xmax), ylim=(ymin[3], ymax[3]))
#ax4.title.set_text('Fourth Plot')
#ax4.set.xlabel("Samples")
#ax4.add_line(lines[0])

anim = animation.FuncAnimation(fig,getSerialData, fargs=(Samples,numData,serialConnection,lines), interval=sampleTime)
plt.show()

serialConnection.close() #Close serial port
