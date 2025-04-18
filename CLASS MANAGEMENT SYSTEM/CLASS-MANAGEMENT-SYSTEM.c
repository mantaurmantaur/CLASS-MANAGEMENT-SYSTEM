
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX 100

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
}Classes;

//global variables
char currentUser[MAX];
int choice;


//methods
void front();
void editClass();
void mainMenu();
void addClass();
void showClass();
void openClass();
void getPassword();
void showArt(FILE *fptr);




int main() {
	
	front();
	
	return 0;
}

void showArt(FILE *fptr){
	    if (fptr == NULL) {  
	        return;
	    }
	    char ch;
	    while ((ch = fgetc(fptr)) != EOF) {
	        putchar(ch);
	    }
	    fclose(fptr);
}

void front() {
    logInCredentials logIn;
    int frChoice;
    char Name[MAX], Password[MAX], conPass[MAX], firstPass[MAX];
    char compName[MAX], compPass[MAX];
    char line[MAX];
    char *token;
    FILE *file;
    
    do {
    	system(CLEAR_SCREEN);
	    
	   FILE *fptr = fopen("menuArt.txt" , "r");  
	   showArt(fptr);
	   
	        printf("Select operation:\n");
	        printf("[1] LOG-IN\n[2] SIGN UP\n[3] EXIT\n\n");
	        printf("Enter choice: ");
	        scanf("%d", &frChoice);
	        
	        switch(frChoice){
	        	case 1: 
	        		{
	        		LOGIN:
	        		system(CLEAR_SCREEN);
	        		  FILE *fptr = fopen("loginArt.txt" , "r");  
	   				showArt(fptr);
	    			
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
		            	printf("ABot ko dri");
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
		   			showArt(fptr);
	    			
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
   
    do {
    	system(CLEAR_SCREEN);
    	
      FILE *fptr = fopen("menuArt.txt" , "r");  
	   showArt(fptr); 

        printf("\n[1] Add Classes\n[2] Show Classes\n[3] Edit Classes\n[4] Log Out\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

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
                getch();
                system(CLEAR_SCREEN);
                return;
                
            default:
                printf("Choice out of bounds, please try again.\n");
                getch();
        }
    } while (choice != 4);
}

void addClass(){
	
	int numClass, i, choice;
	Classes addClass;
	
    FILE *fptr = fopen("addClass.txt", "r");  
	showArt(fptr); 
    
    printf("\t\tCurrent Classes");
    showClass(3);
    Adding:
    printf("\n\nEnter preferred number of classes to add: ");
    scanf("%d", &numClass);
    
    for (i = 0; i < numClass; i++){
    	printf("\nEnter course name: ");
    	scanf(" %[^\n]", addClass.courseName);
    	printf("Enter course code: ");
    	scanf(" %[^\n]", addClass.courseCode);
    	printf("Enter course section: ");
    	scanf(" %[^\n]", addClass.section);
    	
    FILE *file = fopen("classes.csv", "a");
		if (file == NULL) {
		    perror("Error opening file");
		     getch();
		    return;
		}
	fprintf(file, "%s,%s,%s,%s\n", addClass.courseName, addClass.courseCode, addClass.section, currentUser);
	fclose(file);
	printf("\nClass added succesfully!\n\n");
	}
	
	printf("Add more? \n[1] Yes\n[2] No\nEnter choice: ");
	scanf("%d", &choice);
	if(choice == 1)
	{
		goto Adding;
	}	
	else
		getch();

}

void showClass(int indicator){
	Classes showClass;
	char line[MAX];
    char *token;
    FILE *file;
    
    if(indicator == 3)
    	goto showClasses;
    FILE *fptr = fopen("showClassArt.txt", "r");  
	   showArt(fptr);
	
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
	printf("---------------------------------------------------------------\n");	
	fclose(file);
	
	if(indicator == 1 || indicator == 3){
		return;
	}
	else{
		printf("\n\n[1] Open a class\t [2] Back\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		
		if(choice==1){
			openClass();
		}
		else
			return;
	}
}

void openClass(){
	//need pa code, hihi
}

void editClass() {
    Classes editClass, tempClass;
    char line[MAX], newCourse[MAX], newSection[MAX], newCourseCode[MAX];
    char *token;
    FILE *tempFile;
    int lineNum = 0, editChoice;
    int found = 0;
    char Continue[MAX];
	int matchingLines[MAX]; // holds line numbers in the file for filtered classes
	int totalMatches = 0; //i track ang actual number didto sa csv then gamiton for comparing sa choice ug ang actual number niya sa csv file
	    
	
	FILE *file = fopen("classes.csv", "r");
	
	if (file == NULL) {
	    perror("Error opening file");
	    return;
	}
	openEdit:
	// i-Skip ang header
	fgets(line, MAX, file);
	
	int lineCount = 1;
	showClass(1);//i show ang classes dri
	
	while (fgets(line, MAX, file) != NULL) {//ang kani nga loop is to assign data into their designated variable, track ang tinuod nga number niya sa csv
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
	
	    if (strcmp(tempClass.instructor, currentUser) == 0) {
	        totalMatches++;
	        matchingLines[totalMatches] = lineCount;
	    }
	}
	fclose(file);
	
	
//	printf("\n\nTotal matches: %d\n\n", totalMatches);
	
	if (totalMatches == 0) {
	    printf("No classes found for user.\n");
	    getch();
	    return;
	}

    file = fopen("classes.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        getch();
        return;
    }
	
	Editing:
	printf("\nEnter the number of class to edit: ");
	scanf("%d", &choice);
	
	 tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        fclose(file);
        perror("Error creating temporary file");
        return;
    }
	
	if (choice < 1 || choice > totalMatches) {
	    printf("Invalid selection.\n");
	    getch();
	    goto Editing;
	}
	
	
	lineNum = 0;
	int targetLine = matchingLines[choice];
	
     while (fgets(line, MAX, file) != NULL) {
        lineNum++;
        line[strcspn(line, "\n")] = '\0'; 
        
        if (lineNum == targetLine) {
            
            strcpy(editClass.courseName, strtok(line, ","));
            strcpy(editClass.courseCode, strtok(NULL, ","));
            strcpy(editClass.section, strtok(NULL, ","));
            strcpy(editClass.instructor, strtok(NULL, ","));

            printf("\nEditing: %s - %s - %s\n", editClass.courseName, editClass.courseCode, editClass.section);
            printf("[1] Edit course name\n[2] Edit course code\n[3] Edit section\n[4] Edit All\nEnter choice: ");
            scanf("%d", &editChoice);
            getchar();

            switch (editChoice) {
                case 1:
                    printf("Enter new course name: ");
                    scanf(" %[^\n]", editClass.courseName);
                    break;
                case 2:
                    printf("Enter new course code: ");
                    scanf(" %[^\n]", editClass.courseCode);
                    break;
                case 3:
                    printf("Enter new section: ");
                    scanf(" %[^\n]", editClass.section);
                    break;
                case 4:
                    printf("Enter new course name: ");
                    scanf(" %[^\n]", editClass.courseName);
                    printf("Enter new course code: ");
                    scanf(" %[^\n]", editClass.courseCode);
                    printf("Enter new section: ");
                    scanf(" %[^\n]", editClass.section);
                    break;
                default:
                    printf("Invalid choice. No changes made.\n");
            }

            fprintf(tempFile, "%s,%s,%s,%s\n", editClass.courseName, editClass.courseCode, 
                    editClass.section, editClass.instructor);
            found = 1;
        } else {
            fputs(line, tempFile);
            fputc('\n', tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("classes.csv");
        rename("temp.csv", "classes.csv");
        printf("Class updated successfully!\n");
    } else {
        remove("temp.csv");
    }
	
	printf("\n\nContinue Editing?\n[1] Yes\t    [2] No\n\n Enter choice: ");
    scanf("%d", &choice);
    if(choice==1)
    {
        system(CLEAR_SCREEN);
        goto openEdit;
    }
    else
    	return;
}

       
