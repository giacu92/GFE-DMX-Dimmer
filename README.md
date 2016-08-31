# DMX-Dimmer (currently under update..)
DIY 5 channels dmx dimmer for 4 stage halogen lights

* Author: Giacomo Mammarella
* email: giacomo.mammarella@student.univaq.it
* [YouTube](https://www.youtube.com/watch?v=KfEGCJoeCmY): testing video

# About software:
The software is based on a finite state machine. The DMX start address can be choosen on the software  modifying "#define DMX_START_ADDRESS 65".
The DMX channels are currently set like following:
* DMX CHANNEL 65: lamp 1 dimmer (0 -> 100% fade)
* DMX CHANNEL 66: lamp 2 dimmer 
* DMX CHANNEL 67: lamp 3 dimmer 
* DMX CHANNEL 68: lamp 4 dimmer 
* DMX CHANNEL 69: strobo all lamps at chosen speed (0 to 1s)

# File list:
* [DMX_dimmer.brd](https://github.com/giacu92/DMX-Dimmer/blob/master/DMX_dimmer.brd): the Cadsoft Eagle 6.5 board file.
* [DMX_dimmer.sch](https://github.com/giacu92/DMX-Dimmer/blob/master/DMX_dimmer.sch): the Cadsoft Eagle 6.5 schematic file for the board.
* [dmx_dimmer.ino](https://github.com/giacu92/DMX-Dimmer/blob/master/dmx_dimmer.ino): the Arduino sketch for the project.

# Connections:
![Board](http://i66.tinypic.com/nwhfls.png)

# Some pics:
Painting the enclosure and test fitting the pcb:
![PIC1](http://i67.tinypic.com/mtaux3.jpg)
