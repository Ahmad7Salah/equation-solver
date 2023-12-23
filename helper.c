#include <math.h>
#include <stdio.h>


#include "helper.h"


void solve_simultaneous(float coefficients1[3], float coefficients2[3])
{
    float ans[2][1];
    float coef_matrix[2][2];
    // to make a coefficientMatrix
    for(int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (i == 0)
            {
                coef_matrix[i][j] = coefficients1[j];
            }
            else if (i == 1)
            {
                coef_matrix[i][j] = coefficients2[j];
            }
        }
    }
    float determinantMatrix;
    // to evaluate the determinant of matrix
    determinantMatrix = (coef_matrix[0][0] * coef_matrix[1][1]) - (coef_matrix[1][0] * coef_matrix[0][1]);

    float inverse_matrix[2][2];
    float const_matrix[2][1];
    // to make constants matrix
    for (int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 1; ++j)
        {
            if (i == 0)
            {
                const_matrix[i][j] = coefficients1[2];
            }
            else if (i == 1)
            {
                const_matrix[i][j] = coefficients2[2];
            }
        }
    }
    if (determinantMatrix != 0)
    {
        // to make an inverse matrix
        inverse_matrix[0][0] = coef_matrix[1][1] / determinantMatrix;
        inverse_matrix[1][1] = coef_matrix[0][0] / determinantMatrix;
        inverse_matrix[1][0] = -coef_matrix[1][0] / determinantMatrix;
        inverse_matrix[0][1] = -coef_matrix[0][1] / determinantMatrix;
        // to get the result of the two equation
        ans[0][0] = inverse_matrix[0][0] * const_matrix[0][0] + inverse_matrix[0][1] * const_matrix[1][0];
        ans[1][0] = inverse_matrix[1][0] * const_matrix[0][0] + inverse_matrix[1][1] * const_matrix[1][0];
        // to print the result relate to x and y
        printf("x = %.4f and y = %.4f\n", ans[0][0], ans[1][0]);
    }
    // we check if the two equations have infinite solution of no solution
    int determinantM1, determinantM2;
    if (determinantMatrix == 0)
    {
        determinantM1 = coef_matrix[0][0] * const_matrix[1][0] - coef_matrix[1][0] * const_matrix[0][0];
        determinantM2 = coef_matrix[0][1] * const_matrix[1][0] - coef_matrix[1][1] * const_matrix[0][0];

        if ((determinantM1 == 0) && (determinantM2 == 0))
        {
            printf("The two equations have an infinite solution.");
        }
        else
        {
            printf("No solution for the two equations.");
        }
    }
}

void solve_quadratic(float coefficients[3])
{
    // This function calculates the real/complex roots of the given quadratic equation.
    float ans[2];
    float discriminant = pow(coefficients[1], 2) - 4 * coefficients[0] * coefficients[2];
    // if the roots are real.
    if (discriminant >= 0)
    {
        ans[0] = (-coefficients[1] + sqrt(discriminant)) / (2 * coefficients[0]);
        ans[1] = (-coefficients[1] - sqrt(discriminant)) / (2 * coefficients[0]);
        printf("x1 = %.4f, x2 = %.4f\n", ans[0], ans[1]);
        return;
    }
    // if the roots are complex numbers.
    ans[0] = -coefficients[1] / (2.0 * coefficients[0]);
    ans[1] = sqrt(-discriminant) / (2 * coefficients[0]);
    printf("x1 = %.4f + %.4fi, x2 = %.4f - %.4fi\n", ans[0], ans[1], ans[0], ans[1]);
    return;
}

void solve_cubic(float coefficients[4])
{
    float ans[3];
    // simplifying equation
    float a = coefficients[1] / coefficients[0];
    float b = coefficients[2] / coefficients[0];
    float c = coefficients[3] / coefficients[0];
    // let p = b - a^2 / 3 and q = (2*a^3 / 27) - (a * b / 3) + c
    // Discriminant = q^2 / 4 + p^3 / 27
    float p = b - pow(a, 2) / 3.0;
    float q = (2 * pow(a, 3) / 27.0) - (a * b / 3.0) + c;
    float discriminant = (pow(q, 2) / 4.0) + (pow(p, 3) / 27.0);
    // Case 1: Roots of a cubic equation when ∆ > 0 there is only one real solution.
    if (discriminant > 0)
    {
        ans[0] = cbrt((-q / 2.0) + sqrt(discriminant)) + cbrt((-q / 2.0) - sqrt(discriminant)) - a / 3.0;
        // dividing by the calculated root.
        float n_coeffs[3];
        n_coeffs[0] = 1;
        for (int i = 1; i < 3; i++)
        {
            n_coeffs[i] = (n_coeffs[i - 1] * ans[0]) + (coefficients[i] / coefficients[0]);
        }
        // solving the new quadratic equation to get the 2nd and 3rd roots.
        solve_quadratic(n_coeffs);
        printf("x3 = %.4f\n", ans[0]);
        return;
    }
    // Case 2: Roots of a cubic equation when ∆=0 there are repeated roots.
    else if (round(discriminant) == 0)
    {
        ans[0] = -2 * cbrt(q / 2.0) - a / 3.0;
        ans[1] = ans[2] = cbrt(q / 2.0) - a / 3.0;
    }
    // Case 3: Roots of a cubic equation when ∆<0 there are three real solutions.
    else
    {
        ans[0] = ((2.0 / sqrt(3)) * sqrt(-p) * sin(1 / 3.0 * asin((3 * sqrt(3) * q) / (2.0 * pow(-p, 3 / 2.0))))) - a / 3.0;
        ans[1] = ((-2.0 / sqrt(3)) * sqrt(-p) * sin(1 / 3.0 * asin((3 * sqrt(3) * q) / (2.0 * pow(-p, 3 / 2.0))) + 22 / 21.0)) - a / 3.0;
        ans[2] = ((2.0 / sqrt(3)) * sqrt(-p) * cos(1 / 3.0 * asin((3 * sqrt(3) * q) / (2.0 * pow(-p, 3 / 2.0))) + 22 / 42.0)) - a / 3.0;
    }
    printf("x1 = %.4f, x2 = %.4f, x3 = %.4f\n", ans[0], ans[1], ans[2]);
    return;
}

void solve_quartic(float coefficients[5], float diff[4])
{
    float j = 0;
    float n_coeffs[4];
    do
    {
        // if multiples isn't a root. we try newton's raphson.
        if (j == coefficients[4])
        {
            j = newton_raphson(coefficients, diff, 0, 1);
            // synthetic division
            n_coeffs[0] = 1;
            for (int i = 1; i < 4; i++)
            {
                n_coeffs[i] = (n_coeffs[i - 1] * j) + coefficients[i];
            }
            break;
        }
        // finding multiples of e
        for (int i = j + 1; i <= coefficients[4]; i++)
        {
            if ((int) coefficients[4] % i == 0)
            {
                j = i;
                break;
            }
        }
        // dividing equation by j.
        n_coeffs[0] = 1;
        for (int i = 1; i < 4; i++)
        {
            n_coeffs[i] = (n_coeffs[i - 1] * j) + coefficients[i];
        }
        // breaks out of the loop if j was a root of the equation.
        if (n_coeffs[3] * j + coefficients[4] == 0)
        {
            break;
        }
        else
        {
        // testing again for the negative value of j.
            for (int i = 1; i < 4; i++)
            {
                n_coeffs[i] = (n_coeffs[i - 1] * -j) + coefficients[i];
            }
            if (n_coeffs[3] * -j + coefficients[4] == 0)
            {
                j = -j;
                break;
            }
        }
    } while (1);
    solve_cubic(n_coeffs);
    printf("x4 = %.4f\n", j);
}

float newton_raphson(float coefficients[5], float diff[4], float x0, int i)
{
    // This function uses Newton Raphson method to calculate the real roots of given quartic polynomial.
    // stop condition. i: number of iterations.
    if (i == 30)
    {
        return x0;
    }
    // Substitution in the quartic equation and it's derivative.
    float y = 0;
    float yy = 0; 
    for (int i = 0, j = 4; i < 5; j--, i++)
    {
        y += coefficients[i] * pow(x0, j);
        if (j == 0)
        {
            break;
        }
        yy += diff[i] * pow(x0, j - 1);
    }
    // Newton's equation.
    x0 -= y / yy;
    // recursion for better approximation.
    newton_raphson(coefficients, diff, x0, ++i);
}