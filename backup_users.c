//sample users of sim card

#include <stdio.h>
void main()
{
	FILE *ptr;
	ptr = fopen("users.bin", "wb");
	fprintf(ptr, "remo\t1234567890\t5.00\t0\nlara\t9876543210\t15.00\t0\nseria\t7777777777\t50.00\t0\nseros\t1235864790\t25.00\t0\nsojit\t1122334455\t55.00\t0\n");
	fclose(ptr);
}