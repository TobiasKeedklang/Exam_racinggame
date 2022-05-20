// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class RACEGAME_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	int32 Seconds;

	UTextRenderComponent* CountdownText{nullptr};

	void TimerUpdate();
	void TimerTick();
	void TimerFinish();

	FTimerHandle CountdownTimerHandle;

};
