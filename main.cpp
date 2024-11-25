#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdlib.h>

using namespace std;

// Структура для динамического массива строк
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
            cout << "Неверный индекс." << endl;
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
            cout << "Неверный индекс." << endl;
        }
    }

    void compute() const
    {
        cout << "Вычисления выполняются над данными, например, подсчет числа записей." << endl;
        cout << "Общее количество записей: " << size << endl;
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
            cout << "Данные успешно сохранены в файл: " << filename << endl;
        } else
        {
            cout << "Не удалось открыть файл для записи." << endl;
        }
    }
};

// Функция для чтения данных из файла
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
        cout << "Данные успешно загружены из файла: " << filename << endl;
    } else
    {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

int main()
{
    system("chcp 1251>0");
    const int initialCapacity = 10;
    DynamicArray dataArray(initialCapacity);
    string filename;
    cout << "Введите имя файла для загрузки данных: ";
    cin >> filename;
    readFromFile(dataArray, filename);

    int choice;
    do
    {
        cout << "\nМеню:" << endl;
        cout << "1. Просмотр данных" << endl;
        cout << "2. Корректировка данных" << endl;
        cout << "3. Добавление данных" << endl;
        cout << "4. Удаление данных" << endl;
        cout << "5. Вычисления" << endl;
        cout << "6. Сохранение данных в новый файл" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Данные:" << endl;
                dataArray.display();
                break;
            case 2:
            {
                int index;
                string newEntry;
                cout << "Введите индекс для редактирования: ";
                cin >> index;
                --index;
                cout << "Введите новую строку: ";
                cin.ignore();
                getline(cin, newEntry);
                dataArray.edit(index, newEntry);
                break;
            }
            case 3:
            {
                string newEntry;
                cout << "Введите новую строку: ";
                cin.ignore();
                getline(cin, newEntry);
                dataArray.add(newEntry);
                break;
            }
            case 4:
            {
                int index;
                cout << "Введите индекс для удаления: ";
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
                cout << "Введите имя нового файла для сохранения: ";
                cin >> newFilename;
                dataArray.save(newFilename);
                break;
            }
            case 0:
                cout << "Выход из программы." << endl;
            break;
            default:
                cout << "Неверный выбор." << endl;
        }
    }
    while (choice != 0);
    return 0;
}
