import RPi.GPIO as GPIO
import time
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

MotorA0 = 27
MotorA1 = 22
MotorAE = 17

MotorB0 = 6
MotorB1 = 13
MotorBE = 5

#IR SENSORS
S1=14
S2=15
S3=18
S4=23
S5=24

#Δηλωση εξοδων
GPIO.setup(MotorA0,GPIO.OUT)
GPIO.setup(MotorA1,GPIO.OUT)
GPIO.setup(MotorAE,GPIO.OUT)
GPIO.setup(MotorB0,GPIO.OUT)
GPIO.setup(MotorB1,GPIO.OUT)
GPIO.setup(MotorBE,GPIO.OUT)

#Δηλωση εισοδων
GPIO.setup(S1,GPIO.IN)
GPIO.setup(S2,GPIO.IN)
GPIO.setup(S3,GPIO.IN)
GPIO.setup(S4,GPIO.IN)
GPIO.setup(S5,GPIO.IN)
#Κυριo loop
while 1:

    if (GPIO.input(S3) == 1 and GPIO.input(S2)== 0 and GPIO.input(S1)== 0 and GPIO.input(S4)== 0 and GPIO.input(S5)== 0): #εαν ο μεσος σενσορας ειναι ανοιχτος προχωρανε μποστα και τα 2 μοτερ    
        GPIO.output(MotorA0, 0)
        GPIO.output(MotorA1, 1)
        GPIO.output(MotorAE, 1)
        GPIO.output(MotorB0, 0)
        GPIO.output(MotorB1, 1)
        GPIO.output(MotorBE, 1)

    elif(GPIO.input(S3) == 1 and GPIO.input(S2)== 1 and GPIO.input(S1)== 0): #εαν ο μεσος σενσορας και ο s2 ειναι ανοιχτος σταματα το ενα μοτερ 
        GPIO.output(MotorA0, 0)
        GPIO.output(MotorA1, 1)
        GPIO.output(MotorAE, 1)
        GPIO.output(MotorB0, 0)
        GPIO.output(MotorB1, 0)
        GPIO.output(MotorBE, 1)
    elif(GPIO.input(S3) == 1 and GPIO.input(S4)== 1 and GPIO.input(S5)== 0): #εαν ο μεσος σενσορας και ο s4 ειναι ανοιχτος σταματα το ενα μοτερ  
        GPIO.output(MotorA0, 0)
        GPIO.output(MotorA1, 0)
        GPIO.output(MotorAE, 1)
        GPIO.output(MotorB0, 0)
        GPIO.output(MotorB1, 1)
        GPIO.output(MotorBE, 1)
    elif(GPIO.input(S2) == 1 or GPIO.input(S1)== 1): #εαν ο s2 και ο s1 ειναι ανοιχτος το ενα μοτερ παει μπροστα το αλλο πισω 
        GPIO.output(MotorA0, 1)
        GPIO.output(MotorA1, 0)
        GPIO.output(MotorAE, 1)
        GPIO.output(MotorB0, 0)
        GPIO.output(MotorB1, 1)
        GPIO.output(MotorBE, 1)
    elif(GPIO.input(S4) == 1 or GPIO.input(S5)== 1): #εαν ο s4 και ο s5 ειναι ανοιχτος το ενα μοτερ παει μπροστα το αλλο πισω 
        GPIO.output(MotorA0, 0)
        GPIO.output(MotorA1, 1)
        GPIO.output(MotorAE, 1)
        GPIO.output(MotorB0, 1)
        GPIO.output(MotorB1, 0)
        GPIO.output(MotorBE, 1)
    else:
        GPIO.output(MotorA0, 0)
        GPIO.output(MotorA1, 0)
        GPIO.output(MotorAE, 0)
        GPIO.output(MotorB0, 0)
        GPIO.output(MotorB1, 0)
        GPIO.output(MotorBE, 0)