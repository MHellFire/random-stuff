# Programowanie w MIPS32 assembly
---
Program napisany na architekturę MIPS 32 w języku asemblera. Jest on rozwiązaniem zadania, odpowiedzią na problem przedstawiony na jednym z forów internetowych [Programowanie w Spim Assembler - elektroda.pl](https://www.elektroda.pl/rtvforum/topic2276013.html).

## MIPS
---
[MIPS](https://pl.wikipedia.org/wiki/Architektura_MIPS) jest architekturą komputerową rozwijaną przez firmę MIPS Technologies. Istnieje zarówno w wersji 32- jak i 64-bitowej.

## SPIM (QtSpim)
---
[SPIM - Wikipedia](https://en.wikipedia.org/wiki/SPIM) jest symulatorem procesora MIPS32 (**R2000** oraz **E3000**). Wczytuje oraz wykonuje program napisany w jezyku asemblera dla tego procesora. Dostarcza prostyego debuggera. Nie wykonuje skompilowanych programów.

**QtSpim** jest najnowszą wersją symulatora **SPIM**. W odróżnieniu do starszych wersji jest ona wieloplatformowa (wspiera systemy Microsoft Windows, Mac OS X oraz GNU/Linux) oraz dzięki wykorzystaniu przenośnej biblioteki **Qt** interfejs użytkownika jest w tych systemach ujednolicony.

Najnowszy **QtSpim**, w którym można uruchomić poniższy program, można pobrań z oficjalnej strony [SPIM MIPS Simulator](http://spimsimulator.sourceforge.net/).

Bezpośredni link [spim mips simulator - Browse Files at SourceForge.net](https://sourceforge.net/projects/spimsimulator/files/).

## Treść zadania
---
Napisać program, który sprawdza czy podany ciąg znaków (wzorzec) wystepuje w łańcuchu podanych znaków. Zarówno wzorzec jak i łańcuch mogą być dowolnym ciągiem znaków pisarskich. Program ma pracować w dwóch wariantach: (1) z uwzględnieniem wielkości liter, (2) bez uwzględnienia wielkości liter.

## Algorytm działania
---
Algorytm jest bardzo prosty. Po uruchomieniu programu wyświetlamy komunikat powitalny oraz menu. Czekamy na decyzję użytkownika. Po wczytaniu odpowiedzi wykonujemy odpowiedni fragment kodu.

![8173562400_1334859989.png](:storage/9fec5bb6-299c-4d0c-ae2c-e29fe18255cd/90e4edd5.png)

## Kod źródłowy w języku asemblera
---
Kod żródłowy zmajduje się w pliku **MIPS32_QtSpim.asm**.

## Przykład działania
---
Program uruchamiamy we wspomnianym wcześniej symulatorze **QtSpim**. W menu klikamy na **File**, następnie **Load File** i wybieramy plik z naszym kodem. Po wczytaniu pliku klikamy w menu **Simulator** i wybbieramy **Run/Continue**. W tym momencie nasz program zostanie uruchomiony i powinniśmy go zobaczyć w oknie konsoli **Console**.

Poniżej znajduje się zrzut ekranu uruchomionego programu z kilkoma próbami wyszukania ciągu znaków w podanym tekście:
![console](https://github.com/MHellFire/random-stuff/blob/master/MIPS32-assembly/screenshots/74f7d35c.png)
![console](/screenshots/74f7d35c.png?raw=true)

## Autor
---
* **Mariusz Helfajer**

## Licencja
---
Niniejsze opracowanie udostępniam na licencji MIT. Szczegóły znajdują się w pliku LICENSE.

Copyright (c) 2019 Mariusz Helfajer
