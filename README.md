# RFIDAccessControl

## Introduction

This access control system by RFID cards was developed as a project for University. It keeps track of the registered RFID tags, storing them as users in a MongoDB database. Users can be added, updated or deleted through a web interface designed and run in Node-RED. It also stores in the database all the attempted accesses, and these are also easily visualized through the web interface. Users can also be added and deleted directly at the reader if a card with administrator permissions is used.

The system is composed of two main elements, the central node and the reader node. 

The central node is controlled by a Raspberry Pi in which the local MongoDB database and the control logic in Node-RED runs. The Raspberry Pi is connected via serial port to a NodeMCU board which uses to communicate to the reader nodes through ESP-NOW, which enables the system to work without the need of Wifi connection access. The Raspberry Pi needs internet access, which can be provided via ethernet cable if Wifi connection isn't available, in order to access the web interface.

The reader node is controlled by a NodeMCU board which manages the readings from a RC522 RFID reader, the visual feedback red and green leds and a relay used to open an electrical lock. The reader node communicates through ESP-NOW the readings to the central node and recieves from it the corresponding response behavior. The system is built so up to 19 reader nodes can be working at the same time, due to ESP-NOW limitations.

## Files

- MainPlacaSerial: this folder contains the files that will be used to program the NodeMCU board of the central node. The main file is MainBoardSerial.ino, and this will be the file that needs to be uploaded to the board from the Arduino IDE.

- MainPlacaLector: this folder contains the files that will be used to program the NodeMCU board of each of the reader nodes. The main file is MainBoardReader.ino, and this will be the file that needs to be uploaded to the board from the Arduino IDE.

- Node-RED_NodoCentral.json: This file contains the flows programmed in Node-RED. To import them, you just need to open the menu in the upper right corner, click “Import” > “Select file to import” and select the Node-RED_NodoCentral.json file. The database and serial nodes will need to be configured.

## Hardware connections

### Central node

![Esquema general nodo central](https://user-images.githubusercontent.com/50139839/171245515-ddfd1097-6249-42c1-ba79-8f4c9bf683ed.png)

### Reader nodes

![Diagrama general nodo lector](https://user-images.githubusercontent.com/50139839/171245837-fc95aad5-5413-4c5e-8db3-b52fff1bb247.jpg)
