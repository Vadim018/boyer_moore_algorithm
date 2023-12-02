#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// Функція для обчислення зсувів символів в шаблоні
unordered_map<char, int> calculate_shifts(const string& pattern) 
{
    unordered_map<char, int> shifts;

    int m = pattern.length();

    for (int i = 0; i < m - 1; i++) 
    {
        shifts[pattern[i]] = m - 1 - i;
    }

    return shifts;
}

// Функція для знаходження всіх входжень підрядка в тексті за допомогою алгоритму Бойера-Мура
vector<int> boyer_moore(const string& text, const string& pattern) 
{
    int n = text.length();
    int m = pattern.length();

    unordered_map<char, int> shifts = calculate_shifts(pattern);

    int i = m - 1;  // Початкова позиція в тексті
    int j = m - 1;  // Початкова позиція в шаблоні

    vector<int> occurrences;  // Зберігає позиції входжень підрядка

    while (i < n) {
        if (text[i] == pattern[j]) 
        {
            if (j == 0) 
            {
                occurrences.push_back(i);  // Знайдено входження підрядка
                i += m;  // Зсув на довжину шаблону
            }
            else 
            {
                i -= 1;
                j -= 1;
            }
        }
        else 
        {
            if (shifts.find(text[i]) != shifts.end()) 
            {
                int shift = shifts[text[i]];
                i += m - min(j, 1 + shift);
            }
            else 
            {
                i += m;
            }
            j = m - 1;
        }
    }
    return occurrences;
}

int main() 
{
    setlocale(LC_ALL, "Ukr");
    string text = "fdfacbacbacbadafc";
    string pattern = "cbacbacba";

    vector<int> occurrences = boyer_moore(text, pattern);

    if (!occurrences.empty()) 
    {
        cout << "Входження підрядка знайдені на позиціях: " << endl;

        for (int pos : occurrences)
        {
            cout << pos << endl;
        }
    }
    else 
    {
        cout << "Підрядок не знайдено!" << endl;
    }
    return 0;
}