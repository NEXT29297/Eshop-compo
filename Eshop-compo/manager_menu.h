#ifndef MANAGER_MENU_H
#define MANAGER_MENU_H

#include "publicdata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int manager_view_product();
int manager_reorder_product();
int manager_remove_product();
int manager_addnew_product();
int manager_UpdateInv();

int manager() {
  int x = 1;
  int choice;
  printf("--------Manager--------\n");
  while (x > 0) {
    printf("What do you want to do\n");
    printf("1. View Product\n");
    printf("2. Reorder Product\n");
    printf("3. Remove Product\n");
    printf("4. AddNew Product\n");
    printf("5. Update Inventory\n");
    printf("6. Exit\n");
    printf("Enter your choice: \n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("\n");
      manager_view_product();
      x = 0;
      break;
    case 2:
      printf("\n");
      manager_reorder_product();
      x = 0;
      break;
    case 3:
      printf("\n");
      manager_remove_product();
      x = 0;
      break;
    case 4:
      printf("\n");
      manager_addnew_product();
      x = 0;
      break;
    case 5:
      printf("\n");
      manager_UpdateInv();
      x = 0;
      break;
    case 6:
      x = 0;
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please choose again.\n");
      printf("\n");
    }
  }
}

int manager_reorder_product() {
  int reorder_threshold = 40;
  struct product Reor;
  ProdPTR = fopen("ProductList.csv", "r");
  if (ProdPTR == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  fscanf(ProdPTR, "%*[^\n]\n");
  // printf("Id\tName\tQuantity\tCost\tSelling Price\n");
  FILE *TempPTR = fopen("ProductList(Modified).csv", "w");
  if (TempPTR == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  while (fscanf(ProdPTR, "%[^,],%[^,],%d,%d,%d\n", Reor.id, Reor.name, &Reor.quantity, &Reor.cost, &Reor.selling_price) == 5) {
    if (Reor.quantity < reorder_threshold) {
      printf("Reordering product %s. Current quantity: %d\n", Reor.id, Reor.quantity);
      // printf("%s,%s,%d,%d,%d\n",Reor.id, Reor.name,
      //     Reor.quantity, Reor.cost, Reor.selling_price);
    }
  }
  int new_quantity = reorder_threshold + 10;
  // Reor.quantity = new_quantity;


  fprintf(TempPTR, "Id,Name,Quantity,Cost,Selling Price\n");

  rewind(ProdPTR); // Reset file pointer to the beginning of the file

  // Skip the first line (header) by reading and discarding it
  fscanf(ProdPTR, "%*[^\n]\n");

  while (fscanf(ProdPTR, "%[^,],%[^,],%d,%d,%d\n", Reor.id, Reor.name,
                &Reor.quantity, &Reor.cost, &Reor.selling_price) == 5) {
    if(Reor.quantity >= reorder_threshold){
    fprintf(TempPTR, "%s,%s,%d,%d,%d\n", Reor.id, Reor.name, Reor.quantity, Reor.cost, Reor.selling_price);
    }else if(Reor.quantity < reorder_threshold){
      fprintf(TempPTR, "%s,%s,%d,%d,%d\n", Reor.id, Reor.name, new_quantity, Reor.cost, Reor.selling_price);
    }
  }

  fclose(TempPTR);

  printf("Reordering complete. New quantity: %d\n", new_quantity);

fclose(ProdPTR);
  printf("\n");
  manager();
}

int manager_remove_product() {
  FILE *TempPtr;
  char line[100], nameToDelete[50];
  int found = 0;

  ProdPTR = fopen("ProductList.csv", "r");

  if (ProdPTR == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  TempPtr = fopen("ProductList(Modified).csv", "w");

  if (TempPtr == NULL) {
    perror("Error opening file");
    fclose(ProdPTR);
    exit(EXIT_FAILURE);
  }

  printf("Enter the name to delete: ");
  fgets(nameToDelete, sizeof(nameToDelete), stdin);
  nameToDelete[strcspn(nameToDelete, "\n")] = '\0';

  while (fgets(line, sizeof(line), ProdPTR) != NULL) {
    if (strstr(line, nameToDelete) == NULL) {
      fputs(line, TempPtr);
    } else {
      found = 1;
    }
  }

  fclose(ProdPTR);
  fclose(TempPtr);

  rename("Temp.csv", "ProductList.csv");

  if (found) {
    printf("Name '%s' deleted successfully.\n", nameToDelete);
  } else {
    printf("Name '%s' not found in the file.\n", nameToDelete);
  }
  printf("\n");
  manager();
}

int manager_addnew_product() {
  char ProdID[50], ProdName[50];
  int Quantity, Price;
  printf("Please input a Product ID : ");
  scanf("%s", ProdID);
  printf("Please input a Product Name : ");
  scanf("%s", ProdName);
  printf("Please input quantities : ");
  scanf("%d", &Quantity);
  printf("Please input a price : ");
  scanf("%d", &Price);
  ProdPTR = fopen("ProductList.csv", "a");
  fprintf(ProdPTR, "\n%s,%s,%d,%d", ProdID, ProdName, Quantity, Price);
  fclose(ProdPTR);
  printf("\n");
  manager();
}

int manager_UpdateInv() {
  char choice[1];
  printf("Are you sure you want to update the inventory? (Y/N)");
  scanf("%c", choice);
  switch (choice[0]) {
  case 'Y':
    remove("ProductList.csv");
    rename("ProductList(Modified).csv", "ProductList.csv");
    break;
  case 'y':
    remove("ProductList.csv");
    rename("ProductList(Modified).csv", "ProductList.csv");
    break;
  case 'N':
    break;
  case 'n':
    break;
  }
  printf("\n");
  manager();
}

int manager_view_product() {
  ProdPTR = fopen("ProductList.csv", "r");

  char List[50];
  while (fgets(List, 50, ProdPTR)) {
    printf("%s", List);
  }

  fclose(ProdPTR);
  printf("\n");
  manager();
}

#endif // MANAGER_MENU_H