#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  9 00:44:19 2020

@author: malay
Sample code for GPIO, SPI and I2C using FT232h and python on desktop
Requires Adfruit Blinka 
Run this line on terminal before running this program
    set BLINKA_FT232H=1
"""
import time
import board
import busio
import digitalio

# import usb
#dev = usb.core.find(idVendor=0x0403, idProduct=0x6014)

# =============================================================================
# GPIO OUTPUT
# =============================================================================

led = digitalio.DigitalInOut(board.C0)
led.direction = digitalio.Direction.OUTPUT

i=0 
while i<8:
    led.value = True
    time.sleep(0.5)
    led.value = False
    time.sleep(0.5)
    i = i+1


# =============================================================================
# GPIO INPUT
# =============================================================================    
    
led = digitalio.DigitalInOut(board.C0)
led.direction = digitalio.Direction.INPUT

i=0 
while i<10:
    print(led.value)  
    time.sleep(0.4)
    i = i+1

# =============================================================================
# SPI
# =============================================================================
# (Activate pins SCK, MOSI and MISO on the board)
spi = busio.SPI(board.SCK, board.MOSI, board.MISO) #SCK=D0, MOSI=D1, MISO=D2
# use pin C0 as CS output:
cs = digitalio.DigitalInOut(board.C0) #set pin C0 on the board as CS
cs.direction = digitalio.Direction.OUTPUT #direction: CLK is output (PC is master)

# CLK is high: in SPI protocol this means communication is off:
cs.value = True


spi.try_lock() # gets a lock
baudrate = 25000000 # freq = 25MHz
spi.configure(baudrate, phase=0, polarity=0) #configure values

# Communicate something:

cs.value = False #cs off = communication on
time.sleep(1) 
spi.write(bytes([0xD0, 0x00,])) # send bytes A1 and D0   
time.sleep(1) # 1 second delay
cs.value = True #cs on = communication off

spi.unlock()

# =============================================================================
# I2C
# =============================================================================

# Create library object using our Bus I2C port
# SCL = D0
# SDA = D1 = D2
i2c = busio.I2C(board.SCL, board.SDA)
i2c.init(board.SDA,board.SCL,100000)  #freq = 100000
address = 0x01
bufferOut = [0]
bufferIn = [0]

i2c.try_lock() # initiates communication
i2c.writeto_then_readfrom(address,bufferOut, bufferIn)
i2c.unlock() # releases lock


 
