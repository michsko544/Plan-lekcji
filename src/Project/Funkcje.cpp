#include "Header.h"
#include "DetectMemoryLeaks.h"

void Help()
{
	cout << "\nHELP\nUzyj przelacznika -i przed sciezka do pliku, ktory chcesz wczytac" << endl;
}

bool LoadArguments(int argc, char ** argv, string & InFileName)
{
	const string INPUT("-i");
	const string HELP("-h");
	const int    InputFlag = 1;

	const int    correct = InputFlag;
	int result = 0;

	if (argc == 1)
	{
		Help();
		exit(6);
	}

	for (int i = 1; i < argc; i++)
	{
		string arg(argv[i]);
		if (arg == INPUT && argv[i+1])
		{
			InFileName = argv[i + 1];
			result |= InputFlag;
		}
		if (arg == HELP)
		{
			Help();
			exit(6);
		}
	}

	if (result == correct)
		return true;
	else
		return false;
}

bool CheckData(const string &time, const string &day_name, const string &group, const string &teacher, const string &subject)
{
	if (time == " " || day_name == " " || group == " " || teacher == " " || subject == " ")
		return false;
	else
		return true;
}

bool LoadFileInAndCheckFileIn(node* &tree, string &file_name)
{
	fstream i(file_name, ios_base::in);
	if (!i.is_open()) {  cout << "Plik wejsciowy " << file_name << " nie zostal znaleziony!" << endl; exit(1);}
	else { cout << "Plik wejsciowy zostal otworzony" << endl; }

	string time;
	string day_name;
	week day;
	string group;
	string teacher;
	string subject;
	string line;
	
	while (getline(i, line))
	{
		if (line == "")
			continue;
		istringstream str(line);
		str >> time >> day_name >> group >> teacher >> subject;
		day = convertday(day_name);
		node* position = SearchExistTeacher(tree, teacher);
		
		if (!CheckData(time, day_name, group, teacher, subject))
		{
			cout << "Blednie wpisane dane (pusta zmienna)"<<endl;
			return false;
		}

		if (!str)
		{
			cout << "Blad danych, sprawdz zawartosc pliku wejsciowego" << endl;
			return false;
		}

		else
		{
			if (position == nullptr)
				AddNewSortedNode(tree, teacher, time, day, group, subject);
			else
			{
				AddSortedLessons(position, time, day, group, subject);
			}
		}
	}

	i.close();
	return true;
}

week convertday(string &day)
{
	if (day == "pn")
	{
		return pn;
	}
	else if (day == "wt")
	{
		return wt;
	}
	else if (day == "sr")
	{
		return sr;
	}
	else if (day == "cz")
	{
		return cz;
	}
	else if (day == "pt")
	{
		return pt;
	}
	else if (day == "sb")
	{
		return sb;
	}
	else if (day == "nd")
	{
		return nd;
	}
	else
	{
		cout << "Zle podany dzien w pliku";
		exit(2);
	}
}

node* SearchExistTeacher(node* &tree, string &teacher)
{
	node* tmp = tree;

	if (tmp == nullptr) return nullptr;
	else
	{
		if (teacher == tmp->teacher) return tmp;
		if (teacher < tmp->teacher)
		{
			SearchExistTeacher(tmp->lroot, teacher);
		}
		else
		{
			SearchExistTeacher(tmp->rroot, teacher);
		}
	}
}

void AddSortedLessons(node* &position, string &time, week &day, string &group, string &subject)		//sortowanie wg dwóch zmiennych
{

	//dodanie na poczatek
	if (position->head_data->day > day || (position->head_data->day == day && position->head_data->time>time))
	{
		position->head_data = new list{ time, day, group, subject, position->head_data };
	}

	//dodanie w œrodku
	else
	{
		list* help = nullptr;
		list* tmp = position->head_data;
		while (tmp)
		{
			if (tmp->day < day || (tmp->day == day && tmp->time<time))
			{
				if (tmp->next)
				{
					help = tmp;
					tmp = tmp->next;
				}
				else
					break;
			}
			if (tmp->day>day || (tmp->day == day && tmp->time >= time))
			{
				tmp = new list{ time, day, group, subject, tmp };
				help->next = tmp;
				break;
			}
		}

		//dodanie na koniec
		if (!tmp->next)
			tmp->next = new list{ time,day,group,subject,nullptr };
	}
}


void AddNewSortedNode(node* &tree, string &teacher, string &time, week day, string &group, string &subject)			//tworzy nowe wêz³y
{
	if (!tree)
	{
		tree = new node{ teacher,new list{ time, day, group ,subject, nullptr },nullptr,nullptr };
	}
	else if (teacher < tree->teacher)
	{
		AddNewSortedNode(tree->lroot, teacher, time, day, group, subject);
	}
	else
	{
		AddNewSortedNode(tree->rroot, teacher, time, day, group, subject);
	}
}


string convertNumber(int num)
{
	string day;
	if (num == 1)
	{
		day = "pn";
		return day;
	}
	else if (num == 2)
	{
		day = "wt";
		return day;
	}
	else if (num == 3)
	{
		day = "sr";
		return day;
	}
	else if (num == 4)
	{
		day = "cz";
		return day;
	}
	else if (num == 5)
	{
		day = "pt";
		return day;
	}
	else if (num == 6)
	{
		day = "sb";
		return day;
	}
	else if (num == 7)
	{
		day = "nd";
		return day;
	}
	else
		exit(3);
}

void CreateFilesInPreOrder(node* &tree)
{
	if (tree)
	{
		CreateFilesInPreOrder(tree->lroot);
		CreateFile(tree);
		CreateFilesInPreOrder(tree->rroot);
	}
}

void CreateFile(node* &tree)
{
	fstream out(tree->teacher + ".txt", ios_base::out);
	if (!out.is_open()) { cout << "Blad otwarcia pliku"<<endl; exit(4); }
	else { cout << "Stworzono nowy plik " << tree->teacher << ".txt dla prowadzacego" << endl; }
	list* tmp = tree->head_data;
	while (tmp)
	{
		out << tmp->time << " " << convertNumber(tmp->day) << " " << tmp->group << " " << tmp->subject << endl;
		tmp = tmp->next;
	}
	out.clear();
	out.close();
}

void DeleteList(list* &head)
{
	list* tmp;
	while (head)
	{
		tmp = head;
		head = tmp->next;
		delete tmp;
	}
}

void DeleteDynamicStruct(node* &tree)
{
	if (tree)
	{
		DeleteDynamicStruct(tree->lroot);				//PostOrder
		DeleteDynamicStruct(tree->rroot);
		DeleteList(tree->head_data);
		delete tree;
		tree=nullptr;
	}
}

