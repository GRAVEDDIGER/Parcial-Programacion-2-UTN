# PROGRAMACION 2 - PARCIAL 1
## Duración: 72 horas
## Entrega: entregar el proyecto comprimido llamado APELLIDO_NOMBRE y 
subirlo en Primer parcial 1 - Entrega que figura en el tema Primer parcial
del Campus Virtual de la materia. El programa debe compilar para ser tenido 
en cuenta.
### IMPORTANTE: El sistema no admite entregas después de transcurrido el 
tiempo. Utilizar los archivos ya creados que se encuentran en 
Recursos Parcial 1.rar
## ENUNCIADO
La Secretaría de Transportes dispone de un sistema para el control de la tarjeta 
SUBE. Tiene, entre otros, los siguientes archivos:
Tarjetas.dat
⎯ char numeroTarjeta[6];
⎯ int mesAlta;
⎯ char dniDuenio[9];
⎯ float saldo;
⎯ bool estado; (1 - Activa, 0 - Dada de baja)
Viajes.dat
⎯ char numeroViaje[5];
⎯ char numeroTarjeta[6];
⎯ int medioTransporte; (1 - Colectivo, 2 - Subte, 3 - Tren)
⎯ int mesViaje;
⎯ float importeViaje;
El archivo de viajes tiene la información desde el año 2018.
## RESOLVER:
Se solicita se desarrolle un programa en Code::Blocks en C++ para resolver los 
siguientes puntos:
1. Informar para un número de tarjeta que se ingresa por teclado la 
cantidad de viajes realizados en cada uno de los medios de transporte.
2. El viaje con menor importe. Mostrar todo el registro.
3. El mes de mayor recaudación por viajes en subte entre todos los viajes.
4. Informar para CADA número de tarjeta la cantidad de viajes realizados 
en colectivos el mes de mayo.
5. El numero viaje con mayor importe. Mostrar el número de tarjeta y el DNI 
del dueño. Debe mostrar los tres datos solicitados.
6. Informar para cada una de las tarjetas activas el importe total gastado 
por TODOS viajes realizados.
### NOTA:
Resolver creando/utilizando todas las funciones, estructuras, archivos y menús 
necesarios.
## DATOS ADICIONALES:
En Recursos Parcial 1.rar encontraran los siguientes archivos:
Viajes.h, Tarjetas.h, Viajes.cpp y main.cpp. Además de Viajes.dat y Tarjetas.dat
Los archivos Viajes.dat y Tarjetas.dat incluyen los siguientes registros.

## RESOLUCION:
Se creo un struct *FileResponse* con un constructor basico y un destructor que libera la memoria alocada dentro del mismo que porta
2 propiedades, un entero que equivale al numero de items dentro del archivo y un puntero que apunta a una posicion de la memoria 
Heap que es un buffer del archivo.

```cpp
struct FileResponse
{
	T* ptr;
	int items;
	FileResponse(T* puntero,int numeroDeItems)
		:ptr(puntero),items(numeroDeItems)
	{}
	~FileResponse()
	{
		delete[] ptr;
	}
};
```
Se creo una funcion que abre el archivo valida cada una de las operaciones con el archivo y devuelve un *FileResponse*
Alocando en memoria dinamica la informacion contenida en el archivo. 
unico parametro un *const char** que representa el path del archivo.
Esta es una templated funcion y toma el tipo 
```cpp
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
```

## ADRIAN DANIEL ABADIN
