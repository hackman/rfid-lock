This is a simple project aiming to create RFID electric lock for my home.

Required parts:
- Arduino
- RFID reader
- Relay

I used SeeedStudio 125KHz RFID reader - http://www.seeedstudio.com/depot/Grove-125KHz-RFID-Reader-p-1008.html

The RFID readers are connected to Digital pins 2 & 3, and 4 & 5.
The relay is connected to Digital pin 7.

Once you add your RFID tags to the card array evry time the arduino detects a valid RFID tag it will open the relay for 2seconds.

TODO: 
- Make the card array dynamic
- Add a push button to activate card learning

