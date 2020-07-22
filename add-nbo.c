#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int cross_file(char *message, const char* mode)
{
	uint32_t a;
	uint32_t *pa = &a;
	uint32_t cross;

	FILE *fp = fopen(message, mode);
	if(fp == NULL)
		printf("Can't open file\n");
	fread(pa, 1, 4, fp);
	cross = ntohl(a);

	fclose(fp);

	return cross;	
}

int main(int argc, char *argv[])
{   
	uint32_t a1, b1;
    uint32_t sum_cross=0;
    
    if(argc < 3)
    {
        printf("Usage : %s thousand.bin five-hundred.bin", argv[0]);
        return 0;
    }
    
    a1 = cross_file(argv[1], "rb");
    sum_cross += a1;

	b1 = cross_file(argv[2], "rb");
	sum_cross += b1;
    
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)", a1, a1, b1, b1, sum_cross, sum_cross);

    return 0;
}
