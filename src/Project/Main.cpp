//Temat 17 - PLAN - Micha� Skorus TI2 gr7 prowadz�cy Agnieszka Danek
//Struktur� danych b�dzie drzewo binarne list
//Ka�dy korze� drzewa bedzie posiada� nazw� nauczyciela i przechowywa� wska�nik na list� z jego zaj�ciami
//Lista bedzie przechowywa� reszt� zaj�� z danymi

//Exit
//1-b��d wczytywania pliku
//2-b��dny dzie� w pliku
//3-b��dny dana dnia w li�cie i konwesja danej wyrzuca b��d
//4-b��d zapisywania pliku
//5-brak lub z�y prze��cznik
//6-wykorzystano program do wy�wietlenia jego instrukcji
//111- SUKCES


#include "Header.h"
#include "DetectMemoryLeaks.h"


using namespace std;


int main(int argc, char** argv)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	string file_name;

	bool load=LoadArguments(argc, argv, file_name);
	if (load == 0)
	{
		cout << "Nieprawidlowe parametry" << endl;
		Help();
		exit(5);
	}


	node* tree = nullptr;

																
	LoadFileInAndCheckFileIn(tree,file_name);			//PROBLEM
	

	CreateFilesInPreOrder(tree);
	DeleteDynamicStruct(tree);

	return 111;
}