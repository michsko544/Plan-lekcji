#pragma once
#include "DetectMemoryLeaks.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

enum week
{
	pn = 1,
	wt = 2,
	sr = 3,
	cz = 4,
	pt = 5,
	sb = 6,
	nd = 7
};

struct list
{
	string time;
	week day;
	string group;
	string subject;
	list* next;
};

struct node
{
	string teacher;
	list* head_data;
	node* lroot;
	node* rroot;
};

void Help();
bool LoadArguments(int argc, char ** argv, string & InFileName);
bool CheckData(const string &time, const string &day_name, const string &group, const string &teacher, const string &subject);
bool LoadFileInAndCheckFileIn(node* &tree, string &file_name);
week convertday(string &day);
node* SearchExistTeacher(node* &tree, string &teacher);
void AddSortedLessons(node* &position, string &time, week &day, string &group, string &subject);
void AddNewSortedNode(node* &tree, string &teacher, string &time, week day, string &group, string &subject);
string convertNumber(int num);
void CreateFilesInPreOrder(node* &tree);
void CreateFile(node* &tree);
void DeleteList(list* &head);
void DeleteDynamicStruct(node* &tree);
