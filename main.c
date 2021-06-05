#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

void menu();
int check(int);
void checkrepeat(int, int);
void gotoxy(int, int);
int stringsz(char s[]);
void add();
void display();
void delete_record();
void search();
void modify();
void clear();
void exit();
void suc();

struct grades {
    int math;
    int electronics;
    int circuits;
    int programming;
    int lang;
    int totalMarks;
} ;
struct grades degree; //the total scores of all student

struct studentNode {
    struct studentNode* nextsucstudent;
    int id;
    char firstName[15];
    char lastName[15];
    struct grades studentgrades;
    struct studentNode* next;
};

struct studentNode* head = NULL;

int main() {
    gotoxy(20, 10);
    printf("<< Students Database Management System >>");
    gotoxy(40, 15);
    printf("Press any key to continue");
    _getch();               // pauses the Output Console untill a key is pressed & is defined in conio.h header file
    menu();
    return 0;
}
void menu() {
    int choice;
    system("cls");          // to clear the output screen & is defined in stdlib.h header file
    gotoxy(5, 3);
    puts("<< MENU >>");
    gotoxy(10, 5);
    puts("Choose a number to perform the task you want");
    gotoxy(15, 7);
    puts("1 : Add Record");
    gotoxy(15, 8);
    puts("2 : Delete Record");
    gotoxy(15, 9);
    puts("3 : Search");
    gotoxy(15, 10);
    puts("4 : Display all students records");
    gotoxy(15, 11);
    puts("5 : show the score of the student");
    gotoxy(15, 12);
    puts("6 : Clear");
    gotoxy(15, 13);
    puts("7 : Exit");


    gotoxy(10, 16);
    printf("Enter your choice : ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        add();
        break;
    case 2:
        delete_record();
        break;
    /*case 3:
        search();
        break;*/
    case 4:
        display();
        break;
    case 5:
        suc();
        break;
    /*case 6:
        clear();
        break;
    case 7:
        exit();
        break;*/
    default:
        /*gotoxy(25, 17);
        puts("Invalid Choice .. Choose a number from 1 to 7.");*/
        menu();
    }
}
int check(int i) {
    struct studentNode* checkptr = malloc(sizeof(struct studentNode));
    checkptr = head;
    if (head == NULL) {
        return 3;         // does not exist
    }
    while (checkptr != NULL) {
        if (checkptr->id == i) {
            return 2;    // exist
        }
        checkptr = checkptr->next;
    }
    return 3;
}
void checkrepeat(int x, int y) {
    gotoxy(x, y);
    int c;
    printf("Enter 1 to perform another task or 0 to exit: ");
    scanf("%d", &c);
    if (c == 1) menu();
    //else exit();
}
void gotoxy(int x, int y) {                // is defined in windows.h header file
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
int stringsz(char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

void add() {
    int id, ch;
    char firstName[15], lastName[15];
    gotoxy(25, 17);
    printf("Enter the student name: ");
    scanf("%14s %14s", firstName, lastName);
    gotoxy(25, 18);
    printf("Enter the student ID: ");
    scanf("%d", &id);

    if (check(id) == 2) {
        gotoxy(10, 21);
        puts("The student with this ID is already exist.");
        checkrepeat(25, 23);
    }
    else {
        struct studentNode* newNode = malloc(sizeof(struct studentNode));
        if (newNode != NULL) {
            newNode->studentgrades.lang = 0;
            newNode->studentgrades.programming = 0;
            newNode->studentgrades.circuits = 0;
            newNode->studentgrades.electronics = 0;
            newNode->studentgrades.math = 0;
            newNode->studentgrades.totalMarks = 0;
            newNode->id = id;
            strcpy(newNode->firstName, firstName);
            strcpy(newNode->lastName, lastName);
            newNode->next = NULL;
            gotoxy(25, 19);
            printf("Enter 1 to add student grades or 0 to continue without adding: ");
            scanf("%d", &ch);

            int x = 20;
            if (ch == 1) {
                gotoxy(25, 20);
                printf("Enter Mathematics grade: ");
                scanf("%d", &newNode->studentgrades.math);
                gotoxy(25, 21);
                printf("Enter Electronics grade: ");
                scanf("%d", &newNode->studentgrades.electronics);
                gotoxy(25, 22);
                printf("Enter Programming grade: ");
                scanf("%d", &newNode->studentgrades.programming);
                gotoxy(25, 23);
                printf("Enter Circuits grade: ");
                scanf("%d", &newNode->studentgrades.circuits);
                gotoxy(25, 24);
                printf("Enter Language grade: ");
                scanf("%d", &newNode->studentgrades.lang);
                newNode->studentgrades.totalMarks = newNode->studentgrades.math + newNode->studentgrades.electronics + newNode->studentgrades.programming + newNode->studentgrades.circuits + newNode->studentgrades.lang;
                x = 25;
            }

            if (head == NULL) head = newNode;
            else {
                int i = 1, j = 0;
                struct studentNode* current = head, * previous = NULL;

                while (current != NULL && newNode->firstName[0] >= current->firstName[0]) {
                    if (newNode->firstName[0] == current->firstName[0]) {
                        for (i = 1; (newNode->firstName[i] == current->firstName[i]) && (newNode->firstName[i] != '\0') && (current->firstName[i] != '\0'); i++);     // to compare every character for the first name of each node and will close when they are not equal

                         //if the program end the for because they reached end of string and all character are equal, it will enter that if condition
                        if ((stringsz(newNode->firstName) == i) && (stringsz(current->firstName) == i)) {
                            for (j = 0; (newNode->lastName[j] == current->lastName[j]) && (newNode->lastName[j] != '\0') && (current->lastName[j] != '\0'); j++);       // this if is to check the last name by the same method as the first one if the first name of the two nodes are identical
                            if ((stringsz(newNode->lastName) == j) && (stringsz(current->lastName) == j)) break;
                            else if (current->lastName[j] > newNode->lastName[j])  break;           //if the character we break the for loop on the last name of new node is less than that of current node it will break through the while loop giving us the pointer where we need
                        }
                        else if (current->firstName[i] > newNode->firstName[i]) break;                // the same to that of the last name if it break through the because the two characters arent equal so it will break through the while loop if the last name of new node is less than that of current node
                    }
                    previous = current;
                    current = current->next;
                }

                if (previous == NULL) {
                    newNode->next = head;
                    head = newNode;
                }
                else {
                    previous->next = newNode;
                    newNode->next = current;
                }
            }
            gotoxy(10, x + 2);
            puts("The record is added successfully.");
            checkrepeat(25, x + 4);
        }
        else {
            gotoxy(10, 21);
            puts("student is not inserted. No memory available.");
        }
    }
}
void display() {
    gotoxy(3, 17);
    if (head == NULL) {
        puts("The system is empty.");
        checkrepeat(25, 19);
        return;
    }
    struct studentNode* print = head;
    printf("%-7s %-20s %-15s %-15s %-15s %-15s %-15s %s\n", "ID", "Name", "Electronics", "Circuits", "Programming", "Mathematics", "Language", "TOTAL");
    int x = 19;
    while (print != NULL) {
        gotoxy(3, x++);
        printf("%-7d %-5s %-15s %-15d %-15d %-15d %-15d %-15d %d\n", print->id, print->firstName, print->lastName, print->studentgrades.electronics, print->studentgrades.circuits, print->studentgrades.programming, print->studentgrades.math, print->studentgrades.lang, print->studentgrades.totalMarks);
        print = print->next;
    }
    checkrepeat(25, 25);
}
void delete_record() {
    int id;
    gotoxy(25, 17);
    printf("Enter the ID of the student you want to delete: ");
    scanf("%d", &id);
    if (head == NULL) {
        gotoxy(10, 19);
        puts("Record does not exist.");
    }
    else {
        struct studentNode* current = head;
        struct studentNode* previous = head;
        while (current != NULL && current->id != id) {
            previous = current;
            current = current->next;
        }
        if (current == NULL) {
            gotoxy(10, 19);
            puts("Record does not exist.");
        }
        else {
            previous->next = current->next;
            free(current);
            gotoxy(10, 19);
            puts("Record is deleted successfully.");
        }
    }
    checkrepeat(25, 21);

}
void suc(){
    int sum=0;

     gotoxy(3, 17);
    if (head == NULL) {
        puts("The system is empty.");
        checkrepeat(25, 19);
        return;
    }

    struct studentNode* print = head;
    struct studentNode* max = head;  //pointer to the first student
    struct studentNode* begin = NULL;
    struct studentNode* end = NULL;  //head of the passed student
    degree.electronics=0;
     degree.circuits=0;
     degree.programming=0;
     degree.math=0;
    degree.lang=0;
     degree.totalMarks=0;

    while (print != NULL) {
        print->nextsucstudent=NULL;
         int flag=0;
       degree.electronics +=print->studentgrades.electronics;
       degree.circuits +=print->studentgrades.circuits;
       degree.programming +=print->studentgrades.programming;
       degree.math +=print->studentgrades.math;
       degree.lang +=print->studentgrades.lang;
       degree.totalMarks +=print->studentgrades.totalMarks;
       if(max->studentgrades.totalMarks< print->studentgrades.totalMarks && print->studentgrades.totalMarks>=250)max=print; //the first student


       if(print->studentgrades.electronics<50 )flag++;
       if(print->studentgrades.circuits<50 )flag++;
       if(print->studentgrades.programming<50 )flag++;
       if(print->studentgrades.math<50 )flag++;
       if(print->studentgrades.lang<50 )flag++;

       if(flag<=2){ //the student passed
        sum++;
            if(begin==NULL){
                    begin=end=print;
                    begin->nextsucstudent=NULL;
            }else{
                end->nextsucstudent=print;
                end=print;
                end->nextsucstudent=NULL;
            }

       }


        print = print->next;
    }
    printf(" %-15s %-15s %-15s %-15s %-15s %s\n", "Electronics", "Circuits", "Programming", "Mathematics", "Language", "TOTAL");
    int x = 19;

        gotoxy(3, x);
        printf("%-15d %-15d %-15d %-15d %-15d %-15d \n",degree.electronics,degree.circuits,degree.programming,degree.math,degree.lang,degree.totalMarks  );
        printf("the first student:\n");
        printf("%-7s %-20s %-15s %-15s %-15s %-15s %-15s %s\n", "ID", "Name", "Electronics", "Circuits", "Programming", "Mathematics", "Language", "TOTAL");
        printf("%-7d %-5s %-15s %-15d %-15d %-15d %-15d %-15d %d\n", max->id, max->firstName, max->lastName, max->studentgrades.electronics, max->studentgrades.circuits, max->studentgrades.programming, max->studentgrades.math, max->studentgrades.lang, max->studentgrades.totalMarks);


        if(sum>0){
            printf("the number of passed student is: %d\n",sum);
            printf("the student who passed is\n");
            end=begin;
            while(end !=NULL){
               printf("%-7s %-20s %-15s %-15s %-15s %-15s %-15s %s\n", "ID", "Name", "Electronics", "Circuits", "Programming", "Mathematics", "Language", "TOTAL");
                printf("%-7d %-5s %-15s %-15d %-15d %-15d %-15d %-15d %d\n", end->id, end->firstName, end->lastName, end->studentgrades.electronics, end->studentgrades.circuits, end->studentgrades.programming, end->studentgrades.math, end->studentgrades.lang, end->studentgrades.totalMarks);

                end=end->nextsucstudent;
            }

        }else printf("there is no succeeded student.\n");





    checkrepeat(50, 50);

}


/*
void search() {
}
void clear() {
}
void exit() {
}
*/
