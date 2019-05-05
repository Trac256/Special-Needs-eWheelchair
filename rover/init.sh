#!/bin/sh

echo 17 > /sys/class/gpio/export
echo 27 > /sys/class/gpio/export
echo 22 > /sys/class/gpio/export
echo  5 > /sys/class/gpio/export
echo  6 > /sys/class/gpio/export
echo 13 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio17/direction
echo out > /sys/class/gpio/gpio27/direction
echo out > /sys/class/gpio/gpio22/direction
echo out > /sys/class/gpio/gpio5/direction
echo out > /sys/class/gpio/gpio6/direction
echo out > /sys/class/gpio/gpio13/direction