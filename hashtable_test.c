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

#include <stdio.h>
#include <string.h>

#include "hashtable.h"

int main(void) {
    hashtable *ht = hashtable_new();
    hashtable_put(ht, "foo", "bar");

    char *v = hashtable_get(ht, "foo");
    if (v) {
        if (strcmp(v, "bar") != 0) {
            printf("`bar' expected, but got `%s'\n", v);
        }
    } else {
        puts("`bar' expected, but no value found.");
    }

    hashtable_free(ht);
}
