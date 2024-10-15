#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "hash_t.h"


struct pair
{
	key* k;
	int c;
};
struct tree 
{
private:
	tree* check_na_nullptr(tree* x, tree* y)
	{
		if (x != nullptr and y == nullptr) return x;
		else if (y != nullptr and x == nullptr) return y;
		return nullptr;
	}

	key* check_na_nullptr_k(key* x, key* y)
	{
		if (x != nullptr and y == nullptr) return x;
		else if (y != nullptr and x == nullptr) return y;
	}

	tree* maximus(tree* root1)
	{
		if (root1 == nullptr) return nullptr;
		tree* r = maximus(root1->right);
		tree* l = maximus(root1->left);
		if (r == nullptr and l == nullptr) return root1;
		else
		{
			if (r != nullptr and l != nullptr)
			{
				if ((r->Date > l->Date) and (r->Date > l->Date)) return r;  
				else return l;
			}
			else
			{
				if (r != nullptr and l == nullptr) return r;
				else return l;
			}
		}
		return root1;
	}

public:
	tree* root = nullptr;
	tree* right = nullptr;
	tree* left = nullptr;
	tree* parent = nullptr;
	int color;


	hash_table HT;
	date Date;
	

	tree() {};
	tree(date d,int size) : Date(d),HT(size) {}   
	


	int height(tree* root1) //++
	{
		if (root1 == nullptr) return 0;

		if (root1->color == 0) return 1 + std::max(height(root1->left), height(root1->right));
		else return std::max(height(root1->left), height(root1->right));
	}


	bool fill(key el, int size) 
	{
		tree* z = new tree(el.Date,size);
		tree* y = nullptr;
		tree* x = this->root;

		bool marker = true;

		while (x != nullptr)
		{
			y = x;
			if ((x->Date > z->Date))  
				x = x->left;
			else x = x->right;
		}

		z->parent = y;
		if (y == nullptr)
		{
			root = z;
			marker = root->HT.insert_hash_table(el);
		}
		else {
			if ((z->Date == y->Date))  
			{
				marker = y->HT.insert_hash_table(el);

			}
			else {
				if ((y->Date > z->Date)) 
				{
					marker = z->HT.insert_hash_table(el);
					y->left = z;
				}
				else
				{
					marker = z->HT.insert_hash_table(el);
					y->right = z;
				}
			}
			z->left = nullptr;
			z->right = nullptr;
			z->color = 1;
			fix(z);
			
		}
		return marker;
	}

	void fix(tree* z)
	{
		tree* y;
		while (z->parent != nullptr and z->parent->parent != nullptr and z->parent->color == 1)
		{
			if (z->parent == z->parent->parent->left)  
			{
				y = z->parent->parent->right;
				if (y != nullptr and y->color == 1) 
				{
					z->parent->color = 0;
					y->color = 0;
					z->parent->parent->color = 1;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right)
					{
						z = z->parent;
						rotate_left(z);
					}

					else { 
						z->parent->color = 0;
						z->parent->parent->color = 1;
						rotate_right(z->parent->parent);
					}
				}
			}
			else
			{
				if (z->parent == z->parent->parent->right) 
				{
					y = z->parent->parent->left;
					if (y != nullptr and y->color == 1)
					{
						z->parent->color = 0;
						y->color = 0;
						z->parent->parent->color = 1;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							rotate_right(z);
						}

						else {
							z->parent->color = 0;
							z->parent->parent->color = 1;
							rotate_left(z->parent->parent);
						}
					}
				}
			}
		}
		root->color = 0;
	}

	void rotate_left(tree* x) 
	{
		tree* y = x->right;
		x->right = y->left;

		if (y->left != nullptr) 
			y->left->parent = x;
		y->parent = x->parent;

		if (x->parent == nullptr)
			root = y;
		else {
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rotate_right(tree* x) 
	{
		tree* y = x->left;
		x->left = y->right;

		if (y->right != nullptr)
			y->right->parent = x;
		y->parent = x->parent;

		if (x->parent == nullptr)
			root = y;
		else
		{
			if (x->parent->right == x)
				x->parent->right = y;
			else
				x->parent->left = y;
		}
			y->right = x;
			x->parent = y;
		
	}

	


	void transplant(tree* u, tree* v)
	{

		if (u->parent == nullptr)
			root = v;
		else
		{
			if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
		}
		if (v != nullptr)
			v->parent = u->parent;
		else
			u->parent = nullptr;



	}


	tree* search_el(date el, tree* root) 
	{
		if (root != nullptr) {
			if (root->Date == el) return root; 
			else {
				if (root->right != nullptr and root->right->Date == el) return root->right;  
				else
				{
					if (root->left != nullptr and root->left->Date == el) return root->left;  
					else
					{
						return check_na_nullptr(search_el(el, root->left), search_el(el, root->right));
					}
				}
			}
		}
		return nullptr;
	}

	key* search_el_in_tree(date el, gos_num num,tree* root, int& count) 
	{
		if (root != nullptr) {
			if (root->Date == el) return root->HT.find_in_ht(num,count); 
			else {
				if (root->right != nullptr and root->right->Date == el) { count++; return root->right->HT.find_in_ht(num,count); }
				else
				{
					if (root->left != nullptr and root->left->Date == el) {
						count++; return root->left->HT.find_in_ht(num, count);
					}
					else
					{
						return check_na_nullptr_k(search_el_in_tree(el,num, root->left,count), search_el_in_tree(el,num, root->right,count));
					}
				}
			}
		}
		return nullptr;
	}

	bool delete_from_tree(date Date) //++
	{
		tree* z = this->search_el(Date, this->root);
		if (z != nullptr)
		{
			tree* x;
			tree* y = z;
			int orig_color = y->color;
				if (z->left == nullptr)
				{
					x = z->right;
					transplant(z, z->right);
				}
				else
				{
					if (z->right == nullptr)
					{
						x = z->left;
						transplant(z, z->left);
					}
					else
					{
						y = maximus(z->left);
						orig_color = y->color;
						x = y->right;   
						if (x != nullptr and y->parent == z)  
							x->parent = y;
						else
						{
							transplant(y, y->right);
							y->right = z->right;
							y->right->parent = y;
						}
						transplant(z, y);
						
						if (y->left != nullptr)
						{
							y->left = z->left;
							y->left->parent = y;
						}
						y->color = z->color;

					}
				}
				if (orig_color == 0)
				{
					delete_fix(x);
				}
			
		}
		return true;
	}


	void delete_tree(tree* root)
	{
		if (root != nullptr)
		{
			delete_tree(root->right);
			delete_tree(root->left);

			delete(root);
		}
	}

	void delete_fix(tree* x) //++
	{
		tree* w;
		while (x != nullptr and x != root and x->color == 0)
		{
			if (x == x->parent->left)
			{
				w = x->parent->right;
				if (w->color == 1)
				{
					w->color = 0;
					x->parent->color = 1;
					rotate_left(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == 0 and w->right->color == 0)
				{
					w->color = 1;
					x = x->parent;
				}
				else
				{
					if (w->right->color == 0)
					{
						w->left->color = 0;  
						w->color = 1; 
						rotate_right(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = 0;
					w->right->color = 0;
					rotate_left(x->parent);
					x = root;
				}
			}
			else
			{
				w = x->parent->left;
				if (w->color == 1)
				{
					w->color = 0;
					x->parent->color = 1;
					rotate_right(x->parent);
					w = x->parent->left;
				}
				if (w->right != nullptr and w->left != nullptr and w->right->color == 0 and w->left->color == 0) 
				{
					w->color = 1;
					x = x->parent;
				}
				else
				{
					if (w->right != nullptr and w->left != nullptr and w->left->color == 0)
					{
						w->right->color = 0;
						w->color = 1;
						rotate_left(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = 0;
					w->left->color = 0;
					rotate_right(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}


	

	void draw(tree* root, int op,std::vector<std::string> &result) //++
	{
		if (root != nullptr)
		{
			std::vector<std::string> list;
			std::string OP;
			std::string res;
			draw(root->right, op + 8, result);
			for (int i = 0; i < op; i++)
			{
				std::cout << " ";
				OP.append(" ");
			}
			res = OP;
			res += root->Date.get_string();
			std::string col = root->color == 1 ? "Red" : "Black";
			res += col;
			root->HT.draw_ht(op,list);
			for (std::string i : list)
			{
				res += OP + i;
			}
			res += "\n";
			result.push_back(res);
			draw(root->left, op + 4, result);

		}
	}

	

	std::vector<std::string> fill_RB_tree(std::string path, int si) //++
	{
		std::vector<std::string> list;
		std::ifstream fin;
		fin.open(path);
		int count = 0;
		tree RESULT;
		std::string number_gos, fio, car_brand, car_model, data;
		while (!fin.eof())
		{
			getline(fin, data, '|');
			if (data != "") {
				getline(fin, fio, '|');
				getline(fin, car_brand, '|');
				getline(fin, car_model, '|');
				getline(fin, number_gos, '\n');

				gos_num n(number_gos);
				date d(data);
				key a(d, fio, car_brand, car_model, n);

				if (a.correct_car_brand() and a.correct_car_model() and a.correct_fio() and a.Date.correct() and a.Number.correct_gos_num()) {
					
					if (!this->fill(a,si))
						list.push_back("a duplicate was discovered");
				}
				else
				{
					list.push_back("error with the data format");
				}
				count++;
			}
		}
			
		
		fin.close();
		return list;
	}


	bool delete_from_list(key el) //++
	{
		tree* del_el = search_el(el.Date, this->root);
		if (del_el != nullptr)
		{
			int index = del_el->HT.get_hash1(el.Number);
			index = del_el->HT.vector[index].listt.first == nullptr ? -1 : index;
			if (index >= 0)
			{
				if (del_el->HT.vector[index].listt.delete_el(el))
				{
					del_el->HT.count_el--;
					if (del_el->HT.count_el == 0)
						delete_from_tree(el.Date);
					return true;
				}
			}
		}
		return false;
	}


	void range_search(date Date1, date Date2, tree* root, gos_num number,int& count, std::vector<pair>& list)  
	{
		if (Date2 < Date1)
		{
			if (root != nullptr)
			{
				if (root->Date.in_the_range(Date1, Date2))
				{
					pair s;
					s.k = root->HT.find_in_ht(number,count);
					s.c = count;
					list.push_back(s);
				}
				if (root->right != nullptr and root->right->Date.in_the_range(Date1, Date2)) {
					count++; range_search(Date1, Date2, root->right, number, count, list);
				}
				if (root->left != nullptr and root->left->Date.in_the_range(Date1, Date2)) { count++; range_search(Date1, Date2, root->left, number, count, list); }
				
			}
		}
	}

	std::vector<key> make_list_tree(tree* current) //++
	{
		if (current != nullptr)
		{
			std::vector<key> result;
			std::vector<key> temp = current->HT.make_list_ht();
			for (auto i : temp)
				result.push_back(i);
			if (current->left != nullptr) { for (auto i : make_list_tree(current->left)) result.push_back(i); }
			if (current->right != nullptr) { for (auto i : make_list_tree(current->right)) result.push_back(i); }
			return result;
		}
	}

	
	void Input_file_tree(std::fstream &file, tree* current) //++
	{
		
		if (current == nullptr) return;
		else
		{
			if (current->parent == nullptr)
			{
				current->root->HT.In_file_hash(file);
				if (current->root->left != nullptr) Input_file_tree(file, current->root->left);
				if (current->root->right != nullptr) Input_file_tree(file, current->root->right);
			}
			else
			{
				current->HT.In_file_hash(file);
				if (current->left != nullptr) Input_file_tree(file, current->left);
				if (current->right != nullptr) Input_file_tree(file, current->right);
			}
			
		}
	}

};