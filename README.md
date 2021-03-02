# Hashtable

This is a hashtable implementation for studying for myself.

## Usage


```c
//#include "hashtable.h"

hashtable *ht = hashtable_new();
hashtable_put(ht, "foo", "bar"); // Now, the hashtable has "bar" indexed by "foo".
hashtable_get(ht, "foo");        // will get "bar".
hashtable_free(ht);              // Discard the hashtable.
```

For more sample code, see `hashtable_test.c`.
