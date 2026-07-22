
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // For converting string to number
#include <sys/stat.h>

int main() {
    char user[20], pass[20], data[100], perm_str[4], choice;
    FILE *f;

    // 1. Authentication
    printf("Username: "); scanf("%s", user);
    printf("Password: "); scanf("%s", pass);
    if (strcmp(user, "admin") != 0 || strcmp(pass, "123") != 0) {
        printf("Access Denied\n"); return 1;
    }
    printf("Access Granted\n\n");

    // 2. Ask what to write
    printf("Enter text to write: "); 
    scanf(" %[^\n]", data);  // Read whole line including spaces
    
    // Fixed path from repo root (works everywhere)
    f = fopen("task3/output/secure.txt", "w");
    if (f == NULL) { printf("Error creating file!\n"); return 1; }
    fprintf(f, "%s", data);
    fclose(f); 
    printf("File written.\n");

    // 3. Ask what permissions to set (e.g. 754)
    printf("Enter permission (e.g. 754): "); scanf("%s", perm_str);
    // Convert text "754" to octal number 0754 for the system
    int perm = (int)strtol(perm_str, NULL, 8);
    chmod("task3/output/secure.txt", perm);
    printf("Permissions set to %s.\n", perm_str);

    // 4. Read file
    f = fopen("task3/output/secure.txt", "r");
    if (f == NULL) { printf("Error reading file!\n"); return 1; }
    fscanf(f, "%[^\n]", data);
    fclose(f);
    printf("Read data: %s\n", data);

    // 5. Delete with yes/no
    printf("Delete file? (y/n): "); scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        remove("task3/output/secure.txt");
        printf("File deleted.\n");
    } else {
        printf("Deletion cancelled.\n");
    }

    return 0;
}
