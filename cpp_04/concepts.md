# Concetti del Modulo 04 — Subtype Polymorphism, Abstract Classes, Interfaces

Il modulo 03 (ereditarietà) introduceva l'"is-a" ma **senza** polimorfismo a runtime:
`scavtrap.attack()` chiamava sempre la versione giusta perché il tipo dichiarato
dell'oggetto era già `ScavTrap`. Il modulo 04 aggiunge l'ingrediente che mancava:
**decidere quale funzione chiamare in base al tipo reale dell'oggetto, non al tipo
del puntatore/riferimento con cui lo guardi**. Tutto il resto (abstract class,
interfacce) è una conseguenza diretta di questa idea.

---

## 1. Subtype polymorphism e `virtual` (ex00)

```cpp
const Animal* j = new Dog();
j->makeSound();   // stampa "Woof! Woof!", NON il suono generico di Animal
```

`j` è dichiarato `Animal*`, ma l'oggetto puntato è un `Dog`. Se `makeSound()` è
dichiarato `virtual` in `Animal`, il compilatore non decide più a compile-time
quale funzione chiamare (**static binding**, quello che succedeva in cpp_03):
inserisce invece un meccanismo di lookup a runtime (concettualmente una tabella
di puntatori a funzione per classe, la **vtable**) che guarda il tipo *reale*
dell'oggetto e chiama `Dog::makeSound`. Questo è il "subtype polymorphism" del
titolo del modulo: un `Animal*` può in realtà comportarsi come qualsiasi suo
sottotipo.

**Regola pratica**: se una classe è pensata per essere usata tramite
puntatore/riferimento alla base ed avere comportamento specializzato, il metodo
in questione **deve** essere `virtual` nella base. Senza `virtual`, `j->foo()`
chiama sempre la versione della classe del puntatore (`Animal::foo`), mai quella
dell'oggetto reale — questo è esattamente il bug che l'esercizio ti fa costruire
apposta con `WrongAnimal`/`WrongCat` (vedi §2).

## 2. Static binding vs dynamic binding — perché serve `WrongAnimal` (ex00)

`WrongAnimal::makeSound()` **non** è virtual. `WrongCat::makeSound()` la
ridefinisce, ma tecnicamente non fa *override* (non c'è nulla da sovrascrivere a
runtime): la "nasconde" solo per chi guarda l'oggetto come `WrongCat`.

```cpp
const WrongAnimal* wrongCat = new WrongCat();
wrongCat->makeSound(); // stampa il suono di WrongAnimal, non quello del gatto!
```

Qui la scelta della funzione avviene **a compile-time**, guardando il tipo
statico del puntatore (`WrongAnimal*`), non l'oggetto realmente allocato. È la
dimostrazione voluta dal subject di *cosa succede se ti dimentichi `virtual`*.

**Corollario — distruttore virtuale.** Lo stesso problema si applica al
distruttore: se elimini un `Dog` tramite un puntatore `Animal*` e `~Animal()`
non è `virtual`, viene chiamato solo `~Animal()` — il distruttore di `Dog` non
gira mai (comportamento indefinito in generale, e qualunque risorsa allocata da
`Dog` non verrebbe liberata). Per questo `Animal` in ex00 ha
`virtual ~Animal();`, mentre `WrongAnimal` no — è voluto, per far notare la
differenza quando cancelli un `WrongCat*` tramite `WrongAnimal*`.

## 3. Composizione ("has-a") e deep copy (ex01)

Ex01 introduce `Brain` (100 `std::string` chiamate `ideas`) come attributo
**privato** di `Dog`/`Cat`, allocato con `new Brain()` nel costruttore e
liberato con `delete` nel distruttore:

```cpp
class Dog : public Animal
{
    private:
        Brain* brain;   // "has-a" Brain, non "is-a" Brain
    ...
};
```

Qui la relazione è "has-a" (composizione), diversa da "is-a" (ereditarietà):
`Dog` non *è* un `Brain`, ne possiede semplicemente uno. Il puntatore introduce
il problema classico della **shallow copy**: se il costruttore di copia si
limita a copiare il puntatore (`brain = other.brain`), due `Dog` finiscono per
condividere lo stesso `Brain` — modificare le idee di uno modifica anche
l'altro, e il doppio `delete` alla distruzione di entrambi è undefined
behavior (double free). La copia corretta (**deep copy**) alloca un `Brain`
*nuovo* e ne copia il contenuto:

```cpp
Dog::Dog(const Dog& other) : Animal(other)
{
    brain = new Brain(*other.brain);   // nuovo oggetto, non stesso indirizzo
}
```

Il subject lo richiede esplicitamente ("A copy of a Dog or a Cat mustn't be
shallow") e chiede di eliminare gli `Animal*` dell'array **direttamente come
Animal** — che è anche il motivo per cui torna utile il distruttore virtuale
del punto precedente: senza, il `delete` di un `Dog` polimorfico non
chiamerebbe mai `~Dog()` e il suo `Brain` farebbe leak.

**Come si verifica concretamente che la copia è deep e non shallow?** Non
basta "sembrare giusto", va dimostrato con dati: nel `main.cpp` di ex01,
`getBrain()` (aggiunto apposta a `Dog`/`Cat`, non richiesto dal subject ma
necessario per *osservare* dall'esterno l'indirizzo del `Brain` privato)
espone il puntatore, e il test copia un'idea, ne modifica una sull'originale
e una sulla copia, poi stampa entrambi gli indirizzi:

```cpp
Dog dog1;
dog1.getBrain()->setIdea(0, "chase the mailman");
Dog dog2(dog1);
dog2.getBrain()->setIdea(0, "take a nap");
// dog1 brain address: 0x... idea[0]: chase the mailman
// dog2 brain address: 0x... idea[0]: take a nap   <- indirizzo diverso, valore indipendente
```

Se la copia fosse stata shallow, i due indirizzi sarebbero risultati
**identici** e modificare l'idea di `dog2` avrebbe cambiato anche quella di
`dog1`. Stesso test ripetuto con `Cat` mediante `operator=` (non solo copy
constructor), perché la shallow copy è un bug possibile in *entrambi* i punti
dell'OCF, non solo nel costruttore di copia.

**Verificato con `valgrind --leak-check=full`**: 0 leak su tutta l'esecuzione
di ex01 (subject example, array misto di 6 `Animal*`, test di deep copy,
`WrongAnimal`/`WrongCat`) — conferma che ogni `new Brain()` allocato nei
costruttori di `Dog`/`Cat` viene liberato esattamente una volta, anche
quando l'oggetto viene distrutto tramite un `Animal*` polimorfico.

## 4. Abstract class e funzioni virtuali pure (ex02)

Ex02 chiede di impedire `new Animal()` diretto: "creare un Animal non ha senso,
non emette alcun suono". Si ottiene rendendo **pura** almeno una funzione
virtuale:

```cpp
virtual void makeSound(void) const = 0;   // "= 0" = pure virtual
```

Una classe con anche una sola funzione virtuale pura diventa **abstract**: il
compilatore rifiuta `new Animal()` (errore già in fase di compilazione, non a
runtime). Puoi però ancora dichiarare `Animal*` o `Animal&` — è proprio questo
che permette al polimorfismo del punto 1 di continuare a funzionare: la classe
astratta serve come "contratto" (tipo comune), le classi concrete (`Dog`,
`Cat`) devono fornire un'implementazione di `makeSound()` altrimenti restano
astratte anche loro.

**Differenza con `virtual` "normale" (non pura):** `virtual void f();` con
corpo è ereditabile e ridefinibile ma non obbliga nessuno a farlo, e la classe
resta istanziabile. `virtual void f() = 0;` obbliga ogni classe concreta
derivata a implementarla, pena restare anch'essa astratta.

**Verifica concreta che `Animal` è davvero astratta**: non basta fidarsi della
teoria, va provato che il compilatore rifiuta l'istanziazione. Compilando un
piccolo file di prova con `Animal a;` si ottiene un errore *in fase di
compilazione* (non un crash a runtime):

```
error: variable type 'Animal' is an abstract class
note: unimplemented pure virtual method 'makeSound' in 'Animal'
```

Da notare **cosa resta invariato**: `Dog`/`Cat` continuano a essere
istanziabili (implementano `makeSound()`), e l'array misto di `Animal*`
usato in ex01 funziona identico in ex02 — il subject lo richiede esplicitamente
("Everything should work as before"). L'unica riga cambiata rispetto a ex01 è
`virtual void makeSound(void) const = 0;` al posto della dichiarazione con
corpo in `Animal.cpp`; nessuna modifica a `Dog`, `Cat` o `Brain`. Anche qui,
`valgrind --leak-check=full` conferma 0 leak: rendere una classe astratta non
cambia nulla nella gestione delle risorse, solo nella regola di istanziazione
verificata dal compilatore.

## 5. Interfacce (ex03)

Il C++98 non ha una keyword `interface` (a differenza di Java/C#). Per
convenzione, una classe con **solo** funzioni virtuali pure (nessun dato, quasi
sempre distruttore virtuale con corpo vuoto) viene chiamata "interfaccia":

```cpp
class ICharacter
{
    public:
        virtual ~ICharacter() {}
        virtual std::string const & getName() const = 0;
        virtual void equip(AMateria* m) = 0;
        virtual void unequip(int idx) = 0;
        virtual void use(int idx, ICharacter& target) = 0;
};
```

`Character` implementa (eredita da) `ICharacter` fornendo un corpo per ogni
metodo — stesso meccanismo di abstract class del punto 4, usato però per
descrivere una *capacità* pura, senza stato né implementazione condivisa.
Una classe può ereditare (implementare) più interfacce contemporaneamente: qui
non serve, ma è il motivo per cui questo pattern esiste — è l'equivalente C++
della "multiple interface implementation".

### Il "virtual clone pattern"

`AMateria` (abstract, non interfaccia pura: ha lo stato `type`) espone:

```cpp
virtual AMateria* clone() const = 0;
```

Problema che risolve: i costruttori (e quindi i costruttori di copia) **non
possono essere virtual** in C++. Se hai un `AMateria*` e non sai se punta a un
`Ice` o a un `Cur e`, non puoi scrivere `new AMateria(*ptr)` per ottenere una
copia del tipo giusto — otterresti sempre un `AMateria` (o un errore, essendo
astratta). `clone()` aggira il problema: è una funzione *virtuale*, quindi
dispatcha correttamente a runtime, e al suo interno ciascuna sottoclasse fa
`return new Ice(*this);` restituendo un nuovo oggetto del proprio tipo reale.
Questo è esattamente ciò che usa `MateriaSource::createMateria()` per
rigenerare una `Materia` a partire da un "prototipo" imparato con
`learnMateria()`.

---

## 6. Concetti nuovi vs concetti già visti in cpp_03

| Concetto | cpp_03 (inheritance) | cpp_04 (polymorphism) |
|---|---|---|
| Relazione is-a | Sì (`class ScavTrap : public ClapTrap`) | Stessa cosa, ma sfruttata a runtime |
| Override di un metodo | Per nome, risolto a compile-time | Con `virtual`, risolto a runtime (dispatch dinamico) |
| Puntatore/riferimento a base | Non usato per polimorfismo | Usato apposta per dimostrare il dispatch |
| Distruttore | Non virtual (non serviva, vedi `DIFESA.md` §1) | Virtual, altrimenti leak/UB cancellando via puntatore a base |
| OCF (Orthodox Canonical Form) | Sì | Sì, ma ora anche con deep copy su risorse possedute (`Brain*`) |
| Composizione "has-a" | Non presente | `Brain*` dentro `Dog`/`Cat` (ex01) |
| Classe non istanziabile | Non presente | Abstract class via pure virtual (ex02) |
| "Interfaccia" | Non presente | Pure abstract class, niente stato (ex03) |
| Copia polimorfica di un oggetto sconosciuto | Non applicabile | `clone()` — virtual copy pattern (ex03) |

## Riassunto da ricordare

Il filo conduttore del modulo è uno solo: **una volta che decidi di guardare un
oggetto attraverso un puntatore/riferimento alla sua classe base, chi decide
quale codice gira davvero è `virtual`, non il tipo del puntatore**. Da lì
derivano tutte le conseguenze: il distruttore deve essere virtuale se vuoi
cancellare in modo sicuro tramite la base; una classe che non ha senso di
esistere da sola diventa astratta con una funzione virtuale pura; un'interfaccia
è solo un caso limite di classe astratta senza stato; e quando serve *copiare*
un oggetto di tipo sconosciuto a runtime, la soluzione è passare da un metodo
virtuale (`clone()`) invece che da un costruttore di copia, che virtuale non può
esserlo.
