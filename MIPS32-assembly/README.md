# Programowanie w MIPS32 assembly
---
Poniższy program napisany jest na architekturę MIPS 32 w języku asemblera. Jest on rozwiązaniem zadania, odpowiedzią na problem przedstawiony na jednym z forów internetowych [Programowanie w Spim Assembler - elektroda.pl](https://www.elektroda.pl/rtvforum/topic2276013.html).

## MIPS
---
[MIPS](https://pl.wikipedia.org/wiki/Architektura_MIPS) jest architekturą komputerową rozwijaną przez firmę MIPS Technologies. Istnieje zarówno w wersji 32- jak i 64-bitowej.

## SPIM (QtSpim)
---
[SPIM - Wikipedia](https://en.wikipedia.org/wiki/SPIM) jest symulatorem procesora MIPS. Program symuluje pracę procesorów **R2000** oraz **E3000**.

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
Kod żródłowy
```asm
# Copyright © 2012 Mariusz Helfajer
#
# Uruchamiane i testowane w QtSpim 9.1.7.
#
# This software may be modified and distributed under the terms
# of the MIT license.  See the LICENSE files for details.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

.data
msg1:     .asciiz "\nWpisz tekst (maksymalnie 100 znakow): "
msg2:     .asciiz "Podaj szukany wzorzec: "
msgY:     .asciiz "\nWzorzec wystepuje\n"
msgN:     .asciiz "\nWzorzec nie wystepuje\n"
msgMenu:  .asciiz "\nMenu:\n1. Sprawdzenie z uwzglednieniem wielkosci liter\n2. Sprawdzenie bez uwzglednienia wielkosci liter\n3. Koniec\n\nTwoj wybor: "
msgStart: .asciiz "########## Witam w moim programie ##########\n"
msgEnd:   .asciiz "\nKoniec programu, dziekuje i do widzenia :)"
str1:     .space 100                 # tekst
str2:     .space 100                 # szukany wzorzec
choice:   .word 0                    # wybrana opcja menu

.text
.globl main

main:
        # powitanie
        la $a0, msgStart
        li $v0, 4                    # print_string
        syscall

menu:
        # wyswietlenie menu
        la $a0, msgMenu
        li $v0, 4                    # print_string
        syscall

        # odczyt wyboru
        li $v0, 5                    # read_int
        syscall
        sw $v0, choice               # kopiowanie wybranej opcji menu pod adres choice

        # sprawdzenie wybranej opcji
        lw $t0, choice
        li $t1, 1                    # opcja 1 z menu
        bne $t0, $t1, opcja2         # jesli nie wybrano 1 skocz do opcja2

        # wybrano opcje 1

        # wyswietlenie prosby o podanie tekstu
        la $a0, msg1
        li $v0, 4                    # print_string
        syscall

        # odczyt tekstu
        li $v0, 8                    # read_string, $a0 = buffer, $a1 = length
        la $a0, str1
        addi $a1, $zero, 100
        syscall

        # wyswietlenie prosby o podanie wzorca
        la $a0, msg2
        li $v0, 4                    # print_string
        syscall

        # odczyt wzorca
        li $v0, 8                    # read_string, $a0 = buffer, $a1 = length
        la $a0, str2
        addi $a1, $zero, 100
        syscall

        la $a0, str1                 # argumenty funkcji
        la $a1, str2
        addi $a2, $zero, 0           # 0 = sprawdzanie z uwzglednienie wielkosci liter
        jal searchstr                # wywolanie funkcji

        beq $v0, $zero, ok1          # jesli funkcja zwrocila 0 skocz do ok1

        la $a0, msgN
        li $v0, 4                    # print_string
        syscall
        j menu

        ok1:
            la $a0, msgY
            li $v0, 4                # print_string
            syscall
            j menu

opcja2:
        # sprawdzenie wybranej opcji
        lw $t0, choice
        li $t1, 2                    # opcja 2 z menu
        bne $t0, $t1, opcja3         # jesli nie wybrano 2 skocz do opcja3

        # wybrano opcje 2
        
        # wyswietlenie prosby o podanie tekstu
        la $a0, msg1
        li $v0, 4                    # print_string
        syscall

        # odczyt tekstu
        li $v0, 8                    # read_string, $a0 = buffer, $a1 = length
        la $a0, str1
        addi $a1, $zero, 100
        syscall

        # wyswietlenie prosby o podanie wzorca
        la $a0, msg2
        li $v0, 4                    # print_string
        syscall

        # odczyt wzorca
        li $v0, 8                    # read_string, $a0 = buffer, $a1 = length
        la $a0, str2
        addi $a1, $zero, 100
        syscall

        la $a0, str1                 # argumenty funkcji
        la $a1, str2
        addi $a2, $zero, 1           # 1 = sprawdzanie bez uwzgledniania wielkosci liter
        jal searchstr                # wywolanie funkcji

        beq $v0, $zero, ok2          # jesli funkcja zwrocila 0 skocz do ok2

        la $a0, msgN
        li $v0, 4                    # print_string
        syscall
        j menu

        ok2:
            la $a0, msgY
            li $v0, 4                # print_string
            syscall
            j menu

opcja3:
        # sprawdzenie wybranej opcji
        lw $t0, choice
        li $t1, 3                    # opcja 3 z menu
        bne $t0, $t1, menu           # jesli nie wybrano 3 skocz do wyswietlenia menu

        # wybrano opcje 3
        
        # pozegnanie
        la $a0, msgEnd
        li $v0, 4                    # print_string
        syscall

        li $v0, 10                   # exit
        syscall

# funkcja szukajaca wzorca w tekscie

searchstr:
        add $t1, $zero, $a0                  # tekst
        add $t2, $zero, $a1                  # wzorzec

        lb $t4($t2)                          # kopiowanie bajta (znaku) spod adresu wskazywanego przez $t2 pod adres $t4
        beq $t4, 10, endN                    # jesli pierwszy znak to 10 = 0xa, znak konca linii, skocz do endN
        
        loop:
            lb $t3($t1)                      # kopiowanie bajta (znaku) spod adresu wskazywanego przez $t1 pod adres $t3
            beq $t3, 10, endN                # koniec tekstu, jesli znak to 10 = 0xa, znak konca linii, skocz do endN
            
            # wybor sposobu porownania
            beqz $a2, check                  # jesli 0 to rozrozniamy wielkosc liter i skaczemy do check
            
            # zamiana duzych liter na male
            
            # sprawdzenie wzorca
            slti $t5, $t4, 65                # $t5 = ($t4 < 65), 0 - false, 1 - true
            bnez $t5, checkstr2              # jesli 1 - true skaczemy do sprawdzania tekstu
            slti $t5, $t4, 91                # $t5 = ($t4 < 91), 0 - false, 1 - true
            beqz $t5, checkstr2              # jesli 0 - false to skaczemy do sprawdzania tekstu
            addi $t4, $t4, 32                # zamiana na mala litera $t4 = $t4 + 32
            
            # sprawdzenie tekstu
            checkstr2:
                slti $t5, $t3, 65            # $t5 = ($t3 < 65), 0 - false, 1 - true
                bnez $t5, check              # jesli 1 - true skaczemy do porownywania
                slti $t5, $t3, 91            # $t5 = ($t3 < 91), 0 - false, 1 - true
                beqz $t5, check              # jesli 0 - false to skaczemy do porownywania
                addi $t3, $t3, 32            # zamiana na mala litera $t3 = $t3 + 32
            
        check:
            beq $t3, $t4, checked            # porownanie 2 znakow, jesli sa takie same skocz do checked

            # znaki nie sa takie same
            add $t2, $zero, $a1              # do $t2 kopiujemy adres poczatku wzorca
            lb $t4($t2)                      # kopiowanie bajta (znaku) spod adresu wskazywanego przez $t2 pod adres $t4
            addi $t1, $t1, 1                 # adres kolejnego znaku tekstu, przesuniecie adresu w $t1 o 1
            j loop                           # skok do loop

            # znaki sa takie same
            checked:
                addi $t2, $t2, 1             # adres kolejengo znaku wzorca, przesuniecie adresu w $t2 o 1
                lb $t4($t2)                  # kopiowanie bajta (znaku) spod adresu wskazywanego przez $t2 pod adres $t4
                beq $t4, 10, endY            # koniec wzorca, jesli znak to 10 = 0xa, znak konca linii, skocz do endY
                addi $t1, $t1, 1             # adres kolejnego znaku tekstu, przesuniecie adresu w $t1 o 1
                j loop

            endY:                            # znaleziono
                add $v0, $zero, $zero
                j endfunction

            endN:                            # nie znaleziono
                addi $v0, $zero, 1

            endfunction:
                jr $ra
```

## Przykład działania
---
Program uruchamiamy we wspomnianym wcześniej symulatorze **QtSpim**. W menu klikamy na **File**, następnie **Load File** i wybieramy plik z naszym kodem. Po wczytaniu pliku klikamy w menu **Simulator** i wybbieramy **Run/Continue**. W tym momencie nasz program zostanie uruchomiony i powinniśmy go zobaczyć w oknie konsoli **Console**.

Poniżej znajduje się zrzut ekranu uruchomionego programu z kilkoma próbami wyszukania ciągu znaków w podanym tekście:
![qtspim.png](:storage/9fec5bb6-299c-4d0c-ae2c-e29fe18255cd/74f7d35c.png)

## Autor
---
* **Mariusz Helfajer**

## Licencja
---
Niniejsze opracowanie udostępniam na licencji MIT. Szczegóły znajdują się w pliku LICENSE.

Copyright (c) 2019 Mariusz Helfajer
