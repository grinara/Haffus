#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;
struct MyCompare
{
	bool operator()(const Uzel* l, const Uzel* r) const { return l->a < r->a; }
};
vector<bool> code1;
map<char, vector<bool> > table1;// ������� �������������� ���� � ��������

void Build1(Uzel* root) {
	if (root->left != NULL) // ���� ����� ���-�� ���� ������ � ������ 0
	{
		code1.push_back(0);
		Build1(root->left); // ���������� �������� �������
	}

	if (root->right != NULL)// ���� ������ ���-�� ���� ������ � ������ 1
	{
		code1.push_back(1);
		Build1(root->right);// ���������� �������� �������
	}

	if (root->left == NULL && root->right == NULL) {
		table1[root->c] = code1;  // ���� ���������� �� �����, �� ����������� � � ����� � table

	}
	if (!code1.empty()) {
		code1.pop_back(); //��������� ��� �� 1}
	}
}
void Print1(Uzel* root, unsigned k = 0) {
	if (root != NULL) {
		Print1(root->left, k + 3);
		for (unsigned i = 0; i < k; i++) {
			cout << " ";
		}
		if (root->c) {
			cout << root->a << " (" << root->c << ")" << endl;
		}
		else {
			cout << root->a << endl;
			Print1(root->right, k + 3);
		}
	}
}
void main1() {
	setlocale(LC_ALL, "Russian");
	ifstream file1("112.txt", ios::out | ios::binary);
	map<char, int>  m;
	int zise;
	file1.read((char*)&zise, sizeof(int));
	cout << zise<<endl;
	file1.seekg(4, ios::beg);
	char buff;
	int c;
	for (int i = 4; i < (zise*5); i=i+5) {
		file1.seekg(i, ios::beg);
		file1.read((char*)&buff, sizeof(char));
		file1.seekg(i+1, ios::beg);
		file1.read((char*)&c, sizeof(int));
		m[buff] = c;
	}
	list<Uzel*> da;

	map<char, int>::iterator i;

	for (i = m.begin(); i != m.end(); ++i) {
		Uzel* k = new Uzel;
		k->c = i->first; // char � map 
		k->a = i->second; // int � map
		da.push_back(k); // ��������� ��������� � list
	}
	while (da.size() != 1) // ���� �� ���������� ���� �������
	{
		da.sort(MyCompare()); //���������� �� MyCompare

		Uzel* SonL = da.front(); // ������ ������ ������� ���� ������ ������� �� list 
		da.pop_front(); // ������� �������
		Uzel* SonR = da.front(); // ������ ������� ������� ���� ������(����� �������� �������) ������� �� list 
		da.pop_front(); // ������� �������

		Uzel* parent = new Uzel(SonL, SonR); // ������ ���� 
		da.push_back(parent); // ��������� ��� � list
	}
	Uzel* root = da.front(); // ��������� �� ������ ������
	Print1(root);
	Build1(root);

	Uzel* p = root;
	int count = 0;
	char byte = 0;
	byte = file1.get();
	while (!file1.eof())
	{
		bool b = byte & (1 << (7 - count)); // ��������� 1 ��� 0 � ���������
		if (b) p = p->right; else p = p->left; // ���� 1 ��������� ������ ����� �����
		if ((p->left == NULL) && (p->right == NULL)) { cout << p->c; p = root; } // ������� ������ 
		count++;
		if (count == 8) { count = 0; byte = file1.get(); } // ���� cout = 8 �������� ��� � ������������� ��������� ������
	}

	file1.close(); // �� �������� ������� ����
	return;
}