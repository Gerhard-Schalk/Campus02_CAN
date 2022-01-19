#!/usr/bin/python3
import os
import can
import time

#os.system('sudo ip link set can0 up type can bitrate 100000')

can1 = can.interface.Bus(channel = 'can1', bustype = 'socketcan_ctypes') # socketcan_native

msg1 = can.Message(arbitration_id=0x000, data=[0x00], extended_id=False)
msg2 = can.Message(arbitration_id=0x000, data=[0x00], extended_id=False)

for i in range(0,10):
    can1.send(msg1, timeout=0.5 )
    print("send msg1 " + str(i))
    time.sleep(0.5)
    
    can1.send(msg2, timeout=0.5)
    print("send msg2 " + str(i))
    time.sleep(0.5)

#os.system('sudo ifconfig can0 down')
