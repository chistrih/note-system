#include <iostream>
#include "NoteManager.h"
#include "ConsoleCRUDHandler.h"

int main() {
	ConsoleCRUDHandler app;
	
	app.handleCreateNote();
	app.handleReadNotes();
	
	return 0;
}


