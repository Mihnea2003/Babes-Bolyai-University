#pragma once
#include "MaterialRepo.h"

typedef struct {
	MaterialRepository* materialRepository;
	DynamicArray* undoStack;
	int undoPointer;
} Service;

/// <summary>
/// This function creates the service.
/// </summary>
/// <param name="materialRepo"></param>
/// <returns> The created service. </returns>
Service* createService(MaterialRepository* materialRepo);

/// <summary>
/// This function destroys the service.
/// </summary>
/// <param name="service"></param>
void destroyService(Service* service);

/// <summary>
/// This function gets the material repository.
/// </summary>
/// <param name="service"></param>
/// <returns> the material repository </returns>
MaterialRepository* getMaterialRepository(Service* service);

/// <summary>
/// This function creates a material with the given name, supplier, quantity and expiration date and the it adds it 
/// to the repository.
/// </summary>
/// <param name="service"></param>
/// <param name="name">: the name of the material to be added </param>
/// <param name="supplier">: the supplier of the material to be added </param>
/// <param name="quantity">: the quantity of the material to be added </param>
/// <param name="expiration date">: the expiration date of the material to be added </param>
/// <returns> 1 if the material was successfully added, else 0 </returns>
int add(Service* service,const char* name,const char* supplier, int quantity, double expiration_date);

/// <summary>
/// This function deletes the material with the given name,supplier and expiration date.
/// </summary>
/// <param name="service"></param>
/// <param name="name">: the name of the material to be deleted </param>
/// <param name="supplier">: the supplier of the material to be deleted </param>
/// <param name="expiration date">: the expiration date of the material to be deleted </param>
/// <returns> 1 if the material was successfully deleted, else 0 </returns>
int deleteMaterialServ(Service* service,const char* name,const char* supplier, double expiration_date);

/// <summary>
/// This function updates the quantity of a material with given name,supplier and expiration date.
/// </summary>
/// <param name="service"></param>
/// <param name="name">: the name of the material to be updated </param>
/// <param name="supplier">: the supplier of the material to be updated </param>
/// <param name="expiration date">: the expiration date of the material to be updated </param>
/// <param name="new_quantity">: the new quantity of the material</param>
/// <returns> 1 if the material was successfully updated, else 0 </returns>
int update(Service* service,const char* name,const char* supplier, double expiration_date, int new_quantity);

/// <summary>
/// This function gets the materials.
/// </summary>
/// <param name="serv"></param>
/// <returns> The array of materials.</returns>
DynamicArray* getMaterials(Service* serv);

/// <summary>
/// This function creates an array with the materials that contain a given string in their name.
/// If the given string is -1 it returns all the materials.
/// </summary>
/// <param name="serv"></param>
/// <param name="name">: the given name </param>
/// <returns> the array of materials with the given string. </returns>
DynamicArray* getMaterialsByName(Service* serv,const char* name);

/// <summary>
/// This function creates an array with the materials that are in short supply (their quantity is less than a
/// given quantity).
/// </summary>
/// <param name="serv"></param>
/// <param name="quantity">: the given quantity </param>
/// <returns> the array of materials in short supply. </returns>
DynamicArray* getMaterialsByQuantity(Service* serv, int quantity);

/// <summary>
/// This function creates an array with the materials that have a price smaller than a given price.
/// </summary>
/// <param name="serv"></param>
/// <param name="price">: the given price </param>
/// <returns> the array of medications with the smaller price. </returns>
DynamicArray* getMaterialsByExpirationDate(Service* serv, double expiration_date);

/// <summary>
/// This function sorts the array of materials ascending by their quantity.
/// </summary>
/// <param name="arr">: the array of materials</param>
void sortMaterialsVectorAscendingByQuantity(DynamicArray* arr);

/// <summary>
/// This function sorts the array of materials descending by their quantity.
/// </summary>
/// <param name="arr">: the array of materials</param>
void sortMaterialsVectorDescendingByQuantity(DynamicArray* arr);

/// <summary>
/// This function undoes the last operation
/// </summary>
/// <returns> 1 if the operation was successfully undone, else 0</returns>
int undo(Service* serv);

/// <summary>
/// This function redoes the last operation
/// </summary>
/// <returns> 1 if the operation was successfully redone, else 0</returns>
int redo(Service* serv);

void testService();
