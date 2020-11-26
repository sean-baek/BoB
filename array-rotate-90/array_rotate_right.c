#include <stdio.h>
#include <string.h>

int main(void)
{
    int i, j, k, a, pos=0;
    int arr[10][10];
    int arr2[10][10];
    char input[20];

    scanf("%[^\n]s", input);
    int len = strlen(input);
    int s = (len + 1) / 2;

    for(i=0; i<s; i++)
        arr[0][i] = input[i*2]-'0';

    for(i=1; i<s; i++)
    {
        for(j=0; j<s; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    for(i=s-1; i>=0; i--)
    {
        for(j=0; j<s; j++)
        {

            arr2[j][i] = arr[s-1-i][j];
        }
    }

    printf("\n");

    for(i=0; i<s; i++)
    {
        for(j=0; j<s; j++)
        {
            printf("%d ", arr2[i][j]);
        }
        printf("\n");
    }

    return 0;
}
