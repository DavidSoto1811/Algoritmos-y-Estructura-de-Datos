#pragma once
#include <iostream>
std::string generarPaciente() {
	std::string usuario;
	for (int i = 1; i <= 5; i++) {
		usuario += char(65 + rand() % (90 - 65));
	}
	return usuario;
}