#include <ctype.h>
#include <stdio.h>
#include "helper.c"


int main(void)
{
    int choice = 0;
    do
    {
        char str[10];
        printf("What equation do you want to solve?\n1-simultaneous equation\n2-2nd degree polynomial\n3-3rd degree polynomial\n4-4th degree polynomial\n5-Exit\n");
        fgets(str, 10, stdin);
        if (sscanf(str, "%d", &choice) != 1 || choice < 1 || choice > 5)
        {
            printf("Invalid input: please enter a number from 1 to 5\n");
            continue;
        }
        switch(choice)
        {
            case 1:
                // to receive the coefficients of the first equation.
                float coefficients1[3], coefficients2[3];
                printf("Please enter the first equation coefficients:\n");
                for (int i = 0; i < 3; i++)
                {
                    do
                    {
                        printf("%c:", 'a' + i);
                        fgets(str, 10, stdin);
                        if (sscanf(str, "%f", &coefficients1[i]) == 1) break;
                        printf("Invalid input: please enter a number\n");
                    } while (1);
                }
                // to receive the coefficients of the second equation.
                printf("Please enter the second equation coefficients:\n");
                for (int i = 0; i < 3; i++)
                {
                    do
                    {
                        printf("%c:", 'd' + i);
                        fgets(str, 10, stdin);
                        if (sscanf(str, "%f", &coefficients2[i]) == 1) break;
                        printf("Invalid input: please enter a number\n");
                    } while (1);
                }
                solve_simultaneous(coefficients1, coefficients2);
                break;
            case 2:
                float coefficients3[3];
                // receiving the coefficients of the equation.
                printf("Please enter the equation coefficients:\n");
                for (int i = 0; i < 3; i++)
                {
                    do
                    {
                        printf("%c:", 'a' + i);
                        fgets(str, 10, stdin);
                        if (sscanf(str, "%f", &coefficients3[i]) == 1) break;
                        printf("Invalid input: please enter a number\n");
                    } while (1);
                }
                solve_quadratic(coefficients3);
                break;
            case 3:
                // receiving the coefficients of the equation.
                float coefficients4[4];
                printf("Please enter the equation coefficients:\n");
                for (int i = 0; i < 4; i++)
                {
                    do
                    {
                        printf("%c:", 'a' + i);
                        fgets(str, 10, stdin);
                        if (sscanf(str, "%f", &coefficients4[i]) == 1) break;
                        printf("Invalid input: please enter a number\n");
                    } while (1);
                }
                solve_cubic(coefficients4);
                break;
            case 4:
                // receiving the coefficients of the equation.
                float coefficients5[5];
                printf("Please enter the equation coefficients:\n");
                for (int i = 0; i < 5; i++)
                {
                    do
                    {
                        printf("%c:", 'a' + i);
                        fgets(str, 10, stdin);
                        if (sscanf(str, "%f", &coefficients5[i]) == 1) break;
                        printf("Invalid input: please enter a number\n");
                    } while (1);
                }
                for (int i = 4; i >= 0; i--)
                {
                    coefficients5[i] = coefficients5[i] / coefficients5[0];
                }
                float diff[4];
                for (int i = 4, j = 0; i > 0; j++, i--)
                {
                    diff[j] = coefficients5[j] * i;
                }
                solve_quartic(coefficients5, diff);
                break;
        }
    } while (choice != 5);
}