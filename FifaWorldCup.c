#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

int total = 22, it, ger, tot_ger = 11, tot_it = 11, it_gone = 0, ger_gone = 0, counter = 0, cur;
sem_t lock, lock2;

void *transport(void *arg)
{
	sem_wait(&lock);
	printf("Enter number of German players you want to board the tram:\n");
	scanf("%d", &ger);
	printf("Enter number of Italian players you want to board the tram:\n");
	scanf("%d", &it);
	printf("\n");
	
	if((ger+it)>4 || (ger+it)<4)
	{
	printf("The tram can't carry more than 4 people. Also it always have to carry a full load.\n\n");
	}else{
	if(tot_ger>=ger && ger!=3 && ger!=1)
	{
	tot_ger = tot_ger - ger;
	}else{
	printf("Combination not available\n");
	}
	
	if(tot_it>=it && it!=3 && it!=1)
	{
	tot_it = tot_it - it;
	}else{
	printf("Combination not available\n");
	}
	}
	sem_post(&lock);
}

void *report(void *arg)
{
	sem_wait(&lock2);
	if((ger+it)>4 || (ger+it)<4)
	{
	//do nothing here.
	}else{
	printf("German arrived: ");
	cur = ger_gone + ger;
	for(int i=ger_gone+1; i<=cur; i++)
	{
	printf("%d ",i);
	}
	ger_gone = cur;
	printf("\nGerman players reamaining: %d\n", tot_ger);
	
	printf("Italian arrived: ");
	cur = it_gone + it;
	for(int i=it_gone+1; i<=cur; i++)
	{
	printf("%d ",i);
	}
	it_gone = cur;
	printf("\nItalian players reamaining: %d\n", tot_it);
	}
	
	printf("\n\n");
	sem_post(&lock2);
}

int main()
{
sem_init(&lock, 0, 1);
sem_init(&lock2, 0,1);
pthread_t iit, sid;
printf("As we know, A football team is consisted of 11 players. As we have to transport players of two team, so the total number of player is 22.\n\n");

printf("The tram always have to be in full load, so the combination becomes:\n3 Germans and 1 Italians\n3 Italians and 1 Germans\n2 Germans and 2 Italians\n2 Italians and 2 Germans\n4 Germans and 0 Italians\n4 Italians and 0 Germans\n\n");

printf("Since we cant put majority, so the first two combination is not safe. The other combination can be used and those are safe.\n\n");

printf("Enter your combination below:\n");

while(total>=4)
{
pthread_create(&iit, NULL, transport, NULL);
pthread_create(&sid, NULL, report, NULL);
pthread_join(iit, NULL);
pthread_join(sid, NULL);
}
sem_destroy(&lock);
sem_destroy(&lock2);
}
