# RFID Access Control System

## Overview

This is an access control system that utilizes RFID cards to grant or deny access. This project was developed as my end-of-degree project for university, and it showcases my knowledge of developing and implementing an access control system using technologies such as Node-RED, MongoDB, and NodeMCU boards. The system is designed to keep track of registered RFID tags, store them as users in a MongoDB database, and allow administrators to manage these users through a web interface created through Node-RED. 

The system consists of two main components: the central node and the reader node. The central node is controlled by a Raspberry Pi, which runs the local MongoDB database and the control logic in Node-RED. The Raspberry Pi communicates with the reader nodes through a NodeMCU board, which is connected via serial port. The system is designed to work without a Wifi connection, as communication between the Raspberry Pi and the reader nodes is facilitated through ESP-NOW.

The reader node is also controlled by a NodeMCU board, which manages the readings from a RC522 RFID reader and provides visual feedback through red and green LEDs. The reader node communicates with the central node through ESP-NOW, and the system is built to support up to 19 reader nodes at a time.

## Repository Structure

The repository contains three main files:

- MainPlacaSerial: This folder contains the files needed to program the NodeMCU board for the central node. The main file is MainBoardSerial.ino, which should be uploaded to the board using the Arduino IDE.

- MainPlacaLector: This folder contains the files needed to program the NodeMCU board for each of the reader nodes. The main file is MainBoardReader.ino, which should be uploaded to the board using the Arduino IDE.

- Node-RED_NodoCentral.json: This file contains the Node-RED flows that were programmed for the project. To import them, simply open the menu in the upper right corner of the Node-RED interface, select “Import”, then “Select file to import”, and select the Node-RED_NodoCentral.json file. Note that the database and serial nodes will need to be configured.

## Hardware Connections

The system requires connections between the central node and the reader nodes. Diagrams for both the central node and reader nodes are provided below:

### Central Node

![Central Node Diagram](https://user-images.githubusercontent.com/50139839/171245515-ddfd1097-6249-42c1-ba79-8f4c9bf683ed.png)

### Reader Nodes

![Reader Node Diagram](https://user-images.githubusercontent.com/50139839/171245837-fc95aad5-5413-4c5e-8db3-b52fff1bb247.jpg)

## Features

- Register and manage RFID tags as users in a MongoDB database
- Easily visualize attempted accesses and manage users through a web interface designed and run in Node-RED
- Add and delete users directly at the reader node with a card with administrator permissions
- No Wifi connection required for system operation as communication between the central node and reader nodes is facilitated through ESP-NOW
- System is built to support up to 19 reader nodes at a time

## Possible future features

- Ability to set different access levels for users to certain areas controlled by different reader nodes
- Option to receive notifications through email or telegram for successful or unsuccessful access attempts
- Implement time-based access restrictions for users, such as only allowing access during certain hours of the day
- Ability to generate reports and track usage statistics for the system, including the number of access attempts, success rate, and user activity

## Setting it up

1. Install the required hardware components and connect them according to the diagrams provided above.
2. Download and install the Arduino IDE and required libraries (NodeMCU and RC522).
3. Program the NodeMCU boards for the central node and reader nodes using the MainBoardSerial.ino and MainBoardReader.ino files.
4. Download and install Node-RED on the Raspberry Pi.
5. Import the Node-RED flows by following the instructions in the repository.
6. Configure the serial and database nodes in Node-RED.
7. Add the required users to the MongoDB database through the web interface and assign them to their respective RFID tags.

## What I learned

During the development of this project, I learned about:

- Implementing an access control system using RFID technology.
- Connecting and communicating between different microcontrollers using ESP-NOW and Arduino.
- Storing and managing data in a MongoDB database.
- Developing a web interface for data visualization and management using Node-RED.
- Interfacing with different components, such as RFID readers, LEDs, and the Raspberry Pi.
- Consolidation of the concept of state-machines applying it to this example.

## Conclusion

The RFID Access Control System is a great showcase of my knowledge and skills in developing and implementing an access control system using a range of technologies. The system is robust, reliable, and easy to use, making it an excellent choice for controlling access to secure areas. With its range of features, it offers the flexibility to be adapted to a variety of use cases and applications while being reasonably cheap and easy to implement.
