# Linux

## Kali linux

**Kali linux** je distribucija s prednaloženimi orodji za različne panoge kibernetske varnosti. V času krožka bomo v učilnicah uporabljali [VirtualBox verzijo](https://www.kali.org/get-kali/#kali-virtual-machines). Za uvoz distribucije v VirtualBox je potrebno [klikniti *Uvoz* oz. *Import*](https://docs.oracle.com/cd/E26217_01/E26796/html/qs-import-vm.html) kjer izberemo prenešeno sliko. Na naslednjem oknu lahko pregledamo nastavitve in, vkolikor se spoznate ali pa se hočete malo poigrati, spremenite izpisane parametre.


## BASH

**BASH** je uporabniški vmesnik kjer uporavljamo s sistemo (kot npr. `cmd.exe` na Windows-u). Z njim se bomo bolj podrobno spoznavali tekom krožka, za zdaj pa rabite razumeti naslednje ukaze:

| Ukaz          | Opis                                                        | Primer                  |
|:-------------:|:------------------------------------------------------------|:------------------------|
| `cd`          | Sprehajanje po mapah                                        | `cd folder`             |
| `ls`          | Izpiše mape in datoteke v mapi                              | `ls`                    |
| `cat`         | Izpiše vsebino datoteke                                     | `cat datoteka`          |
| `more`/`less` | Izpisano vsebino naredi "scrollable"                        | `more datoteka`         |
| `grep`        | Izpiše vrstice, ki vsebujejo neko zaporedje znakov (string) | `grep printf program.c` |
| `rm`          | Izbriši datoteko ali mapo                                   | `rm datoteka`           |
| `man`         | Izpiše dokumentacijo za program                             | `man cat`               |

Večina programov ima možnost posredovanja argumentov za prirejeno delovanje programa. Npr. če zaženemo `ls -a`, bomo v izhodu opazili tudi skrite datoteke in mape (v linux kontekstu to pomeni tiste datoteke ali mape, ki se začnejo s `.`).

Prav tako poznamo preusmeritve vhodov/izhodov. To pomeni, da lahko izhod enega programa preusmerimo na vhod drugega ali v datoteko, prav tako pa lahko vsebino datoteke podamo kot vhod pogramu. Preusmeritev naredimo z operatorjem `|`, npr: `ls | grep xyz` izpiše samo tiste datoteke, ki vsebujejo niz `xyz`. Za zapis izhoda v datoteko uporabimo `ls > datoteka`. Prav tako pa lahko nastavimo vsebino vhoda v program z `grep printf < progra.c` (uporabno za vpisovanje testnih podatkov v program v času razvoja).


## Datotečni sistem

S strani napadalca je zanimo pogledati številne pomembne mape:
* `/var/log/`: Tu se nahajajo izpisi delujočih programov (ang. logs)
* `/bin/`: Mapa za glavne binarne datoteke 
* `/proc/net/`: Skupek aktivnih spletnih povezav na/iz strežnika
* `/etc/`: Mapa za konfiguracijo programov
* `/home/`: Domača mapa za uporabnike (primerljivo z Windowsovim `C:\Users\`)


# Reverse engineering

Orodja, ki jih bomo potrebovali:
* `gdb`: Debugger za vpogled v delovanje programa
* `ghidra`: Disassembler za pretvorbo binarne datoteke nazaj v assembly in do neke mere tudi C kodo

Prav tako imamo na voljo veliko manjših uporabnih ukazov za pridobivanje podatkov iz datoteke, spreminjanje njene reprezentacije, branje metapodatkov, itd.
* `file`: Izpiše informacije o datoteki
* `strings`: Izpiše vsebine datoteke, ki izgledajo kot nizi
* `hexdump`: Spremeni binarno reprezentacijo v šestnajstiški (ang. hexadecimal) format
* `readelf`: Izpiše osnovne podatke o ELF (binarni) datoteki
* `objdump`: Izpiše logične predele binarne datoteke


## Primer

Med datotekam je tudi primer programa iz krožka `hello_world.c` in compiled verzija `hello_world`. Vkolikor hočete samo compile-ati to datoteko jo prenesite v virtualko, se v terminalu s pomočjo ukazov `ls` in `cd` premaknite kamor ste jo shranili (npr. `cd Desktop`) in jo prevedite z ukazom `gcc -o hello_world hello_world.c`.

> Za naslednje ukaze se morate prav tako premakniti v mapo, kjer se nahaja datoteka `hello_world`.

* `file hello_world`: Izpiše da je to ELF binarna datoteka
* `strings hello_world`: Izpiše vse nize v datoteki. Če malo preiščete izhod, boste med drugim našli nize, katere smo napisali v funkciji `printf` in `scanf`.
* `readelf -h hello_world`: Izpiše podatke v glavi (ang. headers) ELF programa
* `objdump -x hello_world`: Izpiše velik nabor metapodatkov o datoteki. Glavo, knjižnice (npr. `libc`), imena funkcij, itd.

Z zgornjimi ukazi lahko najdemo informacije o datoteki s katero se soočamo. Nato lahko to datoteko damo v program `ghidra` in jo disassemblamo. Za inštalacijo programa rabite naslednja dva ukaza:
```sh
sudo apt-get update
sudo apt-get install ghidra
```

Nato lahko poženete program z ukazom `ghidra`. Ob prvem zagonu morate narediti nov projekt nato pa lahko v njega dodate program `hello_world` (najlažje tako, da ga "drag and drop"-ate v okno projekta). V njem dvakrat kliknete dodan program in sledite oknom. Med prvim pogonom programa bo ghidra ponudila analizo programa, kar bo izvedlo disassembler in prevedlo kodo nazaj v C. Na levi strani lahko nato poiščete funkcije in med njimi funkcijo `main`. Na desnem oknu se vam bo pokazal disassemble-an program, ki bo zgledal podobno vhodnemu vendar ne popolnoma enako!

Tako se začne svet reverse engineering-a in od tu naprej bomo na nadaljnih programih gledali kaj delajo in kako jih nato rešujemo. Za testno nalogo lahko to probate nad `Rev 101` challange-om, ki je že na voljo na CTF spletni strani.
