#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

int main()
{
	// ftok to generate unique key 
    key_t key=ftok("a8",8);
    // shmget returns an identifier in shmid     
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    // shmat to attach to shared memory 
    char *str=(char*) shmat(shmid,(void*)0,0);

    int accBal=0,i=0,j=0;
    char name[100],temp[100];

    if (shmid == -1) {
          perror("Could not get shared memory");
          return 0;
    }
    while(str[i]!='-'){
        name[i]=str[i];
        i++;
    }
    name[i]='\0';
    i++;
    while(str[i]!='\0'){
        temp[j]=str[i];
        i++;
        j++;
    }

    sscanf(temp,"%d",&accBal);
    printf("*******************************************************************\n \t\tAccount Holder Name :: %s \n\t\tAccount Balance     :: %d\n*******************************************************************\n",name,accBal);

    int ch;
    do{
    printf("-------------------------------------------------------------------\n");
    printf("-------------------------------\n\t MENU\n-------------------------------\n1.Total Account Balance \n2.Withdraw Amount \n3.Deposit Cash \n4.Exit \n\nEnter Choice : ");
    scanf("%d",&ch);    
    switch (ch)
    {
    case 1: printf("\nTotal Balance : %d\n",accBal);
            break;

    case 2: printf("\nEnter Amount to Withdraw : ");
            int x=0;
            scanf("%d",&x);
            if(x<=accBal){
                accBal=accBal-x;
                printf("\nSuccessfully Withdrawl !!!!! \n\nAmount After Withdrawl : %d\n",accBal);
            }
            else{
                printf("\nAccount balance is low !!!!!!\n");
            }
            break;

    case 3: printf("\nEnter Amount to Deposit : ");
            int y=0;
            scanf("%d",&y);
            accBal=accBal+y;
            printf("\nSuccessfully Deposited !!!!! \n\nAmount After Deposit : %d\n",accBal);
            break;
    
    default:
            shmdt(str);		    // detaches the shared memory 
    }
    }while(ch<4); 
    return 0;
}
