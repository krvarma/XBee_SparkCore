Using Spark Core and XBee for RF Communication, Part #1
----------------------------------------------

This is a part one of my project that uses Spark Core and XBee for RF Communication. My intention is to use XBee(s) and Spark Core to create very simple Home Automation project. In this part, I just turn on/off a remote bulb which can be controlled using a Web Application. 

The project is to control a remote light, i.e. turn on/off the light. In this part I am using Spark Core and two XBee Series 2B (Zigbee Mesh). One XBee is configured as Coordinator API and the other one as Router AT. Actually there is no need to configure the second one as Router AT, you can configure as End Device, in that case also it will work.

**Introduction**

Here in this project the Coordinator API XBee is connected to Spark Core and communicate using Serial. Here Spark Core is used as Internet Gateway to control XBee. The Core application uses XBee Library ported by @pkourany.  For this project I am using XBee Remote AT command to control remote XBee(s). For more about API Mode and Remote AT Commands please refer to [this link](http://www.digi.com/support/kbase/kbaseresultdetl?id=2184).

The Router XBee is connected to a Single Channel Relay module which is connected to Electrical Light. In this sample the Relay is connected to DIO2 of the Router XBee. But you can use any IO pins and specify the pin when sending command.

To send Remote AT Command, you can either use a Broadcast address or a destination 64-bit (MAC/EUI64) address of the XBee module. Using the 64-bit destination address allows us to send commands to a particular XBee. There is also a 16-bit configurable address which can be used to group multiple XBees and send commands to that group. Since this is a different topic and is not in our scope, for more information refer to the [Digi documentation](http://www.digi.com/support/kbase/kbaseresultdetl?id=2187).

The sample JavaScript Web application is used to control the remote light. To use this application you should replace the *deviceid* and *accesstoken* with actual values. When the application is opened you will be asked to enter the Name (any name, just for display purpose) and the 64-bit remote address of the XBee that is connected to the Relay Module. Once it is entered you can turn on/off 

[Here](http://ftp1.digi.com/support/utilities/digi_apiframes2.htm) you can find a very useful API Frame Generator from Digi International. This is extremely useful for the development and debugging, I used it a lot for this project.

**Wiring**

*Coordinator XBee and Spark Core*

 - XBee Vcc to Spark Core 3V3 
 - XBee GND to Spark Core GND 
 - XBee DOUT to Spark Core Rx 
 - XBee DIN to Spark Core Tx

*Router XBee and Relay Module*

 - XBee Vcc to 3v3
 - XBee GND to GND
 - XBee DIO2 to Relay Modules Signal Pin

**Screenshots**

**Demo Video**