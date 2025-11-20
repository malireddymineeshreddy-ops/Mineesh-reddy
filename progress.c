#include <stdio.h>
#include <string.h>

#define MAX 100

// ARRAYS TO STORE RECORDS
int ids[MAX];
char names[MAX][100];
char courses[MAX][100];
float totalFee[MAX];
float paidFee[MAX];
float pendingFee[MAX];
char contact[MAX][50];

int count = 0;   // number of records present

// ---------- FUNCTION DECLARATIONS ----------
void addRecord();
void viewRecords();
void searchRecord();
void updateRecord();
void deleteRecord();

// ---------- MAIN FUNCTION ----------
int main() {
    int choice;

    do {
        printf("\n===============================\n");
        printf("    FEE MANAGEMENT SYSTEM\n");
        printf("===============================\n");
        printf("1. Add New Record\n");
        printf("2. View All Records\n");
        printf("3. Search Record\n");
        printf("4. Update Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("-------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: searchRecord(); break;
            case 4: updateRecord(); break;
            case 5: deleteRecord(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}

// ---------- ADD RECORD ----------
void addRecord() {
    int id;

    printf("\nEnter Fee ID: ");
    scanf("%d", &id);
    getchar();

    // Check ID already exists
    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            printf("Error: ID already exists!\n");
            return;
        }
    }

    ids[count] = id;

    printf("Enter Name: ");
    fgets(names[count], 100, stdin);
    names[count][strcspn(names[count], "\n")] = '\0';

    printf("Enter Course: ");
    fgets(courses[count], 100, stdin);
    courses[count][strcspn(courses[count], "\n")] = '\0';

    printf("Enter Total Fee: ");
    scanf("%f", &totalFee[count]);

    printf("Enter Paid Fee: ");
    scanf("%f", &paidFee[count]);
    getchar();

    pendingFee[count] = totalFee[count] - paidFee[count];

    printf("Enter Contact: ");
    fgets(contact[count], 50, stdin);
    contact[count][strcspn(contact[count], "\n")] = '\0';

    count++;

    printf("Record added successfully!\n");
}

// ---------- VIEW ALL RECORDS ----------
void viewRecords() {
    if (count == 0) {
        printf("\nNo records available.\n");
        return;
    }

    printf("\n%-6s %-15s %-10s %-10s %-10s %-10s %-15s\n",
           "ID", "Name", "Course", "Total", "Paid", "Pending", "Contact");

    for (int i = 0; i < count; i++) {
        printf("%-6d %-15s %-10s %-10.2f %-10.2f %-10.2f %-15s\n",
               ids[i], names[i], courses[i],
               totalFee[i], paidFee[i], pendingFee[i], contact[i]);
    }
}

// ---------- SEARCH ----------
void searchRecord() {
    int id;
    int found = 0;

    printf("\nEnter Fee ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            printf("\nRecord Found:\n");
            printf("ID: %d\nName: %s\nCourse: %s\nTotal Fee: %.2f\nPaid Fee: %.2f\nPending: %.2f\nContact: %s\n",
                   ids[i], names[i], courses[i],
                   totalFee[i], paidFee[i], pendingFee[i], contact[i]);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record not found!\n");
}

// ---------- UPDATE RECORD ----------
void updateRecord() {
    int id, found = 0;

    printf("\nEnter Fee ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            found = 1;

            printf("Enter new Paid Fee: ");
            scanf("%f", &paidFee[i]);
            getchar();

            pendingFee[i] = totalFee[i] - paidFee[i];

            printf("Enter new Contact: ");
            fgets(contact[i], 50, stdin);
            contact[i][strcspn(contact[i], "\n")] = '\0';

            printf("Record updated successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Record not found!\n");
}

// ---------- DELETE RECORD ----------
void deleteRecord() {
    int id, found = 0;

    printf("\nEnter Fee ID to delete: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            found = 1;

            // Shift all above
            for (int j = i; j < count - 1; j++) {
                ids[j] = ids[j + 1];
                strcpy(names[j], names[j + 1]);
                strcpy(courses[j], courses[j + 1]);
                totalFee[j] = totalFee[j + 1];
                paidFee[j] = paidFee[j + 1];
                pendingFee[j] = pendingFee[j + 1];
                strcpy(contact[j], contact[j + 1]);
            }

            count--;
            printf("Record deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Record not found!\n");
}