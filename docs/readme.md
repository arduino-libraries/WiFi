# WiFi library
The firmware for the WiFi shield has changed in Arduino IDE 1.0.5. You are recommended to install this update per [these instructions](https://www.arduino.cc/en/Hacking/WiFiShieldFirmwareUpgrading)

With the Arduino WiFi Shield, this library allows an Arduino board to connect to the internet. It can serve as either a server accepting incoming connections or a client making outgoing ones. The library supports WEP and WPA2 Personal encryption, but not WPA2 Enterprise. Also note, if the SSID is not broadcast, the shield cannot connect.

Arduino communicates with the WiFi shield using the SPI bus. This is on digital pins 11, 12, and 13 on the Uno and pins 50, 51, and 52 on the Mega. On both boards, pin 10 is used as SS. On the Mega, the hardware SS pin, 53, is not used but it must be kept as an output or the SPI interface won't work. Digital pin 7 is used as a handshake pin between the Wifi shield and the Arduino, and should not be used.

The WiFi library is very similar to the [Ethernet](https://www.arduino.cc/en/Reference/Ethernet) library, and many of the function calls are the same.

For additional information on the WiFi shield, see the [Getting Started](https://www.arduino.cc/en/Guide/ArduinoWiFiShield) page and the [WiFi shield hardware page](https://www.arduino.cc/en/Main/ArduinoWiFiShield).

To use this library
```
#include <WiFi.h>
```
## Examples
- [ConnectNoEncryption](https://www.arduino.cc/en/Tutorial/ConnectNoEncryption) : Demonstrates how to connect to an open network
- [ConnectWithWEP](https://www.arduino.cc/en/Tutorial/ConnectWithWEP) : Demonstrates how to connect to a network that is encrypted with WEP
- [ConnectWithWPA](https://www.arduino.cc/en/Tutorial/ConnectWithWPA) : Demonstrates how to connect to a network that is encrypted with WPA2 Personal
- [ScanNetworks](https://www.arduino.cc/en/Tutorial/ScanNetworks) : Displays all WiFi networks in range
- [WiFiChatServer](https://www.arduino.cc/en/Tutorial/WiFiChatServer) : Set up a simple chat server
- [WiFiWebClient](https://www.arduino.cc/en/Tutorial/WiFiWebClient) : Connect to a remote webserver
- [WiFiWebClientRepeating](https://www.arduino.cc/en/Tutorial/WiFiWebClientRepeating) : Make repeated HTTP calls to a webserver
- [WiFiWebServer](https://www.arduino.cc/en/Tutorial/WiFiWebServer) : Serve a webpage from the WiFi shield
- [WiFiSendReceiveUDPString](https://www.arduino.cc/en/Tutorial/WiFiSendReceiveUDPString) : Send and receive a UDP string
- [UdpNTPClient](https://www.arduino.cc/en/Tutorial/UdpNTPClient) : Query a Network Time Protocol (NTP) server using UDP