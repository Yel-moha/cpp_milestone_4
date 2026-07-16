# Guida di correzione e difesa - CPP Module 02

## Verdetto rapido

- `ex00`: corretto e difendibile.
- `ex01`: corretto.
- `ex02`: corretto nella logica richiesta dalla scheda.

## Cosa devi saper spiegare in difesa

### Ex00 - My First Class in Orthodox Canonical Form

Obiettivo: dimostrare di sapere cos'e' una classe in forma canonica ortodossa e come funziona il minimo indispensabile per gestire un valore intero raw.

Punti da spiegare:
- La classe conserva il valore interno in un `int` privato.
- `fractionalBits` e' `static const` perche' il numero di bit frazionari e' uguale per tutti gli oggetti.
- Il costruttore di default inizializza il raw value a `0`.
- Il copy constructor e l'operator= copiano il valore interno.
- `getRawBits()` e `setRawBits()` espongono e modificano il valore grezzo.

Valutazione del tuo codice:
- La struttura della classe e' corretta.
- La forma canonica e' presente.
- I metodi richiesti dalla scheda sono implementati e funzionano.
- Il programma di test compila e gira con le flag richieste.

Se ti chiedono un miglioramento:
- Il copy constructor potrebbe usare un member initializer list oppure assegnare direttamente il campo, ma la versione attuale resta funzionale.

### Ex01 - Towards a more useful fixed-point number class

Obiettivo: estendere la classe per costruire oggetti da `int` e `float`, e per convertire il valore fixed-point in `float` e `int`.

Punti da spiegare:
- Il valore fixed-point usa `8` bit frazionari.
- Il costruttore da `int` sposta il valore di `8` bit a sinistra.
- Il costruttore da `float` moltiplica per `2^8` e arrotonda con `roundf`.
- `toFloat()` divide il raw value per `2^8`.
- `toInt()` elimina la parte frazionaria con uno shift a destra.
- `operator<<` stampa la rappresentazione in `float`.

Valutazione del tuo codice:
- La parte numerica e' corretta.
- Le conversioni funzionano come richiesto.
- L'overload di `<<` e' presente e utile per stampare l'oggetto.
- Il copy constructor copia direttamente il valore interno, quindi non introduce output extra e resta coerente con la richiesta.

### Ex02 - Now we are talking

Obiettivo: aggiungere confronti, operazioni aritmetiche, incrementi/decrementi e `min`/`max` statiche.

Punti da spiegare:
- Le sei comparazioni confrontano il raw value, quindi il confronto resta coerente con la rappresentazione fixed-point.
- `+` e `-` sommano o sottraggono direttamente i raw value.
- `*` usa un `long` temporaneo per evitare overflow intermedio e poi riporta il risultato nella scala fixed-point.
- `/` scala il dividendo prima della divisione per conservare la precisione.
- Gli operatori `++` e `--` modificano di un'unita' il raw value; il post-fix restituisce una copia del valore precedente.
- Le versioni `min` e `max` sono sovraccaricate per oggetti const e non const.

Valutazione del tuo codice:
- Le implementazioni richieste ci sono tutte.
- I confronti e le operazioni base funzionano.
- Gli operatori di incremento/decremento seguono il comportamento atteso.
- `min` e `max` sono implementate sia per riferimenti const sia non const.

Punto da tenere presente in difesa:
- La divisione non gestisce esplicitamente il caso di denominatore zero. Non e' richiesto dalla scheda, ma se ti fanno una domanda su robustezza o casi limite, quello e' il punto piu' facile da citare.

## Risposta breve da dare all'esaminatore

- "Ho rispettato la struttura canonica richiesta e ho separato i tre passi del modulo: base class, conversioni e operatori."
- "In ex01 il comportamento numerico e' corretto; l'unica cosa migliorabile e' il copy constructor, che oggi passa da `operator=` e quindi stampa una riga in piu'."
- "In ex02 ho mantenuto le operazioni coerenti con il fixed-point: comparazioni sui raw value, aritmetica con scaling corretto, incrementi/decrementi e overload di `min`/`max`."

## Giudizio finale

- Hai fatto bene su `ex00`.
- Hai fatto bene su `ex01`.
- Hai fatto bene su `ex02`.

## Se vuoi migliorare il lavoro prima della difesa

- In `ex02`, valuta una protezione contro la divisione per zero se vuoi rendere il codice piu' robusto.
