//
// Created by Giacomo Cunardi on 23/09/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "UDP.H"
#include "wind.h"

#define UDP_PORT 54321

struct wind_data{
    float wind_speed;
    int wind_direction;
};

int wind(float *wind_speed, int *wind_direction)
{
    int h = 0;
    while(h == 0)
    {
        struct wind_data wind_data;
        wind_data.wind_speed = random();
        wind_data.wind_direction = random();

        if(wind_data.wind_speed < 0 && wind_data.wind_speed > 140 && wind_data.wind_direction < 0 && wind_data.wind_direction > 360)
        {
            h = 1;
        }
        else
        {
            h = 3;
        }
    }
    return 0;
}


int main(void)
{
    unsigned char buffer[1024];     //reception buffer
    unsigned long ip_address;       //variabile che memorizzere l'ip del client
    unsigned short port_number;	    //variabile che memorizzera  la porta del client
    unsigned int num;               //variabile per numero da generare
    int n;

    if (UDP_init(UDP_PORT) < 0) // inizializzazione socket con porta UDP numero 54321
    {
        printf("ERR 101: Socket Error\r\n");
        return -1;
    }

    printf("Service Activated\r\n");

    while (1)
    {
        if ((n = UDP_receive( &ip_address, &port_number, buffer, sizeof(buffer))) > 0) // ricezione di un datagram e verifica del messaggio
        {
            buffer[n] = '\0'; // terminatore di stringa

            if (strcmp((char*)buffer, "WIND?") == 0)
            {
                // richiesta di generazione di un nuovo numero

                num = sequence();

                UDP_send (ip_address, port_number, (void*)&num, sizeof(unsigned int));

                printf("...inviato numero %u.\r\n", num);
            }
        }
    }
    UDP_close();
    return 0;
}
