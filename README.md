# Tetris Game in C++

Questo progetto è un'implementazione del classico gioco **Tetris**, scritto in **C++** utilizzando la libreria **ncurses** per il rendering grafico nel terminale.

## Caratteristiche del Gioco

- **Movimenti base dei tetramini**: Spostamento a sinistra, destra, e verso il basso.
- **Caduta automatica**: I tetramini cadono automaticamente a velocità crescente.
- **Rotazioni**: Rotazioni dei tetramini per adattarsi meglio alle posizioni sul tabellone.
- **Eliminazione delle linee**: Le linee complete vengono eliminate e le righe superiori scendono per riempire gli spazi vuoti.
- **Livelli**: Si può scegliere tra 5 livelli, ogni livello ha una velocità di caduta dei tetramini diversa.
- **Nome del Giocatore**: Il giocatore può inserire il proprio nome all'inizio del gioco.
- **Punteggio**: Il punteggio aumenta in base al numero di linee eliminate e il livello scelto.
- **Tovella Score**: I 10 migliori punteggi vengono salvati in un file e possono essere visualizzati in maniera decrescente nel menu principale.
- **Game Over**: Il gioco termina quando non c'è spazio per un nuovo tetramino.

## Requisiti

- **g++ Compiler**: È necessario un compilatore.
- **Libreria ncurses**: Utilizzata per la grafica nel terminale. Può essere installata con il gestore di pacchetti della tua distribuzione:
  - Debian: `sudo apt-get install libncurses5-dev libncursesw5-dev`

## Compilazione e Avvio

1.  compilazione del gioco:
    ```bash
    make
    ```
2.  Avvio del gioco:
    ```bash
    ./Gioco
    ```
