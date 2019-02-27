/*********************************************************************************
 * This file is part of Age Calculator.                                          *
 *                                                                               *
 * Copyright © 2019 Mariusz Helfajer                                             *
 *                                                                               *
 * This software may be modified and distributed under the terms                 *
 * of the MIT license.  See the LICENSE files for details.                       *
 *                                                                               *
 * Permission is hereby granted, free of charge, to any person obtaining a copy  *
 * of this software and associated documentation files (the "Software"), to deal *
 * in the Software without restriction, including without limitation the rights  *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     *
 * copies of the Software, and to permit persons to whom the Software is         *
 * furnished to do so, subject to the following conditions:                      *
 *                                                                               *
 * The above copyright notice and this permission notice shall be included in    *
 * all copies or substantial portions of the Software.                           *
 *                                                                               *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     *
 * THE SOFTWARE.                                                                 *
 * *******************************************************************************/

#include <iostream>
#include <cmath>
#include <ctime>

#include <QDate>
#include <QtMath>

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

// Returns true if the specified year is a leap year; otherwise returns false.
bool isLeapYear(int year)
{
    // No year 0 in Gregorian calendar, so -1, -5, -9 etc are leap years
    // ISO 8601 - year 0000 is being equal to 1 BC
    if (year < 1)
        ++year;

    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// Returns the number of days in the month (28 to 31) for given date. Returns 0 if the date is invalid.
int daysInMonth(const tm &date)
{
    const char monthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (date.tm_mon == 2 && isLeapYear(date.tm_year))
        return 29;
    else
        return monthDays[date.tm_mon];
}

// Returns age[0] = years; age[1] = months; age[2] = days;
// or nullptr if any of the given dates is not valid or if the birth date is from the future.
int* calculateAge2(const tm &birthDate, const tm &todayDate)
{
    // TODO: check if dates are valid

    // check if the birth date is not from the future
    if (birthDate.tm_year > todayDate.tm_year)
        return nullptr;
    else if (birthDate.tm_year == todayDate.tm_year && birthDate.tm_mon > todayDate.tm_mon)
        return nullptr;
    else if (birthDate.tm_year == todayDate.tm_year && birthDate.tm_mon > todayDate.tm_mon && birthDate.tm_mday > todayDate.tm_mday)
        return nullptr;

    int *age = new int[3];                                // age[0] = years; age[1] = months; age[2] = days;
    int t1 = birthDate.tm_year*12 + birthDate.tm_mon - 1; // total months for birthdate
    int t2 = todayDate.tm_year*12 + todayDate.tm_mon - 1; // total months for now
    int dm = t2 - t1;                                     // delta months

    if (todayDate.tm_mday >= birthDate.tm_mday)
    {
        age[0] = int(floor(dm/12));                     // years
        age[1] = dm%12;                                 // months
        age[2] = todayDate.tm_mday - birthDate.tm_mday; // days
    }
    else
    {
        dm--;

        age[0] = int(floor(dm/12));                                              // years
        age[1] = dm%12;                                                          // months
        age[2] = daysInMonth(birthDate) - birthDate.tm_mday + todayDate.tm_mday; // days
    }

    return age;
}

int main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

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
}
