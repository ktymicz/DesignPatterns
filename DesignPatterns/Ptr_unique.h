#pragma once

#include <memory>

template <typename T, typename D>
class Ptru
{
	using parent = std::unique_ptr<T, D>;
	using pointer = typename parent::pointer;

	parent* p;
	pointer ptr_t;

	Ptru(const Ptru& nocopy) = delete;
	Ptru& operator=(const Ptru& nocopy) = delete;
public:
	Ptru(std::unique_ptr<T, D>& borrow)
	: p{ &borrow }, ptr_t{ borrow.release() } {}
	Ptru(Ptru && mover)
		: p{ std::move(mover.p) }, ptr_t{ std::move(mover.ptr_t) } 
	{
		mover.p = nullptr;
	}
	Ptru& operator=(Ptru&& mover) 
	{
		p = std::move(mover.p);
		ptr_t = std::move(mover.ptr_t);
		mover.p = nullptr;
		return *this;
	}
	operator pointer*() { return &ptr_t; }
	~Ptru() { if (p) { p->reset(ptr_t);} }
};