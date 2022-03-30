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

#include <bits/functexcept.h>

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

	void __attribute__((weak))
	__throw_bad_exception()
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_bad_alloc()
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_bad_cast()
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_bad_typeid()
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_logic_error(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_domain_error(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_invalid_argument(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_length_error(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_out_of_range(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_runtime_error(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_range_error(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_overflow_error(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_underflow_error(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_bad_optional_access()
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_bad_variant_access(const char* __s __attribute__((unused)))
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_bad_function_call()
	{ __builtin_abort(); }

	void __attribute__((weak))
	__throw_bad_any_cast()
	{ __builtin_abort(); }

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace
