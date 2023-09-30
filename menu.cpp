#include <iostream>
#include "functions.h"
void menu()
{
	int opcion = -1;
	while (true)
	{
		system("cls");
		std::cout << "*****************************************************\n";
		std::cout << "1 - Viajes realizados por cada medio de transporte\n";
		std::cout << "2 - Mostrar viaje de menor importe\n";
		std::cout << "3 - Mes de mayor recaudacion para viajes en subte\n";
		std::cout << "4 - Viajes en colectivo x cada Tarjeta\n";
		std::cout << "5 - Viaje de mayor importe\n";
		std::cout << "6 - Importe TOTAL gastado para cada tarjeta ACTIVA\n";
		std::cout << "*****************************************************\n";
		std::cout << "                     0 - SALIR\n";
		std::cin >> opcion;
		switch (opcion)
		{
		case 0:
			return;
			break;
		case 1:
			char numeroTarjeta[6];
			std::cin.ignore();
			std::cout << "Ingrese el numero de tarjeta (6 DIGITOS): ";
			std::cin.getline(numeroTarjeta, 6);
			numeroDeViajes(numeroTarjeta);
			system("pause");
			break;
		case 2:
			viajeMenorImporte();
			system("pause");
			break;
		case 3:
			subteMayorRecaudacion();
			system("pause");
			break;
		case 4:
			viajesXTarjeta();
			system("pause");
			break;
		case 5:
			viajeMayorImporte();
			system("pause");
			break;
		case 6:
			importesTarjetasActivas();
			system("pause");
			break;
		default:
			std::cout << "Opcion Incorrecta!\n";
			system("pause");
			break;
		}
	
	}
	
}