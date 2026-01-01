/**
* ---------- LIBRARY MANAGEMENT SYSTEM ----------*
* @author Jay Patil *
* @date 31/12/2025 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
syntax: fread(address, size, count, file_pointer)
fread() returns the number of records successfully read
if count = 1 it means to read 1 record at a time
So:
If it reads 1 record -> returns 1
If it reaches end of file -> returns 0
*/
struct book{
    int book_id;
    char title[50];
    char author[50];
    int quantity;
};

void add_book(){
    struct book b;
    FILE *fp;

    printf("Enter Book ID: ");
    scanf("%d", &b.book_id);

    printf("Enter Book Title: ");
    scanf(" %[^\n]", b.title);      //" %[^\n]" -> reads string with spaces

    printf("Enter Author Name: ");
    scanf(" %[^\n]", b.author);

    do{
        printf("Enter Quantity: ");
        scanf("%d", &b.quantity);

        if (b.quantity < 0){
            printf("\nInvalid Input!!\n");
            printf("Quantity can't be Negative.\n");
        }
    }while(b.quantity <= 0);



    fp = fopen("Library.dat","ab");   //"ab" -> append mode (does not erase existing data)
    if (fp == NULL) {
        printf("File error\n");
        return;
    }

    fwrite(&b, sizeof(b), 1, fp);   //fwrite() -> stores entire structure at once

    fclose(fp);

    printf("Book Added Successfully. \n");

}

void display_all_books(){
    struct book b;
    FILE *fp;

    fp = fopen("Library.dat", "rb");   //"rb" -> read-only mode

    if(fp==NULL){
        printf("No Records Found.\n");
        return;
    }

    printf("\nBook ID\tTitle\t\tAuthor\t\tQuantity\n");
    printf("--------------------------------------------------\n");

    //fread() -> reads one structure at a time
    while (fread(&b, sizeof(b), 1, fp)) {
        printf("%d \t %s \t\t %s \t\t %d \n",
               b.book_id, b.title, b.author, b.quantity);
    }

    fclose(fp);
}

void search_book(){
    struct book b;
    FILE *fp;
    //Searching by ID avoids duplicate issues
    int search_id = 0;
    int found = 0;   //found flag avoids false messages

    printf("Enter Book ID to search: ");
    scanf("%d", &search_id);


    fp = fopen("Library.dat", "rb");

    if(fp==NULL){
        printf("No Records found.\n");
        return;
    }

    while(fread(&b,sizeof(b),1,fp)){
        if (b.book_id == search_id){
            printf("Book Found\n");
            printf("Book Id: %d\n", b.book_id);
            printf("Book Title: %s\n", b.title);
            printf("Book Author: %s\n", b.author);
            printf("Quantity: %d\n", b.quantity);
            found = 1;
            break;
        }
    }
    if(!found){
        printf("Book Not Found. \n");
    }

    fclose(fp);
}

void issue_book(){
    /**
    * LOGIC:
    * 1.Open original file (library.dat) in read mode
    * 2.Open temporary file (temp.dat) in write mode
    * 3.Copy all records:
        a.If book ID matches -> reduce quantity
        b.Else -> copy as it is
    * 4.Replace original file with temp file
    */

    struct book b;
    FILE *fp, *temp;
    int issue_id = 0;
    int found = 0;
    int issued = 0;

    printf("Enter Book Id to issue: ");
    scanf("%d", &issue_id);

    fp = fopen("Library.dat", "rb");
    temp = fopen("Temp.dat", "wb");

    if (fp==NULL || temp==NULL){
        printf("No Books Available.\n");
        return;
    }

    while(fread(&b, sizeof(b), 1, fp)){
        if (b.book_id == issue_id){
            found = 1;
            if(b.quantity>0){
                b.quantity--;
                issued = 1;
            }
        }
        fwrite(&b, sizeof(b), 1, temp);
    }

    if (found && issued){
        printf("Book Issued Successfully.\n");
    }
    else if (found && !issued){
        printf("Book Not Available.\n");
    }
    else{
        printf("Book ID Not Found.\n");
    }

    fclose(fp);
    fclose(temp);

    if(found){
        remove("Library.dat");
        rename("Temp.dat", "Library.dat");
    }

}

void return_book(){
    // Logic is same as the logic of issue book
    struct book b;
    FILE *fp,*temp;
    int return_id = 0;
    int found = 0;

    printf("Enter Book ID to Return: ");
    scanf("%d",&return_id);

    fp = fopen("Library.dat", "rb");
    temp = fopen("Temp.dat", "wb");

    if (fp==NULL || temp==NULL){
        printf("File Error.\n");
        return;
    }
    while(fread(&b, sizeof(b), 1, fp)){
        if(b.book_id == return_id){
            found = 1;
            b.quantity++;
        }
        fwrite(&b, sizeof(b), 1, temp);
    }

    if (found) {
        printf("Book Returned Successfully.\n");
    }
    else {
        printf("Book ID not Found.\n");
    }

    fclose(fp);
    fclose(temp);

    if(found){
        remove("Library.dat");
        rename("Temp.dat", "Library.dat");
    }

}

void delete_book(){
    /**
    * LOGIC:
    * 1.Open original file (library.dat) in read mode
    * 2.Open temp file (temp.dat) in write mode
    * 3.Copy all records except the selected book
    * 4.Replace original file with temp file
    */

    struct book b;
    FILE *fp, *temp;
    int delete_id = 0;
    int found = 0;

    printf("Enter Book ID to delete: ");
    scanf("%d", &delete_id);

    fp = fopen("Library.dat", "rb");
    temp = fopen("Temp.dat", "wb");

    if (fp==NULL || temp==NULL){
        printf("File Error.\n");
        return;
    }

    while(fread(&b, sizeof(b), 1, fp)){
        if (b.book_id == delete_id){
            found = 1;
            continue;
        }
        fwrite(&b, sizeof(b), 1, temp);
    }
    if (!found){
        printf("Book ID not found.\n");
    }
    else{
        printf("Book Deleted Successfully.\n");
    }

    fclose(fp);
    fclose(temp);

    if(found){
        remove("Library.dat");
        rename("Temp.dat", "Library.dat");
    }

}

int main()
{
    int choice = 0;
    printf("Welcome to my Library\n");
    while(choice!=7){
        printf("---------- Menu ----------\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Delete Book\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                add_book();
                break;
            case 2:
                display_all_books();
                break;
            case 3:
                search_book();
                break;
            case 4:
                issue_book();
                break;
            case 5:
                return_book();
                break;
            case 6:
                delete_book();
                break;
            case 7:
                printf("Thank you for Visiting\n");
                break;
            default:
                printf("Invalid choice!!!\n");
                printf("Enter a Valid choice from 1 to 7\n");
                break;
        }
    }

    return 0;
}
