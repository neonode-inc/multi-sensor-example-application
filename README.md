## About The Project

This project is aiming to provide a usable example to demonstrate how to use more than one Neonode touch sensor to create a larger area for contactless interaction. It allows for connecting up to four Neonode Touch sensors to a RPi4 and presenting them as a single absolute mouse input to the connected PC.

This project uses the [Neonode zForceSDK](https://support.neonode.com/docs/display/SDKDOC) for communicating with the Neonode touch sensors. It only supports 1-finger click and 1-finger panning.

*NOTE: This is not a finished product and should not be used as such.*

## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

In order to run this example, you'll need following hardware:

* [Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/specifications/)
* USB type-C male-to-male cable
* 5V 3A power supply
* Power supply to 2-pin 2.54mm header pin converter
* 2 or 4 Neonode Touch Sensor Modules
* 2 or 4 Neonode Interface Boards

### Hardware connections

```text
	                 _________________________________
	                |                                 |
	Sensor 1 -USB-> |                   40-pin header | <-2.54mm pitch 2-pin connector-> 5V 3A power supply
	Sensor 2 -USB-> | Raspberry Pi 4                  |
	Sensor 3 -USB-> | 1GB/2GB/4GB/8GB        Power in |
	Sensor 4 -USB-> |                        USB port | <-USB type-c cable-> Host computer
	                |_________________________________|
```

### And go through these software configuration steps:

#### Step 1. Enable Raspberry Pi 4 USB OTG capability

```sh
	echo "dtoverlay=dwc2" | sudo tee -a /boot/config.txt
	echo "dwc2" | sudo tee -a /etc/modules
	sudo echo "libcomposite" | sudo tee -a /etc/modules
```
*Reboot*:
```sh
	sudo reboot
```

#### Step 2. Clone the repo

```sh
	cd ~
	git clone https://github.com/neonode-inc/multi-sensor-example-application.git
```

#### Step 3. Create a USB gadget using the file `neonode_usb` from the repo

```sh
	sudo cp multi-sensor-app/Scripts/neonode_usb /usr/bin/neonode_usb
	sudo chmod 755 /usr/bin/neonode_usb
	sudo nano /etc/rc.local
```
Add the following before the line containing exit 0:
```sh
	/usr/bin/neonode_usb # libcomposite configuration
```
*Reboot*:
```sh
	sudo reboot
```
Now the raspberry pi should run the `neonode_usb` script on startup which creates the USB absolute mouse device.

### Installation

1. Clone the repo if have not done in previous steps
```sh
	git clone https://github.com/neonode-inc/multi-sensor-example-application.git
```
2. Install build tools
```sh
	sudo apt-get update
	sudo apt-get install build-essential
	sudo apt install libudev-dev
```
3. Build executable 
```sh
	cd multi-sensor-app
	make
```
4. Run executable 
```sh
	sudo ./app
```

### Configuration

1. Edit `Common.h` file under the Source folder with number of sensors, orientation and screen width and height of the host system.
```
	#define NUMBER_OF_SENSORS 2                     // Number of sensors connected to the raspberry pi. Example code supports 2 or 4.
	#define SENSOR_ORIENTATION_HORIZONTAL 1         // Which orientation the sensors are mounted on the screen. 0 for vertical (on the sides), 1 for horizontal (top and bottom).


	static const int32_t hostScreenWidth = 3000;    // Width of the screen which the raspberry pi will be sending touches to, unit is 1/10 mm.
	static const int32_t hostScreenHeight = 3000;   // Height of the screen which the raspberry pi will be sending touches to, unbit is 1/10 mm.
```

2. Rebuild the executable 
```sh
	make
```

### Usage

After running the application for the first time, the application will create a CSV file named `sensor_position.csv`. This file will contain the value for the sensor position and the sensors unique identifier. The values for the sensor positions are:
```C
	typedef enum SensorPosition
	{
	    SensorPositionTopLeft = 0,
	    SensorPositionBottomLeft = 1,
	    SensorPositionTopRight = 2,
	    SensorPositionBottomRight = 3
	} SensorPosition;
```
You must now modify the sensor positions in the CSV file to match your sensor configuration. **NOTE** the `sensor_position.csv` file is read during the startup of the application, so you need to restart the application after modifying it's content. If the application is unable to read the `sensor_position.csv` file, or if the file is missing a position for a sensor, the file will be created or overwritten with the current sensor positions and their unique identifiers.

For example a configuration with 2 sensors, one to the left, and one to the right, could have the following configuration
```sh
cat sensor_positions.csv
	0,280032000A51363334393737
	2,120033000A51363334393737	
```
### Mounting the sensors

Below are the four configurations supported by this example code
```text
                   4-Sensor setup                                         2-sensor setup

       HORIZONTAL 1            HORIZONTAL 0 (i.e. vertical)     HORIZONTAL 1        HORIZONTAL 0 (i.e. vertical)

    Top Left  Top Right     Top Left   Top Right                Top Left          Top Left   Top Right
     _______  _______          _         _                       _______             _          _
    |c______||______c|        |c|       |c|                     |c______|           |c|        |c|
                              | |       | |                                         | |        | |
                              |_|       |_|                                         |_|        |_|
     _______  _______          _         _                       _______             
    |c______||______c|        | |       | |                     |c______|
                              | |       | |
    Btm Left  Btm Right       |c|       |c|                     Btm Left

                           Btm Left   Btm Right

	                            c indicates the connector side of the touch sensor
```
The touch sensors should always be mounted so that there is room for the four sensor setup, this means that the connectors must be placed outward like in the illustration above. For instance, in horizontal configuration, the top left sensor should have it's cable coming out on the left side and same goes for the bottom left, while the top and bottom right sensors should have the cable coming out on the right side. This is also true for a two sensor setup which for example could be configured with one "Top Left", and one "Top Right" sensor.

The sensors opposite of each other (e.g. Btm Left and Btm Right in the vertical illustration above) must be of the same length so there are no gaps in the touch active area. In the four sensor configurations, both opposite pairs of sensors does not need to be the same size (e.g. In the vertical illustration Btm Left and Btm Right can have one length while Top Left and Top Right have another).
If for some reason you need to setup the touch sensors in a different way, you need to modify how their coordinates are mapped in the `TouchInfo * MapTouchCoordinates(TouchInfo *output, TouchInfo *input)` function in `Merger.c` file.

Note that the sensors cannot face each other directly, i.e. the light from one sensor should not be allowed to enter another sensors detection area. If it does interferences will occur, normally manifested like "ghost touches" appearing randomly over the active area. In order to avoid this there are some things that should be considered while mounting the sensors.

#### Point the sensors slightly upward

This will cause the light from one sensor to overshoot the sensor on the opposite side, and not to interfere with its optics. Overshooting by 2-3 cm should be sufficient, and can be achieved by simply placing a thin tape under the front side of the sensor.

#### Limit the overlapping area

Another way to minimize interference is to make the overlapping area between the sensors as small as possible. This is achieved by adjusting the sensors touch active area. For details check out [implementation examples](#support--examples).

## Troubleshooting

* "Unable to connect to device: (1106) Could not open file."  
Make sure the sensors are connected correctly. Make sure you are running the application with admin privileges (sudo).
* "Error: Unable to open hidg0 (absolute mouse)."  
Make sure to follow the configuration steps regarding the USB OTG capability. Make sure the `neonode_usb` script is running.
* "Error: Writing to hidg0 (absolute mouse): Resource temporarily unavailable."  
Sometimes the host system is busy and cannot receive the absolute mouse messages. This is not critical as the application will continue running but it might affect the user interaction.
* "Coordinates are inverted or wrong in the host system."  
Make sure the sensors are mounted correctly. Review the configurations in `Common.h` and the sensor positions in `sensor_position.csv`. Read [Configuration](#configuration), [Mounting the sensors](#mounting-the-sensors) and [Usage](#usage) for guidance.

## Known Issues

* The application is currently not able to detect if a sensor is disconnected. This is due to a known bug in zForceSDK that is planned to be fixed in the next release.

## Support & Examples

For help and support check out [Neonode Support](https://support.neonode.com/). There are illustrations and implementation examples on the support site in the **User's Guide** under **Implementation Examples**.

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This example code is licensed under the Unlicense, for more information refer to the `LICENSE` file.
