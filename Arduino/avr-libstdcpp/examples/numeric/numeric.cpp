/*
 * Copyright (c) 2022, Christopher Kormanyos
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <array>
#include <numeric>

#if (defined(__cpp_lib_constexpr_numeric) && (__cpp_lib_constexpr_numeric >= 201911L))
#define MODM_CONSTEXPR constexpr
#define MODM_CONSTEXPR_NUMERIC_IS_CONSTEXPR 1
#else
#define MODM_CONSTEXPR
#define MODM_CONSTEXPR_NUMERIC_IS_CONSTEXPR 0
#endif

MODM_CONSTEXPR std::array<int, 3U> a { 1, 2, 3 };

int main()
{
	// 6
	auto MODM_CONSTEXPR sum = std::accumulate(a.cbegin(), a.cend(), 0);

	#if (MODM_CONSTEXPR_NUMERIC_IS_CONSTEXPR == 1)
	static_assert(sum == 6, "Error: Unexpected std::accumulate result!");
	#endif

	return (sum == 6 ? 0 : -1);
}
