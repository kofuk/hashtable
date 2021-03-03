// Copyright (C) 2021 Koki Fukuda

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef HASHTABLE_H
#define HASHTABLE_H

#ifdef __cplusplus
#define BEGIN_DECL extern "C" {
#define END_DECL }
#else // not defined(__cplusplus)
#define BEGIN_DECL
#define END_DECL
#endif // defined(__cplusplus)

BEGIN_DECL

/* On MSVC, we have to `dllexport' symbols so that linker can find them. */
#ifdef _WIN32
#ifdef HASHTABLE_LIBRARY_BUILD
#define HASHTABLE_API __declspec(dllexport)
#else // not defined(HASHTABLE_LIBRARY_BUILD)
#define HASHTABLE_API __declspec(dllimport)
#endif // defined(HASHTABLE_LIBRARY_BUILD)
#else  // not defined(_WIN32)
#define HASHTABLE_API
#endif // defined(_WIN32)

typedef struct hashtable hashtable;

HASHTABLE_API hashtable *hashtable_new(void);
HASHTABLE_API void hashtable_free(hashtable *obj);

HASHTABLE_API void hashtable_put(hashtable *ht, char const *key, char const *val);
HASHTABLE_API char *hashtable_get(hashtable const *ht, char const *key);
HASHTABLE_API void hashtable_erase(hashtable *ht, char const *key);

END_DECL

#endif
