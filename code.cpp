#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;
vector<bool> vec;
t tab[255];
void Build_cod(Node* root) {
	if (root->l != NULL) // если слева что-то есть вносим в вектор 0
	{
		vec.push_back(0);
		Build_cod(root->l); // рекурсивно вызываем функцию
	}

	if (root->r != NULL)// если справа что-то есть вносим в вектор 1
	{
		vec.push_back(1);
		Build_cod(root->r);// рекурсивно вызываем функцию
	}

	if (root->c) {
		tab[root->c].vec = vec;  // если наткнулись на букву, то ассоциируем её с годом в tab

	}
	if (!vec.empty()) {
		vec.pop_back(); //сокращаем код на 1}
	}
}

void coding() {
	setlocale(LC_ALL, "Russian");
	string file_name_to_code;
	cout << "Введите имя файла для кодирования: ";
	cin>>file_name_to_code;
	ifstream file1;
	file1.open(file_name_to_code.c_str(), ios::in | ios::binary);
	if (file1) { cout << "Файл успешно открыт" << endl; }
	else { cout << "Файл не открыт" << endl; return; }
	himan m[255];
	int N=0;
	while (!file1.eof()) { //ищём количество вхождений каждого символа
		char  c0 = file1.get();
		if (c0>0) {
			m[c0].c = c0;
			m[c0].count++;
			tab[c0].c = c0;
		}
	}
	for (int i = 0; i < 255; i++) {
		if (m[i].count > 0) { N++; }
	}
	list <Node*> da;
	for (int i = 0; i < 255; i++) {
		if (m[i].count > 0) {
			Node* k = new Node;
			k->c = m[i].c;
			k->a = m[i].count;
			da.push_back(k);
		}
	}
	while (da.size() != 1) // пока не останеться один элемент
	{
		da.sort(Sort()); //сортировка по MyCompare

		Node* SonL = da.front(); // создаём левого потомка берём первый элемент из list 
		da.pop_front(); // удаляем элемент
		Node* SonR = da.front(); // создаём правого потомка берём первый(после удаления другого) элемент из list 
		da.pop_front(); // удаляем элемент
		Node* parent = new Node(SonL, SonR); // создаём узел 
		da.push_back(parent); // добавляем его в list
	}
	Build_cod(da.front());
	file1.clear(); // сбрасываем указатель
	file1.seekg(0);// возвращаем указатель в начало файла

	fstream file1_cip("112.txt", ios::binary | ios::out);
	int c = N;
	char kar = 0;
	file1_cip.write((char*)&c, sizeof(int));
	for (int i = 0; i < 255;i++) {
		if (m[i].count > 0) {
			kar = m[i].c;
			c = m[i].count;
			file1_cip.write((char*)&kar, sizeof(char));
			file1_cip.write((char*)&c, sizeof(int));
		}
	}

	int count = 0; // счётчик
	char buf = 0; //вспомогательная переменная
	while (!file1.eof()) {
		char c = file1.get();
		vector<bool> x = tab[c].vec;
		for (int j = 0; j < x.size(); j++) {
			buf = buf | x[j] << (7 - count); // преобразуем вектор x в байт
			count++;
			if (count == 8) { count = 0; file1_cip << buf; buf = 0; } // если достигли count = 8  байт записывем в file1_cip
		}
	}

	file1.close(); // не забываем закрыть файл
	file1_cip.close(); // не забываем закрыть файл
	return;
}


