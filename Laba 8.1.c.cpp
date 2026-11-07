#include <iostream>
#include <cstring>

using namespace std;

// Визначає довжину групи однакових символів, що починається з позиції pos.
//   str - рядок, що аналізується
//   pos - позиція першого символу групи (str[pos] != '\0')
// Повертає кількість однакових символів поспіль, починаючи з str[pos].
size_t CountSameChars(const char* str, size_t pos)
{
    char set[2] = { str[pos], '\0' };   // набір з одного символу str[pos]

    return strspn(str + pos, set);      // скільки символів підряд належать набору
}

// Виясняє, чи є в рядку четвірка сусідніх однакових символів.
//   str - рядок, що аналізується
// Повертає true, якщо така четвірка є, інакше - false.
bool ContainsFourSame(const char* str)
{
    size_t pos = 0;                     // pos - початок чергової групи однакових символів
    while (str[pos] != '\0')
    {
        size_t count = CountSameChars(str, pos);

        if (count >= 4)
            return true;

        pos += count;                   // переходимо до наступної групи
    }

    return false;
}

// Замінює кожну четвірку сусідніх однакових символів парою зірочок "**".
//   str - початковий рядок (не змінюється)
// Повертає вказівник на новий динамічний рядок-результат;
// пам'ять під нього має бути звільнена у місці виклику (delete[]).
// Група з count однакових символів дає count / 4 пар "**" та count % 4 символів,
// що залишилися (з "aaaaa" буде "**a").
char* Change(const char* str)
{
    char* dest = new char[strlen(str) + 1];   // результат не довший за початковий рядок
    char* t = dest;                           // t - місце, куди дописується результат

    size_t pos = 0;
    while (str[pos] != '\0')
    {
        size_t count = CountSameChars(str, pos);
        size_t pairs = count / 4;             // кількість четвірок у групі
        size_t rest = count % 4;              // символи, що не склали четвірку

        memset(t, '*', pairs * 2);            // кожна четвірка -> "**"
        t += pairs * 2;

        memcpy(t, str + pos, rest);           // решта символів групи без змін
        t += rest;

        pos += count;
    }
    *t = '\0';

    return dest;
}

int main()
{
    char str[101];

    cout << "Enter string:" << endl;
    cin.getline(str, 101);

    if (ContainsFourSame(str))
        cout << "String contains four identical adjacent characters" << endl;
    else
        cout << "String does not contain four identical adjacent characters" << endl;

    char* dest = Change(str);

    cout << "Original string (param) : " << str << endl;
    cout << "Modified string (result): " << dest << endl;

    delete[] dest;

    return 0;
}