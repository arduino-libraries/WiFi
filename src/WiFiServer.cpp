/*
  WiFiServer.cpp - Library for Arduino WiFi shield.
  Copyright (c) 2011-2014 Arduino LLC.  All right reserved.

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

#include <string.h>
#include "utility/server_drv.h"

extern "C" {
  #include "utility/debug.h"
}

#include "WiFi.h"
#include "WiFiClient.h"
#include "WiFiServer.h"

WiFiServer::WiFiServer(uint16_t port)
{
    _port = port;
}

void WiFiServer::begin()
{
    uint8_t _sock = WiFiClass::getSocket();
    if (_sock != NO_SOCKET_AVAIL)
    {
        ServerDrv::startServer(_port, _sock);
        WiFiClass::_server_port[_sock] = _port;
        WiFiClass::_state[_sock] = _sock;
    }
}

WiFiClient WiFiServer::available(byte* status)
{
	static int cycle_server_down = 0;
	const int TH_SERVER_DOWN = 50;

    for (int sock = 0; sock < MAX_SOCK_NUM; sock++)
    {
        if (WiFiClass::_server_port[sock] == _port)
        {
        	WiFiClient client(sock);
            uint8_t _status = client.status();
            uint8_t _ser_status = this->status();

            if (status != NULL)
            	*status = _status;

            //server not in listen state, restart it
            if ((_ser_status == 0)&&(cycle_server_down++ > TH_SERVER_DOWN))
            {
            	ServerDrv::startServer(_port, sock);
            	cycle_server_down = 0;
            }

            if (_status == ESTABLISHED)
            {                
                return client;  //TODO 
            }
        }
    }

    return WiFiClient(255);
}

uint8_t WiFiServer::status() {
    return ServerDrv::getServerState(0);
}


size_t WiFiServer::write(uint8_t b)
{
    return write(&b, 1);
}

size_t WiFiServer::write(const uint8_t *buffer, size_t size)
{
	size_t n = 0;

    for (int sock = 0; sock < MAX_SOCK_NUM; sock++)
    {
        if (WiFiClass::_server_port[sock] != 0)
        {
        	WiFiClient client(sock);

            if (WiFiClass::_server_port[sock] == _port &&
                client.status() == ESTABLISHED)
            {                
                n+=client.write(buffer, size);
            }
        }
    }
    return n;
}
