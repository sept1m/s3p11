#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdlib.h>

using namespace std;

// ��������� ��� ������������� ������� �����
struct DynamicArray
{
    string* data;
    int size;
    int capacity;

    DynamicArray(int cap) : size(0), capacity(cap)
    {
        data = new string[capacity];
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    void add(const string& entry)
    {
        if (size >= capacity)
        {
            capacity *= 2;
            string* newData = new string[capacity];
            for (int i = 0; i < size; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = entry;
    }

    void display() const {
        for (int i = 0; i < size; i++)
        {
            cout << i + 1 << ": " << data[i] << endl;
        }
    }

    void edit(int index, const string& newEntry)
    {
        if (index >= 0 && index < size)
        {
            data[index] = newEntry;
        } else
        {
            cout << "�������� ������." << endl;
        }
    }

    void remove(int index)
    {
        if (index >= 0 && index < size)
        {
            for (int i = index; i < size - 1; i++)
            {
                data[i] = data[i + 1];
            }
            size--;
        } else
        {
            cout << "�������� ������." << endl;
        }
    }

    void compute() const
    {
        cout << "���������� ����������� ��� �������, ��������, ������� ����� �������." << endl;
        cout << "����� ���������� �������: " << size << endl;
    }

    void save(const string& filename) const
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (int i = 0; i < size; i++)
            {
                file << data[i] << endl;
            }
            file.close();
            cout << "������ ������� ��������� � ����: " << filename << endl;
        } else
        {
            cout << "�� ������� ������� ���� ��� ������." << endl;
        }
    }
};

// ������� ��� ������ ������ �� �����
void readFromFile(DynamicArray& arr, const string& filename)
{
    ifstream file(filename);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            arr.add(line);
        }
        file.close();
        cout << "������ ������� ��������� �� �����: " << filename << endl;
    } else
    {
        cout << "�� ������� ������� ���� ��� ������." << endl;
    }
}

int main()
{
    system("chcp 1251>0");
    const int initialCapacity = 10;
    DynamicArray dataArray(initialCapacity);
    string filename;
    cout << "������� ��� ����� ��� �������� ������: ";
    cin >> filename;
    readFromFile(dataArray, filename);

    int choice;
    do
    {
        cout << "\n����:" << endl;
        cout << "1. �������� ������" << endl;
        cout << "2. ������������� ������" << endl;
        cout << "3. ���������� ������" << endl;
        cout << "4. �������� ������" << endl;
        cout << "5. ����������" << endl;
        cout << "6. ���������� ������ � ����� ����" << endl;
        cout << "0. �����" << endl;
        cout << "�������� ��������: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "������:" << endl;
                dataArray.display();
                break;
            case 2:
            {
                int index;
                string newEntry;
                cout << "������� ������ ��� ��������������: ";
                cin >> index;
                --index;
                cout << "������� ����� ������: ";
                cin.ignore();
                getline(cin, newEntry);
                dataArray.edit(index, newEntry);
                break;
            }
            case 3:
            {
                string newEntry;
                cout << "������� ����� ������: ";
                cin.ignore();
                getline(cin, newEntry);
                dataArray.add(newEntry);
                break;
            }
            case 4:
            {
                int index;
                cout << "������� ������ ��� ��������: ";
                cin >> index;
                --index;
                dataArray.remove(index);
                break;
            }
            case 5:
                dataArray.compute();
                break;
            case 6:
            {
                string newFilename;
                cout << "������� ��� ������ ����� ��� ����������: ";
                cin >> newFilename;
                dataArray.save(newFilename);
                break;
            }
            case 0:
                cout << "����� �� ���������." << endl;
            break;
            default:
                cout << "�������� �����." << endl;
        }
    }
    while (choice != 0);
    return 0;
}
