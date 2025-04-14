// Copyright (c) 2024 Clarisma / GeoDesk contributors
// SPDX-License-Identifier: LGPL-3.0-only

#pragma once

#include <atomic>

namespace clarisma {

class RefCounted
{
public:
	RefCounted() : refcount_(1) {}
	virtual ~RefCounted() {};   // needs to have a virtual destructor

	/*
	void addref() const { ++refcount_; }
	void release() const
	{
		if (--refcount_ == 0)
		{
			delete this;
		}
	}
	*/

	void addref() const
	{
		refcount_.fetch_add(1, std::memory_order_relaxed);
	}

	void release() const
	{
		if (refcount_.fetch_sub(1, std::memory_order_acq_rel) == 1)
		{
			delete this;
		}
	}

private:
	mutable std::atomic_uint32_t refcount_;
};

} // namespace clarisma
