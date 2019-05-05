#!/usr/bin/env python

import pygame
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

pygame.init()

# Αναζητηση του joystick
j = pygame.joystick.Joystick(0)
j.init()

print('Initialized Joystick : %s' % j.get_name())


# θυρες για τα μοτερ
MotorA0 = 27
MotorA1 = 22
MotorAE = 17

MotorB0 = 6
MotorB1 = 13
MotorBE = 5

A0 = 0
A1 = 0
B0 = 0
B1 = 0

#δηλωση εξοδων
GPIO.setup(MotorA0,GPIO.OUT)
GPIO.setup(MotorA1,GPIO.OUT)
GPIO.setup(MotorAE,GPIO.OUT)

GPIO.setup(MotorB0,GPIO.OUT)
GPIO.setup(MotorB1,GPIO.OUT)
GPIO.setup(MotorBE,GPIO.OUT)


# δηλωση ολων των μοτερ στο'off'
GPIO.output(MotorA0, A0)
GPIO.output(MotorA1, A1)
GPIO.output(MotorAE, 0)
GPIO.output(MotorBE, 0)
GPIO.output(MotorB0, B0)
GPIO.output(MotorB1, B1)


# δηλωση μεταβλητης για το κενο
threshold = 0.50

δηλωση joystick
LeftTrack = 0
RightTrack = 0


#ξεκινημα των μοτερ
def setmotors():
        GPIO.output(MotorA0, A0)
        GPIO.output(MotorA1, A1)
        GPIO.output(MotorAE, 1)
        GPIO.output(MotorBE, 1)
        GPIO.output(MotorB0, B0)
        GPIO.output(MotorB1, B1)

# ξεκινημα των μοτερ
try:
    # Turn on the motors
    GPIO.output(MotorAE, 1)
    GPIO.output(MotorBE, 1)

    # το κυριο προγραμμα
    while True:

        # οριζουμε την μεταβλητη για να τσεκαρουμε την κινηση
        events = pygame.event.get()
        for event in events:
          UpdateMotors = 0

          # τσεκαρουμε εαν το κατω η το πανω κινηται στα 2 joystick
          if event.type == pygame.JOYAXISMOTION:
            if event.axis == 1:
              LeftTrack = event.value
              print(event.value)
              UpdateMotors = 1
            elif event.axis == 4:
              RightTrack = event.value
              print(event.value)
              UpdateMotors = 1

            # τσεκαρουμε εαν χρειαζεται να κανει αλλαγη
            if UpdateMotors  == 1 :

              # τσεκαρουμε το ενα μοτερ

              # μπροστα
              if (RightTrack > threshold):
                  A0 = 0
                  A1 = 1
              # πισω
              elif (RightTrack < -threshold):
                  A0 = 1
                  A1 = 0
              # στοπ
              else:
                  A0 = 0
                  A1 = 0

              # τσεκαρουμε το αλλο μοτερ
              #μπροστα
              if (LeftTrack > threshold):
                  B0 = 0
                  B1 = 1
              # πισω
              elif (LeftTrack < -threshold):
                  B0 = 1
                  B1 = 0
              # σταματα
              else:
                  B0 = 0
                  B1 = 0

              setmotors()

except KeyboardInterrupt:
    # κλεισε τα μοτερ εαν πατησουμε κουμπι στο πληκτρολογιο
    GPIO.output(MotorAE, 0)
    GPIO.output(MotorBE, 0)
    j.quit()#!/usr/bin/env python

GPIO.cleanup()
