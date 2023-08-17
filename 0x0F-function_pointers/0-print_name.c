#include "function_pointers.h"
#include <stdio.h>
/**
 * print_name - Prints a name using the provided function
 * @name: The name to be printed
 * @f: A function pointer to the printing function
 *
 * Description: This function takes a name and a function pointer as
 * arguments. It calls the provided function to print the given name.
 */
void print_name(char *name, void (*f)(char *))
{
	if (name != NULL && f != NULL)
		f(name);
}
