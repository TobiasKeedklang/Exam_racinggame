// Fill out your copyright notice in the Description page of Project Settings.


#include "Countdown.h"
#include "VehiclePawn.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Countdown"));
	CountdownText->SetWorldSize(300.0f);
	CountdownText->SetTextRenderColor(FColor::Blue);
	RootComponent = CountdownText;

	Seconds = 3;

}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
	TimerUpdate();
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::TimerTick, 1.0f, true);

	
}

// Called every frame
void ACountdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountdown::TimerUpdate()
{
	CountdownText->SetText(FText::AsNumber(Seconds));
}

void ACountdown::TimerTick()
{
	TimerUpdate();
	if (Seconds < 1)
	{
		TimerFinish();
	}
	if (Seconds < 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
		Destroy();
	}
	Seconds--;
}

void ACountdown::TimerFinish()
{
	AVehiclePawn* Player = Cast<AVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	Player->bEnableInput = true;
}

