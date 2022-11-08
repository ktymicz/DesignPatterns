#pragma once
#include <iostream>
#include <memory>

template<typename T, typename D>
class Temporary_Ptr_unique
{
	using parent_ptr = typename std::unique_ptr<T, D>;
	using pointer =typename parent_ptr::pointer;

	Temporary_Ptr_unique(const Temporary_Ptr_unique& nocopy)= delete;
	Temporary_Ptr_unique& operator=(const Temporary_Ptr_unique& nocopy) = delete;



public:
	parent_ptr* p;
	pointer ptr_t;
	Temporary_Ptr_unique(std::unique_ptr<T,D> & ptr) : 
		p(&ptr), ptr_t(ptr.release()) {}
	Temporary_Ptr_unique(Temporary_Ptr_unique&& mover) : 
		p(std::move(mover.p)),
		ptr_t(std::move(mover.ptr_t)) {	mover.p = nullptr; }
	Temporary_Ptr_unique& operator=(Temporary_Ptr_unique&& mover) 
	{
		p = mover.p;
		ptr_t = mover.ptr_t;
		mover.p = nullptr;
	}
	~Temporary_Ptr_unique() { if(p)p->reset(ptr_t); }
	operator pointer*() { return &ptr_t; }
};