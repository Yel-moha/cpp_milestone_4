# Ereditarieta: il punto di ex01

`ScavTrap` e un tipo piu specifico di `ClapTrap`:

```cpp
class ScavTrap : public ClapTrap
```

La parte `public` esprime una relazione "ScavTrap e un ClapTrap". Per questo
ScavTrap eredita i dati e i metodi pubblici di ClapTrap, ad esempio `takeDamage`
e `beRepaired`. Non dobbiamo riscriverli.

Gli attributi di ClapTrap sono `protected`: il codice esterno non puo leggerli o
modificarli, ma la classe figlia puo usarli per impostare le sue statistiche:

| Tipo | HP | Energia | Danno |
| --- | ---: | ---: | ---: |
| ClapTrap | 10 | 10 | 0 |
| ScavTrap | 100 | 50 | 20 |

ScavTrap definisce un proprio `attack()`. Quando chiami `scavtrap.attack(...)`,
viene quindi usata la versione di ScavTrap, con il suo messaggio, invece di quella
ereditata. `guardGate()` e invece una nuova abilita che esiste solo in ScavTrap.

## Costruzione e distruzione

Un oggetto ScavTrap contiene prima di tutto la sua parte ClapTrap. Per questo, quando
costruisci uno ScavTrap, C++ costruisce sempre prima ClapTrap e poi ScavTrap:

```text
ClapTrap constructor
ScavTrap constructor
```

Alla fine della vita dell'oggetto accade l'opposto:

```text
ScavTrap destructor
ClapTrap destructor
```

E necessario: ScavTrap potrebbe usare dati della parte ClapTrap, quindi quella base
deve esistere prima e deve essere eliminata per ultima.

## Riassunto da ricordare

Ex01 non chiede di copiare ClapTrap e cambiare tre numeri. Chiede di modellare una
relazione "e un": ScavTrap riusa comportamento e stato comune, aggiunge un'abilita e
personalizza l'attacco. I messaggi di costruttori e distruttori servono a rendere
visibile questa catena.
