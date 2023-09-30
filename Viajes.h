#ifndef VIAJES_H_INCLUDED
#define VIAJES_H_INCLUDED
#include <iostream>
struct Viajes
{
    char numeroViaje[5];
    char numeroTarjeta[6];
    int medioTransporte;//(1 - Colectivo, 2 - Subte, 3 - Tren)
    int mesViaje;
    float importeViaje;
    void printData() {
        std::cout << this->numeroViaje << "," << this->numeroTarjeta << "," << this->medioTransporte << "," << this->mesViaje << "," << this->importeViaje << std::endl;
    }
};

void mostrarViaje(Viajes);

#endif // VIAJES_H_INCLUDED
