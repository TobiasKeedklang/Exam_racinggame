// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehiclePawn.h"
#include "MeowMeow.generated.h"

UCLASS()
class RACEGAME_API AMeowMeow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeowMeow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* CatMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health = 200.f;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult);

	FVector MoveDirection = FVector(0.f, 0.f, 0.f);
private:
	UPROPERTY(EditAnywhere)
		float Speed = 75.f;
};
