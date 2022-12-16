#include<stdio.h>
#include<mpi.h> 
#include<stdlib.h> 


int main (int argc,char* v[]) {
	int x[100]; 
	int y[100];
       	int z[100]; 	
	int root = 0; 
	int page_rank, comm_sz; 
	int size = 7;

	for (int i=0; i<size; i++) {
		x[i] = rand()%10; 
		y[i] = rand()%10; 

		printf ("%dth element of the vectors are (x, y)=>(%d, %d)\n", i, x[i], y[i]); 
	
	}

	MPI_Init (&argc, &v); 
	MPI_Comm_size (MPI_COMM_WORLD, &comm_sz); 
	MPI_Comm_rank (MPI_COMM_WORLD, &page_rank); 
	int subsize = size/comm_sz;

	int *x_small = malloc(sizeof(int)*subsize);
	int *y_small = malloc(sizeof(int)*subsize);

	MPI_Scatter(x, subsize, MPI_INT, x_small, subsize, MPI_INT, root, MPI_COMM_WORLD); 
	MPI_Scatter(y, subsize, MPI_INT, y_small, subsize, MPI_INT, root, MPI_COMM_WORLD); 
	
	int *z_small = malloc(sizeof(int)*subsize);
	
	for (int i=0; i<subsize; i++)
	z_small[i] = x_small[i] + y_small[i]; 
	
	MPI_Gather(z_small, subsize, MPI_INT, z,size, MPI_INT, root, MPI_COMM_WORLD); 
	
	if (page_rank == root) {
		printf ("Results: \n"); 
		for (int i=0; i<size; i++) {
			printf("%d ", z[i]);
		}
	printf("\n"); 
	}
	MPI_Finalize ();
}
		
