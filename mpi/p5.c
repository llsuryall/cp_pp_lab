#include<stdio.h> 
#include<mpi.h> 

void get_input (double *a, double *b, int *n, int process_rank) {
	double aval, bval; 
	int nval; 
	if (process_rank == 0) {
		printf("Enter the value for a, b and n \n"); 
		scanf ("%lf", &aval); 
		scanf ("%lf", &bval); 
		scanf ("%d", &nval);
	       	a = &aval;
       	       	b = &bval; 
	       	n = &nval;        
	}

		MPI_Bcast (a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
		MPI_Bcast (b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
		MPI_Bcast (n, 1, MPI_INT, 0, MPI_COMM_WORLD); 
	if (process_rank != 0) {
		printf ("a=%lf for process %d \n", *a, process_rank);
	       	printf ("b=%lf for proces %d \n", *b, process_rank); 
		printf ("n = %d for process %d \n", *n, process_rank); 
	} 
}

int main (int argc, char** argv) {
	double a, b; 
	int n; 

	int page_rank, comm_sz; 

	MPI_Init (&argc, &argv); 
	MPI_Comm_size (MPI_COMM_WORLD, &comm_sz); 
	MPI_Comm_rank (MPI_COMM_WORLD, &page_rank); 

	get_input (&a, &b, &n, page_rank); 

	MPI_Finalize ();
       return 0;	
}


