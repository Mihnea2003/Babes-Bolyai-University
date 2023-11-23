#include "Service.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

Service* createService(MaterialRepository* materialRepo)
{
    Service* service = (Service*)malloc(sizeof(Service));
    if (service == NULL) {
        return NULL;
    }
    service->materialRepository = materialRepo;
    addTenElements(service->materialRepository);
    service->undoStack = createDynamicArray(10, (DestroyElementFunction)destroyMaterialRepository, (CopyElementFunction)copyMaterialRepo);
    addElement(service->undoStack, copyMaterialRepo(service->materialRepository));
    service->undoPointer = -1;
    return service;
}

void destroyService(Service* service)
{
    if (service == NULL) {
        return;
    }
    destroyMaterialRepository(service->materialRepository);
    destroyDynamicArray(service->undoStack);
    free(service);
    service = NULL;
}

MaterialRepository* getMaterialRepository(Service* service)
{
    return service->materialRepository;
}

void correctUndoPointer(Service* serv)
{
    while (getArrayLength(serv->undoStack) - 2 != serv->undoPointer)
        deleteElement(serv->undoStack, getArrayLength(serv->undoStack) - 1);
}

void addToUndoList(Service* serv)
{
    correctUndoPointer(serv);
    addElement(serv->undoStack, copyMaterialRepo(serv->materialRepository));
    serv->undoPointer++;
}

int add(Service* service, char* name, char* supplier, int quantity, double expiration_date)
{
    Material* material = createMaterial(name, supplier, quantity, expiration_date);
    int returnValue = addMaterial(service->materialRepository, material);
    if (returnValue == 1)
    {
        addToUndoList(service);
    }
    return returnValue;
}

int deleteMaterialServ(Service* service, char* name, char* supplier, double expiration_date)
{
    int returnValue = deleteMaterial(service->materialRepository, name, supplier, expiration_date);
    if (returnValue == 1)
    {
        addToUndoList(service);
    }
    return returnValue;
}

int update(Service* service, char* name, char*supplier, double expiration_date, int new_quantity)
{
    int returnValue = updateMaterial(service->materialRepository, name,supplier, expiration_date, new_quantity);
    if (returnValue == 1)
    {
        addToUndoList(service);
    }
    return returnValue;
}

DynamicArray* getMaterials(Service* serv)
{
    if (serv == NULL)
    {
        return NULL;
    }

    return getRepoMaterials(serv->materialRepository);
}

DynamicArray* getMaterialsByQuantity(Service* serv, int quantity)
{
    if (serv == NULL || quantity < 0) {
        return NULL;
    }

    DynamicArray* materials = getMaterials(serv);
    DynamicArray* result = createDynamicArray(materials->capacity, (DestroyElementFunction)destroyMaterial, (CopyElementFunction)copyMaterial);

    int count = getArrayLength(materials);
    for (int i = 0; i < count; i++)
    {
        Material* material = (Material*)getElementAtIndex(materials, i);
        if (material->quantity< quantity) {
            Material* copyMaterial = createMaterial(getName(material), getSupplier(material), getQuantity(material), getExpirationDate(material));
            addElement(result, copyMaterial);
        }
    }
    return result;
}

void sortMaterialsVectorAscendingByQuantity(DynamicArray* arr)
{
    if (arr == NULL)
    {
        return;
    }

    int ok = 0;
    do {
        ok = 1;
        for (int i = 1; i < arr->length; i++)
        {
            if (getQuantity((Material*)arr->elements[i]) < getQuantity((Material*)arr->elements[i - 1]))
            {
                ok = 0;
                void* tmp = arr->elements[i];
                arr->elements[i] = arr->elements[i - 1];
                arr->elements[i - 1] = tmp;
            }
        }
    } while (!ok);
}

void sortMaterialsVectorDescendingByQuantity(DynamicArray* arr)
{
    if (arr == NULL)
    {
        return;
    }

    int ok = 0;
    do {
        ok = 1;
        for (int i = 1; i < arr->length; i++)
        {
            if (getQuantity((Material*)arr->elements[i]) > getQuantity((Material*)arr->elements[i - 1]))
            {
                ok = 0;
                void* tmp = arr->elements[i];
                arr->elements[i] = arr->elements[i - 1];
                arr->elements[i - 1] = tmp;
            }
        }
    } while (!ok);
}

int undo(Service* serv)
{
    int undoStackLength = getArrayLength(serv->undoStack);
    if (undoStackLength <= 1 || serv->undoPointer < 0)
    {
        return 0;
    }
    else
    {
        destroyMaterialRepository(serv->materialRepository);
        serv->materialRepository = copyMaterialRepo((MaterialRepository*)getElementAtIndex(serv->undoStack, serv->undoPointer));
        serv->undoPointer--;
        return 1;
    }
}

int redo(Service* serv)
{
    int undoStackLength = getArrayLength(serv->undoStack);
    if (serv->undoPointer == undoStackLength - 2 || serv->undoPointer < -1)
    {
        return 0;
    }
    else
    {
        destroyMaterialRepository(serv->materialRepository);
        serv->materialRepository = copyMaterialRepo((MaterialRepository*)getElementAtIndex(serv->undoStack, serv->undoPointer + 2));
        serv->undoPointer++;
        return 1;
    }
}

DynamicArray* getMaterialsByName(Service* serv, char* name)
{
    if (serv == NULL || name == NULL)
    {
        return NULL;
    }

    DynamicArray* meds = getMaterials(serv);
    DynamicArray* result = createDynamicArray(meds->capacity, (DestroyElementFunction)destroyMaterial, (CopyElementFunction)copyMaterial);

    int count = getArrayLength(meds);
    for (int i = 0; i < count; i++)
    {
        Material* material = (Material*)getElementAtIndex(meds, i);
        if (strstr(getName(material), name))
        {
            Material* copyMaterial = createMaterial(getName(material), getSupplier(material), getQuantity(material), getExpirationDate(material));
            addElement(result, copyMaterial);
        }
    }
    return result;
}

DynamicArray* getMaterialsByExpirationDate(Service* serv, int expiration_date)
{
    if (serv == NULL || expiration_date < 0) {
        return NULL;
    }

    DynamicArray* materials = getMaterials(serv);
    DynamicArray* result = createDynamicArray(materials->capacity, (DestroyElementFunction)destroyMaterial, (CopyElementFunction)copyMaterial);

    int count = getArrayLength(materials);
    for (int i = 0; i < count; i++)
    {
        Material* material = (Material*)getElementAtIndex(materials, i);
        if (material->expiration_date < expiration_date) {
            Material* copyMaterial = createMaterial(getName(material), getSupplier(material), getQuantity(material), getExpirationDate(material));
            addElement(result, copyMaterial);
        }
    }
    return result;
}



void testService()
{
    MaterialRepository* materialRepo = createMaterialRepository(15);
    Service* serv = createService(materialRepo);

    add(serv, "abcd", "mer", 10, 8);
    assert(getMaterialRepoLength(serv->materialRepository)== 11);

    update(serv, "abcd", "mer", 100, 100);
    assert(getQuantity((Material*)serv->materialRepository->materialsData->elements[10])== 100);
    assert(getExpirationDate((Material*)materialRepo->materialsData->elements[10])== 100);

    DynamicArray* materialsByName = getMaterialsByName(serv, "abcd");
    assert(materialsByName->length== 1);
    destroyDynamicArray(materialsByName);

    DynamicArray* materialsByQuantity = getMaterialsByQuantity(serv, 101);
    assert(materialsByQuantity->length== 1);
    destroyDynamicArray(materialsByQuantity);

    DynamicArray* materialsbyExpirationDate = getMaterialsByExpirationDate(serv, 500);
    assert(materialsbyExpirationDate->length== 11);
    destroyDynamicArray(materialsbyExpirationDate);

    deleteMaterialServ(serv, "algocalmin", "mer",100);
    assert(serv->materialRepository->materialsData->elements== NULL);

    undo(serv);
    assert(serv->materialRepository->materialsData->length== 11);

    redo(serv);
    assert(serv->materialRepository->materialsData->elements== NULL);

    destroyService(serv);
    assert(serv== NULL);
}