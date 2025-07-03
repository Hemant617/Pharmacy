#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Medicine {
    int id;
    char name[50];
    int quantity;
    float price;
    char expiry[15];
};

// Check if file is empty
int isFileEmpty(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    return ftell(fp) == 0;
}

// Add medicine
void addMedicine() {
    struct Medicine m;
    FILE *fp = fopen("medicine.txt", "a+");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write header if file is empty
    if (isFileEmpty(fp)) {
        fprintf(fp, "%-5s %-10s %-10s %-10s %-15s\n", "ID", "Name", "Quantity", "Price", "Expiry");
    }

    printf("Enter Medicine ID: ");
    scanf("%d", &m.id);
    printf("Enter Medicine Name: ");
    scanf(" %[^\n]", m.name);
    printf("Enter Quantity: ");
    scanf("%d", &m.quantity);
    printf("Enter Price: ");
    scanf("%f", &m.price);
    printf("Enter Expiry Date (dd-mm-yyyy): ");
    scanf(" %[^\n]", m.expiry);

    fprintf(fp, "%-5d %-10s %-10d %-10.2f %-15s\n", m.id, m.name, m.quantity, m.price, m.expiry);
    fclose(fp);
    printf("Medicine added successfully!\n");
}

// View all medicines
void viewMedicines() {
    char line[200];
    FILE *fp = fopen("medicine.txt", "r");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n--- Medicine Records ---\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

// Update medicine by ID
void updateMedicine() {
    struct Medicine m;
    int id, found = 0;

    FILE *fp = fopen("medicine.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char header[200];
    fgets(header, sizeof(header), fp); // Read header
    fprintf(temp, "%s", header);       // Write header to temp

    printf("Enter Medicine ID to update: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f %s", &m.id, m.name, &m.quantity, &m.price, m.expiry) == 5) {
        if (m.id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", m.name);
            printf("Enter New Quantity: ");
            scanf("%d", &m.quantity);
            printf("Enter New Price: ");
            scanf("%f", &m.price);
            printf("Enter New Expiry Date: ");
            scanf(" %[^\n]", m.expiry);
            found = 1;
        }
        fprintf(temp, "%-5d %-10s %-10d %-10.2f %-15s\n", m.id, m.name, m.quantity, m.price, m.expiry);
    }

    fclose(fp);
    fclose(temp);

    remove("medicine.txt");
    rename("temp.txt", "medicine.txt");

    if (found)
        printf("Medicine updated successfully!\n");
    else
        printf("Medicine with ID %d not found.\n", id);
}

// Delete medicine by ID
void deleteMedicine() {
    struct Medicine m;
    int id, found = 0;

    FILE *fp = fopen("medicine.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char header[200];
    fgets(header, sizeof(header), fp); // Read header
    fprintf(temp, "%s", header);       // Keep header

    printf("Enter Medicine ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d %f %s", &m.id, m.name, &m.quantity, &m.price, m.expiry) == 5) {
        if (m.id == id) {
            found = 1;
            continue;
        }
        fprintf(temp, "%-5d %-10s %-10d %-10.2f %-15s\n", m.id, m.name, m.quantity, m.price, m.expiry);
    }

    fclose(fp);
    fclose(temp);

    remove("medicine.txt");
    rename("temp.txt", "medicine.txt");

    if (found)
        printf("Medicine deleted successfully!\n");
    else
        printf("Medicine with ID %d not found.\n", id);
}

// Main menu
int main() {
    int choice;

    do {
        printf("\n--- Pharmacy Medicine Management System ---\n");
        printf("1. Add Medicine\n");
        printf("2. View Medicines\n");
        printf("3. Update Medicine\n");
        printf("4. Delete Medicine\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMedicine(); break;
            case 2: viewMedicines(); break;
            case 3: updateMedicine(); break;
            case 4: deleteMedicine(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
