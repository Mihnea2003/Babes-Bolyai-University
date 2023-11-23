#include "MaterialRepo.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "assert.h"

MaterialRepository* createMaterialRepository(int capacity)
{
    MaterialRepository* materialRepo = (MaterialRepository*)malloc(sizeof(MaterialRepository));
    if (materialRepo == NULL) {
        return NULL;
    }

    materialRepo->materialsData = createDynamicArray(capacity, (DestroyElementFunction)destroyMaterial, (CopyElementFunction)copyMaterial);

    return materialRepo;
}

void destroyMaterialRepository(MaterialRepository* materialRepo)
{
    if (materialRepo == NULL) {
        return;
    }

    destroyDynamicArray(materialRepo->materialsData);
    free(materialRepo);
    materialRepo = NULL;
}

int getMaterialRepoLength(MaterialRepository* materialRepo)
{
    return materialRepo->materialsData->length;
}

int findMaterial(MaterialRepository* materialRepo, char name[], char supplier[],double expiration_date)
{
    int length = getMaterialRepoLength(materialRepo);
    for (int i = 0; i < length; i++) {
        if (strcmp(getName((Material*)materialRepo->materialsData->elements[i]), name) == 0 &&
            getExpirationDate((Material*)materialRepo->materialsData->elements[i]) == expiration_date) {
            if (strcmp(getSupplier((Material*)materialRepo->materialsData->elements[i]), supplier) == 0) {
                return i;
            }
        }
    }
    return -1;
}

int addMaterial(MaterialRepository* materialRepo, Material* material)
{
    int position = findMaterial(materialRepo, material->name, material->supplier, material->expiration_date);
    if (position == -1) {
        addElement(materialRepo->materialsData, material);
        return 1;
    }
    else {
        Material* oldMaterial = (Material*)getElementAtIndex(materialRepo->materialsData, position);
        updateMaterial(materialRepo, material->name, material->supplier, material->expiration_date , oldMaterial->quantity);
        destroyMaterial(material);
        return 1;
    }
    return 0;
}


void addTenElements(MaterialRepository* materialRepo)
{
    addMaterial(materialRepo, createMaterial("Ulei", "Bunica", 50, 10.5));
    addMaterial(materialRepo, createMaterial("Faina", "Bunica", 35, 8));
    addMaterial(materialRepo, createMaterial("Sare", "Kaufland", 80, 15));
    addMaterial(materialRepo, createMaterial("Piper", "Kaufland", 60, 35));
    addMaterial(materialRepo, createMaterial("Grau", "Bunica", 15, 12.3));
    addMaterial(materialRepo, createMaterial("Apa", "Aquavia", 100, 15));
    addMaterial(materialRepo, createMaterial("Suc", "Proxi", 70, 24));
    addMaterial(materialRepo, createMaterial("Tarate", "Proxi", 45, 6));
    addMaterial(materialRepo, createMaterial("Zahar", "Kristal", 50, 18));
    addMaterial(materialRepo, createMaterial("Gem", "Bunica", 90, 40));
}

int deleteMaterial(MaterialRepository* materialRepo, char name[], char supplier[],double expiration_date)
{
    int position = findMaterial(materialRepo, name, supplier, expiration_date);
    if (position != -1) {
        deleteElement(materialRepo->materialsData, position);
        return 1;
    }
    else {
        return 0;
    }
}

int updateMaterial(MaterialRepository* materialRepo, char* name, char* supplier, double expiration_date, int newQuantity)
{
    int count = getArrayLength(materialRepo->materialsData);
    for (int i = 0; i < count; i++)
    {
        Material* material = (Material*)getElementAtIndex(materialRepo->materialsData, i);
        if (strcmp(getName(material), name) == 0 && getExpirationDate(material) == expiration_date && strcmp(getSupplier(material), name) == 0)
        {
            setQuantity(material, newQuantity);
            return 1;
        }
    }

    return 0;
}

DynamicArray* getRepoMaterials(MaterialRepository* materialRepo)
{
    if (materialRepo == NULL)
    {
        return NULL;
    }

    return materialRepo->materialsData;
}

MaterialRepository* copyMaterialRepo(MaterialRepository* materialRepo)
{
    MaterialRepository* newMaterialRepo = createMaterialRepository(materialRepo->materialsData->capacity);
    destroyDynamicArray(newMaterialRepo->materialsData);
    newMaterialRepo->materialsData = copyDynamicArray(materialRepo->materialsData);
    return newMaterialRepo;
}

void testMaterialRepo()
{
    MaterialRepository* materialRepo = createMaterialRepository(15);
    Material* material = createMaterial("Faina", "Bunica", 10, 8);

    assert(getRepoMaterials(materialRepo)== materialRepo->materialsData);


    addMaterial(materialRepo, material);
    Material* material2 = createMaterial("Faina", "Bunica", 10, 8);
    assert(material == material2);
    assert(materialRepo->materialsData->elements[0] == material);
    assert(getMaterialRepoLength(materialRepo)== 1);

    updateMaterial(materialRepo, "Faina", "Bunica", 100, 100);
    assert(getQuantity((Material*)materialRepo->materialsData->elements[0])== 100);
    assert(getExpirationDate((Material*)materialRepo->materialsData->elements[0])== 100);

    deleteMaterial(materialRepo, "Faina", "Bunica",100);
    assert(materialRepo->materialsData->elements== NULL);

    destroyMaterialRepository(materialRepo);
    assert(materialRepo== NULL);
}