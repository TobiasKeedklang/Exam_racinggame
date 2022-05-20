// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SplineActor.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class RACEGAME_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	ASplineActor* SplinePtr;


	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UTextBlock* HealthNum;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		class UProgressBar* HealthBar;
};
