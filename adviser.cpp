#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

// Инициализация констант
const int N = 5000;
const int N_BOOKS = 1;

// Вектор с количеством слов в книге
int words_in_book[N_BOOKS] = {31566};

// Создание векторов для каждого типа слова  
vector <string> noun;
vector <string> adj;
vector <string> adv;  // Наречие
vector <string> verb;
vector <string> pron; // Местоимение 
vector <string> card; // Число
vector <string> ord;  // Исчисление
vector <string> prep; // "ПРИМЕР" Через, 

// Метод добавления слова в вектор
void add (string word,string type) {
    if(type == "noun")
        noun.push_back(word);
    else if(type == "adj")
        adj.push_back(word);
    else if(type == "adv")
        adv.push_back(word);
    else if(type == "verb")
        verb.push_back(word);
    else if(type == "pron")
        pron.push_back(word);
    else if(type == "card")
        card.push_back(word);
    else if(type == "ord")
        ord.push_back(word);    
    else if(type == "prep")
        prep.push_back(word);    
}

// Метод считывания
void cycle_for_words() {
    // Указание откуда считывать и куда
    ifstream fin("books/words.txt");
    for(int i = 0; i < N; i++) {
        string temp, temp2;
        fin >> temp >> temp >> temp >> temp2;
        add(temp, temp2);    
    }
}

// Рандомная книга
int rand_book() {
    int num_of_book_file = rand() % N_BOOKS;   
    return num_of_book_file;
}

// Совет по рандомным словам
string word_advise() { 
    cycle_for_words();
    string advise = adj[rand() % adj.size()] +  " " + noun[rand() % noun.size()] + " " + adv[rand() % adv.size()]+ " " + verb[rand() % verb.size()] + " " + noun[rand() % noun.size()];
    return advise;
}

// Совет из книги
string book_advise() {
    int book = rand_book();
    ifstream bin("books/"+to_string(book)+".txt");
    int i = 0;
    int sentence_num = rand() % words_in_book[book] + 1;
    string sentence;
    while (i != sentence_num) {
        char ch;
        sentence = "";
        do {
            bin >> ch;
            if (ch == ' ')
                sentence += ' ';
            else sentence += ch;
        } while(ch != '.');
        i++;
    }
    return sentence;
}

// Функция - ВСЕ БУКВЫ ЗАГЛАВНЫЕ
string to_upper_all_word (string for_upper) {
    for (int i = 0; i < for_upper.length(); i++)
        for_upper[i] -= 32;
    return for_upper;
}

// Выбор типа совета 
string advise (string type) {
    if(to_upper_all_word(type) == "HEADS OR TAILS") {
        if(1 + rand() % 2 == 1) return "Делать!";
        else return "Не делать!";
    }
    else if(to_upper_all_word(type) == "RANDOM WORDS") {
        return word_advise();
    } else if (to_upper_all_word(type) == "ADVISE FROM BOOKS") {
        return book_advise();
    } else if (to_upper_all_word(type) == "EXIT") {
        return "Желаю Вам удачи!)";
    } else if (to_upper_all_word(type) == "AGAIN") {
        return "AGAIN";
    } else {
        return "ERROR";
    }
}

// Ознакомление с типами советов
string hello() {
    cout << "Выберите тип совета(напишите \"HELP\", чтобы узнать типы советов): ";
    string choose;
    cin >> choose;
    if (to_upper_all_word(choose) == "EXIT") 
        return 0;
    else if (to_upper_all_word(choose) == "HELP") {
        cout << "\"HEADS OR TAILS\" - получите совет делать что-то или нет\n\"ADVISE FROM BOOKS\" - получите совет из книги\n\"RANDOM WORDS\" - попытайте удачу и получите  совет от рандомных слов\n\"EXIT\" - to exit"; 
        return "AGAIN";              
    }
    else 
        return choose;
}

// Проверка правильного ввода данных + повтор всего
string advise_after_check () {
    string result = advise(hello());
    if (result == "ERROR")
        return  "Что-то пошло не так, попробуйте заново";
    else    
        return result;
}
int main(){
    srand(time(0));
    cout << "Здравствуйте!" << endl;
    string result;
    do {
    result = advise_after_check();
    if (result != "AGAIN" && result != "ERROR")
        cout << result << endl;
    } while (result != "Желаю Вам удачи!)");
}