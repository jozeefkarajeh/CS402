/*This program utilizes pointers and dynamic memory allocation (malloc) to read different sizes of data sets
functions will be constructed first to be used in the main function for abstraction
to run the program only one argument is needed in addition to the compiled file name to run the program

Yosef Raya
11/24/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*This function loads data from txt file and creates an initial database*/ 
float * Create_Data_Base(char* dataFile, int* data_count, int* arr_size)
{
    int n = 20;

    //allocate memory Dynamically by using malloc() 
    float* dataset = (float*)malloc(n * sizeof(float)); 

    if (dataset == NULL) { //makes sure memory was allocated for data
        printf("Memory was not allocated successfully.\n"); 
        exit(0); 
    } 
    
    //Read data from file and resize of initial size is smaller than counter
    int counter = 0;
    float data = 0;
    FILE *file;
    file = fopen(dataFile, "r");

    char buffer[100];   
    while (fgets(buffer, sizeof(buffer), file))  //while loop to loop data set
    {
        data = strtof(buffer, NULL);
        dataset[counter] = data;
        counter++; 
        
        if (counter == n)//if data set needed more memory space
        {
            n = n*2;    //expand memory allocation by 2
            float* dataset_temp = (float*)malloc(n * sizeof(float)); 

            if (dataset_temp == NULL) { //makes sure memory was allocated for data
                printf("Memory not allocated.\n"); 
                exit(0); 
            }//end of while loop

            //swap spaces
            memcpy(dataset_temp, dataset, n * sizeof(float));
            free(dataset);
            dataset = (float*)malloc(n * sizeof(float)); 
            memcpy(dataset, dataset_temp, n * sizeof(float));
            free(dataset_temp);
        }
    }
    if (feof(file)) // hit end of file
    {
        fclose(file);
    } 

    *arr_size = n;//update arr_size pointer to new n address
    *data_count = counter;//update data_count pointer to new counter address
    return dataset;
}

// Used in selection sort method
void Swap(float* xp, float* yp) 
{ 
    float temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
/*Function for Selection Sort*/
void Selection_Sort(float arr[], int n) 
{ 
    int i, j, min_idx; 

    for (i = 0; i < n - 1; i++) { 

        min_idx = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j] < arr[min_idx]) 
                min_idx = j; 

        Swap(&arr[min_idx], &arr[i]); //swap function defined above
    } 
} 

/*Function that calculates mean for data set*/
double mean(float arr[], int size)
{
    int counter;
    float sum;
    double avg;
    sum = avg = 0;
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + arr[counter];
    }
   
    avg = (double)sum / size;
    return avg;
}

/*Function that calculates median for a data set in an array*/
float median(float arr[], int size)
{
    float median = 0;
    // if number of elements are even
    if(size % 2 == 0)
    {
        median = (arr[(size-1)/2] + arr[size/2])/2.0;
    }
    // if number of elements are odd
    else
    {
        median = arr[size/2];
    }
    return median;
}



/* This function calculates the standard deviation by using the following formula: 
   stddev = sqrt((sum((xi - mean)^2))/N)  */
double stddev(float arr[], int size)
{
    int counter;
    double stddev;
    float sum;

    double avg = mean(arr, size); 
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + ((arr[counter] - avg) * (arr[counter] - avg));
    }

    stddev = (double) sqrt(sum/size);

    return stddev;
}

/*This function prints out the results about the data */        
void Print_Data_Base_stats (float arr[], int n, int total_size)
{
    printf("\nResults:\n");
    printf("-----------------------------------\n");
    printf("Num Values:\t\t%d\n", n);
    printf("      Mean:\t\t%lf\n", mean(arr, n));
    printf("    Median:\t\t%f\n", median(arr, n));
    printf("    Stddev:\t\t%lf\n", stddev(arr, n));
    printf("Unused Array Capacity:\t%d\n\n", (total_size-n));
    printf("-----------------------------------\n");
}

/* Main function, program driver method */
int main(int argc, char *argv[])
{//defining how program must compile and execute 
    if ( argc != 2 ) //argc has to be 2 (executable & file name)
    {
        printf( "usage: %s filename\n", argv[0] );
    }
    else
    {   
        int data_count = 0;
        int arr_size = 20;
        float* data;

        data = Create_Data_Base(argv[1], &data_count, &arr_size);//create data base for file in argv[1]   
        Selection_Sort(data, data_count); //sort data
        Print_Data_Base_stats(data, data_count, arr_size);//print stats      
    }
}