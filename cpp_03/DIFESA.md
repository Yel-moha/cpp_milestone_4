# Difesa cpp_03 — Inheritance (ex00, ex01, ex02)

Nota: ex03 escluso su richiesta (ereditarietà multipla / diamond problem, "Now it's weird!").

---

## 1. Concetti chiave del modulo

### Ereditarietà pubblica ("is-a")
`class ScavTrap : public ClapTrap` significa "ScavTrap è un ClapTrap". La classe
figlia eredita membri e metodi pubblici/protetti della base e può aggiungerne
di nuovi o sovrascriverne alcuni (override, non ancora `virtual` in questo modulo).

**Domanda tipica:** *Perché `public` e non `private`/`protected` inheritance?*
Risposta: `public` preserva la relazione "is-a" — un ScavTrap può essere usato
ovunque sia atteso un ClapTrap (in questo modulo non sfruttiamo ancora il
polimorfismo via puntatori/riferimenti a base, ma è la premessa per i moduli
successivi).

### private → protected
In ex00 gli attributi di ClapTrap sono `private`. Da ex01 in poi diventano
`protected`, perché le classi figlie (ScavTrap, FragTrap) devono poter
impostare direttamente `hit_points`, `energy_points`, `attack_damage` nel loro
costruttore.

**Domanda tipica:** *Perché non tenerli private e usare dei setter?*
Risposta valida entrambe le vie; il subject lascia libertà di design. `protected`
è la scelta standard per questo esercizio perché evita boilerplate di
setter/getter quando la relazione è già "is-a" stretta tra base e figlia.

### Ordine di costruzione/distruzione
Quando costruisci uno ScavTrap, C++ costruisce **prima** la sotto-parte
ClapTrap (chiamando il costruttore scelto nella member initializer list),
poi il corpo del costruttore ScavTrap. Alla distruzione avviene l'inverso:

```
ClapTrap <name> constructor called
ScavTrap <name> constructor called
...
ScavTrap <name> destructor called
ClapTrap <name> destructor called
```

**Perché in quest'ordine?** Una ScavTrap *contiene* una ClapTrap come sua base;
il corpo di ScavTrap potrebbe fare affidamento su membri di ClapTrap già
inizializzati, quindi la base deve esistere per prima e sparire per ultima
(analogo a un membro composto, ma applicato alla sotto-classe).

Verificato con `./scavtrap` e `./claptrap` (ex02): l'ordine osservato è
corretto in entrambi i binari.

### Orthodox Canonical Form (OCF)
Richiesta dal Modulo 02 in poi: costruttore default, costruttore di copia,
`operator=`, distruttore. Tutte e tre le classi (ClapTrap, ScavTrap, FragTrap)
la implementano correttamente, incluso l'inoltro alla base nel costruttore di
copia (`ScavTrap(const ScavTrap& other) : ClapTrap(other)`) e in
`operator=` (`ClapTrap::operator=(other)`).

**Domanda tipica:** *Cosa succederebbe se ScavTrap non chiamasse
`ClapTrap::operator=` nel suo `operator=`?* Risposta: i membri ereditati
(name, hit_points, ecc.) non verrebbero copiati — solo il compilatore
inserirebbe un default se non definisci affatto `operator=`, ma qui essendo
definito esplicitamente va richiamato a mano quello della base.

---

## 2. Ex00 — ClapTrap

Valori: name (param), HP=10, EP=10, AD=0.
Metodi: `attack`, `takeDamage`, `beRepaired`, ognuno costa 1 EP e fallisce se
HP o EP sono a 0.

Punti forti verificati:
- Messaggi di costruttori/distruttore presenti (richiesto esplicitamente dal
  subject per rendere visibile la chiamata ai peer-evaluator).
- `takeDamage` gestisce correttamente il caso `amount >= hit_points` (niente
  underflow, HP va a 0 e non sotto).
- Nessuna interazione diretta tra istanze ClapTrap (target è una stringa, non
  un altro oggetto) — rispetta il vincolo del subject.

Nota minore: `main.cpp` ha l'`#include "ClapTrap.hpp"` ripetuto due volte
(riga 1 e 3) — innocuo grazie agli include guard, ma da ripulire.

---

## 3. Ex01 — ScavTrap

Valori: HP=100, EP=50, AD=20. Nuova abilità `guardGate()`. `attack()`
sovrascritto con messaggio proprio.

Verificato via `./scavtrap`:
- Catena di costruzione/distruzione corretta anche per copy constructor e
  copy assignment (testati esplicitamente in `main.cpp` con `copy` e
  `assigned`).
- `guardGate()` e `attack()` producono i messaggi attesi con il nome corretto.

Tutto conforme al subject.

---

## 4. Ex02 — FragTrap

Valori: HP=100, EP=100, AD=30. Nuova abilità `highFivesGuys()`. Non
sovrascrive `attack()` (non richiesto per FragTrap — solo ScavTrap lo fa).

Verificato via `./claptrap` (nome del binario in questo esercizio): catena di
costruzione/distruzione corretta, `highFivesGuys()` funziona.

Corretto: in origine il distruttore e il costruttore con nome non stampavano
`name`, e il costruttore prendeva `std::string name` per valore invece di
`const std::string&`. Ora tutti i messaggi includono il nome, coerenti con
ClapTrap/ScavTrap, e il parametro è passato per riferimento costante come nel
resto del codice — nessuna copia inutile. Verificato con `make re` (compila
senza warning) e riesecuzione di `./claptrap`:

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

---

## 5. Domande generali che potrebbero fare in difesa

1. **Cosa succede se ometto la member initializer list e assegno gli
   attributi nel corpo del costruttore?**
   Per tipi come `int` non cambia molto qui, ma per `std::string` significa
   costruire di default e poi assegnare, invece di costruire direttamente col
   valore giusto — uno step in più, ma non un errore in questo contesto.

2. **Perché il costruttore di copia di ClapTrap chiama `*this = other`
   invece di inizializzare i membri nella lista?**
   Evita duplicare la logica di copia in due posti (costruttore e
   `operator=`); leggermente meno efficiente (i membri vengono comunque
   costruiti di default prima), ma corretto.

3. **Cosa succede se attacco con HP o EP a 0?**
   Nessun effetto, viene stampato un messaggio che l'azione fallisce
   ("cannot attack" / "cannot be repaired") — richiesto esplicitamente dal
   subject.

4. **Perché ClapTrap ha bisogno del distruttore virtuale?**
   In questo modulo non è strettamente necessario perché non si elimina mai
   un FragTrap/ScavTrap tramite un puntatore a ClapTrap. Diventa un problema
   reale solo quando si introduce polimorfismo runtime (moduli successivi) —
   utile da menzionare per mostrare di aver capito il limite del design
   attuale.