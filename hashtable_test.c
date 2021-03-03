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
#include <stdlib.h>

#include "hashtable.h"

static void check_value(hashtable *ht, char const *key, char const *expected_value) {
    char *v = hashtable_get(ht, key);
    if (v) {
        if (strcmp(v, expected_value) != 0) {
            printf("`%s' expected, but got `%s'\n", expected_value, v);
            exit(1);
        }
    } else {
        printf("`%s' expected, but no value found.\n", expected_value);
    }
}

int main(void) {
    hashtable *ht = hashtable_new();
    hashtable_put(ht, "foo", "1");
    hashtable_put(ht, "bar", "2");
    hashtable_put(ht, "baz", "3");
    hashtable_put(ht, "bar", "4");

    check_value(ht, "foo", "1");
    check_value(ht, "bar", "4");

    hashtable_erase(ht, "baz");
    if (hashtable_get(ht, "baz") != NULL) {
        puts("NULL expected, but got value.");
        exit(1);
    }

    hashtable_free(ht);
}
