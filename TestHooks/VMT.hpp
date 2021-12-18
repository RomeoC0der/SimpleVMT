#pragma once
#include <Windows.h>
#include <iostream>
typedef void(__stdcall* oVoidCall)();

class VMT {
public:
	VMT(void* c_base_class);
	void hook(uint16_t index, uintptr_t function);
	void restore(uint16_t index);
	template <typename T>
	T& getOriginalFunctionCast(uint16_t index) {
		if (index < this->methods_length)
		{
			return reinterpret_cast<T>(this->original_vftable[index]);
		}
		return NULL;
	}
	uintptr_t getOriginalFunction(uint16_t);
	~VMT() {

	}
protected:
	void print_vftable() {
		printf("c_base_class_ptr: 0x%p, methods : %d\n", this->classPtr, this->methods_length);
		printf("vftable_ptr: 0x%p\n", *this->present_vftable);
		for (uint16_t i = 0U; i < this->methods_length; ++i) {
			uintptr_t* function = this->present_vftable[i];
			printf("vftable[%d]: pointer-> 0x%p\n", i, &this->present_vftable[i]);
		}
	}
private:
	uint16_t methods_length{ 0U};
	uintptr_t* original_vftable{ nullptr };
	uintptr_t* shadow_vftable{ nullptr };
	uintptr_t** present_vftable{ nullptr };
	void* classPtr{ nullptr };
	DWORD prev_protect_value{ 0UL };
};