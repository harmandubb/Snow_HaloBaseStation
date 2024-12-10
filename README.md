# Snowboarder Metrics Recording System

**Code for running on a Seeed Studio XIAO nRF52840 (Sense) Board to record snowboarder metrics.**

This project enables real-time data collection from snowboarders' boots to enhance riding performance and provide valuable feedback.

---

## **Features**

The current metrics gathered are:

- **Acceleration**: X, Y, Z
- **Gyroscope**: X, Y, Z
- **Location** (GPS)
- **Speed**
- **Pressure**

---

## **System Overview**

- The **Sense Board** is used for the **right boot**, responsible for:
  - Gathering all metrics.
  - Connecting with the left boot.
  - Acting as the central hub for **data transmission to a phone**.

- A **regular XIAO board** can be used for the **left boot**, responsible for:
  - Connecting with the right boot.
  - Transmitting left boot pressure information.

---

## **Configurable Parameters**

### **Sensor Configuration**
- Specify the number of sensors on each boot.
- Start pin placement at **0.02** and end at **0.05**.

### **Pin Mapping**

| Pin   | Function                     |
|-------|------------------------------|
| 0.02  | SENS1                        |
| 0.03  | SENS2                        |
| 0.28  | SENS3                        |
| 0.29  | SENS4                        |
| 0.04  | SENS5                        |
| 0.05  | SENS6                        |
| 1.11  | GPS RX                       |
| 1.12  | GPS TX                       |
| 1.13  | Pairing Phone Button         |
| 1.14  | Pairing Boards Button        |


---

## **Operation Instructions**
1. Set the Left and Right boot operation using a toggle switch for the given foot
2. pair the boards together by clicking the pairing board button on each board
3. advertise the the right board to a phone for visually seeing the data. 
4. Use the NRF Connect app on IOS.
5. Open up the scanning tab and fine a device that is called SNOW_HALO_R
6. Connect with the device.
7. Go to the Nordic UART Service section and enable notifications to allow data streaming.





