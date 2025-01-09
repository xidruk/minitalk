#include "g_utils.h"

// the stack of bytes function collect a list of variables into old block and return it !
// co_of_bytes : collection of bytes 
// c_bytes : casted bytes
int get_len(char *co_of_bytes)
{
	int len;

	len = 0;
	if (!co_of_bytes)
		return (len = -1, len);
	while (co_of_bytes[len])
		len++;
	return (len);
}

char *hold_null_case(unsigned char byte)
{
	unsigned char *new_data;

	new_data = malloc(2 * sizeof(char));
	new_data[0] = byte;
	new_data[1] = '\0';
	return (new_data);
}



char *stack_0f_bytes(char *co_of_bytes, char c)
{
	char *new_stack_0fb;
	int index;
	int len_of_cob;
	unsigned char *c_bytes;
	unsigned char new_byte;

	index = 0;
	c_bytes = (unsigned char *)co_of_bytes;
	new_byte = (unsigned char)c;
	len_of_cob = get_len(c_bytes);
	if (len_of_cob < 0)
		return (hold_null_case(new_byte));
	new_stack_0fb = malloc((len_of_cob + 2)*sizeof(char));
	if (!new_stack_0fb)
		return (NULL);
	while (c_bytes[index])
	{
		new_stack_0fb[index] = c_bytes[index];
		index++;
	}
	new_stack_0fb[index] = new_byte;
	new_stack_0fb[len_of_cob + 1] = '\0';
	return (new_stack_0fb);
}
