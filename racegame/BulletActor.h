// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "VehiclePawn.h"

#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class RACEGAME_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
		UStaticMeshComponent* BulletMesh = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = "Bullet");
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Bullet");
	float TimeBeforeDestroy = 5.f;

	UPROPERTY(EditAnywhere, Category = "Bullet");
	float TimeLived = 0.f

	UPROPERTY(EditAnywhere, Category = "Bullet");
	UParticleSystem* Bulletfire = nullptr;

	UPROPERTY(EditAnywhere, Category = "Bullet");
	USoundBase* BullerFireSound = nullptr;
};
