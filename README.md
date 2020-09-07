# Roomba
The household pet that picks up after itself

## Repo Dependencies
+ Joystick node

## To upload code via command-line
### Setting up Arduino IDE
1. Download Linux version of the [Arduino IDE](https://www.arduino.cc/en/main/software)
2. Extract arduino folder to the downloads folder, then move it to /opt:  _(eg: ```arduino-#.#.#``` is ```arduino-1.8.5``` for arduino 1.8.5)_
```
cd Downloads/
sudo mv arduino-#.#.# /opt
```
3. Run the install.sh executable inside the arduino folder:
```
cd /opt/arduino-#.#.#/
sudo ./install.sh
```
4. Set permissions (give user access to Arduino when its plugged into USB)
```
sudo adduser $USER dialout
```
You'll need to log out and log back in for the changes to take effect

### Setting up Arduino makefile
Based on instructions here: https://github.com/sudar/Arduino-Makefile

1. `mkdir ~/dev && cd ~/dev/`
2. `git clone https://github.com/sudar/Arduino-Makefile.git`
3. Install PySerial `sudo apt-get install python-serial or sudo pip install pyserial`

### Uploading code
From the `/src/firmwware/` directory:
1. Compile code `make`
2. Upload the Arduino code `make upload`


## Pinout
+ Arduino-side:
  + Black: Ground
  + White: Pin 3
  + Grey: Pin 4
  + Purple: Pin 5
+ Roomba-side:
  + Black: Pin 6
  + White: Pin 4 (Roomba TX)
  + Grey: Pin 3 (Roomba RX)
  + Purple: Pin 5 (Device Detect)

## Startup
+ Click and hold roomba "on" button until a series of tones play - this changes the baud rate from the default 115200 to 19200 (what we'll be using)
+ `roslaunch roomba bringup_min.launch`


## Notes
+ List usergroups: `groups $USER`
+ Create udev rules for kinect (based on https://forum.openframeworks.cc/t/solved-linux-kinect-1473-on-of9/22031/3 and https://elinux.org/Accessing_Devices_without_Sudo)
    + `cd /etc/udev/rules.d`
    + `sudo gedit 66-kinect.rules`
+ Update udev rules: `sudo udevadm trigger`
+ Kinect cannot be plugged into a USB hub


https://cdn-shop.adafruit.com/datasheets/create_2_Open_Interface_Spec.pdf
 Serial sequence: [137] [Velocity high byte] [Velocity low byte] [Radius high byte] [Radius low byte]
 Available in modes: Safe or Full
 Changes mode to: No Change
 Velocity (-500 – 500 mm/s)
 Radius (-2000 – 2000 mm)
Special cases:
Straight = 32768 or 32767 = 0x8000 or 0x7FFF
Turn in place clockwise = -1 = 0xFFFF
Turn in place counter-clockwise = 1 = 0x0001

### Python to Arduino comms
  // Parse serial input from Python and convert to twistCmd
  // Data example 1: SL+100A+100E
  // Data example 2: SL-45A+30E

  // S = 83
  // L = 76
  // A = 65
  // E = 69
  // + = 43
  // - = 45
  // CR = 10

  // 0 = 48
  // 1 = 49
  // 2 = 50
  //  ...

### Arduino to Python comms
L_ENC
//value
R_ENC
//value

## TODO
+ implement heartbeat & e-stopped state
+ Add robustness check for serial
+ create state controller
+ get vacuum to work
