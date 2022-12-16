#include<stdio.h>
#include<mpi.h>

double Trap (double local_a, double local_b, int local_n, double h); 
double estimate (double x);

int main () {
	int page_rank, comm_sz, local_n; 
	double local_a, local_b, local_area, total_area, h;
	
	
	const double a =0.0, b = 3.0, n = 1024;
	
	MPI_Init (NULL, NULL); 
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &page_rank); 

	h = (a+b)/n; 
	local_n = n/comm_sz;

	local_a = a + page_rank*local_n*h; 
	local_b = local_a + local_n*h; 
	
	local_area = Trap (local_a, local_b, local_n, h); 

	if (page_rank != 0) {
		MPI_Send (&local_area, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); 
	} else {
		total_area = local_area;
	       for (int i = 1; i<comm_sz; i++) {	
		MPI_Recv(&local_area, 1, MPI_DOUBLE,i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
		total_area += local_area; 
	       }
	}

	if (page_rank == 0) {
		printf("With n = %f, our estimate of the the integral from %f to %f = %.15e \n", n, a, b, total_area);
	}
	MPI_Finalize (); 
	return 0; 
}	

double Trap (double local_a, double local_b, int local_n, double h) {
	double estimate, x; 
	estimate = (local_a*local_a + local_b*local_b)/2.0; 
	for (int i=0; i<=local_n; i++) {
		x = local_a+i*h; 
		estimate += x*x; 
	}
	estimate = estimate*h; 

	return estimate;
}




	
