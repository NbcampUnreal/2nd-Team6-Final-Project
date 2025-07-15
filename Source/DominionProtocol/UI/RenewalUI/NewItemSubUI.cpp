// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RenewalUI/NewItemSubUI.h"

UInputMappingContext* UNewItemSubUI::GetInputMappingContext_Implementation() const
{
	if (!ItemSubUIMappingContext)
	{
		return nullptr;	
	}

	return ItemSubUIMappingContext;
}
