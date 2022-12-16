#include<stdio.h>
#include<string.h>
#include<mpi.h>

int main () {
	char greetings[100];
	int comm_sz;
	int my_rank;

	MPI_Init (NULL, NULL); 
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	
	if (my_rank !=0) {
		sprintf(greetings, "Greeting from %d of %d\n", my_rank, comm_sz); 
		MPI_Send(greetings, strlen(greetings)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD); 
	} else {
		printf ("Greeting from %d of %d\n", my_rank, comm_sz); 
		for (int q = 1; q<comm_sz; q++) {
			MPI_Recv (greetings, 100, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
			printf("%s \n", greetings);
		}
	}
	
	MPI_Finalize ();

    	return 0;
}
