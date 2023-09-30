#include <iostream>
template<typename T>
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