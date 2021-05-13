#include <iostream>
#include <string>
using namespace std;

//��������� ���������� ���������.
//1. ?     - ����� ������ +
//2. [  ]  - �� ��������� �������� ���� ������ (���� ����� + ����� �� 0 �� 9) +
//3. [^  ] - �� ������ �� ��������� �������� (���� ����� + ����� �� 0 �� 9) +
//4.1. /d  - ����� �� 0 �� 9 (����������)
//4.2  /D  - ��, ����� ����� �� 0 �� 9 



class Regex
{
protected:
    string m_pattern;


public:
    //����������� �� ��������� � ����������� ��������� - ���� ����� ������. 
    Regex(string pattern = "?")
        :m_pattern(pattern)
    {
    }
    // ����� ������� �������.
    virtual void setPattern()
    {
        cout << "������� ������-������: ";
        getline(cin, m_pattern);
    }

    virtual void setPattern(string regex)
    {
        m_pattern = regex;
    }

    //������.
    string getPattern()
    {
        return m_pattern;
    }

    //������������� ������� ��� ���������� �������� ���������� ������ � ���������
    friend std::ostream& operator<< (std::ostream& out, const Regex& pattern);
    friend bool operator== (const Regex& c1, const Regex& c2);
    friend bool operator== (const Regex& c1, const string c2);
    friend bool operator!= (const Regex& c1, const Regex& c2);
    friend bool operator!= (const Regex& c1, const string c2);

    //���������� ���������� �����. ���� � ������
    operator string() { return m_pattern; }

    //���������� ��������� �������������
    Regex& operator= (const Regex& pattern)
    {
        m_pattern = pattern.m_pattern;
        return *this;
    }
    Regex& operator= (const string pattern)
    {
        m_pattern = pattern;
        return *this;
    }


    void regexReplace(int countSymbol, char symbol, int shift, char pattern)
    {
        int rangeStr = (m_pattern.length() - shift);
        char* str = new char[rangeStr];
        bool flag = true;
        for (int i = 0, k = 0; i < m_pattern.length(); i++)
        {
            if (m_pattern.at(i) == pattern && flag)
            {
                str[k++] = symbol;
                i += shift;
                flag = false;
            }
            else str[k++] = m_pattern.at(i);
        }
        str[strlen(str)] = '\0';
        for (int i = 0; i < m_pattern.length(); i++) m_pattern.at(i) = str[i];
        m_pattern.erase(rangeStr);
        delete[] str;
    };


    void checkSize(int size)
    {
        if (size <= 0)
        {
            cout << "������� ����� �������� �������. \n";
            exit(0);
        }
    }


    virtual bool compare(string txt) {
        int flag = 0;
        //�������� �� ��������.
        for (int i = 0; i < m_pattern.length(); i++)
        {
            if (m_pattern.at(i) == '[') flag += 3;
            if (m_pattern.at(i) == '^') flag += 1;
            if (m_pattern.at(i) == '/') flag += 1;
        }
        bool equals = m_pattern.length() == (txt.length() + flag) ? true : false;
        //���������� ���������� �������� � ����� ��� ���������.    
        for (int i = 0; i < m_pattern.length() && equals; i++)
        {
            //������ 1.
            if (m_pattern.at(i) == '?') continue;
            //������ 2 ��� 3.
            if (m_pattern.at(i) == '[')
            {
                //������ 3.
                if (m_pattern.at(i + 1) == '^')
                {
                    //������ ������������ ������ �� ��������� ��������
                    int shift = 4;
                    int sizeRange = ((m_pattern.at(i + 3) - m_pattern.at(i + 2)) + 1);
                    checkSize(sizeRange);
                    char* range = new char[sizeRange];
                    char j = m_pattern.at(i + 2);
                    //������������� ������������ ������ �� ��������� ��������
                    for (int k = 0; k < sizeRange; k++)
                    {
                        range[k] = j++;
                        // ��������� �������� � �������
                         //���� �� ��������
                        if (txt.at(i) == range[k])
                        {
                            delete[] range;
                            equals = false;
                            break;
                        }
                        //���� ��������
                        else if ((range[k] != txt.at(i)) && (k + 1 == sizeRange))
                        {
                            regexReplace(i, txt.at(i), shift, m_pattern.at(i));
                            delete[] range;
                        }
                    }

                }
                //������ 2.
                else
                {
                    //������ ������������ ������ �� ��������� ��������
                    int shift = 3;
                    int sizeRange = ((m_pattern.at(i + 2) - m_pattern.at(i + 1)) + 1);
                    checkSize(sizeRange);
                    char* range = new char[sizeRange];
                    char j = m_pattern.at(i + 1);
                    //������������� ������������ ������ �� ��������� ��������
                    for (int k = 0; k < sizeRange; k++)
                    {
                        range[k] = j++;
                        // ��������� �������� � �������
                        //���� ��������
                        if (txt.at(i) == range[k])
                        {
                            regexReplace(i, range[k], shift, m_pattern.at(i));
                            delete[] range;
                            break;
                        }
                        //���� �� ��������
                        else if ((range[k] != txt.at(i)) && (k + 1 == sizeRange))
                        {
                            delete[] range;
                            equals = false;
                        }
                    }

                }
            }
            //������ 4
            if (m_pattern.at(i) == '/')
            {
                //������ 4.1
                if (m_pattern.at(i + 1) == 'd')
                {
                    int shift = 1;
                    int* range = new int[10];
                    int j = 48;
                    for (int k = 0; k < 10; k++)
                    {
                        range[k] = j++;
                        // ��������� �������� � �������
                        //���� ��������
                        if (txt.at(i) == range[k])
                        {
                            regexReplace(i, range[k], shift, m_pattern.at(i));
                            delete[] range;
                            break;
                        }
                        //���� �� ��������
                        else if ((range[k] != txt.at(i)) && (k + 1 == 10))
                        {
                            delete[] range;
                            equals = false;
                        }
                    }
                }
                //������ 4.2
                else if (m_pattern.at(i + 1) == 'D')
                {
                    int shift = 1;
                    char* range = new char[10];
                    char j = 48;
                    for (int k = 0; k < 10; k++)
                    {
                        range[k] = j++;
                        // ��������� �������� � �������
                        //���� ��������
                        if (txt.at(i) == range[k])
                        {
                            delete[] range;
                            equals = false;
                            break;
                        }
                        //���� �� ��������
                        else if ((range[k] != txt.at(i)) && (k + 1 == 10))
                        {
                            regexReplace(i, txt.at(i), shift, m_pattern.at(i));
                            delete[] range;
                        }
                    }
                }
            }

            //���� ������ ������� � ������ �� �������������
            if (m_pattern.at(i) != txt.at(i))
            {
                equals = false;
            }

        }
        return (equals);
    }
};

class FileMask : public Regex
{

public:

    void setPattern()
    {
        getline(cin, m_pattern);
    }

    Regex& operator= (const string pattern)
    {
        m_pattern = pattern;
        return *this;
    }

    string getPattern()
    {
        return m_pattern;
    }

    bool IsExtensionMatch(string extension)
    {

        return(compare(extension));

    }
    bool isNameMatch(string fileName)
    {

        return(compare(fileName));

    }
    void IsFileMatch(string file)
    {
        int lastDotNumber = 0;
        string fileName;
        string extension;
        for (int i = 0; i < file.length(); i++)
        {
            if (file.at(i) == '.')
            {
                lastDotNumber = i;
            }
        }
        fileName.assign(file, 0, lastDotNumber);
        extension.assign(file, lastDotNumber + 1, file.length() - lastDotNumber);

        cout << "������� ������ ����� �����: ";
        setPattern();

        bool NameMatch = isNameMatch(fileName);
        cout << "������� ������ ���������� �����: ";
        setPattern();
        bool ExtensionMatch = IsExtensionMatch(extension);

        if (NameMatch == true && ExtensionMatch == true)
        {
            cout << "��� ����� � ���������� ������������� �������" << endl;
        }
        else if (NameMatch == true && ExtensionMatch == false)
        {
            cout << "����� �� �������� ��� ������" << endl;
        }
        else if (NameMatch == false && ExtensionMatch == true)
        {
            cout << "��� ����� �� �������� ��� ������" << endl;
        }
        else if (NameMatch == false && ExtensionMatch == false)
        {
            cout << "������ �� �������� ��� ������" << endl;
        }
    }

};

class SimpleRegex : public Regex
{
public:
    void setPattern()
    {
        cout << "������� ���������� ������: ";
        getline(cin, m_pattern);
    }

    Regex& operator= (const string pattern)
    {
        m_pattern = pattern;
        return *this;
    }

    bool compare(string simpleRegex)
    {

        bool equals = m_pattern.length() == (simpleRegex.length()) ? true : false;
        //���������� ���������� �������� � ����� ��� ���������.    
        for (int i = 0; i < m_pattern.length() && equals; i++)
        {
            //������ 1.
            if (m_pattern.at(i) == '?') continue;
            if (m_pattern.at(i) != simpleRegex.at(i))
            {
                equals = false;
            }

        }
        return (equals);

    }
};


//���������� ��������� ������
std::ostream& operator<< (std::ostream& out, const Regex& pattern)
{
    out << "Pattern: " << pattern.m_pattern << endl;
    return out;
}
//���������� ��������� ��������� � ������ ���������� ����������
bool operator== (const Regex& c1, const Regex& c2)
{
    return (c1.m_pattern == c2.m_pattern);
}
//���������� ��������� ��������� �� �������
bool operator== (const Regex& c1, string c2)
{
    return (c1.m_pattern == c2);
}


//���������� ��������� ��������� � ������ ���������� ����������
bool operator!= (const Regex& c1, const Regex& c2)
{
    return !(c1 == c2);
}
//���������� ��������� ��������� �� �������
bool operator!= (const Regex& c1, string c2)
{
    return !(c1 == c2);
}



void GetRegex(Regex* type, string regex)
{
    type->setPattern(regex);
}

int main()
{
    string text;
    FileMask asd;
    setlocale(LC_ALL, "RUS");
    cout << "������� ������ ��� ��������: ";
    getline(cin, text);
    asd.IsFileMatch(text);
    system("pause");
    return 0;
}
