// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseContent.h"

void UBaseContent::SetInfo()
{
	
}

void UBaseContent::SetInfoEmpty()
{
	
}

void UBaseContent::RequestChangingFocusIndex() const
{
	RequestChangingFocusIndexEvent.Broadcast(ContentIndex);
}

void UBaseContent::GetFocus()
{
	
}

void UBaseContent::LoseFocus()
{
	
}

void UBaseContent::NativeConstruct()
{
	Super::NativeConstruct();
	
}
