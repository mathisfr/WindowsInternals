#include "PEParser.h"
#include <iostream>

int main() {
	PEParser peParser("C:\\Program Files\\Recuva\\recuva64.exe");
	if (peParser.b_error) {
		std::cerr << "Une erreur est survenue pendant l'inspection..." << std::endl;
	}
	return 0;
}
