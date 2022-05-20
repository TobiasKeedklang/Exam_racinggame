// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	float Health = SplinePtr->GetHealth();
	float MaxHealth = 500.f;


	if (SplinePtr)
	{
		FString CurrentHealth = "Health: ";
		CurrentHealth.Append(FString::FromInt(Health));
		HealthNum->SetText(FText::FromString(CurrentHealth));

		HealthBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
		HealthBar->SetPercent(Health / MaxHealth);
	}


	else 
	{
		return;
	}
}
