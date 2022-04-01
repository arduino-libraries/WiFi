# WiFi library

## Wifi Class

### `WiFi.begin()`

#### Description 
Initializes the WiFi library's network settings and provides the current status.

#### Syntax
```
WiFi.begin();
WiFi.begin(ssid);
WiFi.begin(ssid, pass);
WiFi.begin(ssid, keyIndex, key);
```
#### Parameters
ssid: the SSID (Service Set Identifier) is the name of the WiFi network you want to connect to.

keyIndex: WEP encrypted networks can hold up to 4 different keys. This identifies which key you are going to use.

key: a hexadecimal string used as a security code for WEP encrypted networks.

pass: WPA encrypted networks use a password in the form of a string for security.

#### Returns 
WL_CONNECTED when connected to a network
WL_IDLE_STATUS when not connected to a network, but powered on
#### Example
``` 
#include <WiFi.h>

//SSID of your network
char ssid[] = "yourNetwork";
//password of your WPA Network
char pass[] = "secretPassword";

void setup()
{
 WiFi.begin(ssid, pass);
}

void loop () {}
```

### `WiFi.disconnect()`
#### Description 
Disconnects the WiFi shield from the current network.

#### Syntax
```
WiFi.disconnect();
```
#### Parameters
none

#### Returns 
nothing

### `WiFi.config()`
#### Description 
WiFi.config() allows you to configure a static IP address as well as change the DNS, gateway, and subnet addresses on the WiFi shield.

Unlike WiFi.begin() which automatically configures the WiFi shield to use DHCP, WiFi.config() allows you to manually set the network address of the shield.

Calling WiFi.config() before WiFi.begin() forces begin() to configure the WiFi shield with the network addresses specified in config().

You can call WiFi.config() after WiFi.begin(), but the shield will initialize with begin() in the default DHCP mode. Once the config() method is called, it will change the network address as requested.

#### Syntax
```
WiFi.config(ip);
WiFi.config(ip, dns);
WiFi.config(ip, dns, gateway);
WiFi.config(ip, dns, gateway, subnet);
```
#### Parameters
ip: the IP address of the device (array of 4 bytes)

dns: the address for a DNS server.

gateway: the IP address of the network gateway (array of 4 bytes). optional: defaults to the device IP address with the last octet set to 1

subnet: the subnet mask of the network (array of 4 bytes). optional: defaults to 255.255.255.0

#### Returns 
Nothing

#### Example
``` 
This example shows how to set the static IP address, 192.168.0.177, of the LAN network to the WiFi shield:

#include <SPI.h>
#include <WiFi.h>

// the IP address for the shield:
IPAddress ip(192, 168, 0, 177);    

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "secretPassword"; // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

void setup()
{  
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while(true);  // don't continue
  }

  WiFi.config(ip);

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // print your WiFi shield's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop () {}
```

### `WiFi.setDNS()`
#### Description 
WiFi.setDNS() allows you to configure the DNS (Domain Name System) server.

#### Syntax
```
WiFi.setDNS(dns_server1)
WiFi.setDNS(dns_server1, dns_server2)
```
#### Parameters
dns_server1: the IP address of the primary DNS server

dns_server2: the IP address of the secondary DNS server

#### Returns 
Nothing

#### Example
``` 
This example shows how to set the Google DNS (8.8.8.8). You can set it as an object IPAddress.

#include <SPI.h>
#include <WiFi.h>

// the IP address for the shield:
IPAddress dns(8, 8, 8, 8);  //Google dns  

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "secretPassword"; // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

void setup()
{  
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while(true);  // don't continue
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // print your WiFi shield's IP address:
  WiFi.setDNS(dns);
  Serial.print("Dns configured.");
}

void loop () {
}
 
```

### `WiFi.SSID()`
#### Description 
Gets the SSID of the current network

#### Syntax
```
WiFi.SSID();
WiFi.SSID(wifiAccessPoint)
```
#### Parameters
wifiAccessPoint: specifies from which network to get the information

#### Returns 
A string containing the SSID the WiFi shield is currently connected to.

string containing name of network requested.

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

//SSID of your network
char ssid[] = "yourNetwork";
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup()
{
  // initialize serial:
  Serial.begin(9600);

  // scan for existing networks:
  Serial.println("Scanning available networks...");
  scanNetworks();

  // attempt to connect using WEP encryption:
  Serial.println("Attempting to connect to open network...");
  status = WiFi.begin(ssid);

  Serial.print("SSID: ");
  Serial.println(ssid);

}

void loop () {}

void scanNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  Serial.print("SSID List:");
  Serial.println(numSsid);
  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") Network: ");
    Serial.println(WiFi.SSID(thisNet));
  }
}
 
```

### `WiFi.BSSID()`
#### Description 
Gets the MAC address of the routher you are connected to

#### Syntax
```
WiFi.BSSID(bssid);
```
#### Parameters
bssid : 6 byte array

#### Returns 
A byte array containing the MAC address of the router the WiFi shield is currently connected to.

#### Example
``` 
#include <WiFi.h>

//SSID of your network
char ssid[] = "yourNetwork";
//password of your WPA Network
char pass[] = "secretPassword";

void setup()
{
 WiFi.begin(ssid, pass);

  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {
  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);    
  Serial.print("BSSID: ");
  Serial.print(bssid[5],HEX);
  Serial.print(":");
  Serial.print(bssid[4],HEX);
  Serial.print(":");
  Serial.print(bssid[3],HEX);
  Serial.print(":");
  Serial.print(bssid[2],HEX);
  Serial.print(":");
  Serial.print(bssid[1],HEX);
  Serial.print(":");
  Serial.println(bssid[0],HEX);
  }
}

void loop () {}
```

### `WiFi.RSSI()`
#### Description 
Gets the signal strength of the connection to the router

#### Syntax
```
WiFi.RSSI();
WiFi.RSSI(wifiAccessPoint);
```
#### Parameters
wifiAccessPoint: specifies from which network to get the information

#### Returns 
long : the current RSSI /Received Signal Strength in dBm

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

//SSID of your network
char ssid[] = "yourNetwork";
//password of your WPA Network
char pass[] = "secretPassword";

void setup()
{
 WiFi.begin(ssid, pass);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {
   // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
  }
}

void loop () {}
```

### `WiFi.encryptionType()`
#### Description 
Gets the encryption type of the current network

#### Syntax
```
WiFi.encryptionType();
WiFi.encryptionType(wifiAccessPoint);
```
#### Parameters
wifiAccessPoint: specifies which network to get information from
#### Returns 
byte : value represents the type of encryption

TKIP (WPA) = 2
WEP = 5
CCMP (WPA) = 4
NONE = 7
AUTO = 8
#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

//SSID of your network
char ssid[] = "yourNetwork";
//password of your WPA Network
char pass[] = "secretPassword";

void setup()
{
 WiFi.begin(ssid, pass);

  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {
   // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption,HEX);
  }
}

void loop () {}
```

### `WiFi.scanNetworks()`
#### Description 
Scans for available WiFi networks and returns the discovered number

#### Syntax
```
WiFi.scanNetworks();
```
#### Parameters
none

#### Returns 
byte : number of discovered networks

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "yourNetwork";  // the name of your network

void setup() {
  Serial.begin(9600);

  int status = WiFi.begin(ssid);

  if (status != WL_CONNECTED) {
    Serial.println("Couldn't get a WiFi connection");
    while (true);
  }
  else {
    // if you are connected, scan for available WiFi networks and print the number discovered:
    Serial.println("** Scan Networks **");
    byte numSsid = WiFi.scanNetworks();

    Serial.print("Number of available WiFi networks discovered:");
    Serial.println(numSsid);
  }
}

void loop() {}
```

### `WiFi.status()`
#### Description 
Return the connection status.

#### Syntax
```
WiFi.status();
```
#### Parameters
none

#### Returns 
WL_CONNECTED: assigned when connected to a WiFi network;
WL_NO_SHIELD: assigned when no WiFi shield is present;
WL_IDLE_STATUS: it is a temporary status assigned when WiFi.begin() is called and remains active until the number of attempts expires (resulting in WL_CONNECT_FAILED) or a connection is established (resulting in WL_CONNECTED);
WL_NO_SSID_AVAIL: assigned when no SSID are available;
WL_SCAN_COMPLETED: assigned when the scan networks is completed;
WL_CONNECT_FAILED: assigned when the connection fails for all the attempts;
WL_CONNECTION_LOST: assigned when the connection is lost;
WL_DISCONNECTED: assigned when disconnected from a network;
#### Example
``` 

#include <SPI.h>
#include <WiFi.h>

char ssid[] = "yourNetwork";                     // your network SSID (name)
char key[] = "D0D0DEADF00DABBADEAFBEADED";       // your network key
int keyIndex = 0;                                // your network key Index number
int status = WL_IDLE_STATUS;                     // the Wifi radio's status

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WEP network, SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, keyIndex, key);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // once you are connected :
  Serial.print("You're connected to the network");
}

void loop() {
  // check the network status connection once every 10 seconds:
  delay(10000);
 Serial.println(WiFi.status());
}

 
```

### `WiFi.getSocket()`
#### Description 
gets the first socket available

#### Syntax
```
WiFi.getSocket();
```
#### Parameters
none

#### Returns 
int : the first socket available

### `WiFi.macAddress()`
#### Description 
Gets the MAC Address of your WiFi shield

#### Syntax
```
WiFi.macAddress(mac);
```
#### Parameters
mac: a 6 byte array to hold the MAC address

#### Returns 
byte array : 6 bytes representing the MAC address of your shield

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "yourNetwork";     // the name of your network
int status = WL_IDLE_STATUS;     // the Wifi radio's status

byte mac[6];                     // the MAC address of your Wifi shield


void setup()
{
 Serial.begin(9600);

 status = WiFi.begin(ssid);

 if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print your MAC address:
  else {
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  }
}

void loop () {}
```

## IPAddress class

### `IPAddress.localIP()`
#### Description 
Gets the WiFi shield's IP address

#### Syntax
```
IPAddress.localIP();
```
#### Parameters
none

#### Returns 
the IP address of the shield

#### Example
``` 

#include <WiFi.h>

char ssid[] = "yourNetwork";      //SSID of your network

int status = WL_IDLE_STATUS;     // the Wifi radio's status

IPAddress ip;                    // the IP address of your shield

void setup()
{
 // initialize serial:
 Serial.begin(9600);

 WiFi.begin(ssid);

  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {
 //print the local IP address
  ip = WiFi.localIP();
  Serial.println(ip);

  }
}

void loop () {}
```

### `IPAddress.subnetMask()`
#### Description 
Gets the WiFi shield's subnet mask

#### Syntax
```
IPAddress.subnet();
```
#### Parameters
none

#### Returns 
the subnet mask of the shield

#### Example
``` 
#include <WiFi.h>
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//SSID of your network
char ssid[] = "yourNetwork";
//password of your WPA Network
char pass[] = "secretPassword";

IPAddress ip;
IPAddress subnet;
IPAddress gateway;

void setup()
{
  WiFi.begin(ssid, pass);

  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {

    // print your subnet mask:
    subnet = WiFi.subnetMask();
    Serial.print("NETMASK: ");
    Serial.println(subnet);

  }
}

void loop () {
}
 
```

### `IPAddress.gatewayIP()`
#### Description 
Gets the WiFi shield's gateway IP address.

#### Syntax
```
IPAddress.gatewayIP();
```
#### Parameters
none

#### Returns 
An array containing the shield's gateway IP address

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

int status = WL_IDLE_STATUS;     // the Wifi radio's status

//SSID of your network
char ssid[] = "yourNetwork";
//password of your WPA Network
char pass[] = "secretPassword";

IPAddress gateway;

void setup()
{
  Serial.begin(9600);

 WiFi.begin(ssid, pass);

  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {

  // print your gateway address:
  gateway = WiFi.gatewayIP();
  Serial.print("GATEWAY: ");
  Serial.println(gateway);

  }
}

void loop () {}
```

## Server class

### `Server`
#### Description 
Server is the base class for all WiFi server based calls. It is not called directly, but invoked whenever you use a function that relies on it.

### `WiFiServer()`
#### Description 
Creates a server that listens for incoming connections on the specified port.

#### Syntax
```
Server(port);
```
#### Parameters
port: the port to listen on (int)

#### Returns 
None

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  else {
    server.begin();
    Serial.print("Connected to wifi. My address:");
    IPAddress myAddress = WiFi.localIP();
    Serial.println(myAddress);

  }
}


void loop() {

}
 
```

### `server.begin()`
#### Description 
Tells the server to begin listening for incoming connections.

#### Syntax
```
server.begin()
```
#### Parameters
None

#### Returns 
None

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "lamaison";          //  your network SSID (name)
char pass[] = "tenantaccess247";   // your network password
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  else {
    server.begin();
    Serial.print("Connected to wifi. My address:");
    IPAddress myAddress = WiFi.localIP();
    Serial.println(myAddress);

  }
}


void loop() {

}
 
```

### `server.available()`
#### Description 
Gets a client that is connected to the server and has data available for reading. The connection persists when the returned client object goes out of scope; you can close it by calling client.stop().

available() inherits from the Stream utility class.

#### Syntax
```
server.available()
```
#### Parameters
None

#### Returns 
a Client object; if no Client has data available for reading, this object will evaluate to false in an if-statement

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "Network";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  else {
    server.begin();
    Serial.print("Connected to wifi. My address:");
    IPAddress myAddress = WiFi.localIP();
    Serial.println(myAddress);

  }
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {

    if (client.connected()) {
      Serial.println("Connected to client");
    }

    // close the connection:
    client.stop();
  }
}
 
```

### `server.write()`
#### Description 
Write data to all the clients connected to a server.

#### Syntax
```
server.write(data)
```
#### Parameters
data: the value to write (byte or char)

#### Returns 
byte : the number of bytes written. It is not necessary to read this.

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "yourNetwork";
char pass[] = "yourPassword";
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  else {
    server.begin();
  }
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client == true) {
       // read bytes from the incoming client and write them back
    // to any clients connected to the server:
    server.write(client.read());
  }
}
```

### `server.print()`
#### Description 
Print data to all the clients connected to a server. Prints numbers as a sequence of digits, each an ASCII character (e.g. the number 123 is sent as the three characters '1', '2', '3').

#### Syntax
```
server.print(data)
server.print(data, BASE)
```
#### Parameters
data: the data to print (char, byte, int, long, or string)

BASE (optional): the base in which to print numbers: BIN for binary (base 2), DEC for decimal (base 10), OCT for octal (base 8), HEX for hexadecimal (base 16).

#### Returns 
byte print() will return the number of bytes written, though reading that number is optional

### `server.println()`
#### Description 
Prints data, followed by a newline, to all the clients connected to a server. Prints numbers as a sequence of digits, each an ASCII character (e.g. the number 123 is sent as the three characters '1', '2', '3').

#### Syntax
```
server.println()
server.println(data)
server.println(data, BASE)
```
#### Parameters
data (optional): the data to print (char, byte, int, long, or string)

BASE (optional): the base in which to print numbers: DEC for decimal (base 10), OCT for octal (base 8), HEX for hexadecimal (base 16).

#### Returns 
byte
println() will return the number of bytes written, though reading that number is optional

## Client class

### `Client()`
#### Description 
Client is the base class for all WiFi client based calls. It is not called directly, but invoked whenever you use a function that relies on it.

Functions

### `WiFiClient()`
#### Description 
Creates a client that can connect to to a specified internet IP address and port as defined in client.connect().

#### Syntax
```
WiFiClient()
```
#### Parameters
none

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Google

// Initialize the client library
WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}

void loop() {

}
```

### `client.connected()`
#### Description 
Whether or not the client is connected. Note that a client is considered connected if the connection has been closed but there is still unread data.

#### Syntax
```
client.connected()
```
#### Parameters
none

#### Returns 
Returns true if the client is connected, false if not.

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Google

// Initialize the client library
WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}

void loop() {
   if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
}
```

### `client.connect()`
#### Description 
Connect to the IP address and port specified in the constructor. The return value indicates success or failure. connect() also supports DNS lookups when using a domain name (ex:google.com).

#### Syntax
```
client.connect(ip, port)
client.connect(URL, port)
```
#### Parameters
ip: the IP address that the client will connect to (array of 4 bytes)

URL: the domain name the client will connect to (string, ex.:"arduino.cc")

port: the port that the client will connect to (int)

#### Returns 
Returns true if the connection succeeds, false if not.

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
char servername[]="google.com";  // remote server we will connect to

WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(servername, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}

void loop() {

}
```

### `client.write()`
#### Description 
Write data to the server the client is connected to.

#### Syntax
```
client.write(data)
```
#### Parameters
data: the byte or char to write

#### Returns 
byte: the number of characters written. it is not necessary to read this value.

### `client.print()`
#### Description 
Print data to the server that a client is connected to. Prints numbers as a sequence of digits, each an ASCII character (e.g. the number 123 is sent as the three characters '1', '2', '3').

#### Syntax
```
client.print(data)
client.print(data, BASE)
```
#### Parameters
data: the data to print (char, byte, int, long, or string)

BASE (optional): the base in which to print numbers:, DEC for decimal (base 10), OCT for octal (base 8), HEX for hexadecimal (base 16).

#### Returns 
byte : returns the number of bytes written, though reading that number is optional

### `client.println()`
#### Description 
Print data, followed by a carriage return and newline, to the server a client is connected to. Prints numbers as a sequence of digits, each an ASCII character (e.g. the number 123 is sent as the three characters '1', '2', '3').

#### Syntax
```
client.println()
client.println(data)
client.print(data, BASE)
```
#### Parameters
data (optional): the data to print (char, byte, int, long, or string)

BASE (optional): the base in which to print numbers: DEC for decimal (base 10), OCT for octal (base 8), HEX for hexadecimal (base 16).

#### Returns 
byte: return the number of bytes written, though reading that number is optional

### `client.available()`
#### Description 
Returns the number of bytes available for reading (that is, the amount of data that has been written to the client by the server it is connected to).

available() inherits from the Stream utility class.

#### Syntax
```
client.available()
```
#### Parameters
none

#### Returns 
The number of bytes available.

#### Example
``` 
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
char servername[]="google.com";  // Google

WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(servername, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}
```

### `client.read()`
Read the next byte received from the server the client is connected to (after the last call to read()).

read() inherits from the Stream utility class.

#### Syntax
```
client.read()
```
#### Parameters
none

#### Returns 
The next byte (or character), or -1 if none is available.

### `client.flush()`
Discard any bytes that have been written to the client but not yet read.

flush() inherits from the Stream utility class.

#### Syntax
```
client.flush()
```
#### Parameters
none

#### Returns 
none

### `client.stop()`
Disconnect from the server

#### Syntax
```
client.stop()
```
#### Parameters
none

#### Returns 
none

## UDP class

### `WiFiUDP`
#### Description 
Creates a named instance of the WiFi UDP class that can send and receive UDP messages. On AVR based boards, outgoing UDP packets are limited to 72 bytes in size currently. For non-AVR boards the limit is 1446 bytes.

#### Syntax
```
WiFiUDP
```
#### Parameters
none

### `WiFiUDP.begin()`

#### Description 
Initializes the WiFi UDP library and network settings. Starts WiFiUDP socket, listening at local port PORT */

#### Syntax
```
WiFiUDP.begin(port);
```
#### Parameters
port: the local port to listen on (int)

#### Returns 
1: if successful
0: if there are no sockets available to use

### `WiFiUDP.available()`
#### Description 
Get the number of bytes (characters) available for reading from the buffer. This is data that's already arrived.

This function can only be successfully called after WiFiUDP.parsePacket().

available() inherits from the Stream utility class.

#### Syntax
```
WiFiUDP.available()
```
#### Parameters
None

#### Returns 
the number of bytes available in the current packet
0: if parsePacket hasn't been called yet

### `WiFiUDP.beginPacket()`

#### Description 
Starts a connection to write UDP data to the remote connection

#### Syntax
```
WiFiUDP.beginPacket(hostName, port);
WiFiUDP.beginPacket(hostIp, port);
```
#### Parameters
hostName: the address of the remote host. It accepts a character string or an IPAddress

hostIp: the IP address of the remote connection (4 bytes)

port: the port of the remote connection (int)
#### Returns 
1: if successful
0: if there was a problem with the supplied IP address or port

### `WiFiUDP.endPacket()`

#### Description 
Called after writing UDP data to the remote connection. It finishes off the packet and send it.

#### Syntax
```
WiFiUDP.endPacket();
```
#### Parameters
None

#### Returns 
1: if the packet was sent successfully
0: if there was an error

### `WiFiUDP.write()`

#### Description 
Writes UDP data to the remote connection. Must be wrapped between beginPacket() and endPacket(). beginPacket() initializes the packet of data, it is not sent until endPacket() is called.

#### Syntax
```
WiFiUDP.write(byte);
WiFiUDP.write(buffer, size);
```
#### Parameters
byte: the outgoing byte
buffer: the outgoing message
size: the size of the buffer
#### Returns 
single byte into the packet
bytes size from buffer into the packet

### `WiFiUDP.parsePacket()`

#### Description 
It starts processing the next available incoming packet, checks for the presence of a UDP packet, and reports the size. parsePacket() must be called before reading the buffer with UDP.read().

#### Syntax
```
UDP.parsePacket();
```
#### Parameters
None

#### Returns 
the size of the packet in bytes
0: if no packets are available

### `WiFiUDP.peek()`
Read a byte from the file without advancing to the next one. That is, successive calls to peek() will return the same value, as will the next call to read().

This function inherited from the Stream class. See the Stream class main page for more information.

#### Syntax
```
WiFiUDP.peek()
```
#### Parameters
none

#### Returns 
b: the next byte or character
-1: if none is available

### `WiFiUDP.read()`

#### Description 
Reads UDP data from the specified buffer. If no arguments are given, it will return the next character in the buffer.

This function can only be successfully called after WiFiUDP.parsePacket().

#### Syntax
```
WiFiUDP.read();
WiFiUDP.read(buffer, len);
```
#### Parameters
buffer: buffer to hold incoming packets (char*)

len: maximum size of the buffer (int)

#### Returns 
b: the characters in the buffer (char)
size: the size of the buffer
-1: if no buffer is available

### `WiFiUDP.flush()`
Discard any bytes that have been written to the client but not yet read.

flush() inherits from the Stream utility class.

#### Syntax
```
WiFiUDP.flush()
```
#### Parameters
none

#### Returns 
none

### `WiFiUDP.stop()`
#### Description 
Disconnect from the server. Release any resource being used during the UDP session.

#### Syntax
```
WiFiUDP.stop()
```
#### Parameters
none

#### Returns 
none

### `WiFiUDP.remoteIP()`

#### Description 
Gets the IP address of the remote connection.

This function must be called after WiFiUDP.parsePacket().

#### Syntax
```
WiFiUDP.remoteIP();
```
#### Parameters
None

#### Returns 
4 bytes : the IP address of the host who sent the current incoming packet

### `WiFiUDP.remotePort()`

#### Description 
Gets the port of the remote UDP connection.

This function must be called after UDP.parsePacket().

#### Syntax
```
UDP.remotePort();
```
#### Parameters
None

#### Returns 
The port of the host who sent the current incoming packet