/*This program reads input from a txt file and creates a database of employees. Then it gives the user
5 options to choose from to interact with the database

read.c is a file that has helper functions to help read a file

Yosef Raya
11/3/22
*/
#include <stdio.h>
#include <string.h>
#include "readfile.h"
#define MAXNAME 64

extern FILE *file; /*declaring a variable to read data file and that file to read is external*/
struct employee  /*declaring an employee object data type to hold info */
{
    char fname[MAXNAME];/*Variable for first name*/
    char lname[MAXNAME];/*Variable for last name*/
    int id; /*Variable for ID*/
    int salary; /* variable for salary*/
};

/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/

struct employee db[1024]; /*declaring an array of employees with size of 1024*/
int counter = 0; /*counter for size of array*/

 /*print database function prints out all employees and thier info, used in case 1*/
void printDataBase(struct employee arr[], int arr_length){
    int i;

    printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
    printf("---------------------------------------------------\n");
    for (i = 0; i < arr_length; i++){
        printf("%-15s\t%-15s\t%d\t%d\n", arr[i].fname, arr[i].lname, arr[i].salary, arr[i].id);
    }
    printf("---------------------------------------------------\n");
    printf(" Number of Employees (%d)\n", arr_length);
}
/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
/*Linear search ID function is used in case 2 in the switch structure to perform a linear search on the data base 
and returns the index of the employee if ID matches, if no match then it returns -1*/
int linearSearchID(struct employee arr[], int counter, int ID) { 
    int i;
    for (i=0; i<counter; i++){
        if(arr[i].id ==ID){
            return i;
        }
    } 
    return -1; 
} 
/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
int lookUpLName (struct employee arr[], int m, char* name){
    int i;
    for (i = 0; i < m; i++)
    {
        if (strcmp(arr[i].lname, name) == 0)
        {
            return i;
        }
    }
    return -1;
}
/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
/*add employee function promps the user for new employee information and confirms validity of entries
if one entry is not applicable user is asked to try again*/
int addEmployee(struct employee arr[])
{
    char newFirstName[MAXNAME];
    char newLastName[MAXNAME];
    int newSalary;
    int confirm;

    printf("\nEnter first name: ");
    scanf("%s", newFirstName);
    if (strlen(newFirstName) > 64)
    {
        printf("Invalid entry. Try again!\n");
        return 0;
    }
    printf("Enter last name: ");
    scanf("%s", newLastName);
    if (strlen(newLastName) > 64)
    {
        printf("Invalid entry. Try again!\n");
        return 0;
    }
    printf("Enter employee's salary (30000 to 150000): ");
    scanf("%d", &newSalary);
    if (newSalary < 30000 || newSalary > 150000)
    {
        printf("Invalid entry. Try again!\n");
        return 0;
    }
    printf("\nWould you like to add the following employee to the DB?\n");
    printf("\t%s %s, \tSalary: %d\n", newFirstName, newLastName, newSalary);
    printf("\nType in: 1 for Yes, 0 for No: ");
    scanf("%d", &confirm);

    if (confirm == 1)
    {
        strcpy(db[counter].fname, newFirstName);
        strcpy(db[counter].lname, newLastName);
        db[counter].salary = newSalary;
        db[counter].id = db[counter -1].id + 1;
        counter++;
        printf("Employee added!\n");
    }
    return 1;
}
/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
/*creat database function used in the start of the program to construct the array of employees with the right array size
in accordance to the input file that is also scanned by this function*/
void CreateDataBase(char* datafile)
{
    if (open_file(datafile) == 0)
    {
        char buffer[135];
        int ret;
        while (fgets(buffer, sizeof(buffer), file)) 
        {
            ret = read_int(buffer, 1, &db[counter].id);
            ret = read_int(buffer, 2, &db[counter].salary);
            ret = read_string(buffer, 1, &db[counter].fname);
            ret = read_string(buffer, 2, &db[counter].lname);
            counter++; 
        }

        if (feof(file))/*function from support library*/
        {
            close_file(file);/*function from support library*/
        } 
    }
}
/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
/*support function used in selection sort function to swap btween employees during sorting*/
void Swap(struct employee* x, struct employee* y) { 
    struct employee temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
void selectionSort(struct employee arr[], int n) { 
    int i, j, min_idx; 
  
    for (i = 0; i < n - 1; i++) { 
        min_idx = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j].id < arr[min_idx].id) 
                min_idx = j; 
  
        Swap(&arr[min_idx], &arr[i]); //function from above
    } 
} 
/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
/*main function driver method to start program*/
int main(int argc, char *argv[])/*command line structure*/
{
    if ( argc != 2 ){ /*if entry is different than structure, instruct user to right format*/
        printf( "usage: %s filename\n", argv[0] );
    }
    else
    {   
        CreateDataBase(argv[1]); /*create database function is called if entry is correct*/
        selectionSort(db, counter); /*selection sort is done after file is scanned into the database*/

        int option; /*user option selection*/
        int index = 0; /*index of employee in database*/
        
        while (1) {/*while loop to reprint menu until 5 is chosen to quit*/
            printf("\nEmployee DataBase Menu:\n");
            printf("---------------------------------------------------\n");
            printf("\t(1) Print the Database\n");
            printf("\t(2) Lookup by ID\n");
            printf("\t(3) Lookup by Last Name\n");
            printf("\t(4) Add an Employee\n");
            printf("\t(5) Quit\n");
            printf("---------------------------------------------------\n");
            printf("Enter your Option: ");

            scanf("%d", &option); /*scan entry from user*/

            switch (option) {/*switch branching for options*/
                case 1:            
                    printDataBase(db, counter);
                    break;

                case 2: ;
                    int ID; 
                    printf("\nPlease enter an ID to search for an Employee: ");
                    scanf("%d", &ID);          
                    index = linearSearchID(db, counter, ID);
                    if (index == -1)
                    {
                        printf("\nEmployee not found\n", ID);
                    }
                    else
                    {
                        printf("\nName\t\t\t\tSALARY\t   ID\n");
                        printf("---------------------------------------------------\n");
                        printf("%-15s\t%-15s\t%d\t%d\n", db[index].fname,db[index].lname,db[index].salary, db[index].id);
                        printf("---------------------------------------------------\n");
                    }
                    break;

                case 3: ;
                    char name[MAXNAME];             
                    printf("\nPlease enter a last name to search for an Employee: ");
                    scanf("%s", name); 
                    index = lookUpLName(db, counter, name);
                    if (index == -1)
                    {
                        printf("\n not found\n", name);
                    }
                    else
                    {
                        printf("\nName\t\t\t\tSALARY\t   ID\n");
                        printf("---------------------------------------------------\n");
                        printf("%-15s\t%-15s\t%d\t%d\n", db[index].fname,db[index].lname,db[index].salary, db[index].id);
                        printf("---------------------------------------------------\n");
                    }                    
                    break;

                case 4:        
                    addEmployee(db);
                    break;

                case 5:
                    printf("\nGoodBye!!\n");      
                    return 0;
                    break;

                default:            
                    printf( "\nInvalid entry. Try again from options (1-5)\n" );
                    break;
            }
        }
    }
}