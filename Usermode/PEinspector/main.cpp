#include "PEParser.h"
#include <iostream>

/*
	Je réfléchis encore à la structure du projet.
	Donc si vous voyez une Class avec des statics alors qu'elles doivent être private c'est normal mdr.
	Le code est loin d'être fini :)
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
