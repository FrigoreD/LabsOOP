#include <iostream>
#include <string>
using namespace std;

int main()
{
    setlocale(LC_ALL, "russian");
    cout << "������� ������-������: ";
    string temp, str; getline(cin, temp);
    cout << "������� ������ ��� �������: ";
    getline(cin, str);
    bool equals = temp.length() == str.length() ? true : false;
    for (int i = 0; i < temp.length() && equals; i++)
    {
        if (temp.at(i) == '?') continue;
        if (temp.at(i) != str.at(i)) equals = false;
    }
    if (equals) cout << "��������� ������ ������������� �������." << endl;
    else cout << "������ �� �������� ��� ������" << endl;
    system("pause");
    return 0;
}