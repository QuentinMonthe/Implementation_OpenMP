#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

float power(int exp, float value);
void calcul(int val);

int n, a;
double value_pi = 0;

int main(int argc, char const *argv[])
{
    int i;

    if (argc > 1)
    {
        n = atoi(argv[1]);

        do
        {
            if (a != 0 && a < n)
            {
                printf("Erreur ! L'ordre de grandeur du calcul est inferieur au nombre de trhead !\n\tVeuillez entrer l'ordre de grandeur : (? >= %d) : ", n);
            }
            else if (a < n)
            {
                printf("Veuillez entrez l'ordre de grandeur du calcul (? >= %d) : ", n);
            }
            scanf("%d", &a);
        } while (a < n);
    
        #pragma omp parallel num_thead(n)
        {
            int pid = omp_get_thread_num();
            calcul(pid);
        }

        printf("Valeur de Pi par calcul parallelise :  %lf\n", value_pi);
    }
    return 0;
}

float power(int exp, float value)
{
    if (exp == 0 || value == 1)
    {
        return 1;
    }

    int i;
    double reault_power = 1;
    for (i = 1; i <= exp; i++)
    {
        reault_power *= value;
    }
    return reault_power;
}

void calcul(int val)
{
    int i;
    double result = 0;
    int index_start = val == 0 ? 0 : (val * a) / n + 1;
    int index_end = (val + 1) * a / n;

    for (i = index_start; i <= index_end; i++)
    {
        result += power(i, -1) / (2 * i + 1);
    }
    printf("Resultat du thread %d : %lf\n\n", val, result);
    value_pi += result * 4;
}

