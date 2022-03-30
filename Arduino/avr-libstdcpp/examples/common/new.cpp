/*
 * Copyright (c) 2018, Christopher Durand
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <new>
#include <bits/functexcept.h>
#include <cstdlib>
#include <cstddef>

template<bool abortOnFail>
static inline void*
allocate(size_t size) _GLIBCXX_USE_NOEXCEPT
{
	void* ptr = malloc(size);

	if constexpr(abortOnFail) {
		if(!ptr) {
			std::__throw_bad_alloc();
		}
	}

	return ptr;
}

void *
operator new(size_t size)
{
	return allocate<true>(size);
}

void *
operator new[](size_t size)
{
	return allocate<true>(size);
}

void*
operator new(std::size_t size, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
{
	return allocate<false>(size);
}

void*
operator new[](std::size_t size, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
{
	return allocate<false>(size);
}

void
operator delete(void* ptr) _GLIBCXX_USE_NOEXCEPT
{
	free(ptr);
}

void
operator delete(void* ptr, size_t) _GLIBCXX_USE_NOEXCEPT
{
	free(ptr);
}

void
operator delete[](void* ptr) _GLIBCXX_USE_NOEXCEPT
{
	free(ptr);
}

void
operator delete[](void* ptr, size_t) _GLIBCXX_USE_NOEXCEPT
{
	free(ptr);
}

void
operator delete(void* ptr, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
{
	free(ptr);
}

void
operator delete[](void* ptr, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
{
	free(ptr);
}
