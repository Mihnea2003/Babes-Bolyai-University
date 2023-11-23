#pragma once

typedef struct
{
	char* name;
	char* supplier;
	int quantity;
	double expiration_date;
} Material;

/// <summary>
/// This function creates a material.
/// </summary>
/// <param name="name"></param>
/// <param name="supplier"></param>
/// <param name="quantity"></param>
/// <param name="expiration_date"></param>
/// <returns></returns>
Material* createMaterial(const char* name, const char* supplier, int quantity, double expiration_date);

/// <summary>
/// This function destroys a material.
/// </summary>
/// <param name="material"></param>
void destroyMaterial(Material* material);

Material* copyMaterial(Material* material);

/// <summary>
/// This function gets the name of a material.
/// </summary>
/// <param name="material"></param>
/// <returns> The name of the material.</returns>
char* getName(Material* material);

/// <summary>
/// This function gets the name of the supplier of a material.
/// </summary>
/// <param name="material"></param>
/// <returns> The supplier of the material. </returns>
char* getSupplier(Material* material);

/// <summary>
/// This function gets the quantity of a material.
/// </summary>
/// <param name="material"></param>
/// <returns> The quantity of the material. </returns>
int getQuantity(Material* material);

/// <summary>
/// This function gets the price of a material.
/// </summary>
/// <param name="material"></param>
/// <returns> The expiration date of the material. </returns>
double getExpirationDate(Material* material);

/// <summary>
/// This function sets the supplier of a given material.
/// </summary>
/// <param name="material"></param>
/// <param name="newSupplier"></param>
void setSupplier(Material* material, const char* newSupplier);

/// <summary>
/// This function sets the quantity of a given material.
/// </summary>
/// <param name="material"></param>
/// <param name="newQuantity"></param>
void setQuantity(Material* material, int newQuantity);

/// <summary>
/// This function sets the expiration date of a given material.
/// </summary>
/// <param name="material"></param>
/// <param name="newExpirationDate"></param>
void setExpirationDate(Material* material, double newExpirationDate);

void toString(Material* material, char str[]);

void TestMaterial();

