#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Book
{
    char bookID[10], name[30], category[30], author[30];
    int quantity;
};

struct Book listBooks[10000];
int numBooks = 0;

void readFile()
{
    FILE* fOut = fopen("Library.txt", "r");
    if (fOut)
    {
        for (;;)
        {
            fscanf(fOut, "%[^,],%[^,],%[^,],%[^,],%d\n", listBooks[numBooks].bookID, listBooks[numBooks].name, listBooks[numBooks].category, listBooks[numBooks].author, &listBooks[numBooks].quantity);
            numBooks++;
            if (feof(fOut))
            {
                break;
            }
        }
    }

    fclose(fOut);
}

void writeFile()
{
    FILE* file = fopen("Library.txt", "w+");
    int i;
    for (i = 0; i < numBooks; i++)
    {
        fprintf(file, "%s,%s,%s,%s,%d\n", listBooks[i].bookID, listBooks[i].name, listBooks[i].category, listBooks[i].author, listBooks[i].quantity);
    }
    fclose(file);
}



void addBook()
{
    struct Book book;
    printf("Enter book id: ");
    gets(book.bookID);
    printf("Enter book name: ");
    gets(book.name);
    printf("Enter category: ");
    gets(book.category);
    printf("Enter author: ");
    gets(book.author);
    printf("Enter quantity: ");
    scanf("%d", &book.quantity);
    listBooks[numBooks++] = book;
    printf("Added new book successful\n\n");
}



int deleteBookByID()
{
    char id[10];
    printf("\nEnter the id of the book you want to find: ");
    gets(id);
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(id, listBooks[i].bookID) == 0) {
            listBooks[i] = listBooks[i + 1];
            printf("Deleted book with id %s\n\n", id);
            numBooks--;
            return 1;
        }
    }

    printf("Can not delete book with id %s\n\n", id);
    return 0;
}

int updateBookByID()
{
    char id[10];
    char tempName[30], tempCategory[30], tempAuthor[30];
    int tempQuantity;
    printf("\nEnter the id of the book you want to find: ");
    gets(id);
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(id, listBooks[i].bookID) == 0) {
            printf("Enter book name: ");
            gets(tempName);
            strcpy(listBooks[i].name, tempName);
            printf("Enter category: ");
            gets(tempCategory);
            strcpy(listBooks[i].category, tempCategory);
            printf("Enter author: ");
            gets(tempAuthor);
            strcpy(listBooks[i].author, tempAuthor);
            printf("Enter quantity: ");
            scanf("%d", &tempQuantity);
            listBooks[i].quantity = tempQuantity;
            printf("Updated book with id %s\n\n", id);
            return 1;
        }
    }

    printf("Can not update book with id %s\n\n", id);
    return 0;
}

int searchBookByID()
{
    char id[10];
    printf("\nEnter the id of the book you want to find: ");
    gets(id);
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(id, listBooks[i].bookID) == 0) {
            printf("------------------------------------------------------------"
                "-----------------------------------------------------------------------\n");
            printf("%-10s%-30s%-30s%-30s%-10s\n", "Book id", "Book name", "Category", "Author", "Quantity");
            printf("%-10s%-30s%-30s%-30s%-10d\n", listBooks[i].bookID, listBooks[i].name, listBooks[i].category, listBooks[i].author, listBooks[i].quantity);
            printf("------------------------------------------------------------"
                "-----------------------------------------------------------------------\n");
            return 1;
        }
    }

    printf("Can not found book with id %s\n\n", id);
    return 0;
}

void viewListBooks()
{
    printf("------------------------------------------------------------"
        "-----------------------------------------------------------------------\n");
    printf("%-10s%-30s%-30s%-30s%-10s\n", "Book id", "Book name", "Category", "Author", "Quantity");
    for (int i = 0; i < numBooks; i++)
    {
        printf("%-10s%-30s%-30s%-30s%-10d\n", listBooks[i].bookID, listBooks[i].name, listBooks[i].category, listBooks[i].author, listBooks[i].quantity);
    }
    printf("-------------------------------------------------------------"
        "----------------------------------------------------------------\n");
}

int main()
{
    int choice = 0;
    readFile();

    do
    {
        printf("=============== MENU ===============\n");
        printf("1. Add book.\n");
        printf("2. Delete book.\n");
        printf("3. Update book.\n");
        printf("4. Search book.\n");
        printf("5. View list books.\n");
        printf("0. Exit.\n");
        printf("Your choose ? ");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 0:
            break;

        case 1:
            addBook();
            writeFile();
            break;

        case 2:
            deleteBookByID();
            writeFile();
            break;

        case 3:
            updateBookByID();
            writeFile();
            break;

        case 4:
            searchBookByID();
            break;

        case 5:
            viewListBooks();
            break;

        default:
            printf("Wrong function, please choose again!\n");
            break;
        }

    } while (choice);
    return 0;
}