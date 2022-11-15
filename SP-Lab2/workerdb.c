/*This program reads input from a txt file and creates a database of employees. Then it gives the user
5 options to choose from to interact with the database

read.c is a file that has helper functions to help read a file

Yosef Raya
11/13/22
*/
#include <stdio.h>
#include <string.h>
#include "readfile.h"
#include <ctype.h>
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
void removeEmployee(struct employee arr[], int n){
    int i;
    int option;

    printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    printf("%-15s\t%-15s\t%d\t%d\n", arr[n].fname, arr[n].lname, arr[n].salary, arr[n].id);
    printf("----------------------------------------------\n");
    printf("Would you like to remove this employee?(1 for Yes, 0 for No)\n");
    printf("Enter your option: ");
    scanf("%d", &option); 
    
    if (option == 1){
            for (i = n; i < counter; i++){
                arr[i] = arr[i+1];
            }
            counter--;
    } else if (option == 0) {printf("\nRemoval not completed.\n");
    } else{
        printf("\nInvalid entry. Please try again\n");}
}

/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
/*creat database function used in the start of the program to construct the array of employees with the right array size
in accordance to the input file that is also scanned by this function*/
void CreateDataBase(char* datafile){
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
void salarySelectionSort(struct employee arr[], int n) 
{ 
    int i;
    int j;
    int min; 
  
    
    for (i = 0; i < n - 1; i++) { //outter loop to locate minimum element 
        min = i; 
        for (j = i + 1; j < n; j++) //inner loop to assign min to new min element
            if (arr[j].salary > arr[min].salary) //condition if satisfied perform swap function
                min = j; 
        Swap(&arr[min], &arr[i]); 
    } 
} 
/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
/*this function takes the salaries of employees from the database and copies it in a new array of salaries. The list is then sorted
to view the highest salaries and the user is asked to enter the number of highest salaries he would like to view*/
void highestSalaries(struct employee arr[], int n)
{
    struct employee salaryList[n];
    int i;//loop counter
    int entry;//user entry number of employees with highest salary
    
    for (i = 0; i < n; i++)//loop to copy employees from data base to salaryList array
    {
        salaryList[i] = arr[i];
    }

    salarySelectionSort(salaryList, n);//sort new list based on salaries using salarySelectionSort method

    printf("\nEnter the number of employees you would like to view with highest salaries: \n");

    scanf("%d", &entry); //scan user input
    if (entry > n)//resize the list to user's entry
    {
        entry = n;
    }
    printDataBase(salaryList, entry);//call printDataBase function and apply it to the new list and list size (entry)

}
/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------*/
int updateEmployeeRecord(struct employee arr[], int index)
{
    int option;
    char fname[MAXNAME];
    char lname[MAXNAME];
    int newSalary;
    int newID;

    printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    printf("%-15s\t%-15s\t%d\t%d\n", arr[index].fname, arr[index].lname, arr[index].salary, arr[index].id);
    printf("----------------------------------------------\n");
    printf("Please make sure this is the correct Employee information you'd like to udpate. (1 for correct, 0 for incorrect): ");
    printf("%d", &option);

    if (option == 1)
    {
        printf("\nWhich information you'd like to edit, choose of of the following options: \n");
        printf("\t(1) First name\n");
        printf("\t(2) Last name\n");
        printf("\t(3) ID\n");
        printf("\t(4) Salary\n");
        printf("\t(5) All fields\n");
        scanf("%d", &option);

        switch (option)
         {
            case 1:
                 printf("\n Enter new First name");
                 scanf("%d", &fname);

                 printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
                 printf("----------------------------------------------\n");
                 printf("%-15s\t%-15s\t%d\t%d\n", arr[index].fname, arr[index].lname, arr[index].salary, arr[index].id);
                 printf("----------------------------------------------\n");
                 printf("Please make sure this is the correct Employee information you'd like to udpate. (1 for correct, 0 for incorrect): ");
                 printf("%d", &option);

                 if (option == 1){
                    printf("\nUpdate was successful");
                    strcpy(arr[index].fname, fname);
                 }
                 if (option == 0){
                    printf("\n Updtae was not successful");
                    } 
                    else{
                        printf("\nInvalid entry. Return to main menue");
                        }
            break;

            case 2:
                printf("\n Enter new Last name");
                scanf("%d", &lname);

                 printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
                 printf("----------------------------------------------\n");
                 printf("%-15s\t%-15s\t%d\t%d\n", arr[index].fname, arr[index].lname, arr[index].salary, arr[index].id);
                 printf("----------------------------------------------\n");
                 printf("Please make sure this is the correct Employee information you'd like to udpate. (1 for correct, 0 for incorrect): ");
                 printf("%d", &option);

                 if (option == 1){
                    printf("\nUpdate was successful");
                    strcpy(arr[index].lname, lname);
                 }
                 if (option == 0){
                    printf("\n Updtae was not successful");
                    } 
                    else{
                        printf("\nInvalid entry. Return to main menue");
                        }
            break;

            case 3:
            printf("\n Enter new Salary: ");
                scanf("%d", &newSalary);

                printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
                 printf("----------------------------------------------\n");
                 printf("%-15s\t%-15s\t%d\t%d\n", arr[index].fname, arr[index].lname, arr[index].salary, arr[index].id);
                 printf("----------------------------------------------\n");
                 printf("Please make sure this is the correct Employee information you'd like to udpate. (1 for correct, 0 for incorrect): ");
                 scanf("%d", &option);

                 if (option == 1){
                    printf("\nUpdate was successful");
                    arr[index].salary = newSalary;
                 }
                 if (option == 0){
                    printf("\n Updtae was not successful");
                    } 
                    else{
                        printf("\nInvalid entry. Return to main menue");
                        }
            break;

            case 4:
            printf("\n Enter new ID: ");
                scanf("%d", &newID);

                 printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
                 printf("----------------------------------------------\n");
                 printf("%-15s\t%-15s\t%d\t%d\n", arr[index].fname, arr[index].lname, arr[index].salary, arr[index].id);
                 printf("----------------------------------------------\n");
                 printf("Please make sure this is the correct Employee information you'd like to udpate. (1 for correct, 0 for incorrect): ");
                 printf("%d", &option);

                 if (option == 1){
                    printf("\nUpdate was successful");
                    arr[index].id = newID;
                 }
                 if (option == 0){
                    printf("\n Updtae was not successful");
                    } 
                    else{
                        printf("\nInvalid entry. Return to main menue");
                        }
            selectionSort(arr, counter);
            break;

            case 5:
            printf("\nEnter new First name: "); 
                scanf("%s", fname);      
                printf("\nEnter new Last name: "); 
                scanf("%s", lname);
                printf("\n Enter new Salary: "); 
                scanf("%d", &newSalary);
                printf("\n Enter new ID: "); 
                scanf("%d", &newID); 

                printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
                printf("----------------------------------------------\n");
                printf("%-15s\t%-15s\t%d\t%d\n", fname, lname, newSalary, newID);
                printf("----------------------------------------------\n");
                printf("Please make sure this is the correct Employee information you'd like to udpate. (1 for correct, 0 for incorrect): ");
                scanf("%d", &option); 

                if (option == 1)
                {
                    printf("\nUpdate was successful");
                    strcpy(arr[index].fname, fname);
                    strcpy(arr[index].lname, lname);
                    arr[index].salary = newSalary;
                    arr[index].id = newID;
                }
               else if (option == 0)
                    {
                    printf("\n Updtae was not successful");
                    } 
                    else
                    {
                    printf("\nInvalid entry. Return to main menue");
                    }
             selectionSort(arr, counter);     
             break;
        }
    }

if (option==0)
    {
        printf("\n return to main menu");
        return 0;
    }
    else {
        printf("\nInvalid entry. Try Again!");
         return 0;
         }

}

int matchingLastNames (struct employee arr[], int n, char* name)
{
    int i;
    int a;
    int s;
    int check = -1;
    char name1[MAXNAME], name2[MAXNAME];

    s = strlen(name);//int s equals the length of this string name
    for (i = 0; i < s; i++)
    {
        name1[i] = tolower(name[i]);//make it case insensitive
    }

    printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    for (i = 0; i < n; i++)//loop array to check for matching names 
    {
        s = strlen(arr[i].lname);//update s int to new vlaue of length of last name at index i in array
        for (a = 0; a < s; a++)
        {
            name2[a] = tolower(arr[i].lname[a]);
        }
        if (strcmp(name1, name2) == 0)
        {
            printf("%-15s\t%-15s\t%d\t%d\n", db[i].fname,db[i].lname,db[i].salary, db[i].id);
            check = 0;
        }
        memset(&name2[0], 0, sizeof(name2)); // clears the memeory block of the 'name2' string for the next name
    }
    printf("\n");

    if (check == 0)
    {
        return check;
    }
    return check;
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
            printf("\t(6) Remove an Employee\n");
            printf("\t(7) Update an Employee's Record\n");
            printf("\t(8) Employees with Highest Salaries\n");
            printf("\t(9) Find all Employees with Matching Last Name\n");
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
                        printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
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
                        printf("\nFirat Name\tLast Name\tSALARY\t   ID\n");
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

                case 6:
                    printf("\n Enter Employee's ID you'd like to remove: ");
                    scanf("%d", &ID);
                    index = linearSearchID(db, counter, ID);

                    if (index == -1){printf("\nEmployee with provided ID was not found. Try Again!");}
                    else {removeEmployee(db, index);}
                    break;

                case 7:
                    printf("Enter Employee's ID you'd like to update: ");
                    scanf("%d", &ID);

                    index = linearSearchID(db, counter, ID);
                     if (index == -1)
                     {
                        printf("\nEmployee with provided ID was not found. Try Again!");
                     }
                     else 
                     {
                        index = updateEmployeeRecord(db, index);
                     }
                break;

                case 8:
                    highestSalaries(db, counter);
                    break;

                case 9:        
                    printf("\nEnter the employee's last name: ");
                    scanf("%s", name); 
                    index = matchingLastNames(db, counter, name);
                    if (index == -1)
                    {
                        printf("\nUser with last name '%s' not found\n", name);
                    }                  
                    break;
                
                default:            
                    printf( "\nInvalid entry. Try again from options (1-5)\n" );
                    break;
            }
        }
    }
}