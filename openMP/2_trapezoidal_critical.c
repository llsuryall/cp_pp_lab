#include<stdio.h>
#include<math.h>
#include<omp.h>

double traprule( double (*f) ( double x ), double a, double b, int n )
{
   int i;
   double h = (b-a)/n;
   double y = (f(a) + f(b))/2.0;
   double x;

   for(i=1,x=a+h; i < n; i++,x+=h) y += f(x);

   return h*y;
}


double integrand ( double x )
{
   return sqrt(1.0 - x*x);
}

int main ( int argc, char *argv[] )
{
   int i;
   int p = 8;
   int n = 1000000;
   double my_pi = 0.0;
   double a,b,c,h,y,pi,error;

   omp_set_num_threads(p);

   h = 1.0/p;

   #pragma omp parallel private(i,a,b,c)
   /* each thread has its own i,a,b,c */
   {
      i = omp_get_thread_num();
      a = i*h;
      b = (i+1)*h;
      c = traprule(integrand,a,b,n);
      #pragma omp critical
      /* critical section protects shared my_pi */
         my_pi += c;
   }
   my_pi = 4.0*my_pi; pi = 2.0*asin(1.0); error = my_pi-pi;
   printf("Approximation for pi = %.15e with error = %.3e\n",my_pi,error);

   return 0;
}

