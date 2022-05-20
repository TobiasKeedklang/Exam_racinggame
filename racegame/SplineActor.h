// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletActor.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SplineActor.generated.h"

UCLASS()
class RACEGAME_API ASplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineActor();

	virtual void OnConstruction(const FTransform& Transform) override;
	
		
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ProcessMovementTimeline(float Value);
	UFUNCTION()
	void OnEndMovementTimeline();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline", meta=(AllowPrivateAccess = "true"))
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	UBoxComponent* Hitbox;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* HealthWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline");
	UCurveFloat* MovementCurve;

	float Health = 500.f;
	int32 Seconds;
	FTimerHandle CountdownTimerHandle;

	void TimerTick();
	void TimerFinish();
	int GetHealth();

	bool bStart = false;

	TArray<FString> Levels;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult);
private:
	FTimeline MovementTimeline;


};
