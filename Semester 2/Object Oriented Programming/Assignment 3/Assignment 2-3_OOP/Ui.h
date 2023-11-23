#pragma once
#include "Service.h"
#include "Material.h"
#include "MaterialRepo.h"

typedef struct {
	Service* service;
} UI;

UI* createUI(Service* service);

void destoryUI(UI* ui);

void printMenu();

int addMaterialUI(UI* ui);

int deleteMaterialUI(UI* ui);

int updateMaterialUI(UI* ui);

void start(UI* ui);

void tests();
