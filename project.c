#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CROPS 5
#define MAX_FARMERS 100
#define MAX_BIDDERS 100

typedef struct
{
    int id;
    char name[50];
    float crops[MAX_CROPS];
} Farmer;

typedef struct
{
    int id;
    char name[50];
    int farmerId;
    float bids[MAX_CROPS];
} Bidder;

const char *cropNames[MAX_CROPS] = {"Wheat", "Rice", "Bajra", "Corn", "Sugarcane"};

// Utility function to save all farmers to the CSV file
void saveAllFarmers(Farmer farmers[], int count)
{
    FILE *file = fopen("farmers.csv", "w");
    if (!file)
    {
        perror("Unable to open file for saving farmers.");
        return;
    }
    for (int i = 0; i < count; ++i)
    {
        fprintf(file, "%d,%s", farmers[i].id, farmers[i].name);
        for (int j = 0; j < MAX_CROPS; ++j)
        {
            fprintf(file, ",%.2f", farmers[i].crops[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Utility function to save all bidders to the CSV file
void saveAllBidders(Bidder bidders[], int count)
{
    FILE *file = fopen("bidders.csv", "w");
    if (!file)
    {
        perror("Unable to open file for saving bidders.");
        return;
    }
    for (int i = 0; i < count; ++i)
    {
        fprintf(file, "%d,%s,%d", bidders[i].id, bidders[i].name, bidders[i].farmerId);
        for (int j = 0; j < MAX_CROPS; ++j)
        {
            fprintf(file, ",%.2f", bidders[i].bids[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Load farmers from file
int loadFarmers(Farmer farmers[])
{
    FILE *file = fopen("farmers.csv", "r");
    int count = 0;
    if (!file)
    {
        return 0;
    }
    while (fscanf(file, "%d,%[^,],%f,%f,%f,%f,%f", &farmers[count].id, farmers[count].name,
                  &farmers[count].crops[0], &farmers[count].crops[1], &farmers[count].crops[2],
                  &farmers[count].crops[3], &farmers[count].crops[4]) != EOF)
    {
        count++;
    }
    fclose(file);
    return count;
}

// Load bidders from file
int loadBidders(Bidder bidders[])
{
    FILE *file = fopen("bidders.csv", "r");
    int count = 0;
    if (!file)
    {
        return 0;
    }
    while (fscanf(file, "%d,%[^,],%d,%f,%f,%f,%f,%f", &bidders[count].id, bidders[count].name, &bidders[count].farmerId,
                  &bidders[count].bids[0], &bidders[count].bids[1], &bidders[count].bids[2],
                  &bidders[count].bids[3], &bidders[count].bids[4]) != EOF)
    {
        count++;
    }
    fclose(file);
    return count;
}

// Display all farmers in a formatted table
void displayFarmers(Farmer farmers[], int count)
{
    printf("\n====================================== Farmers ======================================\n");
    printf("ID   | Name                       | ");
    for (int i = 0; i < MAX_CROPS; ++i)
    {
        printf("%-10s", cropNames[i]);
    }
    printf("\n--------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; ++i)
    {
        printf("%-4d | %-25s | ", farmers[i].id, farmers[i].name);
        for (int j = 0; j < MAX_CROPS; ++j)
        {
            printf("%-10.2f", farmers[i].crops[j]);
        }
        printf("\n");
    }
    printf("=======================================================================================\n");
}

// Display all bidders in a formatted table
void displayBidders(Bidder bidders[], int count)
{
    printf("\n====================================== Bidders ======================================\n");
    printf("ID   | Name                       | Farmer ID | ");
    for (int i = 0; i < MAX_CROPS; ++i)
    {
        printf("%-10s", cropNames[i]);
    }
    printf("\n--------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; ++i)
    {
        printf("%-4d | %-25s | %-9d | ", bidders[i].id, bidders[i].name, bidders[i].farmerId);
        for (int j = 0; j < MAX_CROPS; ++j)
        {
            printf("%-10.2f", bidders[i].bids[j]);
        }
        printf("\n");
    }
    printf("================================================================================================\n");
}

// Add a new farmer
void addFarmer(Farmer farmers[], int *count)
{
    Farmer f;
    int id;
    char name[50];
    printf("Enter Farmer ID: ");
    scanf("%d", &id);
    printf("Enter Farmer Name: ");
    scanf(" %49[^\n]", name);
    strncpy(f.name, name, 50 - 1);
    f.id = id;
    printf("\n");

    printf("Enter the price for each crop (0 if not grown):\n");
    for (int i = 0; i < MAX_CROPS; ++i)
    {
        printf("%s: ", cropNames[i]);
        scanf("%f", &f.crops[i]);
    }
    farmers[(*count)++] = f;
    saveAllFarmers(farmers, *count);
}

// Add a new bidder
void addBidder(Bidder bidders[], int *count)
{
    Bidder b;
    printf("Enter Bidder ID: ");
    scanf("%d", &b.id);
    printf("Enter Bidder Name: ");
    scanf(" %49[^\n]", b.name);
    printf("Enter Farmer ID to bid on: ");
    scanf("%d", &b.farmerId);

    for (int i = 0; i < MAX_CROPS; ++i)
    {
        printf("%s: ", cropNames[i]);
        scanf("%f", &b.bids[i]);
    }
    bidders[(*count)++] = b;
    saveAllBidders(bidders, *count);
}

// Delete a farmer
void deleteFarmer(Farmer farmers[], int *count, int id)
{
    int index = -1;
    for (int i = 0; i < *count; ++i)
    {
        if (farmers[i].id == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Farmer not found.\n");
        return;
    }

    for (int i = index; i < *count - 1; ++i)
    {
        farmers[i] = farmers[i + 1];
    }
    (*count)--;
    saveAllFarmers(farmers, *count);
    printf("Farmer deleted successfully.\n");
}

// Delete a bidder
void deleteBidder(Bidder bidders[], int *count, int id)
{
    int index = -1;
    for (int i = 0; i < *count; ++i)
    {
        if (bidders[i].id == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Bidder not found.\n");
        return;
    }

    for (int i = index; i < *count - 1; ++i)
    {
        bidders[i] = bidders[i + 1];
    }
    (*count)--;
    saveAllBidders(bidders, *count);
    printf("Bidder deleted successfully.\n");
}

// Display all payments made by bidders to farmers
void displayPayments(Farmer farmers[], int farmerCount, Bidder bidders[], int bidderCount)
{
    for (int i = 0; i < bidderCount; ++i)
    {
        printf("Bidder %s has bid on Farmer ID %d's crops:\n", bidders[i].name, bidders[i].farmerId);
        for (int j = 0; j < farmerCount; ++j)
        {
            if (farmers[j].id == bidders[i].farmerId)
            {
                for (int k = 0; k < MAX_CROPS; ++k)
                {
                    if (bidders[i].bids[k] > 0)
                    {
                        printf("%s: %.2f\n", cropNames[k], bidders[i].bids[k]);
                    }
                }
                printf("\n");
            }
        }
    }
}

int main()
{
    Farmer farmers[MAX_FARMERS];
    Bidder bidders[MAX_BIDDERS];
    int farmerCount = loadFarmers(farmers);
    int bidderCount = loadBidders(bidders);

    int choice;
    while (1)
    {
        printf("\n1. Add Farmer\n");
        printf("2. Add Bidder\n");
        printf("3. Delete Farmer\n");
        printf("4. Delete Bidder\n");
        printf("5. Display Farmers\n");
        printf("6. Display Bidders\n");
        printf("7. Display Payments\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            addFarmer(farmers, &farmerCount);
        }
        else if (choice == 2)
        {
            addBidder(bidders, &bidderCount);
        }
        else if (choice == 3)
        {
            int id;
            printf("Enter Farmer ID to delete: ");
            scanf("%d", &id);
            deleteFarmer(farmers, &farmerCount, id);
        }
        else if (choice == 4)
        {
            int id;
            printf("Enter Bidder ID to delete: ");
            scanf("%d", &id);
            deleteBidder(bidders, &bidderCount, id);
        }
        else if (choice == 5)
        {
            displayFarmers(farmers, farmerCount);
        }
        else if (choice == 6)
        {
            displayBidders(bidders, bidderCount);
        }
        else if (choice == 7)
        {
            displayPayments(farmers, farmerCount, bidders, bidderCount);
        }
        else if (choice == 8)
        {
            break;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
