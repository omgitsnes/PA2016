/*
 * lab5 / ficha 05
 * 2016-11-10
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
	 (void)argc; (void)argv;

	 short A = 0x1122;
	 short B = ~A;	/* ~ => negacao de A */

	 printf("A=%hx, B=%hx\n", A, B);
	 printf("size_of_short=%d\n", sizeof(short)*8);

	 return 0;
}
