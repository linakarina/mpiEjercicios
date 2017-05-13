#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	int n = 100000, cs, size, rank,tag=1,i,totalT=0;
	long int total=0;

	MPI_Status Stat;


	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	cs = n/size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for(i=cs*rank+1;i<=cs * (rank+1);i++)		
	{
		total += i;

	}
	if (rank == 0) {
		for(i=1;i<size;i++)
		{		



			MPI_Recv(&totalT, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &Stat);
			printf("%d %d\n", Stat.MPI_SOURCE, totalT);
			total +=totalT;


		}
		printf("el total es %ld\n", total);
	}else {
		



		MPI_Send(&total, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);


	}





	MPI_Finalize();
}
