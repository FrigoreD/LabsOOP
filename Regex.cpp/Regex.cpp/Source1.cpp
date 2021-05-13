#include <iostream>
#include <string>
using namespace std;

int main()
{
    setlocale(LC_ALL, "russian");
    cout << "Введите строку-шаблон: ";
    string temp, str; getline(cin, temp);
    cout << "Введите строку для анализа: ";
    getline(cin, str);
    bool equals = temp.length() == str.length() ? true : false;
    for (int i = 0; i < temp.length() && equals; i++)
    {
        if (temp.at(i) == '?') continue;
        if (temp.at(i) != str.at(i)) equals = false;
    }
    if (equals) cout << "Введенная строка соответствует шаблону." << endl;
    else cout << "Строка не подходит под шаблон" << endl;
    system("pause");
    return 0;
}