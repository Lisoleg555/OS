#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main()
{ 
	double number;
	scanf("%lf", &number);
	int toParent[2], toChild[2];
	if(pipe(toParent) == -1)
	{
		perror("Omagad, pipe toParent is stillborn\tT_T\n");
		return -1;
	}
	if(pipe(toChild) == -1)
	{
		perror("Omagad, pipe toChild is stillborn\tT_T\n");
		return -1;
	}
	pid_t process = fork();
	if(process < 0)
	{
		perror("Omagad, child is stillborn\tT_T\n");
		return -1;
	}
	else if(process > 0)//parent
	{
		while(number >= 0)
		{
			write(toChild[1], &number, sizeof(double));
			read(toParent[0], &number, sizeof(double));
			printf("%lf ", number);
			scanf("%lf", &number);;
		}
		write(toChild[1], &number, sizeof(double));
		printf("\n");
		exit(process);
	}
	else//child
	{
		do
		{
			read(toChild[0], &number, sizeof(double));
			number = sqrt(number);
			write(toParent[1], &number, sizeof(double));
		}
		while (number >= 0);
		exit(0);
	}
}
