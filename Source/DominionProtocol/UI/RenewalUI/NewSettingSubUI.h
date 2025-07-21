// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/UIInterface.h"
#include "NewSettingSubUI.generated.h"

class USoundInstanceSubsystem;

UCLASS()
class DOMINIONPROTOCOL_API UNewSettingSubUI : public UUserWidget, public IUIInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetMasterVolumeValue(const float NewVolumeValue);

	UFUNCTION(BlueprintCallable)
	void SetBackgroundMusicVolumeValue(const float NewVolumeValue);

	UFUNCTION(BlueprintCallable)
	void SetSoundEffectsVolumeValue(const float NewVolumeValue);

	UFUNCTION(BlueprintCallable)
	void SetUIEffectsVolumeValue(const float NewVolumeValue);

	UFUNCTION()
	virtual UInputMappingContext* GetInputMappingContext_Implementation() const override;


protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ApplyMasterVolumeValue(float NewVolumeValue);
	UFUNCTION(BlueprintCallable)
	void ApplyBackgroundMusicVolumeValue(float NewVolumeValue);
	UFUNCTION(BlueprintCallable)
	void ApplySoundEffectsVolumeValue(float NewVolumeValue);
	UFUNCTION(BlueprintCallable)
	void ApplyUIEffectsVolumeValue(float NewVolumeValue);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MasterVolumeValue = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float BackgroundMusicVolumeValue = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SoundEffectsVolumeValue = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float UIEffectsVolumeValue = 1.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DesiredMasterVolumeValue = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DesiredBackgroundMusicVolumeValue = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DesiredSoundEffectsVolumeValue = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DesiredUIEffectsVolumeValue = 1.0f;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USoundInstanceSubsystem> SoundSubsystemInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> SettingSubUIMappingContext;
	
};