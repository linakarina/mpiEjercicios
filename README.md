"# mpiEjercicios" 
código 1122073
Descripción repositorio:

archivo mpiExample4.c
Este programa  busca calcular la suma de los primeros 100000 numeros de forma distribuida. La idea es que cada nodo de procesamiento tome un rango de numeros y los procese. Suponga que existen 5 procesos, la idea es entonces que

El proceso 1 calcule del valor 1 - 20000
El prcoeso 2 calcule del valor 20001 - 40000
El proceso 3 calcule del valor 40001 - 60000
El proceso 4 calcule del valor 60001 - 80000
El proceso 5 calcule del valor 80001 - 100000



int main(int argc,char *argv[]){

//se crean las variables de tipo entero:
n: representan los primeros 100000 numeros,
cs: variable donde se va a almacenar el rango (en este caso 20000),
se obtiene de dividir n/size.
size: cantidad de procesos,
rank: identificador de procesos,
tag: para saber que se esta realizando,
i:para almacenar los numeros del 1 al 100000 y posteriormente 
sumarlos.
totalT: para sumar los valores temporales de los rangos.

//variable de tipo long int 
total: para acumular el total e imprimirlo en consola

//variable Stat de tipo MPI_Status 
a través de esta se puede obtener diferentes datos
en este caso para obtener el identificador de cada 
proceso con Stat.MPI_SOURCE


	int n = 100000, cs, size, rank, tag=1,i,totalT=0;
	long int total=0;

	MPI_Status Stat;


	MPI_Init(&argc,&argv);//inicializar el programa
	MPI_Comm_size(MPI_COMM_WORLD, &size);//recibe el numero de procesos
	cs = n/size; //variable donde se va a almacenar el rango ejemplo( 1-20000),
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);/recibe el identificador de procesos


	//este ciclo suma los numeros desde el 20001 hasta el 100000
	y acumula los valores en la variable total. con el rank != 0
	for(i=cs*rank+1;i<=cs * (rank+1);i++)		
	{
		total += i;

	}
	if (rank == 0) //si el rank es 0, realiza un ciclo por todos los procesos
					
	{
		for(i=1;i<size;i++)
		{		


			//se reciben los valores temporales
			//el numero del proceso i
			//el estado Stat
			MPI_Recv(&totalT, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &Stat);
			printf("%d %d\n", Stat.MPI_SOURCE, totalT);//se imprime el numero del proceso y el subtotal
														//de cada uno
			total +=totalT;


		}
		printf("el total es %ld\n", total);//se imprime el total
	}else {
		


		//se envia el gran total con la variable total, 
		//la cantidad de copias del dato que se guarda en memoria en 
		//este caso es 1
		//el tipo de dato que es int a traves de la variable MPI_INT
		//el identificador del proceso que lo recibe en este caso es 0
		//el tag
		//y el comunicador  MPI_COMM_WORLD
		MPI_Send(&total, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);


	}


	MPI_Finalize();//finalizar el programa

}



archivo mpiBroadcast.c

Implementacion de la version MPI_Bcast usando las primitivas MPI_Send y MPI_Recv. Esta programa  llama a la funcion myBrocast la cual recibe los mismos parámetros de la función MPI_Bcast y al interior realiza lo siguiente:
Si es el nodo raiz, a través de un ciclo, va por todos los procesos en el comunicador y les envía los datos requeridos
Si no es el nodo raíz, el proceso se queda esperando a recibir los datos