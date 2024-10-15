#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


std::string alphabet = "ETYOPAHKXCBM";
std::vector<std::string> car_brands = { "Toyota","Nissan", "Mitsubishi", "Honda", "Subaru", "Lexus", "Mazda", "Lada" };
std::vector<std::string> car_models = { "Rav4", "Aqua", "Belta", "Probox", "Prius", "Logan", "Almera" };
std::vector<std::string> months = { " January ", " February "," March "," April "," May "," June ", " July ", " August ", " September ", " October ", " November ", " December ", " January  ", " February  "," March  "," April  "," May  "," June  ", " July  ", " August  ", " September  ", " October  ", " November  ", " December  " };
struct date
{
    int day;
    int month;
    int year;

    date() {}

    bool VisOrNot()
    {
        if ((year % 4 == 0 && year % 100 != 0) or (year % 400 == 0))
            return true;
        return false;
    }
    

    bool correct_day_in_month()
    {
        if (month == 2)
        {
            if (VisOrNot() and day <= 29 and day > 0)
                return true;
            else
            {
                if (day <= 28 and day>0)
                    return true;
                else
                    return false;
            }
        }
        else {
            if (month == 4 || month == 6 || month == 9 || month == 11)
            {
                if (day <= 30 and day > 0)
                    return true; // апр июнь сен но€б
                else
                    return false;
            }
            else
            {
                if (day <= 31 and day > 0)
                    return true;
                else
                    return false;
                    // €нв март май июль авг окт дек
            }
        }
    }

    std::string get_string()
    {
        std::string result;
        std::string d, m, y;
        if (day < 10)
        {
            d = "0"; d.append(std::to_string(day));
        }
        else
        {
            d = std::to_string(day);
        }

        m = months[month - 1];

        y = std::to_string(year);
        return result.append(d).append(m).append(y);
    }

    bool operator == (date b)
    {
        if (this->day == b.day and this->month == b.month and this->year == b.year) return true;
        return false;
    }
    void operator = (date b)
    {
        day = b.day;
        month = b.month;
        year = b.year;
    }
    bool operator >(date b)
    {
        if (this->year < b.year)
            return true;
        else
            if (this->year == b.year)
                if (this->month < b.month)
                    return true;
                else
                    if (this->month == b.month)
                        if (this->day < b.day)
                            return true;
        return false;
    }

    bool operator < (date b)
    {
        if (this->year > b.year)
            return true;
        else
            if (this->year == b.year)
                if (this->month > b.month)
                    return true;
                else
                    if (this->month == b.month)
                        if (this->day > b.day)
                            return true;
        return false;
    }

    bool in_the_range(date Date1, date Date2)
    {
        return (Date1 > *this and *this > Date2);
    }

    date(unsigned int d, unsigned int m, unsigned int y) {
        if (d > 31)
        {
            day = d % 31;
            m++;
        }

        if (m > 12)
        {
            m = m % 12;
            year++;
        }

        day = d;
        month = m;
        year = y;

    }

    date(std::string dat)
    {
        std::string day, month, year;
        for (char i : dat)
        {
            if (isdigit(i))
            {
                if (day.size() != 2)
                    day += i;
                else
                    year += i;
            }
            else
                month += i;
        }
        
        int index = -12;
        for (int i = 0; i < 24; i++)
        {
            if (months[i] == month)
                index = i;
        }
        
       

        this->day = std::stoi(day);
        this->month = (index + 1) % 12 == 0 ? 12 : (index + 1) % 12;
        this->year = std::stoi(year);
    }

    
   

    bool correct()
    {
        if (1900 <= year and year <= 2025 and 0 < month and month <=12 and correct_day_in_month())
            return true;
        return false;
    }
};

struct gos_num
{
    std::string letter;
    int num;

    gos_num() {}

    gos_num(char ps[2], char vs[3], int number)
    {
        letter += ps[0];
        letter += vs[0];
        letter += vs[1];
        num = number;
    }


    gos_num(std::string number)
    {
        std::string temp_str = "";
        for (char i: number)
        {
            if (isdigit(i))
                temp_str += i;
            else
                letter += i;
        }
        num = std::stoi(temp_str);
    }

    std::string get_string()
    {
        std::string result = letter.substr(0, 1);
        result.append(std::to_string(num));
        result += letter[1];
        result += letter[2];
        return result;
    }
    bool operator ==(gos_num b)
    {
        if (this->letter == b.letter and this->num == b.num) 
            return true;
        return false;
    }

    bool operator >(gos_num b)
    {
        int i = 0;
        while (i < 3)
        {
            if (this->letter[i] > b.letter[i])
                return true;
        }
        return true;
    }

    bool operator < (gos_num b)
    {
        int i = 0;
        while (i < 3)
        {
            if (this->letter[i] < b.letter[i])
                return true;
        }

        return false;
    }

    bool correct_gos_num()
    {
        char l1 = letter[0]; char l2 = letter[1]; char l3 = letter[2];
        bool mark_l1 = false; bool mark_l2 = false; bool mark_l3 = false;
        for (char i : alphabet)
        {
            if (i == l1) mark_l1 = true;
            if (i == l2) mark_l2 = true;
            if (i == l3) mark_l3 = true;
            if (mark_l1 and mark_l2 and mark_l3) return true;
        }
        return false;
    }
};



struct key
{
    date Date;
    std::string FIO;
    std::string Car_brand;
    std::string Car_model;
    gos_num Number;
    key(date D, std::string F, std::string CB, std::string CM, gos_num N) : Date(D), FIO(F), Car_brand(CB),Car_model(CM), Number(N) {};
    key() {};

 
    bool operator ==(key b)
    {
        if ((this->FIO == b.FIO) and (this->Date == b.Date) and (this->Car_brand == b.Car_brand) and (this->Car_model == b.Car_model) and (this->Number == b.Number))
            return true;
        return false;
    }

    

    bool operator >(key b)
    {
        int i = 0; size_t size_a = this->FIO.size(); size_t size_b = b.FIO.size();
        while (this->FIO[i] == b.FIO[i] and i < size_a and i < size_b)
        {
            i++;
        }
        if (this->FIO[i] > b.FIO[i])
            return true;
        return false;
    }


    bool operator <(key b)
    {
        int i = 0; size_t size_a = this->FIO.size(); size_t size_b = b.FIO.size();
        while (this->FIO[i] == b.FIO[i] and i < size_a and i < size_b)
        {
            i++;
        }
        if (this->FIO[i] < b.FIO[i])
            return true;
        return false;
    }

    bool correct_car_brand()
    {
        for (std::string i : car_brands)
        {
            if (Car_brand == i)
                return true;
        }
        return false;
    }
    
    bool correct_car_model()
    {
        for (std::string i : car_models)
        {
            if (Car_model == i)
                return true;
        }
        return false;
    }

    bool correct_fio()
    {
        bool marker = true;
        for (char i : FIO)
        {
            if (marker)
            {
                if (65 <= i and i <= 90)
                    marker = false;
                else
                    return false;
            }
            if (i == ' ')
            {
                marker = true;
            }
        }

    }

};


struct Node
{
    key data;
    Node* next;
    Node* prev;


    bool operator >(Node b)
    {
        int i = 0; size_t size_a = this->data.FIO.size(); size_t size_b = b.data.FIO.size();
        while (this->data.FIO[i] == b.data.FIO[i] and i < size_a and i < size_b)
        {
            i++;
        }
        if (this->data.FIO[i] > b.data.FIO[i])
            return true;
        return false;
    }


    Node(key _val) : data(_val), next(nullptr), prev(nullptr) {}
};

struct list
{
    Node* first;
    list() : first(nullptr) {};
    
public:

    bool operator ==(list b)
    {
        Node* current_this = this->first->next;
        Node* current_b = b.first->next;
        do {
            if (current_this != current_b)
                return false;
            current_this = current_this->next;
            current_b = current_b->next;
        } while (current_this != this->first and current_b != b.first);

        return true;
    }

    key* search_el_in_list(gos_num f, int& count) //++
    {
        Node* arrow = first;
        if (first != nullptr)
        {
            if (first->next == first) {
                count++;
                if (first->data.Number == f) return &first->data;
                else return nullptr;
            }
            else {
                while (arrow->next != first and arrow->data.Number != f) {
                    arrow = arrow->next;
                    count++;
                }
                if (arrow->data.Number == f) return &arrow->data;
                else return nullptr;
            }
        }
        else return nullptr;
    }
    
    void draw_list(std::vector<std::string>& list) //++
    {
        if (first != nullptr)
        {
            std::string otst = "  ";
            std::string res;

            Node* current = first;
            do {
                res += (current->data.FIO + "   " + current->data.Car_brand + "   " + current->data.Number.get_string() + otst + "<->" + otst);
                current = current->next;
            } while (current != first);
            list.push_back(res);
        }
    }

    Node* search_el(key el) { //+++
        Node* arrow = first;
        if (first != nullptr)
        {
            if (first->next == first) { 
                if (first->data == el) return first;
                else return nullptr;
            }
            else {
                while (arrow->next != first and arrow->data != el) {
                    arrow = arrow->next;
                }
                if (arrow->data == el) return arrow;
                else return nullptr;
            }
        }
        else return nullptr;
    }


    bool delete_el(key el) //+++
    {
        Node* current = first->next;
        if (first->data == el)
        {
            if (first->next == first)
            {
                delete(first);
                return true;
            }
            else {
                Node* memory = first;
                first = first->next;
                delete(first);
                return true;
            }
        }
        while (current->data != el and current != first)
        {
            current = current->next;

        }
        if (current == first)
            return false;
        else
        {
            current->next->prev = current->prev;
            current->prev->next = current->next;
            delete(current);
            return true;
        }
    }



    bool fill(key el)///+++
    {
        Node* node1 = new Node(el);
        Node* current1;
        if (first == nullptr) {
            first = node1;
            first->prev = first;
            first->next = first;
            return true;
        }
        else {
            current1 = first;
            do {
                current1 = current1->next;
                if (current1->data.Number == el.Number)
                    return false;

            } while (current1 != first);
            current1 = first;
            if (node1->data > first->data) {
                node1->next = first;
                node1->prev = first->prev;
                first->prev->next = node1;
                first->prev = node1;
                first = node1;
                return true;
            }
            else {
                current1 = first;
                do {
                    current1 = current1->next;
                    if (current1->data.Number == el.Number)
                        return false;
                    
                } while (current1 != first);

                current1 = first;
                while (current1->next != nullptr and current1->next != first and node1->data < current1->next->data) {
                    current1 = current1->next;
                    if (current1->data.Number == el.Number) //r
                        return false; //r
                }
                if (current1->data.Number == el.Number) //r
                    return false; //r
                if (current1->next != first and current1->next != nullptr) {
                    current1->next->prev = node1;
                    node1->next = current1->next;
                    node1->prev = current1;
                    current1->next = node1;
                    return true;
                }
                else {
                    node1->prev = first->prev;
                    first->prev->next = node1;
                    node1->next = first;
                    first->prev = node1;
                    return true;
                }
            }
        }
    }

    void Input_file_spisok(std::fstream& file)  //++
    {
        if (first == nullptr) return;
        else
        {
            Node* current = first;
            do
            {
                file << current->data.Date.get_string() <<" |" << current->data.FIO << "|" << current->data.Car_brand << "|" << current->data.Car_model << "|"
                    << current->data.Number.letter[0] <<current->data.Number.letter[1] << current->data.Number.num<< current->data.Number.letter[2] << "\n";
                current = current->next;
            } while (current != first);
        }
    }

    std::vector<key> make_list_spisok() //++
    {
        std::vector<key> list;
        Node* current = this->first;
        do {
            current = current->next;
            list.push_back(current->data);
        } while (current != first);

        return list;
    }


    /*bool delete_list()
    {
        Node* arrow1 = first;
        Node* arrow2 = first;
        if (arrow1->next != first) {
            while (arrow1->next != first)
            {
                arrow2 = arrow1;
                arrow1 = arrow1->next;
                delete(arrow2);
            }
            first = nullptr;
        }
        else first = nullptr;
        return true;
    }*/
};

