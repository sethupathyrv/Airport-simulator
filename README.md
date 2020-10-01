# Airport-simulator
An airport simulator built in C language using queues implemented by linked list
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
