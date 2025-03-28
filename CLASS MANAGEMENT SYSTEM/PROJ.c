#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
}Classes;


void front();
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
	                    break;
	                }
	            }
	            fclose(file);
	
	            if (found) {
	                mainMenu();
	            } else {
	                printf("\nInvalid credentials. Please try again.\n");
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
		                        return;
		                    }
		                    fprintf(file, "%s,%s\n", Name, firstPass);
		                    fclose(file);
		                    printf("Account created successfully! Please log in.\n");
		                    goto LOGIN;
		                    break;
		                } else {
		                    printf("Passwords do not match! Try again.\n\n");
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
                // editClassMenu();
                break;
            case 4:
                printf("Returning...\n");
                system(CLEAR_SCREEN);
                return;
                
            default:
                printf("Choice out of bounds, please try again.\n");
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
		    return;
		}
	fprintf(file, "%s,%s\n", addClass.courses, addClass.section);
	fclose(file);
	printf("Class added succesfully!\n\n");
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
	        return;
	    }
	
	    int found = 0;
	    printf("\n\n\n");
	    while (fgets(line, MAX, file) != NULL) {
	    found++;
	    line[strcspn(line, "\n")] = 0;
	
	    token = strtok(line, ","); // Initialize token
	    if (token != NULL) strcpy(showClass.courses, token); 
	                
	    token = strtok(NULL, ",");
	    if (token != NULL) strcpy(showClass.section, token);
	    
	    printf("\t[%d] %s \t%s \n", found, showClass.courses, showClass.section);
	    }
		fclose(file);
		
}

