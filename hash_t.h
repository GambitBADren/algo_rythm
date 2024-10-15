#pragma once
#include "Spisok.h"
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>


struct key_h
{
	list listt;	
	key_h(key_h* e)
	{
		this->listt = e->listt;
	}
	key_h(list l) : listt(l) {}
	key_h() {};

	
	bool operator ==(key_h b)
	{
		if (listt == b.listt)
			return true;
		return false;
	}

	bool operator !=(key_h b)
	{
		return !(*this == b);
	}

};


class hash_table
{
private:
	int orig_size;
public:
	std::vector<key_h> vector;
	int size;
	int count_el = 0;

	hash_table() {};

	hash_table(int sizee)
	{
		if (sizee > 0)
		{
			vector.resize(sizee);
			size = sizee; orig_size = sizee;
		}
	};


	~hash_table() {};



	int get_hash1(gos_num el) //++
	{
		std::string k = el.letter;
		size_t size_k = k.size();
		int summ = 0;
		for (int i = 0; i < size_k; i++)
			summ += k[i];
		//посчитал сумму
		summ += el.num;

		return summ % (size);
	}


	

	void draw_ht(int h, std::vector<std::string>& list) //++
	{
		std::vector<std::string> result;
		std::string otst;
		for (int i = 0; i < h; i++)
		{
			otst += " ";
		}
		std::string res = "\n" + otst;
		for (int i = 0; i < size; i++)
		{
			res += std::to_string(i).append(" ");
			vector[i].listt.draw_list(result); 
			for (std::string j : result)
			{
				res += j;
			}
			res += "\n";
			res += otst;
			result.clear(); 
		}
		list.push_back(res);
	}




	bool insert_hash_table(key el) // ++
	{ 
		if (size == 0) { return false; }


		int index = get_hash1(el.Number);

		std::cout << index << "\n";
		//if(vector[index].listt.first != nullptr)

		if (vector[index].listt.fill(el))
		{
			count_el += 1; 
			return true;
		}

		return false;


	}



	key* find_in_ht(gos_num num, int& count) //++
	{
		int index = get_hash1(num);
		if (vector[index].listt.first == nullptr)
			return nullptr;
		return vector[index].listt.search_el_in_list(num, count);
	}



	void In_file_hash(std::fstream& file) //++
	{
		for(int i = 0; i<size;i++)
			if (vector[i].listt.first != nullptr)
			{
				if (vector[i].listt.first != nullptr)
					vector[i].listt.Input_file_spisok(file);
			}	
	}


	
	
	std::vector<key> make_list_ht() //++
	{
		std::vector<key> result;
		for (auto i : vector)
		{
			if (i.listt.first != nullptr)
			{
				std::vector<key> temp = i.listt.make_list_spisok();
				for (auto j : temp)
				{
					result.push_back(j);
				}
			}
		}
		return result;
	}

	
};