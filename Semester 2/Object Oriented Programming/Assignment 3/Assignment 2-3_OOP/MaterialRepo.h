#pragma once
#include "Material.h"
#include "DynamicArray.h"
#include <stdlib.h>

typedef struct {
	DynamicArray* materialsData;
} MaterialRepository;

/// <summary>
/// This function creates a material repository with the given capacity.
/// </summary>
/// <param name="capacity"></param>
/// <returns> The created repository. </returns>
MaterialRepository* createMaterialRepository(int capacity);

/// <summary>
/// This function destroys the given medication repository.
/// </summary>
/// <param name="medRepo"></param>
void destroyMaterialRepository(MaterialRepository* materialRepo);

/// <summary>
/// This function gets the length of the material repository.
/// </summary>
/// <param name="materialRepo"></param>
/// <returns> The length. </returns>
int getMaterialRepoLength(MaterialRepository* materialRepo);

/// <summary>
/// This function searches if a material with the given name, supplier and expiration date exists in the repository.
/// </summary>
/// <param name="materialRepo"></param>
/// <param name="name"></param>
/// <param name="supplier"></param>
/// <param name="expiration date"></param>
/// <returns> the position if it exists, else -1 </returns>
int findMaterial(MaterialRepository* materialRepo, char name[], char supplier[], double expiration_date);

/// <summary>
/// This function adds a material to the repository.
/// </summary>
/// <param name="materialRepo"></param>
/// <param name="material"></param>
/// <returns> 1 if the material was successfully added, else 0 </returns>
int addMaterial(MaterialRepository* materialRepo, Material* material);

/// <summary>
/// This function adds 10 materials to the repository.
/// </summary>
/// <param name="materialRepo"></param>
void addTenElements(MaterialRepository* materialRepo);

/// <summary>
/// This function deletes a material with the given name,supplier and expiration date from the repository.
/// </summary>
/// <param name="materialRepo"></param>
/// <param name="name"></param>
/// <param name="supplier"></param>
/// <param name="expiration date"></param>
/// <returns> 1 if the material was successfully deleted, else 0 </returns>
int deleteMaterial(MaterialRepository* materialRepo,const char* name, const char* supplier, double expiration_date);

/// <summary>
/// This function updates a material with the given name,supplier and expiration date.
/// </summary>
/// <param name="materialRepo"></param>
/// <param name="name"></param>
/// <param name="supplier"></param>
/// <param name="expiration date"></param>
/// <param name="newQuantity"></param>
/// <returns> 1 if the material was successfully updated, else 0 </returns>
int updateMaterial(MaterialRepository* materialRepo, const char* name, const char*supplier, double expiration_date, int newQuantity);

/// <summary>
/// This function gets the data from the material repository.
/// </summary>
/// <param name="materialRepo"></param>
/// <returns></returns>
DynamicArray* getRepoMaterials(MaterialRepository* materialRepo);

MaterialRepository* copyMaterialRepo(MaterialRepository* materialRepo);

void testMaterialRepo();
