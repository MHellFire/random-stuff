# Obliczanie wieku
---
Algorytm oraz kody źródłowe (w C++ oraz dodatkowo z wykorzystaniem biblioteki Qt) obliczający wiek osoby na podstawie podanej daty urodzenia w sposób jaki to się robi na codzień.

## Co to jest
---
Przedstawiam algorytm oraz kod źródłowy obliczający wiek osoby na podstawie podanej daty urodzenia w sposób jaki to się robi na codzień. Nie jest to proste obliczenie liczby dni od daty urodzenia do dnia dzisiejszego i późniejsze dzielenie jej przez stałą liczbę dni w roku czy miesiącu. Algorytm obliczania jest nieco bardziej skomplikowany jednak daje w wyniku naturalny wiek.

W niektórych przypadkach wynik miesięcy oraz dni obliczony poniższym algorytmem może być mylący, szczególnie gdy data początkowa (np. urodzenia) jest ostatnim dniem danego miesiąca). Na przykład liczymy okres od 20 lutego do 20 marca jako jeden miesiąc. Jednak są dwa sposoby na obliczenie wieku np. z 28.02.2015 do 31.03.2015. Jeśli przyjmiemy, że od 28.02 do 28.03 jest jeden miesiąc, wtedy otrzymujemy jako wynik jeden miesiąc oraz 3 dni.

## Przykłady
---
W poniższej tabeli przedstawiam kilka przykładów obliczonego wieku osoby o podanej **Data urodzenia** wyliczonej dla daty z kolumny **Data dzisiejsza**.

| Data dzisiejsza | - | Data urodzenia | = | Lata | Miesiące | Dni |
|-----------------|:-:|----------------|:-:|------|----------|-----|
|2018-06-29| - |2019-02-12| = |0|0|0
|2019-02-12| - |2019-01-01| = |0|1|11
|2019-02-12| - |2017-02-01| = |2|0|11
|2019-02-12| - |1980-02-28| = |37|0|0
|2019-02-12| - |1980-02-28| = |37|0|0

## Algorytm
----
W algorytmie zakładamy, że data urodzenia jest prawidłowa, tzn. nie jest datą z przyszłości.


**floor** - to zaokrąglanie liczby zawsze w dół. Przykładowo liczba 5.9999 zostanie zaokrąglona do 5.
[floor - C++ Reference](http://www.cplusplus.com/reference/cmath/floor/)


**%** - to reszta z dzielenia liczb całkowitych. Przykładowo **5%2** da nam wynik **1**.

## Kod w Qt (C++)
---
Poniższy kod napisany jest w **C++** z wykorzystaniem niektórych typów zmiennych (np. ```QDate```) oraz funkcji (np. ```qFloor```) z biblioteki **Qt** (cross-platform SDK). Szczegónie wykorzystanie klasy ```QDate``` bardzo ułatwia napisanie poniższego kodu.

Funkcja wyliczająca wiek:

```C++
// Returns age[0] = years; age[1] = months; age[2] = days;
// or nullptr if any of the given dates is not valid or if the birth date is from the future.
int* calculateAge(const QDate &birthDate, const QDate &todayDate)
{
    // check if the birth date is valid date
    if (!birthDate.isValid())
        return nullptr;
    // check if the today date is valid date
    if (!todayDate.isValid())
        return nullptr;
    // check if the birth date is not from the future
    if (birthDate > todayDate)
        return nullptr;

    int *age = new int[3];                                // age[0] = years; age[1] = months; age[2] = days;
    int t1 = birthDate.year()*12 + birthDate.month() - 1; // total months for birthdate
    int t2 = todayDate.year()*12 + todayDate.month() - 1; // total months for now
    int dm = t2 - t1;                                     // delta months

    if (todayDate.day() >= birthDate.day())
    {
        age[0] = qFloor(dm/12);                     // years
        age[1] = dm%12;                             // months
        age[2] = todayDate.day() - birthDate.day(); // days
    }
    else
    {
        dm--;

        age[0] = qFloor(dm/12);                                               // years
        age[1] = dm%12;                                                       // months
        age[2] = birthDate.daysInMonth() - birthDate.day() + todayDate.day(); // days
    }

    return age;
}
```

Przykładowe wywołanie funkcji:
```C++
QDate birthDate(QDate(2006, 1, 30));
QDate currentDate(QDate::currentDate());

int *tmp = calculateAge(birthDate, currentDate);

if (tmp != nullptr)
{
    std::cout << "Birth date: " << birthDate.toString("dd.MM.yyyy").toStdString() << std::endl;
    std::cout << "Current date: " << currentDate.toString("dd.MM.yyyy").toStdString() << std::endl;
    std::cout << "Years: " << tmp[0] << std::endl;
    std::cout << "Months: " << tmp[1] << std::endl;
    std::cout << "Days: " << tmp[2] << std::endl << std::endl;
}

delete []tmp;
```

### Kompilacja
W celu kompilacji kodu z wykorzystaniem bilbioteki Qt wykonujemy poniższe polecenia:
```bash
qmake -project
qmake
make
```

Po wykonaniu pierwszego polecenia i wygenerowaniu pliku ***.pro** można do niego dopisać poniższy kod, dodający flagi dla kompilatora GCC, które włączą dokładne, rygorystyczne sprawdzanie napisanego kodu oraz wymuszą użycie standardu C++17:
```QMAKE
QMAKE_CXXFLAGS += -std=c++17 /
    -Wall /
    -Wextra /
    -Wpedantic /
    -Wconversion
```
Następnie można uruchomić program.

## Kod w C++
---
Kod w C++ bez wykorzystania dodatkowych bibliotek jest niestety dużo bardziej skomplikowany. Musimy sami napisać kilka pomocniczych funkcji:
* Funkcja sprawdzająca czy dany rok jest przestępny
```C++
// Returns true if the specified year is a leap year; otherwise returns false.
bool isLeapYear(int year)
{
    // No year 0 in Gregorian calendar, so -1, -5, -9 etc are leap years
    // ISO 8601 - year 0000 is being equal to 1 BC
    if (year < 1)
        ++year;

    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}
```
* Funkcja sprawdzająca ile dni ma dany miesiąc (z uwzględnieniem lat przestępnych)
```C++
// Returns the number of days in the month (28 to 31) for given date. Returns 0 if the date is invalid.
int daysInMonth(const tm &date)
{
    const char monthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (date.tm_mon == 2 && isLeapYear(date.tm_year))
        return 29;
    else
        return monthDays[date.tm_mon];
}
```

Powyższe funkcje są wzorowane na metodach z klasy ```QDate``` z biblioteki **Qt**.

Przykładowe wywołanie funkcji:
```C++
tm birthDate2;
birthDate2.tm_year = birthDate.year();
birthDate2.tm_mon = birthDate.month();
birthDate2.tm_mday = birthDate.day();
tm currentDate2;
currentDate2.tm_year = currentDate.year();
currentDate2.tm_mon = currentDate.month();
currentDate2.tm_mday = currentDate.day();

int *tmp2 = calculateAge2(birthDate2, currentDate2);

if (tmp2 != nullptr)
{
    char date[11];
    birthDate2.tm_year-=1900; // int tm_year; years since 1900
    birthDate2.tm_mon-=1;     // int tm_mon; months since January [0, 11]
    if (strftime(date, sizeof(date), "%d.%m.%Y", &birthDate2) != 0)
    {
        std::cout << "Birth date: " << date << std::endl;
    }

    currentDate2.tm_year-=1900; // int tm_year; years since 1900
    currentDate2.tm_mon-=1;     // int tm_mon; months since January [0, 11]
    if (strftime(date, sizeof(date), "%d.%m.%Y", &currentDate2) != 0)
    {
        std::cout << "Current date: " << date << std::endl;
    }

    std::cout << "Years: " << tmp2[0] << std::endl;
    std::cout << "Months: " << tmp2[1] << std::endl;
    std::cout << "Days: " << tmp2[2] << std::endl << std::endl;
}

delete []tmp2;
```

## Autor
---
* **Mariusz Helfajer**

## Licencja
---
Niniejsze opracowanie udostępniam na licencji MIT. Szczegóły znajdują się w pliku LICENSE.

Copyright (c) 2019 Mariusz Helfajer


