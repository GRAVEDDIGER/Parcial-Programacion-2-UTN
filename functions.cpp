#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Viajes.h"
#include "Tarjetas.h"
#include "string.h"
#include "constants.h"
#include <string>
#include "clases.h"
/*
1. Informar para un número de tarjeta que se ingresa por teclado la
cantidad de viajes realizados en cada uno de los medios de transporte.
*/
int longitudArchivo(FILE* data) {
	int current = ftell(data);
	fseek(data, 0, SEEK_END);
	int bytes = ftell(data);
	fseek(data, 0, current);
	return bytes;
}
/*
Esta funcion usa un template con un tipo T que realiza las siguientes funciones 
1) abre el archivo y valida su apertura
2) verifica la longitud en bytes del archivo
3) genera el numero de items a partir de dividir los bytes/sizeof el tipo pasado 
4) alloca memoria dinamica para contener los items guardados en el archivo
5) lee el archivo completo y lo copia en la memoria dinamica alocada
6) devuelve un struct que tiene un valor int con el numero de items y un puntero a la memoria alocada con el contenido del archivo

valida cada una de las interacciones con el archivo.
el struct FIle Response tiene un constructor basico y un destructor que se encarga de liberar la memoria alocada cuando sale del scope

*/ 
template<typename T>
FileResponse<T> getFileData(const char* path)
{
	FILE* archivo = fopen(path, "rb");
	if (!archivo) {
		std::cout << "Error al abrir el archivo\n";
		return {nullptr,-1};
	}
	int bytes = longitudArchivo(archivo),items=bytes/sizeof(T);
	T* data = new T[items];
	int response = fread(data, bytes, 1, archivo);
	fclose(archivo);
	if (response != 1)
	{
		std::cout << "Error al leer el archivo!\n";
		return { nullptr,-1 };

	}
	
	return {data,items};
}

void numeroDeViajes(char* tarjeta)//VERIFICADA
{
	auto fileData = getFileData<Viajes>(VIAJES);

	int colectivo = 0, subte = 0, tren = 0,total=0;
	for (int i = 0; i < fileData.items; i++)
	{
		if (strcmp(tarjeta,fileData.ptr[i].numeroTarjeta)==0)
		{ 
			total++;
			switch (fileData.ptr[i].medioTransporte) 
			{
			case 1:
				colectivo++;
				break;
			case 2:
				subte++;
				break;
			case 3:
				tren++;
				break;

			}
			
		}
	}
	std::cout << "El total de viajes de la tarjeta " << tarjeta << " fue : " << total << std::endl;
	std::cout << "En colectivo: " << colectivo << std::endl;
	std::cout << "En subte: " << subte << std::endl;
	std::cout << "En tren: " << tren << std::endl;
	
}
//2. El viaje con menor importe. Mostrar todo el registro.
void viajeMenorImporte()//VERIFICADA
{
	FileResponse<Viajes> fileData = getFileData<Viajes>(VIAJES);

	int menorImporte = fileData.ptr[0].importeViaje;
	Viajes viaje;
	for (int i = 0; i < fileData.items; i++)
	{
		if (fileData.ptr[i].importeViaje < menorImporte)
		{
			menorImporte = fileData.ptr[i].importeViaje;
			viaje = fileData.ptr[i];
		}
	}
	mostrarViaje(viaje);
}
//3. El mes de mayor recaudación por viajes en subte entre todos los viajes.
void limpiarArray(float*ptr,int size)
{
	for (int i = 0; i < size; i++)
	{
		ptr[i] = 0;
	}
}
void subteMayorRecaudacion() //VERIFICADO
{
	
	FileResponse<Viajes>  fileData= getFileData<Viajes>(VIAJES);
	int mayorRecaudacion = 0, mes = -1;
	float recaudacionXMes[12];
	limpiarArray(recaudacionXMes, 12);
	for (int i = 0; i < fileData.items; i++)
	{	
		if (fileData.ptr[i].medioTransporte==2)
		{
			int mesInterno = fileData.ptr[i].mesViaje - 1;
			recaudacionXMes[mesInterno] += fileData.ptr[i].importeViaje;
		}
	}
	
	for (int i = 0; i < 12; i++)
	{
		if (recaudacionXMes[i] > mayorRecaudacion) {
			mayorRecaudacion = recaudacionXMes[i];
			mes = i + 1;
		}
	}
	if (mes == -1) {
		std::cout << "No se encontraron viajes en subte registrados\n";
		return;
	}
	std::cout << "El mes de mayor recaudacion fue el mes " << mes <<std::endl;

}

//4. Informar para CADA número de tarjeta la cantidad de viajes realizados 
//verificada
int contarViajesColectivo(char* numeroTarjeta)
{
	FileResponse<Viajes> fileData = getFileData<Viajes>(VIAJES);
	int viajesResultado = 0;
	for (int i = 0; i < fileData.items; i++)
	{
		if (strcmp(numeroTarjeta,fileData.ptr[i].numeroTarjeta)==0 && fileData.ptr[i].medioTransporte==1)
		{
			viajesResultado++;
		}
	}
	return viajesResultado;
}
void viajesXTarjeta()//VERIFICADA
{
	FileResponse<Tarjetas> fileData = getFileData<Tarjetas>(TARJETAS);
	std::string *repetidos = new std::string[fileData.items];
	for (int i =0;i<fileData.items;i++)
	{
		std::cout << "La tarjeta Nro: " << fileData.ptr[i].numeroTarjeta << " tuvo " << contarViajesColectivo(fileData.ptr[i].numeroTarjeta) << " viajes en colectivo." << std::endl;
	}

}

//5. El numero viaje con mayor importe. Mostrar el número de tarjeta y el DNI 
//del dueño.Debe mostrar los tres datos solicitados.
void mostrarDatosTarjeta(char* numeroTarjeta,float importe)
{
	FileResponse<Tarjetas> fileData = getFileData<Tarjetas>(TARJETAS);

	for (int i = 0; i < fileData.items; i++)
	{
		if (strcmp(numeroTarjeta, fileData.ptr[i].numeroTarjeta) == 0)
		{
			std::cout << "El mayor importe fue de: " << importe << " DNI del propietario: " << fileData.ptr[i].dniDuenio << " Tarjeta Nro: " << numeroTarjeta << std::endl;
			return;
		}
}
}
void viajeMayorImporte()//VERIFICADO
{
	FileResponse<Viajes> fileData = getFileData<Viajes>(VIAJES);
	float mayorImporte = 0;
	char numeroDeTarjeta[6];
	for (int i = 0; i < fileData.items; i++)
	{
		if (fileData.ptr[i].importeViaje > mayorImporte)
		{
			strcpy(numeroDeTarjeta, fileData.ptr[i].numeroTarjeta);
			mayorImporte = fileData.ptr[i].importeViaje;
		}
	}
	mostrarDatosTarjeta(numeroDeTarjeta,mayorImporte);
}

//6. Informar para cada una de las tarjetas activas el importe total gastado 
//por TODOS viajes realizados.

float importeTotalTarjeta(char * numeroTarjeta)
{
	FileResponse<Viajes> fileData = getFileData<Viajes>(VIAJES);
	
	float importeTotal = 0;
	for (int i = 0; i < fileData.items; i++)
	{
		if (strcmp(numeroTarjeta,fileData.ptr[i].numeroTarjeta)==0)
		{
			importeTotal += fileData.ptr[i].importeViaje;
		}
	}
	return importeTotal;
}
void importesTarjetasActivas() //verificada
{
	FileResponse<Tarjetas> fileData = getFileData<Tarjetas>(TARJETAS);

	for (int i = 0; i < fileData.items; i++)
	{
		if (fileData.ptr[i].estado)
		{
			std::cout << "La tarjeta Nro: " << fileData.ptr[i].numeroTarjeta << " consumio " << importeTotalTarjeta(fileData.ptr[i].numeroTarjeta) << " $" << std::endl;
		}
	}
}