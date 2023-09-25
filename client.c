//
// Created by Giacomo Cunardi on 23/09/23.
//
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "UDP.h"


#define TIMEOUT 1*CLOCKS_PER_SEC // 1 secondo
#define UDP_PORT 54321

int main(int argc, char* argv[])
{
    unsigned char buffer[1024] = "ASK"; // stringa di richiesta
    unsigned long ip_address;
    unsigned short port_number;
    unsigned long start, now;
    unsigned int *num = (unsigned int*)buffer;
    if (argc < 2)
    {
        printf("Deve essere fornito l'indirizzo IP del server!\r\n");
        return -1;
    }
    // inizializzazione socket con numero di porta UDP arbitrario
    if (UDP_init(0) < 0)
    {
        printf("Errore inizializzazione socket!\r\n");
        return -1;
    }
    ip_address = IP_to_bin(argv[1]);
    port_number = UDP_PORT;
    // trasmissione richiesta al server
    UDP_send(ip_address, port_number, buffer, strlen((char*)buffer));
    start = clock(); // tempo iniziale attesa
    now = clock(); // tempo attuale
    // ciclo di attesa risposta per al massimo un tempo pari a TIMEOUT
    while ((now - start) < TIMEOUT)
    {
        if (UDP_receive( &ip_address, &port_number, buffer, sizeof(buffer)) == sizeof(unsigned int))
        {
            // ricevuto un datagram della dimensione corretta visualizzazione numero
            printf("Ricevuto numero %u.\r\n", *num);
            UDP_close();
            return 0;
        }
        now = clock(); // aggiornamento tempo attuale
    }
    // trascorso un tempo pari a TIMEOUT senza ricevere risposta
    printf("Nessuna risposta ricevuta!\r\n");
    UDP_close();
    return -1;
}
