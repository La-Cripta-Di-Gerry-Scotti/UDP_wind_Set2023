# Wind_UDP_Cunardi_2392023

22 CODING
Un circolo nautico utilizza un dispositivo con sistema operativo Linux per interfacciare un sensore in grado di misurare velocità (Km/h) e direzione (°) del vento: il produttore del sensore rende disponibile un driver che permette di acquisire i valori misurati in tempo reale invocando la seguente funzione in linguaggio C che restituisce il valore 0 in caso di valori validi, -1 altrimenti:
int wind (float *speed, int *direction);
Si intende realizzare un server UDP attivo sulla porta 54321 per rendere disponibili in rete i valori misurati dal sensore: le richieste sono costituite da un datagram UDP che contiene i caratteri
ASCII «WIND?». Realizzare in linguaggio C/C++ per sistema operativo Linux il server UDP richiesto simulando l'invocazione della funzione wind con la restituzione di valori casuali plausibili e un programma client di test che, ricevendone come argomento della riga di comando l'indirizzo IP, interroghi il server e visualizzi i valori correnti della velocità e della direzione del vento, o un messaggio di errore nel caso che il server non risponda entro un secondo.
