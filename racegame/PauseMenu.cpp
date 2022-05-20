// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UPauseMenu::OnContinueClicked);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UPauseMenu::OnRestartClicked);
	}
}

void UPauseMenu::OnContinueClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(),false);
	RemoveFromParent();
}

void UPauseMenu::OnRestartClicked()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
}
