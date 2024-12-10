Code for running on a Seed Studio XIA nrf52840 (Sense) Board to record snowboarder metrics. 
Current metrics gathered are: 
X,Y,Z Acceleration 
X,Y,Z Gyroscope 
Location
Speed
Pressure

Sense Board should be used as the right boot which is responsible for the gathering all data, connectining with the left boot and being the central connecting with a phone for data transmission. 
A regular XIAO board can be used for the left boot which is only resposible for connecting the right boot and communicating the left boot pressure informaiton. 


Configurable Parameters: 
1. Number of sensors present on each boot (start pin placement starting from 0.02 ending with 0.05)

Pin input: 
0.02 SENS1    5V 
0.03 SENS2    GND
0.28 SENS3    3V3
0.29 SENS4    L/R BOARD SEL   1.15
0.04 SENS5    PAIRING BOARDS  1.14
0.05 SENS6    PAIRING PHONE   1.13
1.11 GPS RX           GPS TX  1.12

Operation Instructions: 
1. Set the Left and Right boot operation using a toggle switch for the given foot
2. pair the boards together by clicking the pairing board button on each board
3. advertise the the right board to a phone for visually seeing the data. 
4. Use the NRF Connect app on IOS.
5. Open up the scanning tab and fine a device that is called SNOW_HALO_R
6. Connect with the device.
7. Go to the Nordic UART Service section and enable notifications to allow data streaming.

