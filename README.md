# Roomba
The household pet that picks up after itself

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
From the `/src/main/` directory:
1. Compile code `make`
2. Upload the Arduino code `make upload`


## Pinout
+ Arduino-side:
  + Black: Ground
  + White: Pin 11
  + Grey: Pin 10
+ Roomba-side:
  + Black: Pin 6
  + White: Pin 4 (TX)
  + Grey: Pin 3 (RX)
