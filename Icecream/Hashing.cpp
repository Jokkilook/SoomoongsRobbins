#include "Hashing.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int transform(char* key)
{
	int number = 0;
	while (*key)
		number = number + *key++;
	return number;
}

int hash_function(char* key)
{
	return transform(key) % TABLE_SIZE;
}
