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
	char courses[MAX];
	char section[MAX];
	char instructor[MAX];
}Classes;

//global variables
char currentUser[MAX];

//methods
void front();
void editClass();
void mainMenu();
void addClass();
void showClass();


int main() {
	
	front();
	
	return 0;
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
        scanf("%d", &frChoice);
        
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
	            scanf(" %[^\n]", Password);
	
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
	                    getch();
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

void mainMenu() {
    int choice, menuChoice;
   
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

        printf("\n[1] Add Classes\n[2] Show Classes\n[3] Edit Classes\n[4] Back\n");
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
                printf("\n\n\tGo to menu? [y/n]: ");
				scanf("%s", &menuChoice);
				if(menuChoice == 'y'){
					break;
				}
				else if(menuChoice == 'n'){
					printf("\n\nGoodbye!");
					exit(0);
				}
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
	
	int numClass, i;
	Classes addClass;
	
    FILE *fptr = fopen("addClass.txt", "r");  

    if (fptr == NULL) {  
        return;
    }
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }
    fclose(fptr);  
    
    printf("Enter preferred number of classes to add: ");
    scanf("%d", &numClass);
    
    for (i = 0; i < numClass; i++){
    	printf("Enter course name: ");
    	scanf(" %[^\n]", addClass.courses);
    	printf("Enter course section: ");
    	scanf(" %[^\n]", addClass.section);
    	
    FILE *file = fopen("classes.csv", "a");
		if (file == NULL) {
		    perror("Error opening file");
		     getch();
		    return;
		}
	fprintf(file, "%s,%s,%s\n", addClass.courses, addClass.section, currentUser);
	fclose(file);
	printf("Class added succesfully!\n\n");
	 getch();
	}	
}

void showClass(){
	Classes showClass;
	char line[MAX];
    char *token;
    FILE *file;
    
    FILE *fptr = fopen("showClassArt.txt", "r");  

    if (fptr == NULL) {  
        return;
    }
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }
    fclose(fptr);
	
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

		while (fgets(line, MAX, file) != NULL) {
    	line[strcspn(line, "\n")] = 0;

	    token = strtok(line, ",");
	    if (token != NULL) strcpy(showClass.courses, token); 
	
	    token = strtok(NULL, ",");
	    if (token != NULL) strcpy(showClass.section, token);
	
	    token = strtok(NULL, ",");
	    if (token != NULL) strcpy(showClass.instructor, token);
	
	    if (strcmp(showClass.instructor, currentUser) == 0) {
	        found++;
	        printf("\t[%d] %s \t%s\n", found, showClass.courses, showClass.section);
	    }
}
fclose(file);
		
}

void editClass() {
    Classes editClass, tempClass;
    char line[MAX], newCourse[MAX], newSection[MAX];
    char *token;
    FILE *tempFile;
    int choice, lineNum = 0, editChoice;
    int found = 0;
    char Continue[MAX];
	int matchingLines[MAX]; // holds line numbers in the file for filtered classes
	int totalMatches = 0; //i track ang actual number didto sa csv then gamiton for comparing sa choice ug ang actual number niya sa csv file
	    
	
	FILE *file = fopen("classes.csv", "r");
	
	if (file == NULL) {
	    perror("Error opening file");
	    return;
	}

	// i-Skip ang header
	fgets(line, MAX, file);
	
	int lineCount = 1;
	showClass();//i show ang classes dri
	
	while (fgets(line, MAX, file) != NULL) {//ang kani nga loop is to track ang tinuod nga number niya sa csv
	    lineCount++;
	    line[strcspn(line, "\n")] = 0;
	    token = strtok(line, ",");
	    if (token != NULL) strcpy(tempClass.courses, token);
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
	
	
	printf("\n\nTotal matches: %d\n\n", totalMatches);
	
	if (totalMatches == 0) {
	    printf("No classes found for user.\n");
	    return;
	}

    file = fopen("classes.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
	
	Editing:
	printf("\nEnter the number of class to edit: ");
	scanf("%d", &choice);
	
	if (choice < 1 || choice > totalMatches) {
	    printf("Invalid selection.\n");
	    getch();
	    goto Editing;
	}
	
	int targetLine = matchingLines[choice];

    file = fopen("classes.csv", "r");
	tempFile = fopen("temp.csv", "w");
	lineNum = 0;
	
	while (fgets(line, MAX, file) != NULL) {
    lineNum++;
    line[strcspn(line, "\n")] = 0;
    char tempLine[MAX];
    strcpy(tempLine, line);

    token = strtok(line, ",");
    if (token != NULL) strcpy(editClass.courses, token);
    token = strtok(NULL, ",");
    if (token != NULL) strcpy(editClass.section, token);
    token = strtok(NULL, ",");
    if (token != NULL) strcpy(editClass.instructor, token);
    else strcpy(editClass.instructor, "");

    if (lineNum == targetLine) {
        // Do the editing here
        printf("\nEditing: %s - %s\n", editClass.courses, editClass.section);
        printf("[1] Edit course name\n[2] Edit section\n[3] Edit both\nEnter choice: ");
        scanf("%d", &editChoice);

        switch (editChoice) {
            case 1:
                printf("Enter new course name: ");
                scanf(" %[^\n]", editClass.courses);
                break;
            case 2:
                printf("Enter new section: ");
                scanf(" %[^\n]", editClass.section);
                break;
            case 3:
                printf("Enter new course name: ");
                scanf(" %[^\n]", editClass.courses);
                printf("Enter new section: ");
                scanf(" %[^\n]", editClass.section);
                break;
            default:
                printf("Invalid choice. Skipping edit.\n");
        }

        fprintf(tempFile, "%s,%s,%s\n", editClass.courses, editClass.section, editClass.instructor);
        found = 1;
	} else {
	        fprintf(tempFile, "%s\n", tempLine);
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
        printf("Class not found.\n Continue?: ");
        fgets(Continue, sizeof(Continue), stdin);
        
        for (int i = 0; Continue[i] != '\0'; i++) {//lowercase all inputs
       		Continue[i] = tolower(Continue[i]);
   }
        if(Continue == "yes" || Continue == "y"){
        	goto Editing;
		}
    }

    printf("\nPress any key to continue...");
    getchar(); getchar(); 
}
