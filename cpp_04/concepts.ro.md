# Concepte Modulul 04 — Subtype Polymorphism, Abstract Classes, Interfaces

Modulul 03 (moștenire) introducea relația "is-a", dar **fără** polimorfism la
runtime: `scavtrap.attack()` apela mereu versiunea corectă pentru că tipul
declarat al obiectului era deja `ScavTrap`. Modulul 04 adaugă ingredientul
care lipsea: **decizia asupra cărei funcții este apelată se ia în funcție de
tipul real al obiectului, nu de tipul pointerului/referinței prin care îl
privești**. Tot restul (clasă abstractă, interfețe) este o consecință directă
a acestei idei.

---

## 1. Subtype polymorphism și `virtual` (ex00)

```cpp
const Animal* j = new Dog();
j->makeSound();   // afișează "Woof! Woof!", NU sunetul generic al lui Animal
```

`j` este declarat `Animal*`, dar obiectul indicat este un `Dog`. Dacă
`makeSound()` este declarată `virtual` în `Animal`, compilatorul nu mai
decide la compile-time care funcție este apelată (**static binding**, ceea
ce se întâmpla în cpp_03): introduce în schimb un mecanism de căutare la
runtime (conceptual un tabel de pointeri către funcții, per clasă — **vtable**)
care se uită la tipul *real* al obiectului și apelează `Dog::makeSound`.
Acesta este "subtype polymorphism"-ul din titlul modulului: un `Animal*` se
poate comporta de fapt ca oricare dintre subtipurile sale.

**Regulă practică**: dacă o clasă este gândită să fie folosită printr-un
pointer/referință către clasa de bază și să aibă un comportament specializat,
metoda respectivă **trebuie** să fie `virtual` în clasa de bază. Fără
`virtual`, `j->foo()` apelează mereu versiunea din clasa pointerului
(`Animal::foo`), niciodată versiunea obiectului real — exact acesta este
bug-ul pe care exercițiul te pune să-l construiești intenționat cu
`WrongAnimal`/`WrongCat` (vezi §2).

## 2. Static binding vs dynamic binding — de ce este nevoie de `WrongAnimal` (ex00)

`WrongAnimal::makeSound()` **nu** este virtuală. `WrongCat::makeSound()` o
redefinește, dar tehnic nu face *override* (nu există nimic de suprascris la
runtime): doar o "ascunde" pentru cine privește obiectul ca `WrongCat`.

```cpp
const WrongAnimal* wrongCat = new WrongCat();
wrongCat->makeSound(); // afișează sunetul lui WrongAnimal, nu al pisicii!
```

Aici alegerea funcției se face **la compile-time**, uitându-se la tipul
static al pointerului (`WrongAnimal*`), nu la obiectul alocat efectiv. Este
demonstrația intenționată din subiect a *ce se întâmplă dacă uiți `virtual`*.

**Corolar — destructor virtual.** Aceeași problemă se aplică și
destructorului: dacă ștergi un `Dog` printr-un pointer `Animal*` și
`~Animal()` nu este `virtual`, se apelează doar `~Animal()` — destructorul
lui `Dog` nu rulează niciodată (comportament nedefinit în general, iar orice
resursă alocată de `Dog` nu ar fi eliberată). De aceea `Animal` în ex00 are
`virtual ~Animal();`, în timp ce `WrongAnimal` nu — este intenționat, pentru
a evidenția diferența atunci când ștergi un `WrongCat*` prin `WrongAnimal*`.

## 3. Compoziție ("has-a") și deep copy (ex01)

Ex01 introduce `Brain` (100 de `std::string` numite `ideas`) ca atribut
**privat** al lui `Dog`/`Cat`, alocat cu `new Brain()` în constructor și
eliberat cu `delete` în destructor:

```cpp
class Dog : public Animal
{
    private:
        Brain* brain;   // "has-a" Brain, nu "is-a" Brain
    ...
};
```

Aici relația este "has-a" (compoziție), diferită de "is-a" (moștenire): `Dog`
nu *este* un `Brain`, pur și simplu deține unul. Pointerul introduce
problema clasică a **shallow copy**: dacă constructorul de copiere se
limitează să copieze pointerul (`brain = other.brain`), doi `Dog` ajung să
partajeze același `Brain` — modificarea ideilor unuia le modifică și pe cele
ale celuilalt, iar dublul `delete` la distrugerea ambilor este comportament
nedefinit (double free). Copierea corectă (**deep copy**) alocă un `Brain`
*nou* și îi copiază conținutul:

```cpp
Dog::Dog(const Dog& other) : Animal(other)
{
    brain = new Brain(*other.brain);   // obiect nou, nu aceeași adresă
}
```

Subiectul cere asta explicit ("A copy of a Dog or a Cat mustn't be
shallow") și cere ca `Animal*` din array să fie șterse **direct ca Animal**
— motiv pentru care destructorul virtual de la punctul anterior este
esențial: fără el, `delete`-ul unui `Dog` polimorfic nu ar apela niciodată
`~Dog()`, iar `Brain`-ul lui ar rămâne nealocat (memory leak).

**Cum se verifică în mod concret că o copie este deep și nu shallow?** Nu e
suficient să "pară corect", trebuie demonstrat cu date: în `main.cpp` din
ex01, `getBrain()` (adăugată special la `Dog`/`Cat`, nu este cerută de
subiect, dar este necesară pentru a *observa* din exterior adresa lui
`Brain`, care este privat) expune pointerul, iar testul copiază o idee, o
modifică pe original și pe copie separat, apoi afișează ambele adrese:

```cpp
Dog dog1;
dog1.getBrain()->setIdea(0, "chase the mailman");
Dog dog2(dog1);
dog2.getBrain()->setIdea(0, "take a nap");
// dog1 brain address: 0x... idea[0]: chase the mailman
// dog2 brain address: 0x... idea[0]: take a nap   <- adresă diferită, valoare independentă
```

Dacă copierea ar fi fost shallow, cele două adrese ar fi ieșit **identice**,
iar modificarea ideii lui `dog2` ar fi schimbat-o și pe cea a lui `dog1`.
Același test repetat cu `Cat` prin `operator=` (nu doar prin constructorul de
copiere), pentru că shallow copy este un bug posibil în *ambele* puncte ale
OCF, nu doar în constructorul de copiere.

**Verificat cu `valgrind --leak-check=full`**: 0 leak-uri pe toată execuția
din ex01 (exemplul din subiect, array mixt de 6 `Animal*`, test de deep copy,
`WrongAnimal`/`WrongCat`) — confirmă că fiecare `new Brain()` alocat în
constructorii lui `Dog`/`Cat` este eliberat exact o dată, chiar și atunci
când obiectul este distrus printr-un `Animal*` polimorfic.

## 4. Clasă abstractă și funcții virtuale pure (ex02)

Ex02 cere să se împiedice `new Animal()` direct: "crearea unui Animal nu are
sens, pentru că nu emite niciun sunet". Se obține făcând **pură** cel puțin
o funcție virtuală:

```cpp
virtual void makeSound(void) const = 0;   // "= 0" = pure virtual
```

O clasă cu măcar o funcție virtuală pură devine **abstractă**: compilatorul
respinge `new Animal()` (eroare deja în faza de compilare, nu la runtime).
Poți totuși încă declara `Animal*` sau `Animal&` — exact acest lucru permite
polimorfismului de la punctul 1 să funcționeze în continuare: clasa abstractă
servește drept "contract" (tip comun), iar clasele concrete (`Dog`, `Cat`)
trebuie să furnizeze o implementare pentru `makeSound()`, altfel rămân și
ele abstracte.

**Diferența față de `virtual` "normal" (nepur):** `virtual void f();` cu
corp este moștenibilă și redefinibilă, dar nu obligă pe nimeni să o facă, iar
clasa rămâne instanțiabilă. `virtual void f() = 0;` obligă orice clasă
concretă derivată să o implementeze, altfel rămâne și ea abstractă.

**Verificare concretă că `Animal` este într-adevăr abstractă**: nu e
suficient să te bazezi pe teorie, trebuie dovedit că respinge instanțierea.
Compilând un fișier de test cu `Animal a;` se obține o eroare *în faza de
compilare* (nu un crash la runtime):

```
error: variable type 'Animal' is an abstract class
note: unimplemented pure virtual method 'makeSound' in 'Animal'
```

De remarcat **ce rămâne neschimbat**: `Dog`/`Cat` continuă să fie
instanțiabile (implementează `makeSound()`), iar array-ul mixt de `Animal*`
folosit în ex01 funcționează identic în ex02 — subiectul cere asta explicit
("Everything should work as before"). Singura linie schimbată față de ex01
este `virtual void makeSound(void) const = 0;` în locul declarației cu corp
din `Animal.cpp`; nicio modificare la `Dog`, `Cat` sau `Brain`. Și aici,
`valgrind --leak-check=full` confirmă 0 leak-uri: transformarea unei clase în
abstractă nu schimbă nimic în gestionarea resurselor, doar regula de
instanțiere verificată de compilator.

## 5. Interfețe (ex03)

C++98 nu are un cuvânt cheie `interface` (spre deosebire de Java/C#). Prin
convenție, o clasă cu **doar** funcții virtuale pure (fără date, aproape
mereu cu un destructor virtual cu corp gol) este numită "interfață":

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

`Character` implementează (moștenește din) `ICharacter` furnizând un corp
pentru fiecare metodă — același mecanism de clasă abstractă de la punctul 4,
folosit însă pentru a descrie o *capacitate* pură, fără stare și fără
implementare partajată. O clasă poate moșteni (implementa) mai multe
interfețe simultan: aici nu e nevoie, dar acesta este motivul pentru care
există acest pattern — este echivalentul C++ al "implementării mai multor
interfețe".

### Pattern-ul "virtual clone"

`AMateria` (abstractă, nu interfață pură: are starea `type`) expune:

```cpp
virtual AMateria* clone() const = 0;
```

Problema pe care o rezolvă: constructorii (deci și constructorii de copiere)
**nu pot fi virtuali** în C++. Dacă ai un `AMateria*` și nu știi dacă indică
spre un `Ice` sau un `Cure`, nu poți scrie `new AMateria(*ptr)` pentru a
obține o copie de tipul corect — ai obține mereu un `AMateria` (sau o
eroare, fiind abstractă). `clone()` ocolește problema: este o funcție
*virtuală*, deci se rezolvă corect la runtime, iar în interiorul ei fiecare
subclasă face `return new Ice(*this);`, returnând un obiect nou de propriul
tip real. Exact acest lucru este folosit de `MateriaSource::createMateria()`
pentru a regenera o `Materia` pornind de la un "prototip" învățat prin
`learnMateria()`.

---

## 6. Concepte noi vs. concepte deja văzute în cpp_03

| Concept | cpp_03 (inheritance) | cpp_04 (polymorphism) |
|---|---|---|
| Relația is-a | Da (`class ScavTrap : public ClapTrap`) | Aceeași relație, dar exploatată la runtime |
| Override al unei metode | După nume, rezolvat la compile-time | Cu `virtual`, rezolvat la runtime (dispatch dinamic) |
| Pointer/referință către bază | Nefolosit pentru polimorfism | Folosit special pentru a demonstra dispatch-ul |
| Destructor | Nevirtual (nu era necesar, vezi `DIFESA.md` §1) | Virtual, altfel leak/UB la ștergere printr-un pointer către bază |
| OCF (Orthodox Canonical Form) | Da | Da, dar acum și cu deep copy pe resurse deținute (`Brain*`) |
| Compoziție "has-a" | Absentă | `Brain*` în interiorul lui `Dog`/`Cat` (ex01) |
| Clasă neinstanțiabilă | Absentă | Clasă abstractă prin funcție virtuală pură (ex02) |
| "Interfață" | Absentă | Clasă pur abstractă, fără stare (ex03) |
| Copiere polimorfică a unui obiect de tip necunoscut | Nu se aplică | `clone()` — pattern-ul de copiere virtuală (ex03) |

## Rezumat de reținut

Firul conducător al modulului este unul singur: **odată ce alegi să privești
un obiect printr-un pointer/referință către clasa lui de bază, cel care
decide ce cod rulează efectiv este `virtual`, nu tipul pointerului**. De aici
decurg toate consecințele: destructorul trebuie să fie virtual dacă vrei să
ștergi în siguranță printr-o referință la bază; o clasă care nu are sens să
existe de sine stătător devine abstractă printr-o funcție virtuală pură; o
interfață este doar un caz limită de clasă abstractă fără stare; iar atunci
când este nevoie să *copiezi* un obiect de tip necunoscut la runtime,
soluția este să treci printr-o metodă virtuală (`clone()`) în loc de un
constructor de copiere, care nu poate fi virtual.
