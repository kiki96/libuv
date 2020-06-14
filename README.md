# libuv

Ideja je bila napraviti aplikaciju za backup datoteke preko TCP-a kad se ista promijeni.

Što se tiče client strane otvara se socket prema TCP serveru kao i datoteka čiji backup oćemo napraviti (ja sam hardkodirao file.txt). 
Timer služi za testiranje na način da svakih 10s dodaje slovo a na kraj tekstualne datoteke.
Koristi se fs_poll koji prati promjenu (svake 3s provjerava) na željenoj datoteci te kad se ista dogodi šalje sadržaj serveru preko TCP-a.

Što se tiče serverske strane korišten je primjer TCP echo servera promijenjen na način da sadržaj zapisuje u datoteku backup.bak. Server se diže na portu 7000.

Aplikacija je jednostavna i da bi bila funckionalna trebalo bi još puno poraditi na njoj jer ima probleme poput npr. ograničenog buffera (1024 znaka), ali pošto to nije baš dio vezan uz libuv i u nedostatku vremena se nisam dodatno bavio takvim stvarima već sam samo htio iskoristiti i osposobiti zadane dijelove libuva.

# Upute za kompajliranje

gcc -o client client.c /usr/local/lib/libuv.a -pthread
./client

gcc -o server server.c /usr/local/lib/libuv.a -pthread
./server

