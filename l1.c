/******************************************************************************
* FILE:  l1.c
* 
* DESCRIPTION:
* Lab1: This lab is related with hotplate problem which require computing a solution for 
* steady state heat equation in 2D rectangular region.  
* AUTHOR: Wasim Raja Mondal
* LAST REVISED: 09/17/25
*
*Step 1: Take the input parameters from the command line argument
*Step 2: Initlize the 2D grid
*Step 3: Satisfy the boundary of the grid
*Step 4 :Satisfy the intial interior points of this grid
*Step 5: create a final grid copy starting with initial grid
*Step 6 : Compare final and initial grid (only interior points values) untill their difference is comparable within tolerence
*         parameters.
*References:
 

* Concept of 2D array allocation in C/C++
* //https://www.geeksforgeeks.org/c/dynamically-allocate-2d-array-c/
*
* Program to find whether a given number is power of 2
* //https://www.geeksforgeeks.org/dsa/program-to-find-whether-a-given-number-is-power-of-2/

******************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <stdbool.h>



//This is function for testing a number of 2^n or not.
bool isPowerofTwo(int n) {
    if (n <= 0)
        return false;
    
    while (n > 1) {
        if (n % 2 != 0)
            return false;
        n = n / 2;
    }
    return true;
}




int main(int argc, char *argv[])
{

//checking correct number of argument


	
//step-1: taking input from terminal as argument
	
if (argc !=8) {
       printf("Usage: %s <rows> <columns>\n", argv[0]);
       return 1; //exit with error
}	

//step-2 : convert the string argument to int

int num_rows    = atoi(argv[1]);
int num_cols    = atoi(argv[2]);
int top_temp    = atoi(argv[3]);
int left_temp   = atoi(argv[4]);
int right_temp  = atoi(argv[5]);
int bottom_temp = atoi(argv[6]);
double epsilon  = atof(argv[7]);




//initializing required parameters for boundary and
//initial initial interior points

double total_left_temp =0.0;
int total_left_temp_element=0;
double total_right_temp =0.0;
int total_right_temp_element=0;
double total_top_temp =0.0;
int total_top_temp_element=0;
double total_bottom_temp =0.0;
int total_bottom_temp_element=0;



//step 3: dynamically allocating row
double** grid_initial =malloc((num_rows)* sizeof(double *)); 


//step 4: for each row, dynamically allocating column

for (int i = 0; i < num_rows; i++) {
        grid_initial[i] = malloc(num_cols * sizeof(double));
    }


//step 6: Initializing with 0

 // Initialize everything to 0
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            grid_initial[i][j] = 0.0;
        }
    }
    


//Step-7: Setting boundary (including summing them and collecting total number of elements)


  // ---top row---
    for (int j = 1; j < num_cols-1; j++) {
        grid_initial[0][j] = top_temp;
	total_top_temp = total_top_temp + grid_initial[0][j];
	total_top_temp_element = total_top_temp_element + 1; //elements are collected to overcome double counting during average calculations
    }



  // bottom

for (int j = 0; j < num_cols; j++) {
        grid_initial[num_rows - 1][j] = bottom_temp;
	total_bottom_temp = total_bottom_temp + grid_initial[num_rows - 1][j];
	total_bottom_temp_element = total_bottom_temp_element +1;
    }


//left

for (int i = 0; i < num_rows-1; i++) {
        grid_initial[i][0] = left_temp;
	total_left_temp = total_left_temp + grid_initial[i][0];
	total_left_temp_element=total_left_temp_element+1;

    }





//right

 for (int i = 0; i < num_rows-1; i++) {
        grid_initial[i][num_cols - 1] = right_temp;
	total_right_temp = total_right_temp + grid_initial[i][num_cols - 1];
	total_right_temp_element = total_right_temp_element + 1;
    }



//printf("%.2f\t",total_left_temp);
//printf("%4d\t",total_left_temp_element);
//printf("%.2f\t",total_right_temp);
//printf("%4d\t",total_right_temp_element);
//printf("%.2f\t",total_bottom_temp);
//printf("%4d\t",total_bottom_temp_element);
//printf("%.2f\t",total_top_temp);
//printf("%4d\t",total_top_temp_element);
//printf("\n");



// Initializing with average values
    for (int i = 1; i < num_rows-1; i++) {
        for (int j = 1; j < num_cols-1; j++) {
            grid_initial[i][j] = (total_left_temp+total_right_temp+total_bottom_temp+total_top_temp)/(total_left_temp_element+total_right_temp_element + total_top_temp_element + total_bottom_temp_element);
        }
    }






/*
for (int i=1; i<num_rows-1; i++) {
   for (int j=1; j <num_cols-1; j++)
           printf("%.2f\t",grid_initial[i][j]);
   printf("\n");


}
*/




//Step-8: Printing the initial grid


/*
for (int i=0; i<num_rows; i++) {
   for (int j=0; j <num_cols; j++)
           printf("%.2f\t",grid_initial[i][j]);
   printf("\n");


}

*/

//step -9: initilizing final grid

 double **grid_final   = malloc(num_rows * sizeof(double *));


 for (int i = 0; i < num_rows; i++) {
        grid_final[i]   = malloc(num_cols * sizeof(double));
    }



// step-10: self-consistency


// step 10.1: initize required bariables for self-consistency


int iter=0;
double change=0.0;
double diff;




do {


	diff = 0.0;

        // Copy initial to final
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                grid_final[i][j] = grid_initial[i][j];
            }
        }


//      printf("Inside the loop initial final grid");
//	printf("\n");

/*	
        for (int i=0; i<num_rows; i++) {
              for (int j=0; j <num_cols; j++)
                    printf("%.2f\t",grid_initial[i][j]);
              printf("\n");
         }

*/

//	printf("Inside the loop initial grid after updating interior points");
//        printf("\n");   



	//update the interior points
 
	 for (int i = 1; i < num_rows - 1; i++) {
            for (int j = 1; j < num_cols - 1; j++) {
                  grid_final[i][j] = 0.25 * (      //averaging over 4 quantity i.e 1/4=0.25
                    grid_initial[i - 1][j] + //left-region
                    grid_initial[i + 1][j] + //right-region
                    grid_initial[i][j - 1] + //down-region
                    grid_initial[i][j + 1] //up-region
                );
	    
	    } //j-loop
	 
        } //i-loop




/*	 
         for (int i=0; i<num_rows; i++) {
              for (int j=0; j <num_cols; j++)
                    printf("%.2f\t",grid_final[i][j]);
              printf("\n");
         }   

*/

      //computing maximum difference

      for (int i=1; i<num_rows-1; i++) {
	     for (int j=1; j < num_cols-1; j++) {
	              change=fabs(grid_final[i][j]- grid_initial[i][j]); //computing the difference and taking its absolute value
                      diff=fmax(diff,change); //comparing and taking maximum difference
		      //printf("%.2f\t", diff);
            }

       }	     





       // Copy back
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                grid_initial[i][j] = grid_final[i][j];
            }
        }


        // Print only at powers of 2 or at the last iteration
	if (isPowerofTwo(iter) || diff <= epsilon) 
	
	{
            printf("%6d    %.6f\n", iter, diff);
        }


	 //testing for printing all iterations
        //printf("%6d    %.6f\n", iter, diff);	




	   //updating iterations
           iter++;



          }    while (diff > epsilon); //iteration stops when diff is less than epsilon



// Dynamically deallocating array

free(grid_initial);
free(grid_final);




return 0;

}	

