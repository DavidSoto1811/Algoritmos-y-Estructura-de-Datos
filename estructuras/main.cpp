#include "pch.h"
#include <iostream>
#include <functional>
using namespace std;
#include "generarPaciente.h"
#include "Heap.h"
#include "HashTabla.h"
#include "Tree.h"
#include "Lista.h"
struct Paciente {
	string usuario;
	size_t nvisitas;
};
void cant_nivel(int nivel, int cant) {
	cout << nivel << ":" << cant;
}
int main()
{
	srand(time(NULL));
	size_t npacientes = 100;
	//lambda para imprimir
	function<void(Paciente)> print = [](Paciente a)->void {
		cout << "USUARIO: " << a.usuario << endl;
		cout << "NVISITAS: " << a.nvisitas << endl;
		cout << endl;
	};
	//lambda para comparar si es mayor
	function<bool(Paciente, Paciente)> mayor = [](Paciente a, Paciente b)->bool {
		return a.nvisitas > b.nvisitas;
	};
	//lambda para comparar si es mayor
	function<bool(Paciente, Paciente)> menor = [](Paciente a, Paciente b)->bool {
		return a.nvisitas < b.nvisitas;
	};
	//IMPLEMENTACION ORDENAMIENTO HEAPSORT
	Heap<Paciente> heap = Heap<Paciente>(0, mayor, menor);
	for (int i = 1; i <= npacientes; i++) {
		Paciente paciente;
		paciente.usuario = generarPaciente();
		paciente.nvisitas = rand() % 51;
		heap.insert(paciente);
	}
	heap.heapsort();
	cout << "////////////PACIENTES ORDENADOS POR NUMERO DE VISITAS: \\\\\\\\\\\\\\\\\\\n\n";
	heap.mostrar(print);
	function<void(Paciente)> printusuario = [](Paciente a)->void {
		cout << a.usuario;
	};
	//IMPLEMENTACION HASH TABLE
	HashTable<Paciente> ht = HashTable<Paciente>();
	for (int i = 1; i <= npacientes; i++) {
		Paciente paciente;
		paciente.usuario = generarPaciente();
		paciente.nvisitas = rand() % 51;
		ht.insertar(rand() % 178, paciente);
	}
	cout << "//////////HASH TABLE DE PACIENTES\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n\n";
	for (int i = 0; i < ht.sizeactual(); ++i) {
		cout << i << " : \n";
		print(ht.getvalue(i));
		cout << endl;
	}
	//lambda para comparar
	function<int(Paciente, Paciente)> comparar = [](Paciente a, Paciente b)->int { return a.nvisitas - b.nvisitas; };
	//IMPLEMENTACION ARBOLES BINARIOS DE BUSQUEDA
	Tree<Paciente> tree = Tree<Paciente>(print, comparar, cant_nivel);
	for (int i = 1; i <= npacientes; i++) {
		Paciente paciente;
		paciente.usuario = generarPaciente();
		paciente.nvisitas = rand() % 101;
		tree.Insertar(paciente);
	}
	cout << "PACIENTES MOSTRADOS EN EL ARBOL: \n\n";
	tree.EnOrden();
	cout << "ALTURA: " << tree.Altura();
	cout << endl;
	//BUSCAR ELEMENTOS SEGUN NVISITAS
	string us;
	int n;
	cout << "INGRESAR LOS DATOS DEL PACIENTE QUE DESEA BUSCAR: \n";
	cout << "USUARIO: "; cin >> us;
	cout << "NVISITAS: "; cin >> n;
	Paciente paciente;
	paciente.usuario = us;
	paciente.nvisitas = n;
	if (tree.Buscar(paciente)) {
		cout << "SI SE ENCONTRO EL PACIENTE\n";
	}
	else {
		cout << "NO SE ENCONTRO EL PACIENTE\n";
	}


}