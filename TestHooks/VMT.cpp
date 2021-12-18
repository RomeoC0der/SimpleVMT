#include "VMT.hpp"

VMT::VMT(void* c_base_class)
{
	this->classPtr = c_base_class;
	this->present_vftable = (uintptr_t**)(c_base_class);//read vtable from class (class)->(vftable){[0]->function, [1]->function,...[n]->function}, pointer to vftable
	this->original_vftable = *this->present_vftable;//now -> stores all values of vftable
	while (reinterpret_cast<uintptr_t*>(*this->present_vftable)[this->methods_length])++this->methods_length;
	print_vftable();

	this->shadow_vftable = new uintptr_t[sizeof uintptr_t * this->methods_length];
	memcpy(this->shadow_vftable, this->present_vftable, sizeof uintptr_t * this->methods_length);//full copied/read from original_vftable

}

void VMT::hook(uint16_t index, uintptr_t function)
{
	this->shadow_vftable[index] = function;
	VirtualProtect(this->present_vftable, sizeof uintptr_t * this->methods_length, PAGE_EXECUTE_READWRITE, &this->prev_protect_value);
	*this->present_vftable = this->shadow_vftable;
	VirtualProtect(this->present_vftable, sizeof uintptr_t * this->methods_length, this->prev_protect_value, &this->prev_protect_value);
}

void VMT::restore(uint16_t index)
{
	this->shadow_vftable[index] = this->original_vftable[index];
	VirtualProtect(this->present_vftable, sizeof uintptr_t * this->methods_length, PAGE_EXECUTE_READWRITE, &this->prev_protect_value);
	*this->present_vftable = this->shadow_vftable;
	VirtualProtect(this->present_vftable, sizeof uintptr_t * this->methods_length, this->prev_protect_value, &this->prev_protect_value);
}

uintptr_t VMT::getOriginalFunction(uint16_t index)
{
	if (index < this->methods_length)
	{
		return (this->original_vftable[index]);
	}
	return 0u;
}
