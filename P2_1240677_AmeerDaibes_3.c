/*
    Ameer Daibes
    1240677
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 101

typedef struct
{
    char *name;
    int number;
    char *address;
    int apartments;
    int year;
    char *paid;
} ApartmentBuilding;

typedef struct AVLNode
{
    ApartmentBuilding data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef struct
{
    ApartmentBuilding data;
    int status;   // (0,1,2) = (empty, occupied, deleted)
} Hash;

int height(AVLNode *node) // Returns the height of a node, If null: Height = 0
{
    if(node == NULL)
        return 0;
    return node->height;
}


int maxxx(int a, int b) // Returns the larger value between two integers
{
    if(a > b)
        return a;
    return b;
}


AVLNode* createNode(ApartmentBuilding building) //new AVL node and stores the building info in it
{
    AVLNode *newNode = (AVLNode*)malloc(sizeof(AVLNode)); // Allocate

    newNode->data.name = (char*)malloc(strlen(building.name) + 1);
    strcpy(newNode->data.name, building.name);

    newNode->data.address = (char*)malloc(strlen(building.address) + 1);
    strcpy(newNode->data.address, building.address);

    newNode->data.paid = (char*)malloc(strlen(building.paid) + 1);
    strcpy(newNode->data.paid, building.paid);

    newNode->data.number = building.number;
    newNode->data.apartments = building.apartments;
    newNode->data.year = building.year;

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // Every new node starts with height 1
    return newNode;
}


int getBalance(AVLNode *node) // Calc the balance fact of a node
{
    if(node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}


AVLNode* rightRotate(AVLNode *y) // Performs a right rotation
{
    AVLNode *x = y->left; // x is the new root of this subtree
    AVLNode *T2 = x->right; // Save x's right subtree
    x->right = y; // Perform rotation
    y->left = T2;
    y->height = 1 + maxxx(height(y->left), height(y->right)); // Update height of y
    x->height = 1 + maxxx(height(x->left), height(x->right)); // Update height of x
    return x;
}

// Performs a left rotation
AVLNode* leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;// y becomes the new root of this subtree
    AVLNode *T2 = y->left; // Save y's left subtree
    y->left = x; // Perform rotation
    x->right = T2;
    x->height = 1 + maxxx(height(x->left), height(x->right));  // Update height of x
    y->height = 1 + maxxx(height(y->left), height(y->right)); // Update height of y
    return y;
}


AVLNode* insertAVL(AVLNode *root, ApartmentBuilding building) //insert
{
    
    if(root == NULL) // If the tree is empty, create a new node
        return createNode(building);

    if(strcmp(building.name, root->data.name) < 0) // Insert to left subtree
        root->left = insertAVL(root->left, building);

    else if(strcmp(building.name, root->data.name) > 0) // Insert into right subtree
        root->right = insertAVL(root->right, building);

    else
        return root;

    root->height = 1 + maxxx(height(root->left), height(root->right)); // Update height of current node

    int balance = getBalance(root);

    if(balance > 1 && strcmp(building.name, root->left->data.name) < 0) // Left Left Case
        return rightRotate(root);

    
    if(balance < -1 && strcmp(building.name, root->right->data.name) > 0) // Right Right Case
        return leftRotate(root);

    
    if(balance > 1 && strcmp(building.name, root->left->data.name) > 0) // Left Right Case
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance < -1 && strcmp(building.name, root->right->data.name) < 0) // Right Left Case
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void inorderTraversal(AVLNode *root) // Prints the buildings in alphabetical order
{
    if(root == NULL)
        return;

    inorderTraversal(root->left);
    printf("\nName: %s\n", root->data.name);
    printf("Number: %d\n", root->data.number);
    printf("Address: %s\n", root->data.address);
    printf("Apartments: %d\n", root->data.apartments);
    printf("Year: %d\n", root->data.year);
    printf("Paid Fees: %s\n", root->data.paid);
    inorderTraversal(root->right);
}


int stringToInt(char str[]) // Converts a num string to an integer
{
    int num = 0;
    int i = 0;
    while(str[i] != '\0')
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return num;
}

// Reads buildings from info.txt and inserts them into the AVL tree
AVLNode* loadFromFile(AVLNode *root)
{
    FILE *file = fopen("info.txt", "r");

    if(file == NULL)
    {
        printf("Cannot open info.txt\n");
        return root;
    }

    ApartmentBuilding building;
    char line[300];
    char temp[20];

    char name[100];
    char address[100];
    char paid[10];

    while(fgets(line, sizeof(line), file))// Read each line from the file until end of file is reached
    {
        int i = 0;
        int j = 0;

        // Read building name
        while(line[i] != ':')
        {
            name[j] = line[i];
            i++;
            j++;
        }
        name[j] = '\0';
        i++;

        // Read building number
        j = 0;
        while(line[i] != ':')
        {
            temp[j] = line[i];
            i++;
            j++;
        }
        temp[j] = '\0';
        building.number = stringToInt(temp);// casts a string of number/s into its integer value
        i++;

        // Read address
        j = 0;
        while(line[i] != ':')
        {
            address[j] = line[i];
            i++;
            j++;
        }
        address[j] = '\0';
        i++;

        // Read apartments
        j = 0;
        while(line[i] != ':')
        {
            temp[j] = line[i];
            i++;
            j++;
        }
        temp[j] = '\0';
        building.apartments = stringToInt(temp);
        i++;

        // Read year
        j = 0;
        while(line[i] != ':')
        {
            temp[j] = line[i];
            i++;
            j++;
        }
        temp[j] = '\0';
        building.year = stringToInt(temp);
        i++;

        // Read paid fees
        j = 0;
        while(line[i] != '\n' && line[i] != '\0')
        {
            paid[j] = line[i];
            i++;
            j++;
        }
        paid[j] = '\0';

        building.name = (char*)malloc(strlen(name) + 1);
        strcpy(building.name, name);

        building.address = (char*)malloc(strlen(address) + 1);
        strcpy(building.address, address);

        building.paid = (char*)malloc(strlen(paid) + 1);
        strcpy(building.paid, paid);

        root = insertAVL(root, building);

        free(building.name);
        free(building.address);
        free(building.paid);
    }

    fclose(file);

    return root;
}


// Searches for a building by name
AVLNode* searchBuilding(AVLNode *root, char name[])
{
    if(root == NULL)// building not found
        return NULL;

    if(strcmp(name, root->data.name) == 0)
        return root;

    if(strcmp(name, root->data.name) < 0)
        return searchBuilding(root->left, name);

    return searchBuilding(root->right, name);
    /*
    searches for a building in the AVL tree using its name.
    the function compares the target name with the current node's name using strcmp().
    if strcmp() returns 0, the names are equal and the building is found.
    if it returns a value less than 0, the target name comes before the current node's
    name alphabetically, so the search continues in the left subtree. Otherwise, the
    target name comes after the current node's name alphabetically, so the search
    continues in the right subtree. The function returns a pointer to the matching
    node if found, or NULL if the building does not exist in the tree.
*/
}

// Reads a string including spaces until Enter is pressed
void readString(char str[])
{
    int i = 0;
    char ch;

    do
    {
        scanf("%c", &ch);
    }
    while(ch == '\n');

    while(ch != '\n')
    {
        str[i] = ch;
        i++;

        scanf("%c", &ch);
    }

    str[i] = '\0';
}

// Searches for a building and displays all its information
void searchAndDisplay(AVLNode *root)
{
    char name[100];
    char choice;

    printf("Enter building name to search: ");
    readString(name);

    AVLNode *result = searchBuilding(root, name);

    if(result == NULL)
    {
        printf("\nBuilding not found.\n");
        return;
    }

    printf("\nBuilding Information:\n");
    printf("Name: %s\n", result->data.name);
    printf("Number: %d\n", result->data.number);
    printf("Address: %s\n", result->data.address);
    printf("Apartments: %d\n", result->data.apartments);
    printf("Year: %d\n", result->data.year);
    printf("Paid Fees: %s\n", result->data.paid);

    printf("\nDo you want to update this building? (y/n): ");
    scanf(" %c", &choice);

    if(choice == 'y' || choice == 'Y')
    {
        printf("Enter new building number: ");
        scanf("%d", &result->data.number);

        getchar();

        char tempAddress[100];
        char tempPaid[10];

        printf("Enter new address: ");
        readString(tempAddress);

        free(result->data.address);
        result->data.address = (char*)malloc(strlen(tempAddress) + 1);
        strcpy(result->data.address, tempAddress);

        printf("Enter new number of apartments: ");
        scanf("%d", &result->data.apartments);

        printf("Enter new establishment year: ");
        scanf("%d", &result->data.year);

        printf("Enter paid fees (yes/no): ");
        scanf("%s", tempPaid);

        free(result->data.paid);
        result->data.paid = (char*)malloc(strlen(tempPaid) + 1);
        strcpy(result->data.paid, tempPaid);

        printf("\nBuilding information updated successfully.\n");
    }

/*
    Searches for a building in the AVL tree using its name.
    If the building is found, all of its information is displayed.
    The user is then given the option to update the building's
    number, address, number of apartments, establishment year,
    and fee payment status. If the building does not exist,
    an appropriate message is displayed.
*/
}

AVLNode* insertBuildingFromUser(AVLNode *root)
{
    ApartmentBuilding building;

    char tempName[100];
    char tempAddress[100];
    char tempPaid[10];

    printf("Enter building name: ");
    readString(tempName);

    printf("Enter building number: ");
    scanf("%d", &building.number);

    getchar();

    printf("Enter address: ");
    readString(tempAddress);

    printf("Enter number of apartments: ");
    scanf("%d", &building.apartments);

    printf("Enter establishment year: ");
    scanf("%d", &building.year);

    printf("Enter paid fees (yes/no): ");
    scanf("%s", tempPaid);

    building.name = (char*)malloc(strlen(tempName) + 1);
    strcpy(building.name, tempName);

    building.address = (char*)malloc(strlen(tempAddress) + 1);
    strcpy(building.address, tempAddress);

    building.paid = (char*)malloc(strlen(tempPaid) + 1);
    strcpy(building.paid, tempPaid);

    root = insertAVL(root, building);

    free(building.name);
    free(building.address);
    free(building.paid);

    printf("\nBuilding inserted successfully.\n");
    return root;
}

// Finds the node with the smallest name in a subtree
AVLNode* findMinNode(AVLNode *root)
{
    AVLNode *current = root;

    while(current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Deletes a building from the AVL tree
AVLNode* deleteAVL(AVLNode *root, char name[], int *found)
{
    if(root == NULL)
        return root;

    if(strcmp(name, root->data.name) < 0)
    {
        root->left = deleteAVL(root->left, name, found);
    }
    else if(strcmp(name, root->data.name) > 0)
    {
        root->right = deleteAVL(root->right, name, found);
    }
    else
    {
        *found = 1;

        // Node with one child or no child
        if(root->left == NULL || root->right == NULL)
        {
            AVLNode *temp;

            if(root->left)
                temp = root->left;
            else
                temp = root->right;

            // No child
            if(temp == NULL)
            {
                free(root->data.name);
                free(root->data.address);
                free(root->data.paid);
                free(root);

                return NULL;
            }
            // One child
            else
            {
                AVLNode *old = root;
                root = temp;

            free(old->data.name);
            free(old->data.address);
            free(old->data.paid);
            free(old);
            return root;
            }
        }
        // Node with two children
        else
        {
            AVLNode *temp = findMinNode(root->right);

            free(root->data.name);
            free(root->data.address);
            free(root->data.paid);

            root->data.name = (char*)malloc(strlen(temp->data.name) + 1);
            strcpy(root->data.name, temp->data.name);

            root->data.address = (char*)malloc(strlen(temp->data.address) + 1);
            strcpy(root->data.address, temp->data.address);

            root->data.paid = (char*)malloc(strlen(temp->data.paid) + 1);
            strcpy(root->data.paid, temp->data.paid);

            root->data.number = temp->data.number;
            root->data.apartments = temp->data.apartments;
            root->data.year = temp->data.year;

            root->right = deleteAVL(root->right, temp->data.name, found);
        }
        /*
    Four balancing cases are checked:

    1. Left-Left (LL):
       The left subtree is heavier and its left child is also heavier.
       A single right rotation restores balance.

    2. Left-Right (LR):
       The left subtree is heavier but its right child causes the
       imbalance. A left rotation on the left child followed by a
       right rotation on the current node restores balance.

    3. Right-Right (RR):
       The right subtree is heavier and its right child is also heavier.
       A single left rotation restores balance.

    4. Right-Left (RL):
       The right subtree is heavier but its left child causes the
       imbalance. A right rotation on the right child followed by a
       left rotation on the current node restores balance.
    */
    }

    if(root == NULL)
        return root;

    root->height = 1 + maxxx(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Left Left
    if(balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right
    if(balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right
    if(balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left
    if(balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Deletes a building entered by the user
AVLNode* deleteBuildingFromUser(AVLNode *root)
{
    char name[100];

    printf("Enter building name to delete: ");
    readString(name);

    int found = 0; //flag 4 building
    root = deleteAVL(root, name, &found);

    if(found)
        printf("Building deleted.\n");
    else
        printf("Building not found.\n");

    return root;
}

void buildingsGreaterThan(AVLNode *root, int num)
{
    if(root == NULL)
        return;

    buildingsGreaterThan(root->left, num);

    if(root->data.apartments > num)
    {
        printf("\nName: %s\n", root->data.name);
        printf("Number: %d\n", root->data.number);
        printf("Address: %s\n", root->data.address);
        printf("Apartments: %d\n", root->data.apartments);
        printf("Year: %d\n", root->data.year);
        printf("Paid Fees: %s\n", root->data.paid);
    }

    buildingsGreaterThan(root->right, num);
}

void buildingsNotPaid(AVLNode *root)
{
    if(root == NULL)
        return;

    buildingsNotPaid(root->left);

    if(root->data.paid[0] == 'n' || root->data.paid[0] == 'N')
    {
        printf("\nName: %s\n", root->data.name);
        printf("Number: %d\n", root->data.number);
        printf("Address: %s\n", root->data.address);
        printf("Apartments: %d\n", root->data.apartments);
        printf("Year: %d\n", root->data.year);
        printf("Paid Fees: %s\n", root->data.paid);
    }

    buildingsNotPaid(root->right);
}

void saveToHashFile(AVLNode *root, FILE *file)
{
    if(root == NULL)
        return;

    saveToHashFile(root->left, file);

    fprintf(file,"%s:%d:%s:%d:%d:%s\n",
            root->data.name,
            root->data.number,
            root->data.address,
            root->data.apartments,
            root->data.year,
            root->data.paid);

    saveToHashFile(root->right, file);

}

void saveTreeToFile(AVLNode *root)
{
    FILE *file = fopen("hash.txt", "w");

    if(file == NULL)
    {
        printf("Cannot create hash.txt\n");
        return;
    }

    saveToHashFile(root, file);

    fclose(file);

    printf("Data saved to hash.txt successfully.\n");
}

void initializeHashTable(Hash table[])
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        table[i].status = 0;
    }
}

int hashFunction(char name[])
{
    int sum = 0;

    for(int i = 0; i < 4 && name[i] != '\0'; i++)
    {
        sum += name[i];
    }
    return sum % TABLE_SIZE;
}

int insertHash(Hash table[], ApartmentBuilding building)
{
    int index = hashFunction(building.name);
    int firstDeleted = -1;//-1 can never be a valid index so (-1) is good

    while(table[index].status != 0)
    {
        // (0,1,2) = (empty, occupied, deleted)
        if(table[index].status == 2 && firstDeleted == -1)
        {
            firstDeleted = index;
        }

        if(table[index].status == 1 &&
           strcmp(table[index].data.name, building.name) == 0)
        {
            return 0;
        }

        index = (index + 1) % TABLE_SIZE;
    }

    if(firstDeleted != -1)
    {
        index = firstDeleted;
    }

    table[index].data.name = (char*)malloc(strlen(building.name) + 1);
    strcpy(table[index].data.name, building.name);

    table[index].data.address = (char*)malloc(strlen(building.address) + 1);
    strcpy(table[index].data.address, building.address);

    table[index].data.paid = (char*)malloc(strlen(building.paid) + 1);
    strcpy(table[index].data.paid, building.paid);

    table[index].data.number = building.number;
    table[index].data.apartments = building.apartments;
    table[index].data.year = building.year;

    table[index].status = 1;

    return 1;
}

void loadHashTable(Hash table[])
{
    FILE *file = fopen("hash.txt", "r");

    if(file == NULL)
    {
        printf("Cannot open hash.txt\n");
        return;
    }

    ApartmentBuilding building;
    char line[300];
    char temp[20];

    while(fgets(line, sizeof(line), file))
    {
        char name[100];
        char address[100];
        char paid[10];

        int i = 0;
        int j = 0;

        while(line[i] != ':')
        {
            name[j++] = line[i++];
        }
        name[j] = '\0';
        i++;

        j = 0;
        while(line[i] != ':')
        {
            temp[j++] = line[i++];
        }
        temp[j] = '\0';
        building.number = stringToInt(temp);
        i++;

        j = 0;
        while(line[i] != ':')
        {
            address[j++] = line[i++];
        }
        address[j] = '\0';
        i++;

        j = 0;
        while(line[i] != ':')
        {
            temp[j++] = line[i++];
        }
        temp[j] = '\0';
        building.apartments = stringToInt(temp);
        i++;

        j = 0;
        while(line[i] != ':')
        {
            temp[j++] = line[i++];
        }
        temp[j] = '\0';
        building.year = stringToInt(temp);
        i++;

        j = 0;
        while(line[i] != '\n' && line[i] != '\0')
        {
            paid[j++] = line[i++];
        }
        paid[j] = '\0';

        building.name = (char*)malloc(strlen(name) + 1);
        strcpy(building.name, name);

        building.address = (char*)malloc(strlen(address) + 1);
        strcpy(building.address, address);

        building.paid = (char*)malloc(strlen(paid) + 1);
        strcpy(building.paid, paid);

        insertHash(table, building);

        free(building.name);
        free(building.address);
        free(building.paid);
    }

    fclose(file);
}

void printHashTable(Hash table[])
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        printf("%d : ", i);

        if(table[i].status == 0)
        {
            printf("empty\n");
        }
        else if(table[i].status == 2)
        {
            printf("deleted\n");
        }
        else
        {
            printf("%s\n", table[i].data.name);
        }
    }
}

void printHashInfo(Hash table[])
{
    int occupied = 0;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(table[i].status == 1)
        {
            occupied++;
        }
    }

    printf("Table Size = %d\n", TABLE_SIZE);

    float loadFactor = (float)occupied / TABLE_SIZE;

    printf("Load Factor = %.2f\n", loadFactor);
}

void searchHash(Hash table[])
{
    char name[100];

    printf("Enter building name: ");
    readString(name);

    int index = hashFunction(name);
    int collisions = 0;

    while(table[index].status != 0)
    {
        if(table[index].status == 1 && strcmp(table[index].data.name, name) == 0)
        {
            printf("\nFound!\n");
            printf("Name: %s\n", table[index].data.name);
            printf("Number: %d\n", table[index].data.number);
            printf("Address: %s\n", table[index].data.address);
            printf("Apartments: %d\n", table[index].data.apartments);
            printf("Year: %d\n", table[index].data.year);
            printf("Paid Fees: %s\n", table[index].data.paid);
            printf("Collisions: %d\n", collisions);
            return;
        }

        collisions++;
        index = (index + 1) % TABLE_SIZE;
    }

    printf("Building not found.\n");
}

void insertHashFromUser(Hash table[])
{
    ApartmentBuilding building;

    char name[100];
    char address[100];
    char paid[10];

    printf("Enter building name: ");
    readString(name);

    building.name = (char*)malloc(strlen(name) + 1);
    strcpy(building.name, name);

    printf("Enter building number: ");
    scanf("%d", &building.number);

    getchar();

    printf("Enter address: ");
    readString(address);

    building.address = (char*)malloc(strlen(address) + 1);
    strcpy(building.address, address);

    printf("Enter apartments: ");
    scanf("%d", &building.apartments);

    printf("Enter year: ");
    scanf("%d", &building.year);

    printf("Enter paid fees: ");
    scanf("%s", paid);

    building.paid = (char*)malloc(strlen(paid) + 1);
    strcpy(building.paid, paid);

    if(insertHash(table, building))
    {
        printf("Record inserted.\n");
    }
    else
    {
        printf("Building already exists.\n");
    }

    free(building.name);
    free(building.address);
    free(building.paid);
}

void deleteHash(Hash table[])
{
    char name[100];

    printf("Enter building name: ");
    readString(name);

    int index = hashFunction(name);

    while(table[index].status != 0)
    {
        if(table[index].status == 1 &&
           strcmp(table[index].data.name, name) == 0)
        {
            free(table[index].data.name);
            free(table[index].data.address);
            free(table[index].data.paid);

            table[index].status = 2;

            printf("Record deleted.\n");
            return;
        }

        index = (index + 1) % TABLE_SIZE;
    }

    printf("Building not found.\n");
/*
    This function deletes a building record from the hash table using
    its name as the key. The user first enters the building name, then
    the hash function calculates its initial index. The function searches
    the table using linear probing until either the building is found or
    an empty slot is reached. If the building exists, its status is set
    to 2 (deleted) instead of removing the data completely. This preserves
    the probing sequence and ensures that future searches continue to work
    correctly. If the building cannot be found, an appropriate message is
    displayed to the user.
*/
}

void saveHashTable(Hash table[])
{
    FILE *file = fopen("hash.txt", "w");

    if(file == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(table[i].status == 1)
        {
            fprintf(file,
                    "%s:%d:%s:%d:%d:%s\n",
                    table[i].data.name,
                    table[i].data.number,
                    table[i].data.address,
                    table[i].data.apartments,
                    table[i].data.year,
                    table[i].data.paid);
        }
    }

    fclose(file);

    printf("Hash table saved.\n");
}


void printMenu()
{
    printf("1. Insert Building\n");
    printf("2. Search Building\n");
    printf("3. Print Buildings\n");
    printf("4. Delete Building\n");
    printf("5. Buildings with apartments greater than a number\n");
    printf("6. Buildings that have not paid fees\n");
    printf("7. Save to hash.txt\n");
    printf("8. Load Hash Table\n");
    printf("9. Print Hash Table\n");
    printf("10. Print Hash Info\n");
    printf("11. Search Hash Table\n");
    printf("12. Insert Hash Record\n");
    printf("13. Delete Hash Record\n");
    printf("14. Save Hash Table\n");
    printf("0. Exit\n");
}

//*******************************main*******************************
int main()
{
    Hash table[TABLE_SIZE];
    AVLNode *root = NULL;
    int choice = -1;
    root = loadFromFile(root);
    initializeHashTable(table);

    while(choice != 0)
    {
        printMenu();

        printf("Enter your choice: ");
        scanf(" %d", &choice);

        if(choice == 1)//Insert Building
        {
            root = insertBuildingFromUser(root);
        }

        else if(choice == 2)//Search Building
        {
            searchAndDisplay(root);
        }

        else if(choice == 3)//Print Buildings
        {
            printf("\nBuildings in alphabetical order:\n\n");
            inorderTraversal(root);
        }

        else if(choice == 4)//Delete Building
        {
            root = deleteBuildingFromUser(root);
        }

        else if(choice == 0)// Exit and save hash table to file
        {
            saveHashTable(table);

            for(int i = 0; i < TABLE_SIZE; i++)
            {
                if(table[i].status == 1)
                {
                    free(table[i].data.name);
                    free(table[i].data.address);
                    free(table[i].data.paid);
                }
            }

            printf("Good Bye!\n");
        }

        else if(choice == 5)//Buildings with apartments greater than a number
        {
            int num;
            printf("Enter apartment number: ");
            scanf("%d", &num);
            printf("\nBuildings with apartments greater than %d:\n", num);
            buildingsGreaterThan(root, num);
        }

        else if(choice == 6)//Buildings that have not paid fees
        {
            printf("\nBuildings that have not paid fees:\n\n");
            buildingsNotPaid(root);
        }

        else if(choice == 7)//Save to hash.txt
        {
            saveTreeToFile(root);
        }

        else if(choice == 8)//Load Hash Table
        {
            initializeHashTable(table);
            loadHashTable(table);
            printf("Hash table loaded.\n");
        }

        else if(choice == 9)//Print Hash Table
        {
            printHashTable(table);
        }

        else if(choice == 10)//Print Hash Info
        {
            printHashInfo(table);
        }

        else if(choice == 11)//Search Hash Table
        {
            searchHash(table);
        }

        else if(choice == 12)//Insert Hash Record
        {
            insertHashFromUser(table);
        }

        else if(choice == 13)//Delete Hash Record
        {
            deleteHash(table);
        }

        else if(choice == 14)//Save Hash Table
        {
            saveHashTable(table);
        }

        else// Invalid choice
        {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}