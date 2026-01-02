https://github.com/user-attachments/assets/d6160e7d-52ce-4d4e-ae52-41710bb968f2
## Initial Setup
This repository contains both the code for the Pi to run and the gerber file for the LED Matrix PCB. You may safely delete PCB.zip after uploading it to a fabrication service such as PCBWay or JLCPCB. In case you need the information, the dimensions for the board are 41.5x55mm.

## Hardware
This project requires the following components:

| Component              | Qty. |
|-----------------------:|------|
|3mm 3v LED              |    25|
|NPN Transistor*         |     5|
|1K Ohm Resistor         |     5|
|Male-Female Jumper Wires|    11|

*Any BJT such as 2N2222 or 2N3904 should do the trick

### Assembly
Assembly should be fairly straightforward, but **please ensure that...**
* The flat end of the transistors match the outline on the silkscreen
* The positive ends of the LEDs are wired to the **circular** holes, and the negative ends are wired to the **square** holes

### Connecting the Board to the Pi
If you are wiring individual jumper cables to the PCB inputs like I am, you may use this diagram to make sure each wire is connected to their respective pin:

![Wiring](https://github.com/user-attachments/assets/14fbdcd6-8513-49d9-bcbe-5b923fc96870)

## Software
Now that you have successfully soldered the components to the PCB and connected it to the Pi, it's time to run the software

### Compiling
If you haven't already cloned this repository on your Raspberry Pi, now is the time to do so.
```bash
cd /path/to/LedTextScroller4RaspberryPi
gcc -Wall -lwiringPi -o textWall.o textWall.c
```

### Usage
In the same directory, run
```bash
./textWall.o "Hello World " 75
```
In this case, "Hello World " is the message that you want to display, and 75 is the scroll speed. You may replace these values with anything you like.
*Note that smaller numbers result in faster scroll speeds, with 1 being the fastest and ((1<<63)-1) being the slowest*

Enjoy your new LED display!
