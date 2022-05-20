// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GamePlayStatics.h"
#include "VehiclePawn.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class RACEGAME_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	AVehiclePawn* PlayerShipPtr2 = Cast<AVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UTextBlock* AmmoNum;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	class UProgressBar* AmmoBar;

	/*  UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		  class UTextBlock* SpeedNum;*/
};
