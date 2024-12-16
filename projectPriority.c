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

typedef struct
{
    int bidderId;
    int farmerId;
    char bidderName[50];
    float bidAmount;
} Bid;

typedef struct
{
    Bid data[MAX_BIDDERS];//bid type ka array hai 
    int size;//priority ki size upadate ke liye
} PriorityQueue;

const char *cropNames[MAX_CROPS] = {"Wheat", "Rice", "Bajra", "Corn", "Sugarcane"};//crops ka name nhi badal sakta

// Initialize a priority queue
void initializePriorityQueue(PriorityQueue *pq)
{
    pq->size = 0;
}

// Insert a bid into the priority queue (sorted in descending order)
void insertBid(PriorityQueue *pq, int bidderId, int farmerId, const char *bidderName, float bidAmount)
{
    pq->data[pq->size].bidderId = bidderId;
    pq->data[pq->size].farmerId = farmerId;
    strcpy(pq->data[pq->size].bidderName, bidderName);
    pq->data[pq->size].bidAmount = bidAmount;
    pq->size++;

    // Sorting bids in descending order (max-heap behavior)
    for (int i = pq->size - 1; i > 0 && pq->data[i].bidAmount > pq->data[i - 1].bidAmount; i--)
    {
        Bid temp = pq->data[i];
        pq->data[i] = pq->data[i - 1];
        pq->data[i - 1] = temp;
    }
}

// Display the highest bidders for each crop and for each farmer
void displayHighestBidders(Farmer farmers[], int farmerCount, Bidder bidders[], int bidderCount)
{
    PriorityQueue cropQueues[MAX_CROPS];//5 size ka array h,bid data ka array h , int size store or har ek bid data bhi array hai jiske ander bideer id...
    for (int i = 0; i < MAX_CROPS; ++i)
    {
        initializePriorityQueue(&cropQueues[i]);//pointer pass krna h 
    }

    // Insert bids into the priority queues
    for (int i = 0; i < bidderCount; ++i)
    {
        for (int j = 0; j < MAX_CROPS; ++j)
        {
            if (bidders[i].bids[j] > 0)//biding price not lees then 0
            {
                insertBid(&cropQueues[j], bidders[i].id, bidders[i].farmerId, bidders[i].name, bidders[i].bids[j]);
            }
        }
    }

    // Display the highest bidder for each crop
    printf("\n====================== Highest Bidders by Crop =======================\n");
    for (int i = 0; i < MAX_CROPS; ++i)
    {
        if (cropQueues[i].size > 0)
        {
            printf("%-10s:\n", cropNames[i]);
            printf("Top Bidder: %s with a bid of %.2f (Farmer ID: %d)\n", 
                   cropQueues[i].data[0].bidderName, // 0 pq mai highest pr hoga
                   cropQueues[i].data[0].bidAmount, 
                   cropQueues[i].data[0].farmerId);
            printf("----------------------------------------------------------------------\n");
        }
        else
        {
            printf("%-10s: No bids\n", cropNames[i]);
        }
    }
    printf("=======================================================================\n");

    // Display the highest bidders for each farmer
    printf("\n====================== Highest Bidders by Farmer =====================\n");
    for (int i = 0; i < farmerCount; ++i)
    {
        printf("Farmer: %s (ID: %d)\n", farmers[i].name, farmers[i].id);
        int foundBid = 0;//farmer ke liye bid mila ya nhi
        for (int j = 0; j < MAX_CROPS; ++j)
        {
            if (cropQueues[j].size > 0)
            {
                for (int k = 0; k < cropQueues[j].size; ++k)
                {
                    if (cropQueues[j].data[k].farmerId == farmers[i].id)
                    {
                        printf("Crop: %s | Top Bidder: %s | Bid Amount: %.2f\n",
                               cropNames[j], cropQueues[j].data[k].bidderName, cropQueues[j].data[k].bidAmount);
                        foundBid = 1;
                    }
                }
            }
        }
        if (!foundBid)
        {
            printf("No bids for this farmer.\n");
        }
        printf("----------------------------------------------------------------------\n");
    }
    printf("=======================================================================\n");
}

// Utility function to save all farmers to the CSV file
void saveAllFarmers(Farmer farmers[], int count)//csv ka row and colum
{
    FILE *file = fopen("farmers.csv", "w");
    if (!file)
    {
        perror("Unable to open file for saving farmers.");//file ka error ko print krane ker liye
        return;
    }
    for (int i = 0; i < count; ++i)//farmer ki id ke liye
    {
        fprintf(file, "%d,%s", farmers[i].id, farmers[i].name);
        for (int j = 0; j < MAX_CROPS; ++j)//crops ki price ke liye loop
        {
            fprintf(file, ",%.2f", farmers[i].crops[j]);//file mai prices ko print krane ke liye
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
int loadFarmers(Farmer farmers[])//csv file se fearmer ka data load, karva lega uplod progra ai ho jayega,fir dubara save kr denge
{
    FILE *file = fopen("farmers.csv", "r");
    int count = 0;
    if (!file)
    {
        return 0;
    }
    while (fscanf(file, "%d,%[^,],%f,%f,%f,%f,%f", &farmers[count].id, farmers[count].name,//load krne ke liyee scan kr rha hai
                  &farmers[count].crops[0], &farmers[count].crops[1], &farmers[count].crops[2],//ye inform load hoga
                  &farmers[count].crops[3], &farmers[count].crops[4]) != EOF)//end of file
    {
        count++;//farmer ki ginti quki 100 se uper nhi
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
    printf("=======================================================================================\n");
}

// Add a new farmer
void addFarmer(Farmer farmers[], int *count)
{
    if (*count >= MAX_FARMERS)
    {
        printf("Maximum number of farmers reached.\n");
        return;
    }

    Farmer newFarmer;
    int isUnique = 0;

    while (!isUnique)
    {
        isUnique = 1;
        printf("Enter Farmer ID: ");
        scanf("%d", &newFarmer.id);

        for (int i = 0; i < *count; ++i)
        {
            if (farmers[i].id == newFarmer.id)
            {
                printf("This ID already exists. Please enter a different ID for the farmer.\n");
                isUnique = 0;
                break;
            }
        }
    }

    printf("Enter farmer's name: ");
    scanf(" %[^\n]", newFarmer.name);
    printf("Enter crop prices (Wheat, Rice, Bajra, Corn, Sugarcane and 0 if not grown): \n");
    for (int i = 0; i < MAX_CROPS; ++i)
    {
        printf("%s: ", cropNames[i]);
        scanf("%f", &newFarmer.crops[i]);
    }

    farmers[*count] = newFarmer;
    (*count)++;
    saveAllFarmers(farmers, *count);
}

// Add a new bidder
void addBidder(Bidder bidders[], int *count)
{
    if (*count >= MAX_BIDDERS)
    {
        printf("Maximum number of bidders reached.\n");
        return;
    }
    Bidder newBidder;
    //newBidder.id = *count + 1;
    printf("Enter Bidder ID: ");
    scanf("%d", &newBidder.id);
    printf("Enter bidder's name: ");
    scanf(" %[^\n]", newBidder.name);
    printf("Enter farmer ID to bid on: ");
    scanf("%d", &newBidder.farmerId);
    printf("Enter bid amounts (Wheat, Rice, Bajra, Corn, Sugarcane): \n");
    for (int i = 0; i < MAX_CROPS; ++i)
    {
        printf("%s: ", cropNames[i]);
        scanf("%f", &newBidder.bids[i]);
    }
    bidders[*count] = newBidder;
    (*count)++;
    saveAllBidders(bidders, *count);
}

void updateFarmer(Farmer farmers[], int count) 
{
    int id;
    printf("Enter the Farmer ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++)
    {
        if (farmers[i].id == id)
        {
            printf("Enter new name for the Farmer: ");
            scanf(" %[^\n]", farmers[i].name);
            printf("Enter new production values for each crop:\n");
            for (int j = 0; j < MAX_CROPS; j++)
            {
                printf("%s: ", cropNames[j]);
                scanf("%f", &farmers[i].crops[j]);
            }
            saveAllFarmers(farmers, count);
            printf("Farmer updated successfully.\n");
            return;
        }
    }
    printf("Farmer with ID %d not found.\n", id);
}

// Function to update bidder information
void updateBidder(Bidder bidders[], int count)
{
    int id;
    printf("Enter the Bidder ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++)
    {
        if (bidders[i].id == id)
        {
            printf("Enter new name for the Bidder: ");
            scanf(" %[^\n]", bidders[i].name);
            printf("Enter new Farmer ID for this Bidder: ");
            scanf("%d", &bidders[i].farmerId);
            printf("Enter new bid values for each crop:\n");
            for (int j = 0; j < MAX_CROPS; j++)
            {
                printf("%s: ", cropNames[j]);
                scanf("%f", &bidders[i].bids[j]);
            }
            saveAllBidders(bidders, count);
            printf("Bidder updated successfully.\n");
            return;
        }
    }
    printf("Bidder with ID %d not found.\n", id);
}

// Delete a farmer by ID
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
        printf("Farmer with ID %d not found.\n", id);
        return;
    }
    for (int i = index; i < *count - 1; ++i)
    {
        farmers[i] = farmers[i + 1];
    }
    (*count)--;
    saveAllFarmers(farmers, *count);
}

// Delete a bidder by ID
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
        printf("Bidder with ID %d not found.\n", id);
        return;
    }
    for (int i = index; i < *count - 1; ++i)
    {
        bidders[i] = bidders[i + 1];
    }
    (*count)--;
    saveAllBidders(bidders, *count);
}

int main()
{
    Farmer farmers[MAX_FARMERS];//100 ka farmer type ka array bna diya
    Bidder bidders[MAX_BIDDERS];
    int farmerCount = loadFarmers(farmers); //loading farmers (both loading and counting)
    int bidderCount = loadBidders(bidders); //loading bidders (both loading and counting)

    int choice;
    while (1)
    {
        printf("\n1. Add Farmer\n");
        printf("2. Add Bidder\n");
        printf("3. Delete Farmer\n");
        printf("4. Delete Bidder\n");
        printf("5. Display Farmers\n");
        printf("6. Display Bidders\n");
        printf("7. Update Farmers\n");
        printf("8. Update Bidders\n");
        printf("9. Display Highest Bidders\n");
        printf("10. Exit\n");
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
            updateFarmer(farmers, farmerCount);
        }
        else if (choice == 8)
        {
            updateBidder(bidders, bidderCount);
        }
        else if (choice == 9)
        {
            displayHighestBidders(farmers, farmerCount, bidders, bidderCount);
        }
        else if (choice == 10)
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
