#include "PEParser.h"
#include <iostream>

/*
	Je r�fl�chis encore � la structure du projet.
	Donc si vous voyez une Class avec des statics alors qu'elles doivent �tre private c'est normal mdr.
	Le code est loin d'�tre fini :)
*/

int main() {
	PEParser peParser("C:\\Program Files\\Recuva\\recuva64.exe");
	if (peParser.b_error) {
		std::cerr << "Une erreur est survenue pendant l'inspection..." << std::endl;
		return 1;
	}
	peParser.printDump();
	return 0;
}
