#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 1024

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

typedef struct {
    char name[MAX];
    char pass[MAX];
} logInCredentials;


typedef struct {
	char courseName[MAX];
	char courseCode[MAX];
	char section[MAX];
	char instructor[MAX];
	char file[MAX];
}Classes;

typedef struct StudentDetails{
	char studentNumber[MAX];
	char FirstName[MAX];
	char LastName[MAX];
	
	struct StudentDetails *next;
}StudentDetails;



typedef struct{
	StudentDetails *head, *tail, *next;
}list_t;

//global variables
char currentUser[MAX];
int choice;

//methods
void front();
void attendance();
void addStudent();
void searchStudent(list_t* list, char s[]);
void deleteStudent(char filePath[], list_t*);
void freeMemory(list_t*);
void editStudent(char filePath[], list_t*);
void editClass();
void mainMenu();
void addClass();
void showClass();
void openClass();
void getPassword();
void addFile();
void deleteClass();
//void sort();


int main() {
	
	front();
	
	return 0;
}

StudentDetails *add (list_t *l, StudentDetails *data)
{
    StudentDetails *node = malloc (sizeof *node);   /* allocate node */
    if (!node) {                            /* validate allocation */
        perror ("malloc-node");
        return NULL;
    }

    *node = *data;                      /* initialize members values */
	node->next = NULL;
	
    if (!l->head)                       /* if 1st node, node is head/tail */
        l->head = l->tail = node;
    else {                              /* otherwise */
        l->tail->next = node;           /* add at end, update tail pointer */
        l->tail = node;
    }

    return node;    /* return new node */
}

list_t *list_from_csv(list_t *list, FILE *fp)
{
    char buf[MAX];
    StudentDetails data;
	
	fgets(buf, MAX, fp);
    while (fgets(buf, MAX, fp)) {
       if (sscanf(buf, "%63[^,],%63[^,],%63[^\n]", data.studentNumber, data.FirstName, data.LastName) == 3) {
		    if (!add(list, &data)) 
		        break;
		}
    }
    return list;
}

void del_list (list_t *l)
{
    StudentDetails *n = l->head;

    while (n) {
        StudentDetails *victim = n;
        n = n->next;
        free (victim);
    }
}

void prn_list(list_t *list) {
    StudentDetails *current = list->head;
    int i = 1;

    if (current && strcmp(current->FirstName, "FirstName") == 0 && strcmp(current->LastName, "LastName") == 0) {
        current = current->next;
    }//labels ni sila so i-skip

    if (!current) {
        printf("List is empty.\n");
        return;
    }
    printf(" %-12s %-25s %-25s %-15s\n", "No.", "Student#", "First Name", "Last Name");
    printf("------------------------------------------------------------------------------------------\n");
    while (current) {
        printf(" %-12d %-25s %-25s %-15s\n", i++, current->studentNumber,current->FirstName, current->LastName);
        current = current->next;
    }
    printf("------------------------------------------------------------------------------------------\n");
}

/* TODO (Ann#1#): attendance */
void attendance(char filePath[]){
	//make a new field, rewrite into another file
	//read and edit
	FILE *original_file, *temp_file;
    char line[MAX];
    char new_field_value[256];
    char folderPath[MAX];
    char tempFilePath[MAX];

    // Step 1: Extract folder path
    strcpy(folderPath, filePath);
    char *lastSlash = strrchr(folderPath, '\\');
    if (lastSlash != NULL) {
        *(lastSlash + 1) = '\0'; // Keep up to the last '\'
    } else {
        printf("Invalid file path.\n");
        return;
    }

    // Step 2: Create temp file path
    snprintf(tempFilePath, sizeof(tempFilePath), "%stemp_data.csv", folderPath);

    // Step 3: Open files
    original_file = fopen(filePath, "r");
    if (original_file == NULL) {
        perror("Error opening original CSV file");
        return;
    }

    temp_file = fopen(tempFilePath, "w");
    if (temp_file == NULL) {
        perror("Error creating temporary CSV file");
        fclose(original_file);
        return;
    }

    // Step 4: Get new field name
    printf("Enter the value for the new field: ");
    fgets(new_field_value, sizeof(new_field_value), stdin);
    new_field_value[strcspn(new_field_value, "\n")] = 0; // Remove trailing newline

    // Step 5: Process the header
    if (fgets(line, MAX, original_file) != NULL) {
        line[strcspn(line, "\n")] = 0; // Remove trailing newline
        fprintf(temp_file, "%s,%s\n", line, new_field_value);
    }

    // Step 6: Process each data line
    while (fgets(line, MAX, original_file) != NULL) {
        line[strcspn(line, "\n")] = 0; // Remove trailing newline
        fprintf(temp_file, "%s,\n", line);
    }

    fclose(original_file);
    fclose(temp_file);

    // Step 7: Replace the original file
    if (remove(filePath) != 0) {
        perror("Error deleting original CSV file");
    }
    if (rename(tempFilePath, filePath) != 0) {
        perror("Error renaming temporary CSV file");
    }

    printf("New field added successfully.\n");
    getch();
}

void front() {
    logInCredentials logIn;
    int frChoice;
    char line[MAX], Name[MAX], Password[MAX], conPass[MAX], firstPass[MAX], compName[MAX], compPass[MAX];
    char *token;
    FILE *file;
    
    do {
    	system(CLEAR_SCREEN);
	    FILE *fptr = fopen("menuArt.txt", "r");  
	
	    if (fptr == NULL) {  
	        return;
	    }
	    char ch;
	    while ((ch = fgetc(fptr)) != EOF) {
	        putchar(ch);
	    }
	    fclose(fptr);  
	    
	        printf("Select operation:\n");
	        printf("[1] LOG-IN\n[2] SIGN UP\n[3] EXIT\n\n");
	        printf("Enter choice: ");
	        scanf(" %d", &frChoice);
	        getchar();
	        switch(frChoice){
	        	case 1: 
	        		{
	        		LOGIN:
	        		system(CLEAR_SCREEN);
	        		 FILE *fptr = fopen("logInart.txt", "r");  
	
	    			if (fptr == NULL) {  
	        		return;
	    			}
	    			char ch;
	    			while ((ch = fgetc(fptr)) != EOF) {
	        		putchar(ch);
	    			}
	    			fclose(fptr);
	    			
	    			printf("\n\n\nEnter name: ");
		            scanf(" %[^\n]", Name); 
		            printf("Enter password: ");
		            getPassword(Password, sizeof(Password));
		
		            file = fopen("accounts.csv", "r"); 
		            if (file == NULL) {
		                perror("Error opening file");
		                getch();
		                return;
		            }
		
		            int found = 0;
		            while (fgets(line, MAX, file) != NULL) {
		                line[strcspn(line, "\n")] = 0;
		
		                token = strtok(line, ","); // Initialize token
		                if (token != NULL) strcpy(compName, token); 
		                
		                token = strtok(NULL, ",");
		                if (token != NULL) strcpy(compPass, token);
		
		                if (strcmp(compName, Name) == 0 && strcmp(compPass, Password) == 0) {
		                    printf("Login Successful!\n\n");
		                    found = 1;
//		                    getch();
		                    break;
		                }
		            }
		            fclose(file);
		
		            if (found) {
		                strcpy(currentUser, Name);
		                mainMenu();
		            } else {
		                printf("\nInvalid credentials. Please try again.\n");
		                getch();
						goto LOGIN;
		            }
					}
		            break;
		        case 2:
		        	{
		        		
		        		system(CLEAR_SCREEN);
	        		 FILE *fptr = fopen("signUpArt.txt ", "r");  
	
	    			if (fptr == NULL) {  
	        		return;
	    			}
	    			char ch;
	    			while ((ch = fgetc(fptr)) != EOF) {
	        		putchar(ch);
	    			}
	    			fclose(fptr);
	    			
		        		printf("\n\n\nEnter name: ");
			            scanf(" %[^\n]", Name);
			            
			            do {
			            	PASS:
			                printf("Enter password: ");
			                scanf(" %s", firstPass);
			                printf("Confirm password: ");
			                scanf(" %s", conPass);
			
			                if (strcmp(firstPass, conPass) == 0) {
			                    FILE *file = fopen("accounts.csv", "a");
			                    if (file == NULL) {
			                        perror("Error opening file");
			                        getch();
			                        return;
			                    }
			                    fprintf(file, "%s,%s\n", Name, firstPass);
			                    fclose(file);
			                    printf("Account created successfully! Please log in.\n");
			                    getch();
			                    goto LOGIN;
			                    break;
			                } else {
			                    printf("Passwords do not match! Try again.\n\n");
			                    getch();
			                    goto PASS;
			                }
			            }while(strcmp(firstPass, conPass)==0);
					}
		            break;
	            case 3:
	            	printf("Bye!\n");
	            	exit(0);
	            default: 
					printf("Choice out of bounds, try again!\n");
					getch();
			}
    }while(frChoice!=3);
}

void getPassword(char *buffer, int maxLength) {
    int i = 0;
    char ch;
    
    while (1) {
        ch = getch();//basahon ang inputted characters without showing
        
        if (ch == '\r' || ch == '\n') { 
            buffer[i] = '\0'; 
            printf("\n"); 
            break;
        }
        else if (ch == '\b' && i > 0) {//kung mag delete
            i--;
            printf("\b \b");
        }
        else if (i < maxLength - 1 && ch != '\b') { 
            buffer[i++] = ch;
            printf("*"); //imbes ang letters, asterisk ang iprint
        }
    }
}


void mainMenu() {
    int choice, menuChoice;

    	system(CLEAR_SCREEN);
    FILE *fptr = fopen("menuArt.txt", "r");  

    if (fptr == NULL) {  
        return;
    }
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }
    fclose(fptr);  

        printf("\n[1] Add Classes\n[2] Show Classes\n[3] Edit Classes\n[4] Log Out\n");
    do{
        printf("\nEnter choice: ");
        scanf(" %d", &choice);
        getchar();
        
		  switch (choice) {
	        case 1:
	        	system(CLEAR_SCREEN);
				addClass();
	            break;
	        case 2:
	        	system(CLEAR_SCREEN);
	            showClass();
	            break;
	        case 3:
	        	 system(CLEAR_SCREEN);
	             editClass();
	            break;
	        case 4:
	            printf("Returning...\n");
	            strcpy(currentUser, ""); 
	            front();
	            system(CLEAR_SCREEN);
	            return;
	            
	        default:
	            printf("Choice out of bounds, please try again.\n");
	            break;
	    	}
		}while (choice != 4);
}

void addClass(){//let's try nga maka add ug filepath
	
	int numClass, i, choice;
	Classes addClass;
	char dec[MAX];
	
    FILE *fptr = fopen("addClass.txt", "r");  //art

    if (fptr == NULL) {  
        return;
    }
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }
    fclose(fptr);  
    
    printf("\t\tCurrent Classes");
    showClass(3);
    Adding:
	do{
		printf("\n\nEnter preferred number of classes to add: ");
    	scanf(" %d", &numClass);
    	getchar();	
    	if(numClass<1){
    		printf("Enter valid number.\n");
		}
		else if(numClass>=1)
		{
			break;
		}
		else{
			printf("Enter a valid number.\n");
		}
	}while(true);
    
    
    for (i = 0; i < numClass; i++){
    	printf("\nEnter course name: ");
    	scanf(" %[^\n]", addClass.courseName);
    	printf("Enter course code: ");
    	scanf(" %[^\n]", addClass.courseCode);
    	printf("Enter course section: ");
    	scanf(" %[^\n]", addClass.section);
    	printf("Enter file path: ");
    	scanf(" %[^\n]", addClass.file);
    	
    FILE *file = fopen("classes.csv", "a");
		if (file == NULL) {
		    perror("Error opening file");-
		     getch();
		    return;
		}
	fprintf(file, "%s,%s,%s,%s,%s\n", addClass.courseName, addClass.courseCode, addClass.section, currentUser, addClass.file);
	fclose(file);
	printf("\nClass added succesfully!\n\n");
	}
	
	numClass = 0;
	while(true){
		printf("Add more? \nEnter y/yes || n/no: ");
		scanf("%s", dec);
	
		if (strcmp(dec, "y") == 0 || strcmp(dec, "yes") == 0) {
             goto Adding;
            break;
        } else if (strcmp(dec, "n") == 0 || strcmp(dec, "no") == 0) {
             mainMenu();
            break;
        }
		else{
			printf("Enter a valid choice.\n");
		}
	}
	
	getch();
}

void showClass(int indicator){
    Classes showClass;
    char line[MAX], dec[MAX];
    char *token;
    FILE *file;

    if(indicator == 3)
        goto showClasses;
		system(CLEAR_SCREEN);
	    FILE *fptr = fopen("showClassArt.txt", "r");  
	
	    if (fptr == NULL) {  
	        return;
	    }
	    char ch;
	    while ((ch = fgetc(fptr)) != EOF) {
	        putchar(ch);
	    }
	    fclose(fptr);  

    showClasses:
    file = fopen("classes.csv", "r"); 
        if (file == NULL) {
            perror("Error opening file");
             getch();
            return;
        }
    
    
    int found = 0;
    printf("\n\n\n");
// Skip the header line
    fgets(line, MAX, file);
    printf(" %-5s %-20s %-15s %-10s\n", "No.", "Course Name", "Subject Code", "Section");
    printf("---------------------------------------------------------------\n");
        while (fgets(line, MAX, file) != NULL) {
            line[strcspn(line, "\n")] = 0;

            token = strtok(line, ",");
            if (token != NULL) strcpy(showClass.courseName, token); 

            token = strtok(NULL, ",");
            if (token != NULL) strcpy(showClass.courseCode, token); 

            token = strtok(NULL, ",");
            if (token != NULL) strcpy(showClass.section, token);

            token = strtok(NULL, ",");
            if (token != NULL) strcpy(showClass.instructor, token);

            if (strcmp(showClass.instructor, currentUser) == 0) {
                found++;
                printf(" [%d]   %-20s %-15s %-10s\n", found, showClass.courseName, showClass.courseCode, showClass.section);
            }
        }
    
    if(found>0){
    	printf("---------------------------------------------------------------\n");
	}
	else
	{
		printf("No classes yet.\n");
		printf("---------------------------------------------------------------\n");
	}
    
    fclose(file);
	
	Empty:
    if(indicator == 1 || indicator == 3){
        return;
    }
    else{
        while(true){
		printf("Open a class, delete class, or go back? \nEnter o/open || b/back || d/delete: ");
		scanf("%s", dec);
		
			if (strcmp(dec, "o") == 0 || strcmp(dec, "open") == 0) {
	            openClass();
	            break;
	        } else if (strcmp(dec, "b") == 0 || strcmp(dec, "back") == 0) {
	            mainMenu();
	            break;
	        }
	        else if(strcmp(dec, "d") == 0 || strcmp(dec, "delete") == 0) {
	        	deleteClass();
			}
			else{
				printf("Enter a valid choice.\n");
			}
		}
    }
}

void openClass() {
    Classes editClass, tempClass;
    char line[MAX], filePath[MAX];
    char *token;
    char s[20];
    FILE *file = fopen("classes.csv", "r");
    FILE *tempFile;
    int lineCount = 1, matchingLines[MAX], totalMatches = 0;
    int lineNum = 0, targetLine, choice;
    int found = 0;

    if (!file) {
        perror("Error opening classes.csv");
        getch();
        return;
    }

    fgets(line, MAX, file);  // skip header

    while (fgets(line, MAX, file)) {
        lineCount++;
        line[strcspn(line, "\n")] = '\0';
        token = strtok(line, ",");
        if (token) strcpy(tempClass.courseName, token);
        token = strtok(NULL, ",");
        if (token) strcpy(tempClass.courseCode, token);
        token = strtok(NULL, ",");
        if (token) strcpy(tempClass.section, token);
        token = strtok(NULL, ",");
        if (token) strcpy(tempClass.instructor, token);

        if (strcmp(tempClass.instructor, currentUser) == 0) {
            matchingLines[++totalMatches] = lineCount;
        }
    }
    fclose(file);

    if (totalMatches == 0) {
        printf("No classes found for user.\n");
        getch();
        showClass(0);
    }

	while(true){
		printf("\nEnter the number of class to open: ");
	    scanf("%d", &choice);
	
	    if (choice < 1 || choice > totalMatches) {
	        printf("Invalid selection.\n");
    	}
    	else{
    		break;
		}
	}
    

    file = fopen("classes.csv", "r");
    if (!file) {
        perror("Error reopening classes.csv");
        getch();
        return;
    }

    tempFile = fopen("temp.csv", "w");
    if (!tempFile) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    targetLine = matchingLines[choice];
    lineNum = 0;

    while (fgets(line, MAX, file)) {
        lineNum++;
        line[strcspn(line, "\n")] = '\0';

        if (lineNum == targetLine) {
            strcpy(editClass.courseName, strtok(line, ","));
            strcpy(editClass.courseCode, strtok(NULL, ","));
            strcpy(editClass.section, strtok(NULL, ","));
            strcpy(editClass.instructor, strtok(NULL, ","));
            strcpy(editClass.file, strtok(NULL, ","));
            strcpy(filePath, editClass.file);
            found = 1;
        } else {
            fputs(line, tempFile);
            fputc('\n', tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Open student list file for the selected class
    FILE *studentFile = fopen(filePath, "r");
    if (!studentFile) {
        perror("Error opening class student file");
        getch();
        return;
    }

    list_t list = { .head = NULL, .tail = NULL };
    if (!list_from_csv(&list, studentFile)) {
        fclose(studentFile);
        return;
    }

    fclose(studentFile);
    system(CLEAR_SCREEN);
    prn_list(&list);

	printf("\n\nDo you want to:\n\t[1] Add Student  \t[2] Edit Student\t[3] Delete Student\n\t[4] Search Student\t[5] Input Attendance\t[6] Sort\n\t[7] Back\n");
	while(true){
		printf("\nEnter choice: ");
		scanf("%d", &choice);

		switch(choice){
			case 1:{
				addStudent(filePath, &list);
				break;
			}
			case 2:{
				editStudent(filePath, &list);
				break;
			}
			case 3:{
				deleteStudent(filePath, &list);
				break;
			}
			case 4:{
			Searching:
			    printf("\nEnter Student's Last name: ");
			    scanf(" %s", &s);
				searchStudent(&list, s);
				printf("\n\nContinue searching? \n[1] Yes\n[2] No\nEnter choice: ");
				scanf("%d", &choice);
				if(choice == 1)
				{
					goto Searching;
				}	
				else
					del_list(&list);
					mainMenu();
				}
				break;
		
			case 5:{
				attendance(filePath);
				break;
			}
			case 6:{
//				sort(filePath);
			}
			case 7:{
				
				system(CLEAR_SCREEN);
				showClass(0);
				prn_list(&list);
				break;
				break;
			}
			default:
				printf("Enter a valid choice.");
		}
	}
	del_list(&list);
    getch();
}

void editStudent(char filePath[MAX], list_t* list){
    FILE *file, *temp_file;
    StudentDetails editStud, editTemp;
    char line[MAX], matchingLines[MAX];
    char *token;
    char tempPath[MAX];  
    int studEdit;
    int lineNum = 0, editChoice;

    file = fopen(filePath, "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

openEdit:
    // i-Skip ang header
    fgets(line, MAX, file);
    int lineCount = 1;

    while (fgets(line, MAX, file) != NULL) {
        lineCount++;
        line[strcspn(line, "\n")] = 0;
        token = strtok(line, ",");
        if (token != NULL) strcpy(editTemp.FirstName, token);
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(editTemp.LastName, token);
    }
    fclose(file);

Editing:
    printf("\nEnter student to edit (number): ");
    scanf("%d", &studEdit);

    if (studEdit < 1) {
        printf("Invalid selection.\n");
        getch();
        goto Editing;
    }

    file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    char *lastSlash = strrchr(filePath, '\\');
    if (lastSlash) {
        size_t dirLen = lastSlash - filePath + 1;
        strncpy(tempPath, filePath, dirLen);
        tempPath[dirLen] = '\0'; 
        strcat(tempPath, "temp.csv"); 
    } else {
        strcpy(tempPath, "temp.csv");
    }

    temp_file = fopen(tempPath, "w");
    if (temp_file == NULL) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return;
    }

    while (fgets(line, MAX, file) != NULL) { 
        lineNum++;
        line[strcspn(line, "\n")] = '\0'; // remove newline

        if (lineNum == studEdit) {  
            strcpy(editStud.studentNumber, strtok(line, ","));
            strcpy(editStud.FirstName, strtok(NULL, ","));
            strcpy(editStud.LastName, strtok(NULL, ","));

            printf("\nEditing: %s %s (%s)\n", editStud.FirstName, editStud.LastName, editStud.studentNumber);
            printf("[1] Edit student number\n[2] Edit first name\n[3] Edit last name\n[4] Edit All\n");

            while (true) {
                printf("Enter choice: ");
                scanf("%d", &editChoice);
                getchar();

                switch (editChoice) {
                    case 1:
                        printf("Enter new student number: ");
                        scanf(" %[^\n]", editStud.studentNumber);
                        break;
                    case 2:
                        printf("Enter new first name: ");
                        scanf(" %[^\n]", editStud.FirstName);
                        break;
                    case 3:
                        printf("Enter new last name: ");
                        scanf(" %[^\n]", editStud.LastName);
                        break;
                    case 4:
                        printf("Enter new student number: ");
                        scanf(" %[^\n]", editStud.studentNumber);
                        printf("Enter new first name: ");
                        scanf(" %[^\n]", editStud.FirstName);
                        printf("Enter new last name: ");
                        scanf(" %[^\n]", editStud.LastName);
                        break;
                    default:
                        printf("Invalid choice. No changes made.\n");
                }
                break;
            }
            fprintf(temp_file, "%s,%s,%s\n", editStud.studentNumber, editStud.FirstName, editStud.LastName);
        } else {
            fprintf(temp_file, "%s\n", line);
        }
    }

    fclose(file);
    fclose(temp_file);

    if (remove(filePath) == 0) {
        if (rename(tempPath, filePath) != 0) {
            perror("Error renaming temporary file");
            return;
        }
    } else {
        perror("Error deleting original file");
        return;
    }

    printf("\nStudent %d updated successfully.\n", studEdit);
    getch();
    system(CLEAR_SCREEN);

    FILE *studentFile = fopen(filePath, "r");
    if (!studentFile) {
        perror("Error opening class student file");
        getch();
        return;
    }

    list->head = NULL;
    list->tail = NULL;
    if (!list_from_csv(list, studentFile)) {
        fclose(studentFile);
        return;
    }

    fclose(studentFile);

    printf("\n Updated List:\n");
    prn_list(list);
    del_list(list);
    lineNum = 0;

    printf("\n\nEdit more? \n[1] Yes\n[2] No");
    while (true) {
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            goto Editing;
        } else if (choice == 2) {
            showClass(1);
        } else {
            printf("Enter a valid choice.\n");
        }
    }
}



void addStudent(char filePath[MAX]){
	
	int numClass, i, choice;
	StudentDetails addStud;
	char dec[MAX];
//    FILE *fptr = fopen("addClass.txt", "r");  //art

    Adding:
    printf("\n\nEnter number of students to add: ");
    scanf("%d", &numClass);
    
    for (i = 0; i < numClass; i++){
    	printf("Enter Student ID Number: ");
    	scanf(" %[^\n]", addStud.studentNumber);
    	printf("\nEnter First Name: ");
    	scanf(" %[^\n]", addStud.FirstName);
    	printf("Enter Last Name: ");
    	scanf(" %[^\n]", addStud.LastName);
    	
	    FILE *file = fopen(filePath, "a");
			if (file == NULL) {
			    perror("Error opening file");-
			     getch();
			    return;
			}
		fprintf(file, "%s,%s,%s\n", addStud.studentNumber,addStud.FirstName,addStud.LastName);
		fclose(file);
		printf("\nStudent(s) added succesfully!\n\n");
	}
	
	
	while(true){		
		printf("Add more? \nEnter y/yes || n/no: ");
		scanf("%s", &dec);
		if((strcmp(dec, "y") ==0) ||(strcmp(dec, "yes") ==0)){
		goto Adding;
		break;
		}	
		else if((strcmp(dec, "n") ==0) ||(strcmp(dec, "no") ==0)){
			showClass(0);
		}
		else{
			printf("Enter a valid choice.\n");
		}
	}
	
	getch();
}

void editStudent(char filePath[MAX], list_t* list){
 	FILE *file, *temp_file;
	StudentDetails editStud, editTemp;
	char line[MAX], matchingLines[MAX];
	char *token;
	char tempPath[MAX];  
	int studEdit;
	int lineNum = 0, editChoice;
		
	file = fopen(filePath, "r");
	
	if (file == NULL) {
	    perror("Error opening file");
	    return;
	}
	openEdit:
	// i-Skip ang header
	fgets(line, MAX, file);
	int lineCount = 1;
	while (fgets(line, MAX, file) != NULL) {//ang kani nga loop is to assign data into their designated variable, track ang tinuod nga number niya sa csv
	    lineCount++;
	    line[strcspn(line, "\n")] = 0;
	    token = strtok(line, ",");
	    if (token != NULL) strcpy(editTemp.FirstName, token);
	     token = strtok(NULL, ",");
	    if (token != NULL) strcpy(editTemp.LastName, token);
	}
	fclose(file);
	
	Editing:
	printf("\nEnter student to edit (number): ");
	scanf("%d", &studEdit);
	
	if (studEdit < 1) {
		printf("Invalid selection.\n");
	    getch();
	    goto Editing;   
	}
	
	file = fopen(filePath, "r");
	if (file == NULL) {
	    perror("Error opening file for reading");
	    return;
	}
	
	char *lastSlash = strrchr(filePath, '\\');
	if (lastSlash) {
	    size_t dirLen = lastSlash - filePath + 1;
	    strncpy(tempPath, filePath, dirLen);
	    tempPath[dirLen] = '\0'; 
	    strcat(tempPath, "temp.csv"); 
	} else {
	    strcpy(tempPath, "temp.csv");
	}
	
	temp_file = fopen(tempPath, "w");
	if (temp_file == NULL) {
	    perror("Error opening temporary file for writing");
	    fclose(file);
	    return;
	}
	
while (fgets(line, MAX, file) != NULL) { 
    lineNum++;
    line[strcspn(line, "\n")] = '\0'; // remove newline

    if (lineNum == studEdit) {  
        strcpy(editStud.studentNumber, strtok(line, ","));
        strcpy(editStud.FirstName, strtok(NULL, ","));
        strcpy(editStud.LastName, strtok(NULL, ","));

        printf("\nEditing: %s %s (%s)\n", editStud.FirstName, editStud.LastName, editStud.studentNumber);
        printf("[1] Edit student number\n[2] Edit first name\n[3] Edit last name\n[4] Edit All\n");

        while (true) {
            printf("Enter choice: ");
            scanf("%d", &editChoice);
            getchar();

            switch (editChoice) {
                case 1:
                    printf("Enter new student number: ");
                    scanf(" %[^\n]", editStud.studentNumber);
                    break;
                case 2:
                    printf("Enter new first name: ");
                    scanf(" %[^\n]", editStud.FirstName);
                    break;
                case 3:
                    printf("Enter new last name: ");
                    scanf(" %[^\n]", editStud.LastName);
                    break;
                case 4:
                    printf("Enter new student number: ");
                    scanf(" %[^\n]", editStud.studentNumber);
                    printf("Enter new first name: ");
                    scanf(" %[^\n]", editStud.FirstName);
                    printf("Enter new last name: ");
                    scanf(" %[^\n]", editStud.LastName);
                    break;
                default:
                    printf("Invalid choice. No changes made.\n");
            }
            break;
        }
        fprintf(temp_file, "%s,%s,%s\n", editStud.studentNumber, editStud.FirstName, editStud.LastName);
    } else {
        fprintf(temp_file, "%s\n", line);
    }
}

		else {
            fputs(line, temp_file);
//	            fputc('\n', temp_file);
        	}  
        	lineNum++;
	    }

	fclose(file);
	fclose(temp_file);
	
	if (remove(filePath) == 0) {
	    if (rename(tempPath, filePath) != 0) {
	        perror("Error renaming temporary file");
	        return;
	    }
	} else {
	    perror("Error deleting original file");
	    return;
	}
	
	printf("\nStudent %d updated successfully.\n", studEdit);
	getch();
	system(CLEAR_SCREEN);
	
	FILE *studentFile = fopen(filePath, "r");
	if (!studentFile) {
	    perror("Error opening class student file");
	    getch();
	    return;
	}
	
	list->head = NULL;
	list->tail = NULL;
	if (!list_from_csv(list, studentFile)) {
	    fclose(studentFile);
	    return;
	}
	
	fclose(studentFile);
	
	printf("\n Updated List:\n");
	prn_list(list);
	del_list(list);
	lineNum = 0;
	
	printf("\n\nEdit more? \n[1] Yes\n[2] No");
	while(true){
		printf("Enter choice: ");
		scanf("%d", &choice);
		if (choice == 1){
//				printf("lineNum = %d\n", lineNum);
			 goto Editing;
		}
		else if (choice ==2){
			showClass(1);
		}
		else{
			printf("Enter a valid choice.\n");
		}
	}
}


void searchStudent(list_t* list, char s[]) {
    StudentDetails *current = list->head;
    while (current != NULL) {
        if (strcmp(current->LastName, s) == 0) {
            printf("'%s' Found.\n\n", s);
            printf("Student Details: \n\n");

            if (current && strcmp(current->FirstName, "FirstName") == 0 && strcmp(current->LastName, "LastName") == 0) {
                current = current->next;
            }

            printf(" %-15s %-20s %-20s\n", "Student No.", "First Name", "Last Name");
            printf("---------------------------------------------------------------\n");
            printf(" %-15s %-20s %-20s\n", current->studentNumber, current->FirstName, current->LastName);
            printf("---------------------------------------------------------------\n");
            break;
        }
        current = current->next;	 
    }

    if (current == NULL) {
        printf("%s NOT Found.\n", s);
    }
}
   
void deleteStudent(char filePath[], list_t *list) {
	
    FILE *file, *temp_file;
    char line[MAX];
    char tempPath[MAX];  
    int studDelete;
    int current_row = 0, choice;
	
	Deleting:
    printf("\nEnter student to delete (number): ");
    scanf("%d", &studDelete);

    file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    char *lastSlash = strrchr(filePath, '\\');
    if (lastSlash) {
        size_t dirLen = lastSlash - filePath + 1;
        strncpy(tempPath, filePath, dirLen);
        tempPath[dirLen] = '\0'; 
        strcat(tempPath, "temp.csv"); 
    } else {
        strcpy(tempPath, "temp.csv");
    }

    temp_file = fopen(tempPath, "w");
    if (temp_file == NULL) {
        perror("Error opening temporary file for writing");
        fclose(file);
        return;
    }

    while (fgets(line, MAX, file) != NULL) {
        if (current_row != studDelete) {
            fputs(line, temp_file);
        }
        current_row++;
    }

    fclose(file);
    fclose(temp_file);

    if (remove(filePath) == 0) {
        if (rename(tempPath, filePath) != 0) {
            perror("Error renaming temporary file");
            return;
        }
    } else {
        perror("Error deleting original file");
        return;
    }

    printf("\nStudent %d deleted successfully.\n", studDelete);
    system(CLEAR_SCREEN);
    
    FILE *studentFile = fopen(filePath, "r");
    if (!studentFile) {
        perror("Error opening class student file");
        getch();
        return;
    }

    list->head = NULL;
	list->tail = NULL;
    if (!list_from_csv(list, studentFile)) {
        fclose(studentFile);
        return;
    }
    
	fclose(studentFile);
    
    printf("\nUpdated List:\n");
    prn_list(list);
    
    
    del_list(list);
	current_row = 0;
	studDelete = 0;
    printf("\n\nDelete more? \n[1] Yes\n[2] No\nEnter choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        goto Deleting;
    } else {
    	system(CLEAR_SCREEN);	
        showClass(0);
    }
    getch();
}

void deleteClass() {
    Classes tempClass;
    char line[MAX], confirm[10];
    char *token;
    FILE *file, *tempFile;
    int lineNum = 0, totalMatches = 0, choice;
    int matchingLines[MAX];

    file = fopen("classes.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Skip header
    fgets(line, MAX, file);

    int lineCount = 1;
    showClass(1); // Show user's classes only

    while (fgets(line, MAX, file) != NULL) {
        lineCount++;
        line[strcspn(line, "\n")] = 0;

        token = strtok(line, ",");
        if (token != NULL) strcpy(tempClass.courseName, token);
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(tempClass.courseCode, token);
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(tempClass.section, token);
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(tempClass.instructor, token);
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(tempClass.file, token);

        if (strcmp(tempClass.instructor, currentUser) == 0) {
            totalMatches++;
            matchingLines[totalMatches] = lineCount;
        }
    }
    fclose(file);

    if (totalMatches == 0) {
        printf("No classes found for deletion.\n");
        getch();
        return;
    }

    // Ask user which to delete
    do {
        printf("\nEnter class index to delete (type '0' to return): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0) {
            return;
        }

        if (choice < 1 || choice > totalMatches) {
            printf("Invalid choice. Try again.\n");
        } else {
            break;
        }
    } while (true);

    printf("Are you sure you want to delete class [%d]? (y/n): ", choice);
    scanf("%s", confirm);
    if (strcmp(confirm, "y") != 0 && strcmp(confirm, "Y") != 0) {
        printf("Deletion cancelled.\n");
        return;
    }

    int targetLine = matchingLines[choice];

    // Reopen files
    file = fopen("classes.csv", "r");
    tempFile = fopen("temp.csv", "w");

    if (!file || !tempFile) {
        perror("File error");
        return;
    }

    // Copy and delete selected line
    lineNum = 0;
    while (fgets(line, MAX, file) != NULL) {
        lineNum++;
        if (lineNum == targetLine) {
            continue; // Skip this line (deleting)
        }
        fputs(line, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    remove("classes.csv");
    rename("temp.csv", "classes.csv");

    printf("Class deleted successfully!\n");
}
