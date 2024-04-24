# RC Car - LEGO Powered by Raspberry Pi CM4 with SaraKIT

Welcome to the official GitHub repository for the "RC Car - LEGO Powered by Raspberry Pi CM4 with SaraKIT" project, as featured on [Hackster.io](https://www.hackster.io/sarakit/rc-car-lego-powered-by-raspberry-pi-cm4-with-sarakit-dfc9ac). This project transforms a standard LEGO car into a remotely controlled vehicle using the power of Raspberry Pi CM4 and the versatility of the SaraKIT expansion board.

![shot2](https://github.com/SaraEye/SaraKIT-RCCar-Raspberry-Pi/assets/35704910/4dfd76ce-c000-4830-b9ab-237eaca09b63)

![RCCar_shot5](https://github.com/SaraEye/SaraKIT-RCCar-Raspberry-Pi/assets/35704910/dc234c7c-eb11-41fd-9563-134011135746)

## Overview

This RC Car project demonstrates how to integrate the SaraKIT with a Raspberry Pi Compute Module 4 to control a LEGO-based vehicle. It showcases not only the potential of combining traditional toys with modern technology but also the practical application of C++ programming in hardware control.

## Features

- **Remote Control via WiFi**: Control the direction and speed of the LEGO car using a custom-built remote controller application.
- **Live Camera Feed**: Stream live video from one or two cameras mounted on the car, providing a first-person view (FPV) driving experience.
- **Customizable Speed and Steering**: Detailed control over the car's speed and direction, with support for one or two-finger control schemes.
- **Cross-Platform Compatibility**: The remote controller software is built using Delphi FireMonkey, making it compatible with Android, iOS, and desktop platforms (PC/MAC).

## Getting Started

### Prerequisites

- Raspberry Pi CM4
- SaraKIT expansion board
- LEGO car setup or similar vehicle platform
- One or two compatible cameras (optional for FPV)
- Basic understanding of C++ and Raspberry Pi environment
- Two gimbal motors

### Installation

1. **Set Up Your Raspberry Pi**: Ensure that your Raspberry Pi CM4 is set up with the latest Raspberry Pi OS and connected to the same WiFi network as your remote control device (https://sarakit.saraai.com/getting-started/software)

2. **Connect the SaraKIT**: Attach the SaraKIT to your Raspberry Pi CM4 according to the instructions provided with the kit.

3. **Assemble Your RC Car**: Build your LEGO car or similar vehicle and integrate the motors and optional cameras with the SaraKIT and Raspberry Pi.

4. **Download and Install the Remote Controller Application**: Depending on your device, download the appropriate version of the remote control app from the provided links (coming soon).

5. **Deploy the C++ Code to Your Raspberry Pi**: Clone this repository and follow the build instructions below to compile and run the RC car control software.

```bash
git clone https://github.com/SaraEye/SaraKIT-RCCar-Raspberry-Pi rccar
cd rccar
make
./RCCar
```

## Example Code

The project includes a sample C++ application that demonstrates basic control logic for steering and speed management, as well as camera stream handling. 

## Contributing

Contributions to this project are welcome! Whether it's improving the control logic, adding new features, or creating tutorials, please feel free to fork this repository and submit your pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.

For more detailed instructions, troubleshooting, and other projects, please visit the [Hackster.io project page](https://www.hackster.io/sarakit/rc-car-lego-powered-by-raspberry-pi-cm4-with-sarakit-dfc9ac) and our home page: https://sarakit.saraai.com/

Happy building!


RCCar Python Version: https://github.com/SaraEye/SaraKIT-RCCar-Python-Raspberry-Pi
