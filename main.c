#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define Employee struct emp
#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50
#define MAX_BRANCH_LENGTH 50
#define MAX_PASSWORD_LENGTH 10

void add(FILE *fp);
FILE *del(FILE *fp);
void modify(FILE *fp);
void displayList(FILE *fp);
void searchRecord(FILE *fp);
void displayBasic(FILE *fp);
void basicContact(FILE *fp);
void maleEmp(FILE *fp);
void femaleEmp(FILE *fp);
void fromOthers(FILE *fp);
void mainBranch(FILE *fp);
void otherBranch(FILE *fp);
void printChar(char ch, int n);
void printHead();
void welcome();

struct emp {
    int id;
    char name[100];
    char desgn[10];
    float sal;
    char jdate[8];
    char gender[10];
    char branch[50];
    char psaddr[200];
    char prtaddr[200];
    char phone[15];
    char mail[20];
};


//====Welcome Screen=====
void welcome() {
    printf("\n\n\n\n\n\t[ [ [ WELCOME TO OUR EMPLOYEE MANAGEMENT SYSTEM ] ] ]\n\n\n\n\n\n\n\t");
    system("read -p 'Press Enter to continue...' var");
}

//----Printing character ch n times ------
void printChar(char ch, int n) {
    while (n--) {
        putchar(ch);
    }
}

//-----Printing Head Line of the program -----
void printHead() {
    system("clear");
    printf("\n");
    printChar('=', 65);
    printf("\n");
    printChar('=', 16);
    printf("[EMPLOYEE] [MANAGEMENT] [SYSTEM]");
    printChar('=', 17);
    printf("\n");
    printChar('=', 65);
}

// ==========ADDING NEW RECORD==========================
void add(FILE *fp) {
    printHead();
    printf("\n\t\t\tAdd Employee");
    char another = 'y';
    Employee e;
    int siz = sizeof(e);
    fseek(fp, 0, SEEK_END);

    while (another == 'y' || another == 'Y') {
        printf("\n\n\tEnter ID number : ");
        scanf("%d", &e.id);
        
        printf("\n\tEnter Full Name of Employee : ");
        fflush(stdin);
        fgets(e.name, 100, stdin);
        e.name[strlen(e.name) - 1] = '\0';

        printf("\n\tEnter Designation : ");
        fflush(stdin);
        fgets(e.desgn, 50, stdin);
        e.desgn[strlen(e.desgn) - 1] = '\0';
        
        printf("\n\tEnter Gender : ");
        fflush(stdin);
        fgets(e.gender, 10, stdin);
        e.gender[strlen(e.gender) - 1] = '\0';
        
        printf("\n\tEnter Branch : ");
        fflush(stdin);
        fgets(e.branch, 50, stdin);
        e.branch[strlen(e.branch) - 1] = '\0';
        
        printf("\n\tEnter Salary : ");
        scanf("%f", &e.sal);
        
        printf("\n\tEnter Present Address : ");
        fflush(stdin);
        fgets(e.psaddr, 200, stdin);
        e.psaddr[strlen(e.psaddr) - 1] = '\0';
        
        printf("\n\tEnter Permanent Address : ");
        fflush(stdin);
        fgets(e.prtaddr, 200, stdin);
        e.prtaddr[strlen(e.prtaddr) - 1] = '\0';
        
        printf("\n\tEnter Phone Number : ");
        fflush(stdin);
        fgets(e.phone, 50, stdin);
        e.phone[strlen(e.phone) - 1] = '\0';
        
        printf("\n\tEnter E-mail : ");
        fflush(stdin);
        fgets(e.mail, 50, stdin);
        e.mail[strlen(e.mail) - 1] = '\0';
        
        printf("\n\tEnter Joining Date (DD/MM/YYYY) : ");
        fflush(stdin);
        fgets(e.jdate, 30, stdin);
        e.jdate[strlen(e.jdate) - 1] = '\0';
        
        fwrite(&e, siz, 1, fp);
        
        printf("\n\n\tWant to enter another employee info (Y/N) :\t ");
        fflush(stdin);
        another = getchar();
    }
}

//===================DELETING A RECORD FROM LIST ============
FILE *del(FILE *fp) {
    printHead();
    printf("\n\t\t\tDelete Employee");
    Employee e;
    int flag = 0, tempid, siz = sizeof(e);
    FILE *ft;

    if ((ft = fopen("temp.txt", "wb+")) == NULL) {
        printf("\n\n\t\t\t!!! ERROR !!!\n\t\t");
        system("read -p 'Press Enter to continue...' var");
        return fp;
    }

    printf("\n\n\tEnter ID number of Employee to Delete the Record");
    printf("\n\n\t\t\tID No. : ");
    scanf("%d", &tempid);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1) {
        if (e.id == tempid) {
            flag = 1;
            printf("\n\tRecord Deleted for");
            printf("\n\n\t\t%s\n\n\t\t%s\n\n\t\t%d\n\t", e.name, e.branch, e.id);
            continue;
        }
        fwrite(&e, siz, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("employeeInfo.txt");
    rename("temp.txt", "employeeInfo.txt");

    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL) {
        printf("ERROR");
        return NULL;
    }

    if (flag == 0) printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND \n\t");

    printChar('=', 65);
    printf("\n\t");
    system("read -p 'Press Enter to continue...' var");
    return fp;
}

//====================MODIFY A RECORD =========================
void modify(FILE *fp) {
    printHead();
    printf("\n\t\t\tModify Employee");
    Employee e;
    int flag = 0, tempid, siz = sizeof(e);
    printf("\n\n\tEnter ID number of Employee to Modify the Record : ");
    scanf("%d", &tempid);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1) {
        if (e.id == tempid) {
            flag = 1;
            break;
        }
    }

    if (flag == 1) {
        fseek(fp, -siz, SEEK_CUR);
        printf("\n\n\t\tRecord Found");
        printf("\n\n\t\tEnter New Data for the Record");

        printf("\n\n\t\tEnter ID number: ");
        scanf("%d",&e.id);

        printf("\n\n\t\tEnter Full Name of Employee: ");
        fflush(stdin);
        fgets(e.name, 100, stdin);
        e.name[strlen(e.name) - 1] = '\0';

        printf("\n\n\t\tEnter Designation: ");
        fflush(stdin);
        fgets(e.desgn, 10, stdin);
        e.desgn[strlen(e.desgn) - 1] = '\0';

        printf("\n\n\t\tEnter Gender: ");
        fflush(stdin);
        fgets(e.gender, 10, stdin);
        e.gender[strlen(e.gender) - 1] = '\0';

        printf("\n\n\t\tEnter Branch: ");
        fflush(stdin);
        fgets(e.branch, 50, stdin);
        e.branch[strlen(e.branch) - 1] = '\0';

        printf("\n\n\t\tEnter Salary: ");
        scanf("%f", &e.sal);

        printf("\n\n\t\tEnter Present Address: ");
        fflush(stdin);
        fgets(e.psaddr, 200, stdin);
        e.psaddr[strlen(e.psaddr) - 1] = '\0';

        printf("\n\n\t\tEnter Permanent Address: ");
        fflush(stdin);
        fgets(e.prtaddr, 200, stdin);
        e.prtaddr[strlen(e.prtaddr) - 1] = '\0';

        printf("\n\n\t\tEnter Phone: ");
        fflush(stdin);
        fgets(e.phone, 50, stdin);
        e.phone[strlen(e.phone) - 1] = '\0';

        printf("\n\n\t\tEnter E-mail: ");
        fflush(stdin);
        fgets(e.mail, 20, stdin);
        e.mail[strlen(e.mail) - 1] = '\0';

        fwrite(&e, siz, 1, fp);
    } else {
        printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");
    }

    printf("\n\n\t");
    system("read -p 'Press Enter to continue...' var");
}

//====================DISPLAY LIST ===========================
void displayList(FILE *fp) {
    printHead();
    printf("\n\t\t\tList of Employees");
    Employee e;
    int i, siz = sizeof(e);

    rewind(fp);
    while ((fread(&e, siz, 1, fp)) == 1) {
        printf("\n\t\t\tID : %d", e.id);
        printf("\n\t\t\tName : %s", e.name);
        printf("\n\t\t\tDesignation : %s", e.desgn);
        printf("\n\t\t\tGender : %s", e.gender);
        printf("\n\t\t\tBranch : %s", e.branch);
        printf("\n\t\t\tSalary : %.2f", e.sal);
        printf("\n\t\t\tJoining Date : %s", e.jdate);
        printf("\n\t\t\tPresent Address : %s", e.psaddr);
        printf("\n\t\t\tPermanent Address : %s", e.prtaddr);
        printf("\n\t\t\tPhone : %s", e.phone);
        printf("\n\t\t\tE-mail : %s\n\n", e.mail);
        printChar('=', 65);
        printf("\n\n\t\t\t===============================\n");
    }
    printf("\n\n\n\t");
    printf("\n\t");
    system("read -p 'Press Enter to continue...' var");
}

//==================== SEARCH RECORD ===========================
void searchRecord(FILE *fp) {
    printHead();
    printf("\n\t\t\tSearch Employee Record");
    int tempid, flag, siz;
    Employee e;
    char another = 'y';
    siz = sizeof(e);

    while (another == 'y' || another == 'Y') {
        printf("\n\n\tEnter ID Number of Employee : ");
        scanf("%d", &tempid);
        rewind(fp);

        while ((fread(&e, siz, 1, fp)) == 1) {
            if (e.id == tempid) {
                flag = 1;
                break;
            }
        }

        if (flag == 1) {
            printf("\n\t\tNAME : %s", e.name);
            printf("\n\t\tGENDER : %s", e.gender);
            printf("\n\t\tBranch : %s", e.branch);
            printf("\n\t\tSalary: %.2f", e.sal);
            printf("\n\t\tDesignation: %s", e.desgn);
            printf("\n\t\tPresent Address : %s", e.psaddr);
            printf("\n\t\tPermanent Address : %s", e.prtaddr);
            printf("\n\t\tPhone : %s", e.phone);
            printf("\n\t\tE-mail : %s", e.mail);
            printf("\n\t\tJOINING DATE : %s", e.jdate);
            printf("\n\n\n");
        } else {
            printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND \n\t");
        }

        printf("\n\n\tWant to enter another employee info (Y/N)?");
        fflush(stdin);
        another = getchar();
    }
}

//==================== Display Basic Info ========================
void displayBasic(FILE *fp) {
    printHead();
    printf("\n\t\t\tBasic Info of Employees");
    Employee e;
    int siz = sizeof(e);

    rewind(fp);
    while ((fread(&e, siz, 1, fp)) == 1) {
        printf("\n\t\t\tID : %d", e.id);
        printf("\n\t\t\tName : %s", e.name);
        printf("\n\t\t\tGender : %s", e.gender);
        printf("\n\t\t\tBranch : %s", e.branch);
        printf("\n\t\t\tDesignation : %s", e.desgn);
        printf("\n\n\t\t\t===============================\n");
    }
    printf("\n\n\n\t");
    printChar('=', 65);
    printf("\n\t");
    system("read -p 'Press Enter to continue...' var");
}

//==================== Basic Contact Info ===========================
void basicContact(FILE *fp) {
    printHead();
    printf("\n\t\t\tBasic Contact Info of Employees");
    Employee e;
    int siz = sizeof(e);

    rewind(fp);
    while ((fread(&e, siz, 1, fp)) == 1) {
        printf("\n\t\t\tID : %d", e.id);
        printf("\n\t\t\tName : %s", e.name);
        printf("\n\t\t\tPhone : %s", e.phone);
        printf("\n\t\t\tE-mail : %s", e.mail);
        printf("\n\n\t\t\t===============================\n");
    }
    printf("\n\n\n\t");
    printChar('=', 65);
    printf("\n\t");
    system("read -p 'Press Enter to continue...' var");
}

//====================List of Male Employees ===========================
void maleEmp(FILE *fp) {
    printHead();
    printf("\n\t\t\tList of Male Employees");
    Employee e;
    int siz = sizeof(e);

    rewind(fp);
    while ((fread(&e, siz, 1, fp)) == 1) {
        if (strcasecmp(e.gender, "Male") == 0 ||(strcmp(e.gender,"male")==0)) {
            printf("\n\t\t\tID : %d", e.id);
            printf("\n\t\t\tName : %s", e.name);
            printf("\n\t\t\tBranch : %s", e.branch);
            printf("\n\t\t\tDesignation : %s", e.desgn);
            printf("\n\n\t\t\t===============================\n");
        }
    }
    printf("\n\n\n\t");
    printChar('=', 65);
    printf("\n\t");
    system("read -p 'Press Enter to continue...' var");
}

//====================List of Female Employees ===========================
void femaleEmp(FILE *fp) {
    printHead();
    printf("\n\t\t\tList of Female Employees");
    Employee e;
    int siz = sizeof(e);

    rewind(fp);
    while ((fread(&e, siz, 1, fp)) == 1) {
        if (strcasecmp(e.gender, "Female") == 0 ||(strcmp(e.gender,"female")==0)) {
            printf("\n\t\t\tID : %d", e.id);
            printf("\n\t\t\tName : %s", e.name);
            printf("\n\t\t\tBranch : %s", e.branch);
            printf("\n\t\t\tDesignation : %s", e.desgn);
            printf("\n\n\t\t\t===============================\n");
        }
    }
    printf("\n\n\n\t");
    printChar('=', 65);
    printf("\n\t");
    system("read -p 'Press Enter to continue...' var");
}

//====================Search for Employee's ID from the Phone ===========================
void searchPhone(FILE *fp) {
    printHead();
    printf("\n\t\t\tSearch Employee's ID from Phone");
    char tempPhone[50];
    int flag, siz;
    Employee e;
    char another = 'y';
    siz = sizeof(e);

    while (another == 'y' || another == 'Y') {
        printf("\n\n\tEnter Phone Number of Employee : ");
        fflush(stdin);
        fgets(tempPhone, 50, stdin);
        tempPhone[strlen(tempPhone) - 1] = '\0';
        rewind(fp);

        while ((fread(&e, siz, 1, fp)) == 1) {
            if (strcmp(e.phone, tempPhone) == 0) {
                flag = 1;
                break;
            }
        }

        if (flag == 1) {
            printf("\n\t\tID : %d", e.id);
            printf("\n\t\tNAME : %s", e.name);
            printf("\n\t\tGENDER : %s", e.gender);
            printf("\n\t\tBranch : %s", e.branch);
            printf("\n\t\tSalary: %.2f", e.sal);
            printf("\n\t\tDesignation: %s", e.desgn);
            printf("\n\t\tPresent Address : %s", e.psaddr);
            printf("\n\t\tPermanent Address : %s", e.prtaddr);
            printf("\n\t\tE-mail : %s", e.mail);
            printf("\n\t\tJOINING DATE : %s", e.jdate);
            printf("\n\n\n");
        } else {
            printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND \n\t");
        }

        printf("\n\n\tWant to enter another phone number (Y/N)?");
        fflush(stdin);
        another = getchar();
    }
}

//====================Delete a Record ===========================
void deleteRecord(FILE *fp) {
    printHead();
    printf("\n\t\t\tDelete a Record");
    Employee e;
    int flag = 0, tempid, siz = sizeof(e);
    FILE *ft;

    if ((ft = fopen("Temp.dat", "wb+")) == NULL) {
        printf("\n\n\t\t!!!! ERROR !!!!\n\t");
        system("read -p 'Press Enter to continue...' var");
        return;
    }

    printf("\n\n\tEnter ID number of Employee to Delete the Record : ");
    scanf("%d", &tempid);

    rewind(fp);

    while ((fread(&e, siz, 1, fp)) == 1) {
        if (e.id == tempid) {
            flag = 1;
            printf("\n\tRecord Deleted for");
            printf("\n\t\t%s\n", e.name);
            continue;
        }

        fwrite(&e, siz, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("EMP.DAT");
    rename("Temp.dat", "EMP.DAT");

    if ((fp = fopen("EMP.DAT", "rb+")) == NULL) {
        printf("ERROR");
        return;
    }

    if (flag == 0) {
        printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND \n\t");
    }

    printChar('=', 65);
    printf("\n\t");
    system("read -p 'Press Enter to continue...' var");
}

//====================Display Male/Female Employees by Branch ===========================
void maleFemaleByBranch(FILE *fp) {
    printHead();
    printf("\n\t\t\tMale and Female Employees by Branch");
    Employee e;
    int siz = sizeof(e);
    char branch[50];

    printf("\n\n\tEnter Branch Name : ");
    fflush(stdin);
    fgets(branch, 50, stdin);
    branch[strlen(branch) - 1] = '\0';

    rewind(fp);
    printf("\n\t\t\tMale Employees in %s", branch);
    while ((fread(&e, siz, 1, fp)) == 1) {
        if (strcasecmp(e.branch, branch) == 0 && strcasecmp(e.gender, "Male") == 0) {
            printf("\n\t\t\tID : %d", e.id);
            printf("\n\t\t\tName : %s", e.name);
            printf("\n\t\t\tDesignation : %s", e.desgn);
            printf("\n\n\t\t\t===============================\n");
        }
    }

    rewind(fp);
    printf("\n\t\t\tFemale Employees in %s", branch);
    while ((fread(&e, siz, 1, fp)) == 1) {
        if (strcasecmp(e.branch, branch) == 0 && strcasecmp(e.gender, "Female") == 0) {
            printf("\n\t\t\tID : %d", e.id);
            printf("\n\t\t\tName : %s", e.name);
            printf("\n\t\t\tDesignation : %s", e.desgn);
            printf("\n\n\t\t\t===============================\n");
        }
    }

    printf("\n\n\n\t");
    printChar('=', 65);
    printf("\n\t");
    system("read -p 'Press Enter to continue...' var");
}

//====================Display Employees by Salary Range ===========================
void bySalaryRange(FILE *fp) {
    printHead();
    printf("\n\t\t\tEmployees by Salary Range");
    Employee e;
    int siz = sizeof(e);
    float minSal, maxSal;

    printf("\n\n\tEnter Minimum Salary : ");
    scanf("%f", &minSal);
    printf("\n\tEnter Maximum Salary : ");
    scanf("%f", &maxSal);

    rewind(fp);
    while ((fread(&e, siz, 1, fp)) == 1) {
        if (e.sal >= minSal && e.sal <= maxSal) {
            printf("\n\t\t\tID : %d", e.id);
            printf("\n\t\t\tName : %s", e.name);
            printf("\n\t\t\tDesignation : %s", e.desgn);
            printf("\n\t\t\tSalary : %.2f", e.sal);
            printf("\n\n\t\t\t===============================\n");
        }
    }

    printf("\n\n\n\t");
    printChar('=', 65);
    printf("\n\t");
    system("read -p 'Press Enter to continue...' var");
}

void fromOthers(FILE *fp) {
    Employee e;
    rewind(fp); // Set file pointer to the beginning

    printf("\n\n\t\tEmployees from Other Branches\n");
    while (fread(&e, sizeof(e), 1, fp) == 1) {
        if (strcmp(e.branch, "Main") != 0) { // Assuming "Main" is the branch name for main branch
            printf("\n\n\tEmployee ID: %d", e.id);
            printf("\n\tEmployee Name: %s", e.name);
            printf("\n\tEmployee Branch: %s", e.branch);
        }
    }
    printf("\n\n\tPress any key to continue...");
    getchar();
    getchar();
}

void mainBranch(FILE *fp) {
    Employee e;
    rewind(fp); // Set file pointer to the beginning

    printf("\n\n\t\tEmployees from Main Branch\n");
    while (fread(&e, sizeof(e), 1, fp) == 1) {
        if (strcmp(e.branch, "Main") == 0) { // Assuming "Main" is the branch name for main branch
            printf("\n\n\tEmployee ID: %d", e.id);
            printf("\n\tEmployee Name: %s", e.name);
            printf("\n\tEmployee Branch: %s", e.branch);
        }
    }
    printf("\n\n\tPress any key to continue...");
    getchar();
    getchar();
}

void otherBranch(FILE *fp) {
    Employee e;
    rewind(fp); // Set file pointer to the beginning

    printf("\n\n\t\tEmployees from Other Branches\n");
    while (fread(&e, sizeof(e), 1, fp) == 1) {
        if (strcmp(e.branch, "Main") != 0) { // Assuming "Main" is the branch name for main branch
            printf("\n\n\tEmployee ID: %d", e.id);
            printf("\n\tEmployee Name: %s", e.name);
            printf("\n\tEmployee Branch: %s", e.branch);
        }
    }
    printf("\n\n\tPress any key to continue...");
    getchar();
    getchar();
}

//====================Main Program ===========================
int main() {
    FILE *fp;
    int option;

    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL) 
        {
            if ((fp = fopen("employeeInfo.txt", "wb+")) == NULL) 
                {
                    printf("Can't open file\n");
                    return 0;
                }
        }

    char username[10];
    char password[MAX_PASSWORD_LENGTH + 1]; // +1 for null terminator

    printHead();
    welcome();
    printHead();
    printf("\n");
    printf("\n\t\t\t Login Screen");
    printf("\n\t\t      Enter Your Credential");
    printf("\n\n\n\t\t\tUsername: ");
    scanf("%s", username);
    printf("\n\t\t\tPassword: ");
    scanf("%s",password);

    int i; 
    i = 0;

    if ((strcasecmp(username, "admin") == 0) && (strcasecmp(password, "pass") == 0)) {
        while (1) {
            printHead();
            printf("\n\t\t\tMain Menu");
            printf("\n\n");


            printf("\n\n\t\t\t1. Add Employee");
            printf("\n\n\t\t\t2. Delete Employee");
            printf("\n\n\t\t\t3. Modify Employee");
            printf("\n\n\t\t\t4. Display Employee List");
            printf("\n\n\t\t\t5. Search Record");
            printf("\n\n\t\t\t6. Display Basic Info");
            printf("\n\n\t\t\t7. Display Basic Contact Info");
            printf("\n\n\t\t\t8. List of Male Employees");
            printf("\n\n\t\t\t9. List of Female Employees");
            printf("\n\n\t\t\t10. List of Employees From Other Districts");
            printf("\n\n\t\t\t11. List of Employees of Main Branch");
            printf("\n\n\t\t\t12. List of Employees of Other Branches");
            printf("\n\n\t\t\t0. EXIT");

            printf("\n\n\t\tEnter Your Option :--> ");
            scanf("%d", &option);

            switch (option) 
                {
                case 0: return 1;
                    break;
                case 1: add(fp); 
                    break;
                case 2: fp = del(fp); 
                    break;
                case 3: modify(fp); 
                    break;
                case 4: displayList(fp); 
                    break;
                case 5: searchRecord(fp); 
                    break;
                case 6: displayBasic(fp); 
                    break;
                case 7: basicContact(fp); 
                    break;
                case 8: maleEmp(fp); 
                    break;
                case 9: femaleEmp(fp); 
                    break;
                case 10: fromOthers(fp); 
                    break;
                case 11: mainBranch(fp); 
                    break;
                case 12: otherBranch(fp);  
                    break;
                default: 
                    printf("\n\t\tYou Pressed the wrong key");
                    printf("\n\t\tProgram terminated");
                    getchar();
                    exit(0);
                }
        }
    } else {
        printf("\n\t\tLogin Failed\n");
    }

    return 1;
}