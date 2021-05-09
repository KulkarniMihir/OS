/*
  Mihir Kulkarni
  33132 L9	
  Aim : Bankers Algorithm 
*/
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int process,resource,instance,total=0,k=0,c1=0,c2=0,i,j,choice,req;
	printf("\nEnter number of process: ");
	scanf("%d",&process);
	printf("\nEnter number of resources: ");
	scanf("%d",&resource);

	int instances[resource],available[resource],allocated[process][resource],max[process][resource],
	need[process][resource],finished[process],request[resource];

	for(i=0;i<process;i++)
        finished[i]=0; 

    printf("\nEnter No. of Instances per Resource type: \n");
    for(i=0;i<resource;i++) 
    {
        printf("%c: ",(i+65));
        scanf("%d",&instance);
        instances[i]=instance; //Storing instancees
    }  
    printf("\n------------------------------------------------------------------------" );
    printf("\nEnter Maximum No. of Resource type Instances for each:");
    printf("\n------------------------------------------------------------------------\n" );

    for(i=0;i<process;i++) 
    {
        printf("\nFor P%d: \n",i);
        for(j=0;j<resource;j++) 
        {
            printf("%c: ",(j+65));
            scanf("%d",&instance);
            max[i][j]=instance;               
        } 
    } 
    printf("\n------------------------------------------------------------------------" );
    printf("\nEnter No. of Resource type Instances allocated to each process:");
    printf("\n------------------------------------------------------------------------\n" );
 
    for(i=0;i<process;i++) 
    {
        printf("\nFor P%d: \n",i);
        for(j=0;j<resource;j++) 
        {
            printf("%c: ",(j+65));
            scanf("%d",&instance);
            allocated[i][j]=instance;
                        
            need[i][j]=max[i][j]-allocated[i][j]; //Calculating the Need of each process
        }  
    }

    //Calculating the Available Instances for each Resource type      
    for(j=0;j<resource;j++) 
    {
        total=0;
        for(i=0;i<process;i++) 
        {
            total+= allocated[i][j];
        }  
            available[j]=instances[j]-total;
    }

    printf("\n------------------------------------------------------------------------" );
    printf("\nDo you want to make an additional request ?(1=Yes|0=No)");
    scanf("%d",&choice);
    if(choice==1)
    {
    	printf("\nEnter number of requests you want to make: ");
    	scanf("%d",&req);
    	while(req--)
    	{
    		int ch,check=0,instance=0;
    		printf("\nEnter process for request: ");
    		scanf("%d",&ch);
    		printf("\nEnter request :");
    		printf("\nFor P%d: \n",ch);
	        for(j=0;j<resource;j++) 
	        {
	            printf("%c: ",(j+65));
	            scanf("%d",&instance);
	            request[j]=instance;
				if(request[j]>available[j])
				{
					printf("\nRequest not possible !");
					check++;
					break;
				}	                        
	        }
	        if(check==0)
	        {
	        	for(j=0;j<resource;j++) 
	        	{
	        		available[j] -= request[j];
					allocated[ch][j] += request[j];
					need[ch][j] -= request[j];
	        	}
	        } 
    		
    	}
    }
    printf("------------------------------------------------------------------------\n" );
 

    printf("\n---------------------------------------------------------" );

    printf("\nThe System is in a Safe State\n-> Safe Sequence is: <  ");
    while(c1!=process)
    {
    	c2 = c1;
        for(i=0;i<process;i++) 
        {
        	for(int j=0;j<resource;j++)
        	{
        		if(need[i][j]<=available[j])
        			k++;	
        	}
        	if(k==resource && finished[i]==0)
        	{
        		printf("P%d ",i);
                finished[i]=1; // Setting flag for completed Process
      
                for(j=0;j<resource;j++) 
                {
                    available[j]=available[j]+allocated[i][j]; //Updating Resources
                }  
                c1++;
        	}
        	k=0;
        }
        if(c1==c2) 
    	{
	        printf("STOP ... Deadlock likely to happen!\n");
	        break; 
    	}
    }
    
    printf(" >\n");
    printf("\n---------------------------------------------------------\n" );

}