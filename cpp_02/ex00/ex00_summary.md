# CPP Module 02 - Ex00

## Tema dell'esercizio

L'ex00 si chiama **"My First Class in Orthodox Canonical Form"**. Il suo obiettivo principale non e' ancora costruire una classe numerica davvero utile, ma introdurre due concetti fondamentali che verranno usati in tutto il modulo:

- la **Orthodox Canonical Form** in C++;
- la rappresentazione interna di un numero **fixed-point**.

In pratica, l'esercizio ti chiede di creare una classe `Fixed` che rappresenta un numero a virgola fissa, ma in questa prima versione la classe e' volutamente molto semplice: puo' contenere solo un valore grezzo intero e, di fatto, viene inizializzata a `0`.

## Quale problema affronta

Finora nei progetti hai usato soprattutto interi e floating-point (`int`, `float`, `double`, ecc.). Il subject vuole farti notare che questi tipi hanno caratteristiche diverse:

- gli interi sono precisi, ma non rappresentano frazioni;
- i floating-point rappresentano frazioni e numeri molto grandi o piccoli, ma possono introdurre approssimazioni;
- i fixed-point stanno in mezzo: usano un intero come base, ma riservano alcuni bit alla parte frazionaria.

Il problema affrontato dall'ex00 e' quindi: **come progettare una classe C++ che incapsula una rappresentazione numerica interna, rispettando le regole base di vita, copia e assegnazione di un oggetto?**

L'esercizio non ti chiede ancora di fare conversioni da `int` o `float`, ne' operazioni matematiche. Questo arrivera' negli esercizi successivi. Qui il punto e' costruire la struttura corretta.

## La classe `Fixed`

La classe deve avere due attributi privati:

- un `int` che conserva il valore grezzo del fixed-point;
- uno `static const int` che rappresenta il numero di bit frazionari.

Il numero di bit frazionari deve essere sempre `8`.

Questo significa che la classe non memorizza direttamente un `float`, ma un intero interpretato secondo una certa convenzione. Nell'ex00 questa convenzione viene solo preparata, non ancora sfruttata.

## Orthodox Canonical Form

Da questo modulo in poi, salvo eccezioni esplicite, le classi devono seguire la **Orthodox Canonical Form**. Per una classe significa implementare sempre questi quattro elementi:

- costruttore di default;
- costruttore di copia;
- operatore di assegnazione;
- distruttore.

Nel caso di `Fixed`, servono quindi:

- `Fixed();`
- `Fixed(const Fixed &other);`
- `Fixed &operator=(const Fixed &other);`
- `~Fixed();`

Il motivo e' imparare a controllare esplicitamente il ciclo di vita degli oggetti: creazione, copia, assegnazione e distruzione.

### Perche' esiste questa forma

In C++ un oggetto non e' solo un insieme di dati: ha una vita precisa. Viene costruito, puo' essere copiato, puo' essere assegnato a un altro oggetto gia' esistente, e alla fine viene distrutto.

La Orthodox Canonical Form serve a rendere esplicite queste quattro fasi. Anche se in questo esercizio la classe `Fixed` contiene solo un `int`, quindi non ha una gestione complicata della memoria, il modulo vuole abituarti subito a scrivere classi che si comportano in modo prevedibile.

Il punto teorico e' questo: quando una classe possiede uno stato interno, devi sapere cosa succede a quello stato in ogni situazione.

Esempio:

```cpp
Fixed a;
Fixed b(a);
Fixed c;
c = b;
```

Qui succedono tre cose diverse:

- `Fixed a;` costruisce un nuovo oggetto da zero;
- `Fixed b(a);` costruisce un nuovo oggetto copiando `a`;
- `c = b;` non costruisce `c`, perche' `c` esiste gia': aggiorna il suo contenuto copiando quello di `b`.

Costruzione e assegnazione sembrano simili, ma non sono la stessa cosa. Questa differenza e' uno dei punti piu' importanti dell'ex00.

### I quattro metodi nel dettaglio

Il **costruttore di default** crea un oggetto valido senza ricevere parametri. In questo esercizio deve inizializzare il valore grezzo a `0`.

Il **costruttore di copia** crea un nuovo oggetto partendo da un altro oggetto dello stesso tipo. Deve fare in modo che il nuovo oggetto abbia lo stesso stato interno dell'oggetto copiato.

L'**operatore di assegnazione** copia lo stato di un oggetto dentro un altro oggetto gia' esistente. Di solito restituisce `*this`, cioe' un riferimento all'oggetto corrente, per permettere assegnazioni concatenate come:

```cpp
a = b = c;
```

Il **distruttore** viene chiamato quando l'oggetto termina la sua vita. In ex00 non deve liberare memoria dinamica, ma deve comunque esistere per rispettare la forma canonica e per mostrarti quando gli oggetti vengono distrutti.

### Copia superficiale e copia profonda

In `Fixed`, copiare un oggetto significa copiare un semplice `int`. Questa e' una copia molto semplice.

Pero' la regola diventa molto piu' importante quando una classe contiene risorse come memoria allocata con `new`, file aperti, socket, puntatori o buffer. In quei casi bisogna decidere se copiare solo il puntatore o copiare anche la risorsa puntata.

- Una **copia superficiale** copia solo i valori degli attributi.
- Una **copia profonda** crea una nuova risorsa indipendente e copia il contenuto.

Ex00 non ti mette ancora davanti a questo problema in modo difficile, ma ti prepara al ragionamento: se una classe ha uno stato interno, la copia deve avere un significato chiaro.

## Getter e setter del valore grezzo

L'esercizio richiede anche due funzioni membro:

```cpp
int getRawBits(void) const;
void setRawBits(int const raw);
```

`getRawBits` restituisce il valore interno grezzo.

`setRawBits` modifica il valore interno grezzo.

Queste funzioni non fanno ancora conversioni matematiche. Servono solo per osservare e modificare direttamente la rappresentazione interna.

## Fixed-point numbers: idea teorica

Un numero **fixed-point** e' un numero rappresentato usando un intero, ma interpretando una parte dei suoi bit come parte frazionaria.

La differenza principale rispetto a un `float` e' che nel fixed-point la posizione della virgola e' fissa. Non viene spostata automaticamente in base alla grandezza del numero. Per questo si chiama "fixed point": punto fisso.

Nel caso dell'ex00, il subject dice che la classe deve avere:

```cpp
static const int fractionalBits = 8;
```

Il nome puo' cambiare a seconda del tuo stile, ma il valore deve essere `8`. Questo significa che gli ultimi 8 bit del valore interno vengono considerati come parte frazionaria.

### Cosa significa avere 8 bit frazionari

Se hai 8 bit frazionari, il valore grezzo interno non rappresenta direttamente il numero reale. Rappresenta quel numero moltiplicato per `2^8`.

Poiche':

```text
2^8 = 256
```

la relazione teorica e':

```text
valore reale = valore grezzo / 256
valore grezzo = valore reale * 256
```

Esempi concettuali:

```text
raw = 0      -> valore reale = 0 / 256   = 0
raw = 256    -> valore reale = 256 / 256 = 1
raw = 128    -> valore reale = 128 / 256 = 0.5
raw = 64     -> valore reale = 64 / 256  = 0.25
raw = 512    -> valore reale = 512 / 256 = 2
```

Quindi un fixed-point con 8 bit frazionari puo' rappresentare passi di:

```text
1 / 256 = 0.00390625
```

Questo valore e' la precisione minima della rappresentazione: tra due valori consecutivi rappresentabili c'e' sempre questa distanza.

### Perche' usare un intero per rappresentare frazioni

L'idea puo' sembrare strana: perche' usare un `int` se voglio rappresentare numeri con la virgola?

Il motivo e' che gli interi sono veloci, prevedibili e precisi nella loro rappresentazione. Un fixed-point sfrutta queste proprieta', ma decide che una parte dell'intero rappresenta la frazione.

Con un `float`, invece, il computer usa una rappresentazione piu' flessibile, simile alla notazione scientifica: una parte per il segno, una per l'esponente e una per la mantissa. Questo permette un range molto grande, ma introduce approssimazioni che a volte sorprendono.

Esempio classico: alcuni numeri decimali semplici per noi, come `0.1`, non sono rappresentabili esattamente in binario floating-point.

Il fixed-point sacrifica un po' di range e flessibilita', ma ottiene una precisione prevedibile. Se sai che hai 8 bit frazionari, sai sempre qual e' il passo minimo rappresentabile.

### Range, precisione e compromesso

Un fixed-point divide i bit disponibili tra:

- parte intera;
- parte frazionaria.

Piu' bit assegni alla parte frazionaria, maggiore e' la precisione dopo la virgola, ma minore e' lo spazio rimasto per rappresentare numeri grandi.

Meno bit assegni alla parte frazionaria, minore e' la precisione, ma maggiore e' il range della parte intera.

In ex00 questo compromesso e' gia' deciso dal subject: i bit frazionari sono sempre `8`.

### Perche' ex00 non fa ancora conversioni

Nell'ex00 la classe contiene gia' gli elementi necessari per una rappresentazione fixed-point, ma non espone ancora costruttori da `int` o da `float`, ne' funzioni come `toFloat` o `toInt`.

Questo significa che in ex00 il concetto fixed-point resta quasi tutto "sotto il cofano". Tu prepari:

- il valore grezzo;
- il numero fisso di bit frazionari;
- i metodi per leggere e scrivere il valore grezzo;
- la forma canonica della classe.

Negli esercizi successivi userai davvero la formula `raw / 256` e `real * 256` per convertire i valori.

## Output richiesto

Il subject mostra un `main` di esempio in cui vengono creati tre oggetti:

```cpp
Fixed a;
Fixed b(a);
Fixed c;
c = b;
```

Questo serve a verificare che:

- il costruttore di default venga chiamato quando crei un oggetto normale;
- il costruttore di copia venga chiamato quando inizializzi un oggetto da un altro;
- l'operatore di assegnazione venga chiamato quando assegni un oggetto gia' esistente;
- il distruttore venga chiamato alla fine della vita degli oggetti;
- `getRawBits` restituisca il valore interno, che in questo esercizio sara' `0`.

Il subject chiede di stampare messaggi come:

- `Default constructor called`
- `Copy constructor called`
- `Copy assignment operator called`
- `getRawBits member function called`
- `Destructor called`

Questi messaggi servono per vedere in quale ordine C++ costruisce, copia, assegna e distrugge gli oggetti.

## Dettaglio importante sulla copia

Nel costruttore di copia puoi copiare il valore dell'oggetto sorgente. Una scelta comune e' riutilizzare l'operatore di assegnazione dentro il costruttore di copia, ma in quel caso potresti vedere anche il messaggio dell'assegnazione durante la copia.

Il subject infatti dice che una riga del tipo:

```text
Copy assignment operator called
```

puo' mancare a seconda dell'implementazione.

Questo significa che l'output non deve essere identico al carattere, ma deve avere un comportamento coerente con la costruzione, la copia, l'assegnazione e la distruzione degli oggetti.

## File da consegnare

Dentro la directory `ex00/` dovrebbero esserci:

- `Makefile`
- `main.cpp`
- `Fixed.hpp` oppure `Fixed.h`
- `Fixed.cpp`

La definizione della classe va nel file header, mentre l'implementazione delle funzioni membro va nel `.cpp`.

## Cosa devi capire davvero

Il cuore dell'ex00 non e' il calcolo numerico. Il cuore e':

- capire come una classe protegge i propri dati con attributi `private`;
- capire cosa succede quando un oggetto viene copiato;
- capire la differenza tra costruzione e assegnazione;
- capire perche' un oggetto dovrebbe avere un distruttore anche quando non usa memoria dinamica;
- preparare una base pulita per aggiungere conversioni e operatori negli esercizi successivi.

In breve: **ex00 e' un esercizio di progettazione di classe e ciclo di vita degli oggetti, mascherato da introduzione ai fixed-point numbers**.
