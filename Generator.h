#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#pragma once
#ifndef Generator

std::vector<std::string> make_list_string(std::string path)
{
	std::ifstream fin;
	fin.open(path);
	std::vector<std::string> list;
	std::string a;
	while (!fin.eof())
	{
		getline(fin, a);
		list.push_back(a);
	}
	fin.close();
	return list;
}

int random(int start, int end) {
	return rand() % (end - start + 1);
}

std::string PostOrder_fio(std::vector<std::string> list_name, std::vector<std::string> list_surname, std::vector<std::string> list_fathername)
{
	std::string s = list_name[random(0, size(list_name) - 1)] + " " + list_surname[random(0, size(list_surname) - 1)] + " " + list_fathername[random(0, size(list_fathername) - 1)];
	return s;
}

std::string PostOrder_gosnum(std::string alphabet = "ETYOPAHKXCBM")
{
	std::string	letter;
	std::string number;
	for (int i = 0; i < 3; i++)
	{
		letter+= alphabet[random(0, 11)];
	}

	number = std::to_string(random(100, 999));
	
	std::string result = letter.substr(0, 2); result.append(number); result.append(letter.substr(2));
	return result;
}

std::string PostOrder_brandCar(std::vector <std::string> list_name)
{
	return list_name[random(0, size(list_name) - 1)];
}


std::string PostOrder_date()
{
	std::string result;
	result.append(std::to_string(random(1, 31)));
	result.append(".");
	result.append(std::to_string(random(1, 12)));
	result.append(".");
	result.append(std::to_string(random(1940, 2024)));
	return result;
}
void generator(int n) {
	std::vector<std::string> name; name = make_list_string("generator_name.txt");
	std::vector<std::string> surname; surname = make_list_string("generator_surname.txt");
	std::vector<std::string> fathername; fathername = make_list_string("generator_fathername.txt");
	std::vector<std::string> brandCar; brandCar = make_list_string("brandCar.txt");
	std::basic_ofstream<char> file;

	file.open("generator.txt");
	for (int i = 0; i < n; i++)
	{
		file << std::setw(8) <<PostOrder_gosnum()<< std::setw(16) << PostOrder_brandCar(brandCar) << std::setw(50) << PostOrder_fio(name, surname, fathername) << std::setw(11) << PostOrder_date() << "\n";
	}
	file.close();
}
#endif // !Generator