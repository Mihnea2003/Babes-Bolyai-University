#include "Material.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"

Material* createMaterial(char name[], char supplier[], int quantity, double expiration_date)
{
    Material* material = (Material*)malloc(sizeof(Material));
    if (material == NULL) {
        return NULL;
    }
    material->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    if (material->name != NULL) {
        memcpy(material->name, name, strlen(name) + 1);
    }
    material->supplier = (char*)malloc(sizeof(char) * (strlen(supplier) + 1));
    if (material->supplier != NULL) {
        memcpy(material->supplier, supplier, strlen(supplier) + 1);
    }
    material->quantity = quantity;
    material->expiration_date = expiration_date;

    return material;
}

void destroyMaterial(Material * material)
{
    if (material == NULL) {
        return;
    }

    free(material->name);

    free(material);
    material = NULL;
}

Material* copyMaterial(Material * material)
{
    if (material == NULL) {
        return NULL;
    }
    Material* material1 = createMaterial(material->name, material->supplier, material->quantity, material->expiration_date);
    return material1;
}

char* getName(Material* material)
{
    if (material == NULL) {
        return NULL;
    }
    return material->name;
}

char* getSupplier(Material * material)
{
    if (material == NULL) {
        return NULL;
    }
    return material->supplier;
}

int getQuantity(Material * material)
{
    if (material == NULL) {
        return -1;
    }
    return material->quantity;
}

double getExpirationDate(Material * material)
{
    if (material == NULL) {
        return -1;
    }
    return material->expiration_date;
}

void setSupplier(Material * material, char* newSupplier)
{
    material->supplier = newSupplier;
}

void setQuantity(Material* material, int newQuantity)
{
    material->quantity = newQuantity;
}

void setExpirationDate(Material* material, double newExpirationDate)
{
    material->expiration_date = newExpirationDate;
}

void toString(Material* material, char str[])
{
    if (material == NULL) {
        return;
    }
    printf_s(str, "Name: %s; Supplier: %s; Quantity: %d; Expiration Date: %.2lf", material->name,
        material->supplier, material->quantity, material->expiration_date);
}

void TestMaterial()
{
    Material* material = createMaterial("Faina", "Bunica", 10, 8);
    assert(strcmp(getName(material), "Faina")==0);
    assert(strcmp(getSupplier(material), "Bunica")==0);
    assert(getQuantity(material)== 10);
    assert(getExpirationDate(material)== 8);
    setSupplier(material, "Proxi");
    assert(strcmp(getSupplier(material), "Proxi")==0);
    setQuantity(material, 100);
    assert(getQuantity(material)== 100);
    setExpirationDate(material, 15);
    assert(getExpirationDate(material)== 15);
}
