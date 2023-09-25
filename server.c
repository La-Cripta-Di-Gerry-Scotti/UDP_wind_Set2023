// Created by Giacomo Cunardi on 23/09/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "UDP.h"
#include "wind.h"

#define UDP_PORT 54321

int main(void)
{
    unsigned char buffer[1024];     // Reception buffer
    unsigned long ip_address;       // Variable to store the client's IP address
    unsigned short port_number;     // Variable to store the client's port number
    unsigned int num;               // Variable for the generated number
    int n;

    struct wind_data wind;

    if (UDP_init(UDP_PORT) < 0) // Initialize the socket with UDP port number 54321
    {
        printf("ERR 101: Socket Error\r\n");
        return -1;
    }

    printf("Service Activated\r\n");

    while (1)
    {
        if ((n = UDP_receive(&ip_address, &port_number, buffer, sizeof(buffer))) > 0) // Receive a datagram and check the message
        {
            buffer[n] = '\0'; // String terminator

            if (strcmp((char*)buffer, "WIND?") == 0)
            {
                // Request to generate a new number

                if (wind(wind.wind_speed, wind.wind_direction) < 0)
                {
                    printf("Invalid values\n\r");
                    return -1;
                }

                UDP_send(ip_address, port_number, (void *) &num, sizeof(unsigned int));

                printf("...sent number %u.\r\n", num);
            }
        }
    }
    UDP_close();
    return 0;
}
