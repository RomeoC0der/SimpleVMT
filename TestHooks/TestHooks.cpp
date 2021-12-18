#include <cstdint>
#include <string>
#include <vector>
#include <Windows.h>
//#app includes : 
#include "VMT.hpp"
#include "AppWorker.h"

AppWorker* appWorker = new AppWorker();
VMT vmt = VMT(appWorker);
void __fastcall hkWorkerWorks(void* ecx, int edx) {
	printf("recall of workers work\n");
	vmt.restore(3);
	static void (*original)() =reinterpret_cast<void (*)()>( vmt.getOriginalFunction(2));
	original();//call the original
	vmt.hook(3, (uintptr_t)hkWorkerWorks);
}


int main() {
	vmt.hook(3, (uintptr_t)hkWorkerWorks);
	appWorker->work();
	//delete appWorker;
}