// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class RACEGAME_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ContinueButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	 UButton* RestartButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnContinueClicked();
	UFUNCTION()
	void OnRestartClicked();
	
};
