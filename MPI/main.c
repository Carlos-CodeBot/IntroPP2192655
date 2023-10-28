/* Heat equation solver in 2D. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include "heat.h"

int main(int argc, char **argv) {
    double a = 0.5;             //!< Diffusion constant
    field current, previous;    //!< Current and previous temperature fields
    double dt;                  //!< Time step
    int nsteps;                 //!< Number of time steps
    int image_interval = 500;   //!< Image output interval
    int restart_interval = 200; //!< Checkpoint output interval
    parallel_data parallelization; //!< Parallelization info
    int iter, iter0;            //!< Iteration counter
    double dx2, dy2;            //!< delta x and y squared
    double start_clock;         //!< Time stamps

    // MPI initialization
    MPI_Init(&argc, &argv);

    // Initialization of fields and parameters
    initialize(argc, argv, &current, &previous, &nsteps, &parallelization, &iter0);

    // Output the initial field
    write_field(&current, iter0, &parallelization);
    iter0++;

    // Determine largest stable time step
    dx2 = current.dx * current.dx;
    dy2 = current.dy * current.dy;
    dt = dx2 * dy2 / (2.0 * a * (dx2 + dy2));

    // Mark the start time
    start_clock = MPI_Wtime();

    // Time evolve
    for (iter = iter0; iter < iter0 + nsteps; iter++) {
        // Exchange boundary data and evolve the grid's interior
        exchange_init(&previous, &parallelization);
        evolve_interior(&current, &previous, a, dt);

        // Finish boundary exchange and evolve grid edges
        exchange_finalize(&parallelization);
        evolve_edges(&current, &previous, a, dt);

        // Output images at specified intervals
        if (iter % image_interval == 0) {
            write_field(&current, iter, &parallelization);
        }

        // Create checkpoints for easy restarting at specified intervals
        if (iter % restart_interval == 0) {
            write_restart(&current, &parallelization, iter);
        }

        // Swap fields for the next iteration
        swap_fields(&current, &previous);
    }

    // Report the time used for iterations
    if (parallelization.rank == 0) {
        printf("Iteration took %.3f seconds.\n", (MPI_Wtime() - start_clock));
        printf("Reference value at 5,5: %f\n", previous.data[idx(5, 5, current.ny + 2)]);
    }

    // Write the final state
    write_field(&current, iter, &parallelization);

    // Cleanup
    finalize(&current, &previous, &parallelization);
    MPI_Finalize();

    return 0;
}
