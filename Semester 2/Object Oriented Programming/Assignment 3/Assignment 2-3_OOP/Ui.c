#include "UI.h"
#include "stdio.h"
#include "stdlib.h"
#include <crtdbg.h>
#include <string.h>

UI* createUI(Service* service)
{
    UI* ui = (UI*)malloc(sizeof(UI));
    if (ui == NULL) {
        return NULL;
    }
    ui->service = service;
    return ui;
}

void destoryUI(UI* ui)
{
    if (ui == NULL) {
        return;
    }
    destroyService(ui->service);
    free(ui);
}

void printMenu()
{
    printf("---- OPTIONS MENU ----\n");
    printf("0 : exit \n");
    printf("1 : add material \n");
    printf("2 : delete material \n");
    printf("3 : update material \n");
    printf("4 : print materials by name\n");
    printf("5 : filter materials \n");
    printf("6 : undo \n");
    printf("7 : redo \n");
    printf("8 : print all the materials\n");
}

int readIntegerNumber(const char* message)
{
    char string[16] = { 0 };
    int result;
    int flag = 0;
    int read;

    while (flag == 0) {
        printf(message);
        scanf_s("%15s", &string, 15);
        read = sscanf_s(string, "%d", &result);
        flag = (read == 1);

        if (flag == 0) {
            printf("Invalid option!\n");
        }
    }
    return result;
}

int addMaterialUI(UI* ui)
{
    char name[50];
    char supplier[50];
    double expiration_date = 0;
    int quantity = 0;

    printf("Please input the name of the material: ");

    scanf_s("%49s", &name, 49);

    printf("Please input the supplier: ");

    scanf_s("%49s", &supplier, 49);

    printf("Please input the quantity: ");
    if (1 != scanf_s("%d", &quantity))
    {
        while (getchar() != '\n');
        return 0;
    }

    printf("Please input the expiration_date: ");
    if (1 != scanf_s("%lf", &expiration_date))
    {
        while (getchar() != '\n');
        return 0;
    }

    return add(ui->service, name, supplier, quantity, expiration_date);
}

int deleteMaterialUI(UI* ui)
{
    char name[50];
    char supplier[50];
    double expiration_date = 0;

    printf("Please input the name of the material you want to delete: ");
    scanf_s("%s", &name, 15);
    printf("Please input the supplier of the material you want to delete: ");
    scanf_s("%s", &supplier, 15);
    printf("Please input the expiration date of the material you want to delete: ");
    scanf_s("%lf", &expiration_date);
    return deleteMaterialServ(ui->service, name, supplier, expiration_date);
    return 0;
}

int updateMaterialUI(UI* ui)
{
    char name[50];
    char supplier[50];
    double expiration_date = 0;
    int new_quantity = 0;

    printf("Please input the name of the material you want to update: ");
    scanf_s("%s", &name, 49);
    printf("Please input the supplier of the material you want to update: ");
    scanf_s("%d", &supplier);
    printf("Please input the expiration date of the material you want to update: ");
    scanf_s("%lf", &expiration_date);
    printf("Please input the new quantity of the medication you want to update: ");
    scanf_s("%d", &new_quantity);

    return update(ui->service, name, supplier, expiration_date, new_quantity);
}

void printVector(DynamicArray* vec)
{
    if (vec == NULL)
    {
        return;
    }

    int count = getArrayLength(vec);
    for (int i = 0; i < count; i++)
    {
        Material* material = (Material*)getElementAtIndex(vec, i);
        if (material != NULL)
        {
            char* name = getName(material);
            char* supplier = getSupplier(material);
            int quantity = getQuantity(material);
            double expiration_date = getExpirationDate(material);
            printf("Name:%s | Supplier:%s | Quantity:%d | Expiration date:%f\n", name, supplier, quantity, expiration_date);
        }
    }
}

int chooseSortType() {
    int option;
    printf("How do you want to sort the materials ? \n");
    printf("1 : ascending \n");
    printf("2 : descending \n");
    printf("Please input your option: ");
    scanf_s("%d", &option);
    return option;
}

void printMaterialsByName(UI* ui)
{
    char name[50];
    printf("Please input the string to search for: ");
    scanf_s("%s", &name, 49);

    if (strcmp(name, "-1") == 0)
    {
        DynamicArray* MaterialData = getMaterials(ui->service);
        while (1)
        {
            int sortOption = chooseSortType();
            if (sortOption == 1) {
                sortMaterialsVectorAscendingByQuantity(MaterialData);
                break;
            }
            else if (sortOption == 2) {
                sortMaterialsVectorDescendingByQuantity(MaterialData);
                break;
            }
            else {
                printf("Invalid option for sorting, try again !");
            }
        }
        printVector(MaterialData);
    }
    else
    {
        DynamicArray* materials = getMaterialsByName(ui->service, name);
        while (1)
        {
            int sortOption = chooseSortType();
            if (sortOption == 1) {
                sortMaterialsVectorAscendingByQuantity(materials);
                break;
            }
            else if (sortOption == 2) {
                sortMaterialsVectorDescendingByQuantity(materials);
                break;
            }
            else {
                printf("Invalid option for sorting, try again !");
            }
        }
        printVector(materials);
        destroyDynamicArray(materials);
    }
}
void print_vector(UI* ui)
{
    DynamicArray* MaterialData = getMaterials(ui->service);
    printVector(MaterialData);
}

int chooseFilterType()
{
    int option;
    printf("How do you want to filter the materials ? \n");
    printf("1 : by quantity \n");
    printf("2 : by expiration date \n");
    printf("Please input your option: \n");
    scanf_s("%d", &option);
    return option;
}

void printMaterialsBySomething(UI* ui)
{
    while (1)
    {
        int option = chooseFilterType();
        if (option == 1)
        {
            int quantity;
            printf("Please input the quantity to search for : ");
            scanf_s("%d", &quantity);
            DynamicArray* materials = getMaterialsByQuantity(ui->service, quantity);
            printVector(materials);
            break;
        }
        else if (option == 2)
        {
            double expiration_date;
            printf("Please input the expiration date to search for: ");
            scanf_s("%d", &expiration_date);
            DynamicArray* materials = getMaterialsByExpirationDate(ui->service, expiration_date);
            printVector(materials);
            break;
        }
        else
        {
            printf("Invalid option for filter ! Try again !");
        }
    }
}

int undoUI(UI* ui)
{
    return undo(ui->service);
}

int redoUI(UI* ui)
{
    return redo(ui->service);
}

void start(UI* ui)
{
    while (1) {
        printMenu();
        int option = readIntegerNumber("Please choose your option: ");
        if (option == 0)
        {
            return;
        }
        else if (option == 1)
        {
            int addResult = addMaterialUI(ui);
            if (addResult == 1)
            {
                printf("Material successfully added ! \n");
            }
            else
            {
                printf("Material cannot be added ! \n");
            }
        }
        else if (option == 2)
        {
            int deleteResult = deleteMaterialUI(ui);
            if (deleteResult == 1)
            {
                printf("Material successfully deleted ! \n");
            }
            else
            {
                printf("Material cannot be deleted ! \n");
            }
        }
        else if (option == 3)
        {
            int updateResult = updateMaterialUI(ui);
            if (updateResult == 1)
            {
                printf("Material successfully updated ! \n");
            }
            else
            {
                printf("Material cannot be updated ! \n");
            }
        }
        else if (option == 4)
        {
            printMaterialsByName(ui);
        }
        else if (option == 5)
        {
            printMaterialsBySomething(ui);
        }
        else if (option == 6)
        {
            int undoResult = undoUI(ui);
            if (undoResult == 1)
            {
                printf("Operation successfully undone ! \n");
            }
            else
            {
                printf("Operation cannot be undone ! \n");
            }
        }
        else if (option == 7)
        {
            int redoResult = redoUI(ui);
            if (redoResult == 1)
            {
                printf("Operation successfully redone ! \n");
            }
            else
            {
                printf("Operation cannot be redone ! \n");
            }
        }
        else if (option == 8)
        {
            print_vector(ui);
        }
        else if (option < 0 || option > 7)
        {
            printf("Invalid option ! Try again !");
        }

    }
}

void tests()
{
    TestMaterial();
    testMaterialRepo();
    testService();
    testDynamicArray();
}

int main() {
    MaterialRepository* materialRepo = createMaterialRepository(30);
    Service* service = createService(materialRepo);
    UI* ui = createUI(service);

    start(ui);

    destoryUI(ui);

   // tests();
    _CrtDumpMemoryLeaks();
}