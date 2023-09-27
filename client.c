//
// Created by Giacomo Cunardi on 23/09/23.
//
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "UDP.h"
#include "wind.h"

#define TIMEOUT 1*CLOCKS_PER_SEC // 1 second
#define UDP_PORT 54321

int main(int argc, char* argv[])
{
    unsigned char buffer[1024] = "ASK"; // Request string
    unsigned long ip_address;
    unsigned short port_number;
    unsigned long start, now;
    unsigned int *num = (unsigned int*)buffer;
    struct wind_data wind_udp;

    if (argc < 2)
    {
        printf("The server's IP address must be provided!\r\n");
        return -1;
    }

    // Initialize the socket with an arbitrary UDP port number
    if (UDP_init(0) < 0)
    {
        printf("Socket initialization error!\r\n");
        return -1;
    }

    ip_address = IP_to_bin(argv[1]);
    port_number = UDP_PORT;

    // Transmit request to the server
    UDP_send(ip_address, port_number, buffer, strlen((char*)buffer));
    start = clock(); // Initial waiting time
    now = clock(); // Current time

    // Waiting loop for a response for a maximum time of TIMEOUT
    while ((now - start) < TIMEOUT)
    {
        if (UDP_receive(&ip_address, &port_number, buffer, sizeof(buffer)) == sizeof(wind_udp))
        {
            wind_udp = (struct wind_data*)buffer;
            // Received a datagram of the correct size, display the number
            printf("Received number %u.\r\n", *num);
            UDP_close();
            return 0;
        }
        now = clock(); // Update current time
    }

    // No response received after a time equal to TIMEOUT
    printf("No response received!\r\n");
    UDP_close();
    return -1;
}
