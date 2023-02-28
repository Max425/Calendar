#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Calendar 
{
public:
    Calendar() {
        // Дата по умолчанию
        _day = 1; 
        _month = 1; 
        _year = 2023;
    }

    void SetData(string data) {
        if (!CheckData(data))
            throw invalid_argument("Дата указана некоректно");
    }
    
    string GetDayOfWeekByData() {
        int dayOfWeek = (_day + _monthCode[_month] + (6 + _year % 100 + (_year % 100) / 4) % 7) % 7;
        return _DayOfWeek[dayOfWeek];
    }

    bool IsDataWeekend() {
        return (this->GetDayOfWeekByData() == "Суббота" ||
            this->GetDayOfWeekByData() == "Воскресенье" ||
            (this->_day >= 1 && this->_day <= 8 && this->_month == 2) ||
            (this->_day == 23 && this->_month == 2) ||
            (this->_day == 8 && this->_month == 3) ||
            (this->_day == 1 && this->_month == 5) ||
            (this->_day == 9 && this->_month == 5) ||
            (this->_day == 12 && this->_month == 6) ||
            (this->_day == 4 && this->_month == 11))
            ? true
            : false;
    }

    int GetCountOfDayInMonth() {
        return _month == 2 && _year % 4 == 0
            ? _countOfDayInMonth[_month - 1] + 1
            : _countOfDayInMonth[_month - 1];
    }
private:
    map<int, int> _monthCode{
        {1, 1}, {2, 4}, {3, 4}, {4, 0}, {5, 2}, {6, 5}, 
        {7, 0}, {8, 3}, {9, 6}, {10, 1}, {11, 4}, {12, 6},
    };

    string _DayOfWeek[7]{ "Суббота", "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница" };

    int _countOfDayInMonth[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int _day, _month, _year;
    
    // проверка даты
    bool CheckData(string data) {
        vector<string> dataVector = ParseData(data);
        return IsDataInt(dataVector) && 
            _year >= 0 && _year <= 10000 && 
            _month >= 1 && _month <= 12 && 
            _day >= 1 && _day <= this->GetCountOfDayInMonth()
            ? true
            : false;
    }
    
    // Переводим дату из строки в вектор (spit по точке)
    vector<string> ParseData(string data) {
        vector<string> dataVector;
        string s;
        for (auto i = 0; data[i] != '\0'; ++i) {
            if (data[i] != '.')
                s += data[i];
            else {
                dataVector.push_back(s);
                s.clear();
            }
        }
        dataVector.push_back(s); s.clear();
        return dataVector;
    }
    
    // Проверяем, что дата - числа типа int
    bool IsDataInt(vector<string> dataVector) {
        return dataVector.size() != 3 || 
            sscanf_s(dataVector[0].c_str(), "%d", &_day) != 1 ||
            sscanf_s(dataVector[1].c_str(), "%d", &_month) != 1 || 
            sscanf_s(dataVector[2].c_str(), "%d", &_year) != 1 
            ? false 
            : true;
    }  
};

int main()
{
    setlocale(LC_ALL, "Russian");
    string data;
    cout << "Введите даду в формате DD.MM.YYYY: ";
    cin >> data;
    auto calendar = new Calendar();
    try {
        calendar->SetData(data);
    }
    catch (invalid_argument ex) {
        cout << ex.what();
        return -1;
    }
    cout << "День недели по дате: " << calendar->GetDayOfWeekByData() << endl;
    cout << "Количество дней в месяце: " << calendar->GetCountOfDayInMonth() << endl;
    
    if (calendar->IsDataWeekend()) 
        cout << "Выходной!" << endl;
    else 
        cout << "Будни!" << endl; 
    
    return 0;
}