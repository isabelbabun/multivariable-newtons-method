#include <stdio.h>
#include <math.h>
#include <gsl/gsl_linalg.h>

int main()
{


    double guess_x = -1.470922;

    double guess_y = 0.468263;

    double J[4];

    double f[2];

    J[0] = 2 * guess_x;
    J[1] = 2 * guess_y;
    J[2] = -exp(guess_x);
    J[3] = 1.0;

    f[0] = pow(guess_x, 2) + pow(guess_y, 2) + 4;
    f[1] = exp(guess_x) * (1 - guess_x);

    gsl_matrix_view J_matrix = gsl_matrix_view_array (J, 2, 2);

    gsl_vector_view f_vector = gsl_vector_view_array (f, 2);

    gsl_vector *root_x_y = gsl_vector_alloc (2);

    int s;

    gsl_permutation *p = gsl_permutation_alloc (2);

    gsl_linalg_LU_decomp (&J_matrix.matrix, p, &s);

    gsl_linalg_LU_solve (&J_matrix.matrix, p, &f_vector.vector, root_x_y);

    //printf("root_x_y = \n");

    gsl_vector_fprintf (stdout, root_x_y, "%.16g");

    //gsl_permutation_free (p);
    //gsl_vector_free (root_x_y);

    guess_x = guess_x - gsl_vector_get(root_x_y, 0);

    guess_y = guess_y - gsl_vector_get(root_x_y, 1);

    printf("Value for guess_x: %f\n", guess_x);

    printf("Value for guess_y: %f\n", guess_y);

    gsl_permutation_free (p);
    gsl_vector_free (root_x_y);

    return 0;
}

