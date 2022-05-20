// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "VehiclePawn.generated.h"

UCLASS()
class RACEGAME_API AVehiclePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehiclePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root")
	class USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* VehicleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		UBoxComponent* Hitbox = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	class UPawnMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MoveSpeed = 30.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float ForwardForce = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float BoostLength = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float BoostDuration= 4.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bBoost = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bStop = false;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Triggers")
		bool bShooting = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "triggers")
		bool bRotation = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "triggers")
		bool bSwap = false;
	
	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* AmmoWidgetComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		int Ammo = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		int MaxAmmo = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int Rotation = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UUserWidget> PauseWidgetClass;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	USoundBase* ShootingSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	USoundBase* ReloadingSound = nullptr;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ActorToSpawn;

	void Reload();
	void Shoot();
	int GetAmmo();
	int GetMaxAmmo();
	void OnPause();

	bool bEnableInput = false;
	
private:
	void MoveZAxis(float Value);
	void MoveYAxis(float Value);
	void RotateCam(float value);
	void CameraSwap();

	float ZValue;
	float YValue;

};
