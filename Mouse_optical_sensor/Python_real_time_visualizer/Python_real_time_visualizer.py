from tkinter import *
import time
import serial

SIZE = 18
UPDATE_RATE = 100

pixels = [0]*(SIZE**2)

BAUD_RATE = 115200

time.sleep(1)

def get_port_name():
	for i in range(0, 256):														# Select right port (GNU/Linux and Windows)
		for serial_name in ['/dev/ttyUSB', '/dev/ttyACM', 'COM']:
			try:
				arduino = serial.Serial(serial_name+str(i), BAUD_RATE, timeout=.1)
				for times in range(0, 100):
					data = arduino.readline()[:-2]
					if data:
						return serial_name+str(i)
			except KeyboardInterrupt:
					return 'STOP'
			except:
				pass
	return ''

port = ''
while port == '':
    port = get_port_name()

print('Connecting to port', port)

if port == 'STOP':
    exit()

arduino = serial.Serial(port, BAUD_RATE, timeout=.5)
time.sleep(1)
arduino.write('OK'.encode())
time.sleep(1)
while arduino.read():
    pass
arduino.write('R'.encode())
time.sleep(2)

def create_grid(width, height, pixels_grid):
    color = '#cccccc'

    for y in range(height):
        for x in range(width):
            pixels[SIZE - 1 - y + x*SIZE] = Button(pixels_grid, background=color, state='disabled')
            pixels[SIZE - 1 - y + x*SIZE].grid(column = x, row = (y + 1), sticky = (N+S+E+W))

    for x in range(width):
        Grid.columnconfigure(pixels_grid, x, weight = 1)

    for y in range(height):
        Grid.rowconfigure(pixels_grid, (y + 1), weight = 1)
        
    updater()

def updater():
    sensor_pixels = arduino.readline()[:-2]     # Remove \r\n
#    print(sensor_pixels)
    for i in range(SIZE**2):
        pixels[i]['background']='#'+('%02x'%(round((sensor_pixels[i] & 0b00111111)/(2**6-1)*(2**8))))*3
    arduino.write('R'.encode())
    pixels_grid.after(UPDATE_RATE, updater)
        
pixels_grid = Tk()
pixels_grid.geometry("650x650")
create_grid(SIZE, SIZE, pixels_grid)
pixels_grid.mainloop()
