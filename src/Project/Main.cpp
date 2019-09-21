//Temat 17 - PLAN - Micha³ Skorus TI2 gr7 prowadz¹cy Agnieszka Danek
//Struktur¹ danych bêdzie drzewo binarne list
//Ka¿dy korzeñ drzewa bedzie posiadaæ nazwê nauczyciela i przechowywaæ wskaŸnik na listê z jego zajêciami
//Lista bedzie przechowywaæ resztê zajêæ z danymi

//Exit
//1-b³¹d wczytywania pliku
//2-b³êdny dzieñ w pliku
//3-b³êdny dana dnia w liœcie i konwesja danej wyrzuca b³¹d
//4-b³¹d zapisywania pliku
//5-brak lub z³y prze³¹cznik
//6-wykorzystano program do wyœwietlenia jego instrukcji
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