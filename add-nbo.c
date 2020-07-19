#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{   
    uint32_t a;
    uint32_t *pa = &a;
    uint32_t cross_a;

    uint32_t b;
    uint32_t *pb = &b;
    uint32_t cross_b;

    uint32_t sum_cross;
    
    if(argc < 3)
    {
        printf("Usage : %s 1.bin 2.bin", argv[0]);
        return 0;
    }
    
    FILE *f1 = fopen(argv[1], "rb");
    fread(pa, 4, 1, f1);
    cross_a = ntohl(a);
    
    FILE *f2 = fopen(argv[2], "rb");
    fread(pb, 4, 1, f2);
    cross_b = ntohl(b);

    sum_cross = cross_a + cross_b;
    
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)", cross_a, cross_a, cross_b, cross_b, sum_cross, sum_cross);

    fclose(f1);
    fclose(f2);

    return 0;
}
