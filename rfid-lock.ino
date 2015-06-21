// link between the computer and the SoftSerial Shield
//at 9600 bps 8-N-1
//Computer is connected to Hardware UART
//SoftSerial Shield is connected to the Software UART:D2&D3 
 
#include <SoftwareSerial.h>
#define relay 6
 
SoftwareSerial rfid1(2, 3);
SoftwareSerial rfid2(4, 5);
char buffi[64];		// buffer array for data receive over serial port
int cards=4;		// number of cards
int count=0;		// counter for buffer array 
int i=0;
int a=0;

char card[cards][20] = { 
	// Add your RFID tags here
	// Example: { "0F0038C520D2" }
};

void setup() {
	rfid1.begin(9600);			// the SoftSerial baud rate
	rfid2.begin(9600);			// the SoftSerial baud rate
	Serial.begin(9600);			// the Serial port of Arduino baud rate.
	Serial.println("RFID Ready!");
	pinMode(relay, OUTPUT);
	digitalWrite(relay, LOW);
}
 
void loop() {
	while (rfid1.available()) {	// reading data into char array
		count++;
		buffi[count] = rfid1.read();
    
		// Sanity check
		if (count == 64)
			break;

		// The real work is here. 13 is the amount of chars you want from normal RFID cards
		if (count == 13) {
			if (check_buffer())
				valid_card();
			else
				Serial.println("INVALID card");
			clear_buffer();
			count=-1;
		}
	}
}

void valid_card(void) {
	Serial.println("Valid card");
	digitalWrite(relay, HIGH);
	delay(2000);
	digitalWrite(relay, LOW); 
}

void print_buffer(void) {
	for (i=0;i<=count;i++) {
		Serial.print(buffi[i]);
	}
	Serial.println();
}

int check_buffer(void) {
	for (a=0;a<cards;a++) {
		for(i=0;i<=count;i++) {
			if (card[a][i] != buffi[i+2])
				goto out;
		}
		return 1;
		out: ;
	}
	return 0;
}

void clear_buffer(void) {
	for(i=0;i<=count;i++)
		buffi[i]='\0';
}

