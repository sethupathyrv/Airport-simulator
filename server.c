#include"server.h"

int chooseoperation;    /*For the rand() function to choose between takeoff,landing or both*/
int timeunit=0;         /*To keep track of the current time unit*/
int numland;            /*Number of planes ready to land in a given time unit*/ 
int numtake;            /*Number of planes ready ro take off in a given time unit*/
int planenum=0;         /*Plane number of each plane*/
int endtime;            /*The total number of time the simulation undergoes*/
int maxqueue;           /*Maximum number of planes in both landing and take off queue*/
int idletimeone=-1;     /*Total idle time of runway 1*/
int idletimetwo=-1;     /*Total idle time of runway 2*/
int totland=0;          /*Total planes landed*/
int tottake=0;          /*Total planes taken off*/
int totrefused=0;       /*Total planes refused to land or takeoff*/
int totlandwait=0;      /*Total waiting time of landing plane*/
int tottakewait=0;      /*Total waiting time of taking off plane*/
int landqueue;          /*Number of planes in landing queue*/
int takequeue;          /*Number of planes in taking off queue*/

/*Creating structure for the linked list*/
struct Node{
    int data;
    struct Node* next;
};

/*Creating front and rear for the linked lists to perform queue operations*/
struct Node* frontland= NULL;
struct Node* rearland=NULL;
struct Node* fronttake= NULL;
struct Node* reartake=NULL;

/*Function to add a node to the rear of the linked list*/
void lanEnqueue(int x)
{
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node*));
    temp->data = x;
    temp->next = NULL;
    if(frontland == NULL && rearland == NULL)
    {
        frontland=rearland=temp;
        return;
    }
    else
    {
        rearland->next = temp;
        rearland = temp;
    }
    
}

/*Function to remove element from the front of the linked list*/
void lanDequeue()
{
    struct Node* temp = frontland;
    printf("plane %d landed\n",temp->data);
    if(frontland==NULL)
        return;
    if(frontland==rearland)
    {
        frontland=rearland=NULL;
    }
    else
    {
        frontland=frontland->next;
    }
    free(temp);    
}

/*To display elements in the queue*/
void landispqueue()
{
    struct Node* temp=frontland;
    while(temp!=NULL)
    {
        printf("%d\n",temp->data);
        temp=temp->next;
    }
}

/*To calculate length of the queue*/
int lanlenque()
{
    landqueue=0;
    struct Node* temp=frontland;
    while(temp!=NULL)
    {
        landqueue+=1;
        temp=temp->next;
    }

    return landqueue;
}

/*Function to add a node to the rear of the linked list*/
void takEnqueue(int x)
{
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node*));
    temp->data = x;
    temp->next = NULL;
    if(fronttake == NULL && reartake == NULL)
    {
        fronttake=reartake=temp;
        return;
    }
    else
    {
        reartake->next = temp;
        reartake = temp;
    }
    
}

/*Function to remove element from the front of the linked list*/
void takDequeue()
{
    struct Node* temp = fronttake;
    printf("plane %d took off\n",temp->data);
    if(fronttake==NULL)
        return;
    if(fronttake==reartake)
    {
        fronttake=reartake=NULL;
    }
    else
    {
        fronttake=fronttake->next;
    }
    free(temp); 
    
}

/*Display elements in the queue*/
void takdispqueue()
{
    struct Node* temp=fronttake;
    while(temp!=NULL)
    {
        printf("%d\n",temp->data);
        temp=temp->next;
    }
}

/*To calculate length of the queue*/
int taklenque()
{
    takequeue=0;
    struct Node* temp=fronttake;
    while(temp!=NULL)
    {
        takequeue+=1;
        temp=temp->next;
    }
    
    return takequeue;
}

/*
Function to be called whwn a plane is landed,
    It removes the element from the queue and also prints the output*/
void land()
{
    lanDequeue();
    totland+=1;
}

/*To print everytime the number of planes waiting in each queue*/
void printprint()
{
    printf("planes in landing queue:%d\n",lanlenque());
    printf("planes in taking off queue:%d\n",taklenque());
}

/*Function to be called when a plane takes off
    It removes the elemet from the queue and also prints  the output*/
void takeoff()
{
    takDequeue();
    tottake+=1;
}

/*Function to be called when runway 1 is supposed to be idle*/
void idlerunwayone()
{
    printf("idle\n");
    idletimeone+=1;
}

/*Function to be called when runway 2 is supposed to be idle*/
void idlerunwaytwo()
{
    printf("idle\n");
    idletimetwo+=1;
}

/*Function to be called for every time unit
    to preferentially land and takeoff the planes in the proper runways,
    this basically gives the call for the above functions at the proper time */
void runwaystatus()
{
    if(lanlenque()!=0)
    {
        printf("Runway 1:");
        land();
        if(lanlenque()!=0)
        {
            printf("Runway 2:");
            land();
            printprint();
        }
        else
        {
            if(taklenque()!=0)
            {
                printf("Runway 2:");
                takeoff();
                printprint();
            }
            else
            {
                printf("Runway 2:");
                idlerunwaytwo();
                printprint();
            }
        }    
    }
    else
    {
        if(taklenque()!=0)
        {
            printf("Runway 1:");
            takeoff();
            if(taklenque()!=0)
            {
                printf("Runway 2:");
                takeoff();
                printprint();
            }
            else
            {
                printf("Runway 2:");
                idlerunwaytwo();
                printprint();
            }
        }
        else
        {
            printf("Runway 1:");
            idlerunwayone();
            printf("Runway 2:");
            idlerunwaytwo();
            printprint();
        }
        
    }
}


/*Initiates the simulation by generating random number of planes to
    take off and land at each time unit*/
void initiate()
{
    timeunit=0;
    srand(time(NULL));                              /*Using current time as seed for random generator*/
    for(int i=0;i<=endtime;i++)
    {
        printf("\n\nTime unit=%d\n",timeunit);      /*Prints the present time unit*/
        runwaystatus();                             
        

        timeunit+=1;                                /*Increments time unit for every iteration*/

        /*random number between 1,2,3 and 4 is chosen
        1 makes a random number of planes to get ready for landing
        2 makes a random number of planes to get ready to take off
        3 makes a random number of planes to get ready to land and a random number to get ready to take off
        4 makes no planes ready to takeoff or land  */
        
        chooseoperation=(rand()%4) + 1;             
        if(chooseoperation==1)     
        {
            numland=(rand()%3) + 1;                     /*Randomly Chooses to land 1,2 or 3 planes*/
            for(int j=0;j<numland;j++)
            {
                planenum+=1;
                printf("plane number %d ready to land\n",planenum);

                if(lanlenque()>=maxqueue)               /*If Queue is full,it is refused,else added to the queue*/
                {
                    printf("Plane %d diverted to some other airport\n",planenum);
                    totrefused+=1;
                }
                else
                {
                    lanEnqueue(planenum);
                }
            }
            printf("\n");
        }
        else if(chooseoperation==2)
        {
            numtake=(rand()%3) + 1;                     /*Randomly Chooses to takeoff 1,2 or 3 planes*/
            for(int j=0;j<numtake;j++)
            {
                planenum+=1;
                printf("plane number %d ready to take off\n",planenum);
                if(taklenque()>=maxqueue)               /*If Queue is full,it is refused,else added to the queue*/
                {
                    printf("Plane %d was cancelled\n",planenum);
                    totrefused+=1;
                }
                else
                {
                    takEnqueue(planenum);
                }
                
                

            }
            printf("\n");
        }
        else if(chooseoperation==3)
        {
            numland=(rand()%2) + 1;                     /*Randomly Chooses to land 1 or 2 planes and*/
            numtake=(rand()%2) + 1;                     /*Randomly Chooses to takeoff 1 or 2 planes*/
            for(int j=0;j<numland;j++)
            {
                planenum+=1;
                printf("plane number %d ready to land\n",planenum);

                if(lanlenque()>=maxqueue)               /*If Queue is full,it is refused,else added to the queue*/
                {
                    printf("Plane %d diverted to some other airport\n",planenum);
                    totrefused+=1;
                }
                else
                {
                    lanEnqueue(planenum);
                }
                
                
            }
            for(int j=0;j<numtake;j++)
            {
                planenum+=1;
                printf("plane number %d ready to take off\n",planenum);

                if(taklenque()>=maxqueue)               /*If Queue is full,it is refused,else added to the queue*/
                {
                    printf("Plane %d was cancelled\n",planenum);
                    totrefused+=1;
                }
                else
                {
                    takEnqueue(planenum);
                }

            }
            printf("\n");
        }
        
        else
        {
            printf("No new planes are ready to land or takeoff\n\n");
        }

        totlandwait+=lanlenque();                   /*To calculate the total time landing planes wait*/
        tottakewait+=taklenque();                   /*To calculate the total time taking off planes wait*/
        
    }
}

/*Displays the statistics after the simulation ends*/
void disp()
{
    printf("Simulation has concluded after %d time units\n",endtime);
    printf("Total planes processed              \t\t:%d\n",planenum);
    printf("Number of planes landed             \t\t:%d\n",totland);
    printf("Number of planes taken off          \t\t:%d\n",tottake);
    printf("Number of planes refused            \t\t:%d\n",totrefused);
    printf("Number left ready to takeoff        \t\t:%d\n",taklenque());
    printf("Number left ready to land           \t\t:%d\n",lanlenque());
    printf("Percentage of time runway 1 was idle\t\t:%.2f\n",100*(float)idletimeone/(float)endtime);
    printf("Percentage of time runway 2 was idle\t\t:%.2f\n",100*(float)idletimetwo/(float)endtime);
    if(totland==0)
    {
        printf("Average wait time to land           \t\t:---\n");
    }
    else
    {
        printf("Average wait time to land           \t\t:%.2f\n",(float)totlandwait/(float)totland);
    }
    if(tottake==0)
    {
        printf("Average wait time to take off       \t\t:---\n");
    }
    else
    {
        printf("Average wait time to take off       \t\t:%.2f\n",(float)tottakewait/(float)tottake);
    }
}



