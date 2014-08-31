// This #include statement was automatically added by the Spark IDE.
#include "XBee.h"

#include "XBee.h"

XBee xbee = XBee();

void setup() {
    // Begin serial
    Serial1.begin(9600);
    Serial.begin(9600);
    
    // Start XBee
    xbee.begin(Serial1);
    
    // Define Spark Code function
    Spark.function("sendcmd", controlRemoteLED);    
}

void loop() {
   
}

int controlRemoteLED(String args){
	Serial.print("Received address: ");
	Serial.println(args);

	// If we have arguments in correct format
	if(args.length() >= 26){
		char szS1[9];
		char szS2[9];
		char szS3[5];
		char szS4[3];

		// Parse arguments it will be in the format XXXXXXXXXXXXXXXX,XXXX,XX=X
		// first part is the 64-bit address of the remote XBee, second part the 
		// 16-address of the remote XBee, third is the command value and forth is 
		// the command value.
		//
		// example: 000000000000FFFF.FFFF,D2=5
		// in the above example the first part, 000000000000FFFF,  is the remote XBee's 64-bit
		// address. This particular address is a broadcast address, means it will 
		// send the command to all XBee(s) connected to the network
		//
		// The second part, FFFF, is the 16-bit address. This is also a special address, it will
		// send the commands to all devices including the sleepy devices.
		//
		// The third part, D2, is the command. You can send any command that are available for the XBee, 
		// you can see all the in XCTU software.
		//
		// The forth one 5 is the command value, you cna view the command values form XCTU software. The
		// value 5 means 'Digital High', 4 means 'Digital Low'
		//
		args.substring(0, 8).toCharArray(szS1, 9, 0);
		args.substring(8, 16).toCharArray(szS2, 9, 0);
		args.substring(17, 21).toCharArray(szS3, 5, 0);
		args.substring(22, 24).toCharArray(szS4, 3, 0);

		Serial.println(szS1);
		Serial.println(szS2);
		Serial.println(szS3);
		Serial.println(szS4);

        // Get the 64-bit and 16-bit address
		unsigned long addr641 = strtoul(szS1, NULL, 16);
		unsigned long addr642 = strtoul(szS2, NULL, 16);
		unsigned long addr16 = strtoul(szS3, NULL, 16);
		char value = args.substring(25).toInt();
		
		// Print some debug information
		Serial.print(((addr641 >> 24) & 0xFF), HEX);
		Serial.print(" ");
		Serial.print(((addr641 >> 16) & 0xFF), HEX);
		Serial.print(" ");
		Serial.print(((addr641 >> 8) & 0xFF), HEX);
		Serial.print(" ");
		Serial.print(((addr641) & 0xFF), HEX);
		Serial.print(" ");
		Serial.print(((addr642 >> 24) & 0xFF), HEX);
		Serial.print(" ");
		Serial.print(((addr642 >> 16) & 0xFF), HEX);
		Serial.print(" ");
		Serial.print(((addr642 >> 8) & 0xFF), HEX);
		Serial.print(" ");
		Serial.print(((addr642) & 0xFF), HEX);
		Serial.print(" ");

		Serial.print(((addr16 >> 8) & 0xFF), HEX);
		Serial.print(" ");
		Serial.print(((addr16) & 0xFF), HEX);
		Serial.print(" ");

		Serial.print(szS4[0], HEX);
		Serial.print(" ");
		Serial.print(szS4[1], HEX);
		Serial.print(" ");

		Serial.print(value, HEX);
		Serial.println();

        // Send command
		sendRemoteAtCommand(addr641, addr642, addr16, szS4, value);
	}

	return 1;
}


void sendRemoteAtCommand(unsigned long addr641, unsigned long addr642, unsigned long addr16, char* cmd, char value) {
    uint8_t d0Cmd[] = { cmd[0], cmd[1] };
    uint8_t d0Value[] = { value };

    // SH + SL of your remote radio
    XBeeAddress64 remoteAddress = XBeeAddress64(addr641, addr642);
    
    // Create a remote AT request with the command
    RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));
    
    // Set 16 bit address
    remoteAtRequest.setRemoteAddress16(addr16);
    
    Serial.println("Sending command to the XBee");

    xbee.send(remoteAtRequest);
}