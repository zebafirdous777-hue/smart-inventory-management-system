#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS 100

struct Product
{
    int id;
    char name[50];
    float price;
    int quantity;
};
struct Product products[MAX_PRODUCTS];
int count = 0;

// Save all products to the binary file
void saveProducts()
{
    FILE *fp;

    fp = fopen("products.dat", "wb");

    if (fp == NULL)
    {
        printf("Error saving products!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(products, sizeof(struct Product), count, fp);

    fclose(fp);
}

// Add a new product to the inventory
void addProduct()
{   
     int i;

    if (count == MAX_PRODUCTS)
{
    printf("\n===============================================================\n");
    printf("ERROR: Inventory is Full!\n");
    printf("===============================================================\n");
    return;
}
    
     printf("\nEnter Product ID: ");
    scanf("%d", &products[count].id);
    

for (i = 0; i < count; i++)
{
    if (products[i].id == products[count].id)
    {
        printf("\n===============================================================\n");
        printf("ERROR: Product ID already exists!\n");
        printf("===============================================================\n");
        return;
    }
}

    printf("Enter Product Name: ");
    scanf("%s", products[count].name);

    do
{
    printf("Enter Product Price: ");
    scanf("%f", &products[count].price);

    if (products[count].price <= 0)
    {
        printf("Price must be greater than 0!\n");
    }

} while (products[count].price <= 0);
do
{
    printf("Enter Product Quantity: ");
    scanf("%d", &products[count].quantity);

    if (products[count].quantity < 0)
    {
        printf("Quantity cannot be negative!\n");
    }

} while (products[count].quantity < 0);
    
    count++;
    saveProducts();
    printf("\n===============================================================\n");
    printf("SUCCESS: Product Added Successfully!\n");
    printf("===============================================================\n");

}

// Display all products in the inventory
void viewProducts()
{
    int i;

    if (count == 0)
    {
        printf("\nNo products available!\n");
        return;
    }

    printf("\n=============================================================\n");
    printf("                      VIEW PRODUCTS\n");
    printf("=============================================================\n");
    printf("%-8s %-15s %-12s %-8s\n",
       "ID", "Name", "Price", "Quantity");
    printf("-------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    { printf("%-8d %-15s %-12.2f %-8d\n",
       products[i].id,
       products[i].name,
       products[i].price,
       products[i].quantity);
        
    }
    printf("===============================================================\n");
}

// Search a product using its ID
void searchProduct()
{
    int searchId;
    int i;
    int found = 0;

    printf("\nEnter Product ID to search: ");
    scanf("%d", &searchId);

    for (i = 0; i < count; i++)
    {
        if (products[i].id == searchId)
        {
           printf("\n===============================================================\n");
           printf("                     PRODUCT DETAILS\n");
           printf("===============================================================\n");

           printf("%-15s : %d\n", "Product ID", products[i].id);
           printf("%-15s : %s\n", "Name", products[i].name);
           printf("%-15s : %.2f\n", "Price", products[i].price);
           printf("%-15s : %d\n", "Quantity", products[i].quantity);

           printf("===============================================================\n");

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\n===============================================================\n");
        printf("ERROR: Product not found!\n");
        printf("===============================================================\n");
    }
}

// Search a product using its name
void searchProductByName()
{
    char searchName[50];
    int i;
    int found = 0;

    printf("\nEnter Product Name to search: ");
    scanf("%s", searchName);

    for (i = 0; i < count; i++)
    {
        if (strcasecmp(products[i].name, searchName) == 0)
        {
            printf("\n===============================================================\n");
            printf("                      PRODUCT DETAILS\n");
            printf("===============================================================\n");

            printf("%-18s : %d\n", "Product ID", products[i].id);
            printf("%-18s : %s\n", "Name", products[i].name);
            printf("%-18s : %.2f\n", "Price", products[i].price);
            printf("%-18s : %d\n", "Quantity", products[i].quantity);

            printf("===============================================================\n");

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\n===============================================================\n");
        printf("ERROR: Product not found!\n");
        printf("===============================================================\n");
    }
}

// Display inventory statistics
void inventoryStatistics()
{
    int i;
    int totalQuantity = 0;
    float totalValue = 0;

    int highest = 0;
    int lowest = 0;

    if (count == 0)
    {
        printf("\n===============================================================\n");
        printf("No products available!\n");
        printf("===============================================================\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        totalQuantity += products[i].quantity;
        totalValue += products[i].price * products[i].quantity;

        if (products[i].price > products[highest].price)
        {
            highest = i;
        }

        if (products[i].price < products[lowest].price)
        {
            lowest = i;
        }
    }

    printf("\n===============================================================\n");
    printf("                   INVENTORY STATISTICS\n");
    printf("===============================================================\n");

    printf("%-30s : %d\n", "Total Products", count);
    printf("%-30s : %d\n", "Total Quantity", totalQuantity);
    printf("%-30s : %.2f\n", "Total Inventory Value", totalValue);
    printf("%-30s : %s\n", "Highest Price Product", products[highest].name);
    printf("%-30s : %s\n", "Lowest Price Product", products[lowest].name);

    printf("===============================================================\n");
}

// Display products with low stock
void lowStockProducts()
{
    int i;
    int found = 0;

    printf("\n===============================================================\n");
    printf("                    LOW STOCK PRODUCTS\n");
    printf("===============================================================\n");

    printf("%-8s %-20s %-10s\n",
           "ID", "Name", "Quantity");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        if (products[i].quantity < 5)
        {
            printf("%-8d %-20s %-10d\n",
                   products[i].id,
                   products[i].name,
                   products[i].quantity);

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No low stock products found.\n");
    }

    printf("===============================================================\n");
}


// Update product details
void updateProduct()
{
    int updateId;
    int i;
    int found = 0;

    printf("\nEnter Product ID to update: ");
    scanf("%d", &updateId);

    for (i = 0; i < count; i++)
    {
        if (products[i].id == updateId)
        {
            printf("\n===============================================================\n");
            printf("ERROR: Product not found!\n");
            printf("===============================================================\n");

          do
{
            printf("Enter New Product Price: ");
            scanf("%f", &products[i].price);

       if (products[i].price <= 0)
    {
            printf("Price must be greater than 0!\n");
    }

} while (products[i].price <= 0);


            printf("Enter New Product Price: ");
            scanf("%f", &products[i].price);

            do
       {
            printf("Enter New Product Quantity: ");
            scanf("%d", &products[i].quantity);

           if (products[i].quantity < 0)
         {
           printf("Quantity cannot be negative!\n");
         }

        } while (products[i].quantity < 0);  

            printf("\n===============================================================\n");
            printf("SUCCESS: Product Updated Successfully!\n");
            printf("===============================================================\n");

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\n===============================================================\n");
        printf("ERROR: Product not found!\n");
        printf("===============================================================\n");
    }
}

// Delete a product from the inventory
void deleteProduct()
{
    int deleteId;
    int i;
    int found = 0;

    printf("\nEnter Product ID to delete: ");
    scanf("%d", &deleteId);

    for (i = 0; i < count; i++)
    {
        if (products[i].id == deleteId)
        {
         char confirm;

printf("\nAre you sure you want to delete this product? (Y/N): ");
scanf(" %c", &confirm);

if (confirm != 'Y' && confirm != 'y')
{
    printf("\nDeletion Cancelled!\n");
    return;
}
            int j;

            for (j = i; j < count - 1; j++)
            {
                products[j] = products[j + 1];
            }

            count--;
            saveProducts();
            printf("\n===============================================================\n");
            printf("SUCCESS: Product Deleted Successfully!\n");
            printf("===============================================================\n");

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\n===============================================================\n");
        printf("ERROR: Product not found!\n");
        printf("===============================================================\n");
    }
}

// Load all products from the binary file
void loadProducts()
{
    FILE *fp;

    fp = fopen("products.dat", "rb");

    if (fp == NULL)
    {
        return;
    }

    fread(&count, sizeof(int), 1, fp);
    fread(products, sizeof(struct Product), count, fp);

    fclose(fp);
}

// Display project information
void aboutProject()
{
    printf("\n===============================================================\n");
    printf("             SMART INVENTORY MANAGEMENT SYSTEM\n");
    printf("===============================================================\n\n");

    printf("Developer      : Zeba Firdous\n");
    printf("Course         : B.E. CSE (AI & ML)\n");
    printf("College        : Dayananda Sagar Academy of\n");
    printf("                 Technology & Management\n");
    printf("Language       : C Programming\n");
    printf("Storage        : Binary File Handling\n");
    printf("Project Type   : Console Based CRUD Application\n");
    printf("Version        : 1.0\n");

    printf("\n===============================================================\n");
    printf("      Thank you for using the application!\n");

    printf("\nCopyright (c) 2026 Zeba Firdous\n");

    printf("===============================================================\n");
}

// Generate an inventory report in a text file
void generateReport()
{
    FILE *fp;
    int i;
    int totalQuantity = 0;
    float totalValue = 0;

    fp = fopen("inventory_report.txt", "w");

    if (fp == NULL)
    {
        printf("\nError creating report!\n");
        return;
    }
    

    fprintf(fp, "===============================================================\n");
    fprintf(fp, "                  INVENTORY REPORT\n");
    fprintf(fp, "===============================================================\n\n");
    
    time_t t;
    time(&t);

    fprintf(fp, "Generated On : %s\n", ctime(&t));
    fprintf(fp, "Generated By : Smart Inventory Management System\n\n");
    
    fprintf(fp, "%-8s %-20s %-15s %-10s\n",
            "ID", "Name", "Price", "Quantity");
    fprintf(fp, "---------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        fprintf(fp, "%-8d %-20s %-15.2f %-10d\n",
                products[i].id,
                products[i].name,
                products[i].price,
                products[i].quantity);

        totalQuantity += products[i].quantity;
        totalValue += products[i].price * products[i].quantity;
    }

    fprintf(fp, "---------------------------------------------------------------\n");

    fprintf(fp, "\nTotal Products         : %d\n", count);
    fprintf(fp, "Total Quantity         : %d\n", totalQuantity);
    fprintf(fp, "Total Inventory Value  : %.2f\n", totalValue);

    fprintf(fp, "\n===============================================================\n");

    fclose(fp);

    printf("\n===============================================================\n");
    printf("SUCCESS: Inventory Report Generated Successfully!\n");
    printf("File Name : inventory_report.txt\n");
    printf("===============================================================\n");
}

// Main function - displays the menu and handles user choices
int main()
{
    int choice;
    loadProducts();

    while (1)
    {
       printf("\n===============================================================\n");
       printf("           SMART INVENTORY MANAGEMENT SYSTEM\n");
       printf("===============================================================\n"); 

        printf(" 1. Add Product\n");
        printf(" 2. View Products\n");
        printf(" 3. Search Product by ID\n");
        printf(" 4. Search Product by Name\n");
        printf(" 5. Update Product\n");
        printf(" 6. Delete Product\n");
        printf(" 7. Inventory Statistics\n");
        printf(" 8. Low Stock Products\n");
        printf(" 9. Generate Report\n");
        printf("10. About Project\n");
        printf("11. Exit\n");

        printf("\nEnter your choice: ");
        
        if (scanf("%d", &choice) != 1)
{
    printf("\nPlease enter a valid number!\n");

    while (getchar() != '\n');

    continue;
}

        switch (choice)
        {
            case 1:
                addProduct();
                break;

            case 2:
                viewProducts();
                break;

            case 3:
                searchProduct();
                break;

            case 4:
                searchProductByName();
                break;

            case 5:
                 updateProduct();
                 break;

            case 6:
                deleteProduct();
                break;

            case 7:
                inventoryStatistics();
                break;

            case 8:
                lowStockProducts();
                break;

            case 9:
                generateReport();
                break;

            case 10:
                aboutProject();
                break;

            case 11:
                printf("\nThank you!\n");
                return 0;

            default:
                printf("\n===============================================================\n");
                printf("ERROR: Invalid Choice!\n");
                printf("===============================================================\n");
                
        }
    }
}
