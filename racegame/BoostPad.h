// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "VehiclePawn.h"
#include "BoostPad.generated.h"

UCLASS()
class RACEGAME_API ABoostPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoostPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* PadMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		UBoxComponent* Hitbox = nullptr;

	//UFUNCTION()
	//	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	//		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult);
};
