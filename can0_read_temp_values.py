#!/usr/bin/python3
import os
import can
import time

def BcdToString(value, leading_zeros=False):
    hexString = hex(value)[2:]

    if leading_zeros == False:
        return hexString
    else:
        return '0' *(2 - len(hexString)) + hexString

#os.system('sudo ip link set can0 up type can bitrate 1000000   dbitrate 8000000 restart-ms 1000 berr-reporting on fd on')

can0 = can.interface.Bus(channel = 'can0', bustype = 'socketcan_ctypes') # socketcan_native


while True:
    #Receive all temperature messages    
    for rx_msg in can0:

        #print(rx_msg)
        
        if(rx_msg.arbitration_id==0x000 and rx_msg.dlc==0):
            print("Temp CAN Node 4 = " + BcdToString(rx_msg.data[0]) + "." + BcdToString(rx_msg.data[1],True) + "°C")


#os.system('sudo ifconfig can0 down')