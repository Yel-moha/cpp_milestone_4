# Difesa cpp_03 — Inheritance (ex00, ex01, ex02)

Nota: ex03 (DiamondTrap) escluso su richiesta. Il subject lo dichiara esplicitamente
facoltativo (pag. 13): *"You can pass this module without completing exercise 03."*
Le domande della scheda relative a ex03 vanno quindi risposte con "non svolto,
facoltativo per subject" — vedi §6.

---

## 1. Concetti chiave trasversali

Questi concetti valgono per ex00→ex02 nello stesso modo: li spiego una volta sola
qui e li richiamo per riferimento nelle sezioni successive, invece di ripeterli
esercizio per esercizio.

### Ereditarietà pubblica ("is-a")
`class ScavTrap : public ClapTrap` significa "ScavTrap è un ClapTrap". La classe
figlia eredita membri e metodi pubblici/protetti della base e può aggiungerne di
nuovi o sovrascriverne alcuni (override per nome, non ancora `virtual` in questo
modulo).

**Perché `public` e non `private`/`protected` inheritance?**
`public` preserva la relazione "is-a" — un ScavTrap può essere usato ovunque sia
atteso un ClapTrap (qui non sfruttiamo ancora il polimorfismo via
puntatori/riferimenti a base, ma è la premessa dei moduli successivi).

### private → protected
In ex00 gli attributi di ClapTrap sono `private`. Da ex01 in poi diventano
`protected`, perché le classi figlie (ScavTrap, FragTrap) devono poter impostare
direttamente `hit_points`, `energy_points`, `attack_damage` nel loro costruttore,
senza passare da setter.

**Perché non tenerli private e usare dei setter?**
Entrambe le strade sono valide, il subject lascia libertà di design. `protected`
evita boilerplate di setter/getter quando la relazione è già "is-a" stretta tra
base e figlia.

### Ordine di costruzione/distruzione
Quando costruisci uno ScavTrap (o un FragTrap), C++ costruisce **prima** la
sotto-parte ClapTrap (chiamando il costruttore scelto nella member initializer
list), poi il corpo del costruttore della classe figlia. Alla distruzione avviene
l'inverso:

```
ClapTrap <name> constructor called
ScavTrap <name> constructor called
...
ScavTrap <name> destructor called
ClapTrap <name> destructor called
```

**Perché in quest'ordine?**
Una ScavTrap *contiene* una ClapTrap come sua base; il corpo di ScavTrap potrebbe
fare affidamento su membri di ClapTrap già inizializzati, quindi la base deve
esistere per prima e sparire per ultima (analogo a un membro composto, ma
applicato alla sotto-classe).

Verificato negli output reali di `./ex00/ClapTrap`, `./ex01/scavtrap` e
`./ex02/claptrap`: l'ordine osservato è corretto in tutti e tre i binari (vedi
§3-§5 per gli output puntuali).

### Orthodox Canonical Form (OCF)
Richiesta dal Modulo 02 in poi: costruttore default, costruttore di copia,
`operator=`, distruttore. Tutte e tre le classi (ClapTrap, ScavTrap, FragTrap) la
implementano, incluso l'inoltro alla base nel costruttore di copia
(`ScavTrap(const ScavTrap& other) : ClapTrap(other)`) e in `operator=`
(`ClapTrap::operator=(other)`).

**Cosa succederebbe se ScavTrap non chiamasse `ClapTrap::operator=` nel suo
`operator=`?**
I membri ereditati (name, hit_points, ecc.) non verrebbero copiati — il
compilatore inserirebbe un default solo se non definissi affatto `operator=`, ma
qui essendo definito esplicitamente va richiamato a mano quello della base.

**Perché il costruttore di copia di ClapTrap chiama `*this = other` invece di
inizializzare i membri nella member initializer list?**
Evita di duplicare la logica di copia in due posti (costruttore e `operator=`);
leggermente meno efficiente (i membri vengono comunque costruiti di default
prima e poi riassegnati), ma corretto — nessun accesso a valori non
inizializzati perché `operator=` sovrascrive sempre tutti i campi prima di
essere letti.

### Costo in energia e fallimento delle azioni
`attack` e `beRepaired` costano 1 punto energia e falliscono (stampando un
messaggio, nessun effetto) se `hit_points <= 0` oppure `energy_points <= 0`.
`takeDamage` invece **non** consuma energia e fallisce solo se `hit_points <= 0`
— è l'unica azione sempre possibile finché l'oggetto non è "distrutto", coerente
col subject ("Attacking and repairing each cost 1 energy point").

### Perché ClapTrap non ha un distruttore virtuale?
In questo modulo non è strettamente necessario perché non si elimina mai un
FragTrap/ScavTrap tramite un puntatore a ClapTrap. Diventa un problema reale solo
quando si introduce polimorfismo a runtime (moduli successivi) — utile da
menzionare in difesa per mostrare di aver capito il limite del design attuale.

---

## 2. Prerequisiti generali (sezione "Preliminary tests" della scheda)

| Check | Risposta |
|---|---|
| Compila con `c++ -Wall -Wextra -Werror`? | **Sì**, `make re` pulito su tutti e 3 gli esercizi, zero warning. |
| Compila ancora aggiungendo `-std=c++98`? | **Sì**, il flag è già nel `CFLAGS` di ogni Makefile. |
| Funzione implementata in header (eccetto template)? | **No**, ogni `.hpp` contiene solo dichiarazioni; le implementazioni sono nei `.cpp`. |
| Makefile compila senza le flag richieste o con un compilatore diverso da `c++`? | **No**, `CC = c++` e `CFLAGS` include sempre `-Wall -Wextra -Werror -std=c++98` in tutti e tre i Makefile. |
| Uso di funzioni "C" (`*alloc`, `*printf`, `free`)? | **No** (verificato con grep su tutti i `.cpp`/`.hpp`). |
| Uso di funzioni non permesse dalle guideline dell'esercizio? | **No**. |
| Uso di `using namespace` o `friend`? | **No** (grep negativo, nessuna occorrenza). |
| Uso di librerie esterne o feature C++11+ (container/algoritmi STL inclusi)? | **No**, solo `<iostream>` e `<string>`, sintassi C++98. |

---

## 3. Ex00 — Aaaaand... OPEN!

**Class and attributes** → **Sì**
- `ClapTrap` con attributi `private`: `name` (passato al costruttore), `hit_points`
  (10), `energy_points` (10), `attack_damage` (0) — valori esatti richiesti dal
  subject.

**Member functions** → **Sì**
- `attack`, `takeDamage`, `beRepaired` implementate con la semantica descritta in
  §1 (costo energia, fallimento a HP/EP=0, niente underflow su `takeDamage`
  quando `amount >= hit_points`).
- Nessuna interazione diretta tra istanze ClapTrap: `target` è una stringa, non
  un altro oggetto — rispetta il vincolo esplicito del subject ("the parameters
  will not refer to another instance of ClapTrap").
- Messaggi di costruttore/distruttore presenti, come richiesto per rendere
  visibile la chiamata al valutatore.

Output di riferimento (`./ex00/ClapTrap`, valgrind: 0 leak):
```
ClapTrap CL4P-TP constructor called
ClapTrap CL4P-TP attacks un bersaglio, causing 0 points of damage!
ClapTrap CL4P-TP takes 5 points of damage and has 5 hit points left
ClapTrap CL4P-TP repairs itself for 3 hit points and now has 8 hit points
ClapTrap CL4P-TP destructor called
```

Nota minore (cosmetica, non bloccante): `main.cpp` ha `#include "ClapTrap.hpp"`
ripetuto due volte (righe 1 e 3) — innocuo grazie agli include guard, da
segnalare come pulizia se il valutatore lo nota.

---

## 4. Ex01 — Serena, my love!

**Class and attributes** → **Sì**
- `ScavTrap` eredita pubblicamente da `ClapTrap` (vedi §1), non ridichiara
  attributi, gli attributi di ClapTrap sono ora `protected` (vedi §1).
- Valori inizializzati: HP=100, EP=50, AD=20 — esatti come da subject.

**Member functions** → **Sì**
- `attack` sovrascritto con messaggio proprio, diverso da quello di ClapTrap.
- `takeDamage` e `beRepaired` ereditati (non sovrascritti, non richiesto).
- Output di costruttore/distruttore/`attack()` tutti diversi da quelli di
  ClapTrap.

**Construction and destruction** → **Sì**
- Ordine di chiamata corretto: costruzione ClapTrap→ScavTrap, distruzione
  ScavTrap→ClapTrap (motivazione in §1). Dimostrato esplicitamente in
  `main.cpp` anche per copy constructor e copy assignment (`copy`, `assigned`),
  non solo per il costruttore "semplice".

**Special feature** → **Sì**
- `guardGate()` stampa il messaggio di modalità gate keeper.
- `attack()` messaggio breve e diverso da ClapTrap (già coperto sopra, la scheda
  lo richiede due volte in punti diversi).

Output di riferimento (`./ex01/scavtrap`, valgrind: 0 leak), con i casi limite
testati:
```
ClapTrap SC4V-TP constructor called
ScavTrap SC4V-TP constructor called
ClapTrap copy constructor called
ClapTrap copy assignment operator called
ScavTrap copy constructor called
ClapTrap default constructor called
ScavTrap default constructor called
ScavTrap copy assignment operator called
ClapTrap copy assignment operator called
ScavTrap SC4V-TP attacks a vault hunter, causing 20 points of damage!
ClapTrap SC4V-TP takes 42 points of damage and has 58 hit points left
ClapTrap SC4V-TP repairs itself for 20 hit points and now has 78 hit points
ScavTrap SC4V-TP is now in Gate keeper mode
ClapTrap SC4V-TP takes 200 points of damage and has 0 hit points left
ScavTrap SC4V-TP cannot attack        <- HP=0, azione fallisce correttamente
ClapTrap SC4V-TP cannot be repaired   <- idem, beRepaired ereditato fallisce
ScavTrap SC4V-TP destructor called
ClapTrap SC4V-TP destructor called
(x3, per scavtrap/copy/assigned)
```

---

## 5. Ex02 — Repetitive work

**Class and attributes** → **Sì**
- `FragTrap` eredita pubblicamente da `ClapTrap` (vedi §1), attributi non
  ridichiarati.
- Valori inizializzati: HP=100, EP=100, AD=30 — esatti come da subject.

**Construction and destruction** → **Sì**
- Stessa dinamica di ex01 (vedi §1): costruzione ClapTrap→FragTrap, distruzione
  FragTrap→ClapTrap, messaggi propri e diversi da ClapTrap/ScavTrap.

**Special feature** → **Sì**
- `highFivesGuys()` stampa una richiesta di high-five positiva.

**Perché FragTrap non sovrascrive `attack()`?**
Non richiesto: il subject impone un messaggio diverso da ClapTrap solo per
ScavTrap ("its constructors, destructor, and attack() will print different
messages" è specifico della sezione ScavTrap); per FragTrap chiede solo che
costruzione/distruzione abbiano messaggi diversi. `attack()` di FragTrap usa
quindi quello ereditato da ClapTrap, comportamento voluto e non un bug.

Output di riferimento (`./ex02/claptrap`, valgrind: 0 leak):
```
ClapTrap Jack constructor called
FragTrap Jack constructor called
ClapTrap Jack attacks Bandit, causing 30 points of damage!
ClapTrap Jack takes 20 points of damage and has 80 hit points left
ClapTrap Jack repairs itself for 15 hit points and now has 95 hit points
Jack requests a high five!
FragTrap Jack destructor called
ClapTrap Jack destructor called
```

**Cosa è stato corretto durante lo sviluppo?**
In una versione precedente il costruttore con nome accettava `std::string name`
per valore invece di `const std::string&` (copia inutile), e distruttore/
costruttore non stampavano `name`. Corretto per coerenza con ClapTrap/ScavTrap
(parametro per riferimento costante, nome sempre nel messaggio) — utile da
menzionare se chiedono "hai trovato problemi rileggendo il tuo codice?".

---

## 6. Ex03 — Now it's weird! (non svolto)

`DiamondTrap` (eredità multipla virtuale da FragTrap e ScavTrap) non è stata
implementata. Risposta da dare in difesa: **esercizio facoltativo per subject**
(pag. 13: *"You can pass this module without completing exercise 03"*), scelta
deliberata per concentrare tempo/qualità su ex00-ex02. Tutte le domande della
scheda relative a ex03 (classe DiamondTrap, virtual inheritance, attack() di
ScavTrap, `whoAmI()`, attributo `name` con stesso nome di ClapTrap) vanno
segnate **No**, senza che questo azzeri la valutazione — non è un flag
"Empty work" né "Invalid compilation", è semplicemente lavoro non consegnato per
un esercizio bonus/opzionale.

Se richiesto in difesa di spiegare **come lo si implementerebbe**:
- `class DiamondTrap : public FragTrap, virtual public ScavTrap` (o entrambe
  `virtual`) per evitare due sotto-oggetti ClapTrap distinti (diamond problem).
- Attributo privato `name` in DiamondTrap con **lo stesso nome** di quello in
  ClapTrap (per shadowing intenzionale, richiesto dal subject).
- Un solo costruttore ClapTrap chiamato esplicitamente nella member initializer
  list di DiamondTrap (altrimenti, senza virtual inheritance risolta a mano,
  verrebbe costruito più volte o darebbe ambiguità).
- `attack()` = quello di ScavTrap (richiede `using ScavTrap::attack;` o
  chiamata esplicita, dato che sia FragTrap che ScavTrap ereditano `attack` da
  ClapTrap senza renderlo virtual — altrimenti ambiguità di risoluzione).

---

## 7. Ratings — quali flag spuntare

| Flag | Valore | Motivazione |
|---|---|---|
| Ok | **Sì** | Tutti gli esercizi consegnati (ex00-ex02) funzionano come da subject. |
| Outstanding project | a discrezione del valutatore | Non richiesto per superare il modulo. |
| Empty work | No | Codice presente e funzionante. |
| No author file | N/A | Nessun file "authors" richiesto dal subject C++; se il campus lo richiede come convenzione locale, va verificato a parte. |
| Invalid compilation | No | `make re` pulito con le flag richieste su tutti e tre gli esercizi. |
| Norme | N/A | Il subject dichiara esplicitamente "Goodbye Norminette!" per i moduli C++ — nessuna norma di stile imposta. |
| Cheat | No | — |
| Crash | No | Eseguiti più run di ogni binario, nessun crash. |
| Leaks | No | `valgrind --leak-check=full` pulito (0 leak, tutti i blocchi liberati) su `ClapTrap`, `scavtrap`, `claptrap`. |
| Forbidden function | No | Nessun `*alloc`/`*printf`/`free`, nessuna funzione non permessa (grep verificato). |

---

## 8. Altre domande generali possibili in difesa

1. **Cosa succede se ometto la member initializer list e assegno gli attributi
   nel corpo del costruttore?**
   Per tipi come `int` non cambia molto qui, ma per `std::string` significa
   costruire di default e poi assegnare, invece di costruire direttamente col
   valore giusto — uno step in più, non un errore in questo contesto.

2. **Perché non hai reso `attack`/`takeDamage`/`beRepaired` `virtual`?**
   Non richiesto in questo modulo: l'override qui è per nome/scoping statico
   (chiamando il metodo sul tipo dichiarato dell'oggetto, non tramite puntatore
   a base). La `virtual` diventa necessaria solo quando si introduce
   polimorfismo runtime, argomento dei moduli successivi.

3. **Perché ClapTrap in ex00 ha attributi `private` ma da ex01 `protected`?**
   Vedi §1 — ex00 non ha bisogno di essere ereditata, da ex01 in poi sì.

4. **Cosa succede se attacco/riparo con HP o EP a 0?**
   Nessun effetto, viene stampato un messaggio che l'azione fallisce ("cannot
   attack" / "cannot be repaired") — richiesto esplicitamente dal subject e
   dimostrato nei test di ex01 (vedi §4).

5. **Hai verificato le memory leak? Come?**
   Con `valgrind --leak-check=full` su tutti e tre gli eseguibili: 0 leak, tutti
   i blocchi allocati (dallo `std::string` interno) sono liberati correttamente
   dai distruttori.
