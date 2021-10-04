/*
  wifi_drv.h - Library for Arduino WiFi shield.
  Copyright (c) 2011-2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef WiFi_Drv_h
#define WiFi_Drv_h

#include <inttypes.h>
#include "utility/wifi_spi.h"
#include "IPAddress.h"
#include "WiFiUdp.h"

// Key index length
#define KEY_IDX_LEN     1
// 5 secs of delay to have the connection established
#define WL_DELAY_START_CONNECTION 5000
// firmware version string length
#define WL_FW_VER_LENGTH 6

class WiFiDrv
{
private:
	// settings of requested network
	static char 	_networkSsid[WL_NETWORKS_LIST_MAXNUM][WL_SSID_MAX_LENGTH];
	static int32_t 	_networkRssi[WL_NETWORKS_LIST_MAXNUM];
	static uint8_t 	_networkEncr[WL_NETWORKS_LIST_MAXNUM];

	// firmware version string in the format a.b.c
	static char 	fwVersion[WL_FW_VER_LENGTH];

	// settings of current selected network
	static char 	_ssid[WL_SSID_MAX_LENGTH];
	static uint8_t 	_bssid[WL_MAC_ADDR_LENGTH];
	static uint8_t 	_mac[WL_MAC_ADDR_LENGTH];
	static uint8_t  _localIp[WL_IPV4_LENGTH];
	static uint8_t  _subnetMask[WL_IPV4_LENGTH];
	static uint8_t  _gatewayIp[WL_IPV4_LENGTH];

	/*
	 * Get network Data information
	 */
    static void getNetworkData(uint8_t *ip, uint8_t *mask, uint8_t *gwip);

    static uint8_t reqHostByName(const char* aHostname);

    static int getHostByName(IPAddress& aResult);

    /*
     * Get remote Data information on UDP socket
     */
    static void getRemoteData(uint8_t sock, uint8_t *ip, uint8_t *port);

public:

    /*
     * Driver initialization
     */
    static void wifiDriverInit();

    /*
     * Set the desired network which the connection manager should try to
     * connect to.
     *
     * The SSID of the desired network should be specified.
     *
     * param ssid: The SSID of the desired network.
     * param ssid_len: Length of SSID string.
     * return: WL_SUCCESS or WL_FAILURE
	 */
    static int8_t wifiSetNetwork(const char* ssid, uint8_t ssid_len);

    /* Start WiFi connection with passphrase
     * the most secure supported mode will be automatically selected
     *
     * param ssid: Pointer to the SSID string.
     * param ssid_len: Length of SSID string.
     * param passphrase: Passphrase. Valid characters in a passphrase
     *        must be between ASCII 32-126 (decimal).
     * param len: Length of passphrase string.
     * return: WL_SUCCESS or WL_FAILURE
     */
    static int8_t wifiSetPassphrase(const char* ssid, uint8_t ssid_len, const char *passphrase, const uint8_t len);

    /* Start WiFi connection with WEP encryption.
     * Configure a key into the device. The key type (WEP-40, WEP-104)
     * is determined by the size of the key (5 bytes for WEP-40, 13 bytes for WEP-104).
     *
     * param ssid: Pointer to the SSID string.
     * param ssid_len: Length of SSID string.
     * param key_idx: The key index to set. Valid values are 0-3.
     * param key: Key input buffer.
     * param len: Length of key string.
     * return: WL_SUCCESS or WL_FAILURE
     */
    static int8_t wifiSetKey(const char* ssid, uint8_t ssid_len, uint8_t key_idx, const void *key, const uint8_t len);

    /* Set IP configuration disabling DHCP client
        *
        * param validParams: set the number of parameters that we want to change
        * 					 i.e. validParams = 1 means that we'll change only IP address
        * 					 	  validParams = 3 means that we'll change IP address, gateway and netmask
        * param local_ip: 	Static IP configuration
        * param gateway: 	Static gateway configuration
        * param subnet: 	Static subnet mask configuration
        */
    static void config(uint8_t validParams, uint32_t local_ip, uint32_t gateway, uint32_t subnet);

    /* Set DNS IP configuration
           *
           * param validParams: set the number of parameters that we want to change
           * 					 i.e. validParams = 1 means that we'll change only dns_server1
           * 					 	  validParams = 2 means that we'll change dns_server1 and dns_server2
           * param dns_server1: Static DNS server1 configuration
           * param dns_server2: Static DNS server2 configuration
           */
    static void setDNS(uint8_t validParams, uint32_t dns_server1, uint32_t dns_server2);

    /*
     * Disconnect from the network
     *
     * return: WL_SUCCESS or WL_FAILURE
     */
    static int8_t disconnect();

    /*
     * Disconnect from the network
     *
     * return: one value of wl_status_t enum
     */
    static uint8_t getConnectionStatus();

    /*
     * Get the interface MAC address.
     *
     * return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
     */
    static uint8_t* getMacAddress();

    /*
     * Get the interface IP address.
     *
     * return: copy the IP address value in IPAddress object
     */
    static void getIpAddress(IPAddress& ip);

    /*
     * Get the interface subnet mask address.
     *
     * return: copy the subnet mask address value in IPAddress object
     */
    static void getSubnetMask(IPAddress& mask);

    /*
     * Get the gateway IP address.
     *
     * return: copy the gateway IP address value in IPAddress object
     */
    static void getGatewayIP(IPAddress& ip);

    /*
     * Return the current SSID associated with the network
     *
     * return: SSID string
     */
    static char* getCurrentSSID();

    /*
     * Return the current BSSID associated with the network.
     * It is the MAC address of the Access Point
     *
     * return: pointer to uint8_t array with length WL_MAC_ADDR_LENGTH
     */
    static uint8_t* getCurrentBSSID();

    /*
     * Return the current RSSI /Received Signal Strength in dBm)
     * associated with the network
     *
     * return: signed value
     */
    static int32_t getCurrentRSSI();

    /*
     * Return the Encryption Type associated with the network
     *
     * return: one value of wl_enc_type enum
     */
    static uint8_t getCurrentEncryptionType();

    /*
     * Start scan for available WiFi networks
     *
     * return: Number of discovered networks
     */
    static int8_t startScanNetworks();

    /*
     * Get the networks available
     *
     * return: Number of discovered networks
     */
    static uint8_t getScanNetworks();

    /*
     * Return the SSID discovered during the network scan.
     *
     * param networkItem: specify from which network item want to get the information
	 *
     * return: SSID string of the specified item on the networks scanned list
     */
    static char* getSSIDNetworks(uint8_t networkItem);

    /*
     * Return the RSSI of the networks discovered during the scanNetworks
     *
     * param networkItem: specify from which network item want to get the information
	 *
     * return: signed value of RSSI of the specified item on the networks scanned list
     */
    static int32_t getRSSINetworks(uint8_t networkItem);

    /*
     * Return the encryption type of the networks discovered during the scanNetworks
     *
     * param networkItem: specify from which network item want to get the information
	 *
     * return: encryption type (enum wl_enc_type) of the specified item on the networks scanned list
     */
    static uint8_t getEncTypeNetworks(uint8_t networkItem);

    /*
     * Resolve the given hostname to an IP address.
     * param aHostname: Name to be resolved
     * param aResult: IPAddress structure to store the returned IP address
     * result: 1 if aIPAddrString was successfully converted to an IP address,
     *          else error code
     */
    static int getHostByName(const char* aHostname, IPAddress& aResult);

    /*
     * Get the firmware version
     * result: version as string with this format a.b.c
     */
    static char* getFwVersion();

    friend class WiFiUDP;

};

extern WiFiDrv wiFiDrv;

#endif
