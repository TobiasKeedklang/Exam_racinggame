// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "VehiclePawn.h"

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PlayerShipPtr2) 
	{
		float Ammo = PlayerShipPtr2->GetAmmo();
		float MaxAmmo = PlayerShipPtr2->GetMaxAmmo();
   

		FString CurrentAmmo = "Ammo: ";
		CurrentAmmo.Append(FString::FromInt(Ammo));
		AmmoNum->SetText(FText::FromString(CurrentAmmo));
        
		if (Ammo < 5)
		{
			AmmoBar->SetFillColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
		}
		if (Ammo > 15 && Ammo <= 30)
		{
			AmmoBar->SetFillColorAndOpacity(FLinearColor(0.f, 0.49f, 1.f));
		}
		AmmoBar->SetPercent(Ammo / MaxAmmo);
	}
	
    
	else {
		return;
	}
}