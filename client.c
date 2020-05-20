#include"server.h"

/*

                            Project description:
1. Random number of planes are called at every time unit to perform random task 
    using the rand() function.
2. Two Queues are implemented using linked list using the plane number as the data of 
    the lined list
3. Everytime a plane is READY TO take off or land, it is added to the 
    "taking off queue" or "landing queue respectively".
4. There are 2 runways in which planes can takeoff and land.
5. Landing is given more preference than taking off.
6. Everytime the queue reaches the maximum limit, the next plane is refused.
7. Everytime a plane is FINISHED landing or taking off,it is removed from the 
    respective queue.

*/

/*

                                     Note:
1. As per the instructions, it was asked not to use functions without any return 
    values,but the only reason for using such functions here is it is being called 
    for a huge number of time.
2. It was also asked not to use global variables but i had to pass close to 5-6 parameters
    for each function if I didn't use them.

*/

/*
                                During execution:
1. User has to enter the number of simulation,and the maximum number of planes that can be in the queue.
2. There is no upper bound for both the inputs.
2. Simulation starts with time unit=0, where both the runways are idle and a few planes get ready to either 
    take off or land.
3. After that the,the simulation runs for the given time unit and prints the statistics at the end.

*/



int endtime;            /*The total number of time the simulation undergoes*/
int maxqueue;           /*Maximum number of planes in both landing and take off queue*/

void main()
{
    
    printf("Enter the number of time units the simulation has to under go: ");
    scanf("%d",&endtime);
    printf("Enter the maximum number of planes that can wait in each queue (preferably 5):");
    scanf("%d",&maxqueue);
    
    initiate();         /*Initiates the simulation*/
    disp();             /*Prints the statistics at the end*/
    
}