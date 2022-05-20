// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalTriggerActor.h"
#include "Kismet/GameplayStatics.h"
#include "VehiclePawn.h"



// Sets default values
AGoalTriggerActor::AGoalTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GetRootComponent());

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerComponent->SetupAttachment(MeshComponent);

	Levels.Add("Level1");
	Levels.Add("Level2");
}

// Called when the game starts or when spawned
void AGoalTriggerActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoalTriggerActor::TriggerOnOverlap);
	TriggerComponent->OnComponentEndOverlap.AddDynamic(this, &AGoalTriggerActor::TriggerEndOverlap);
}

// Called every frame
void AGoalTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalTriggerActor::TriggerOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AVehiclePawn::StaticClass()))
	{
		bGoalOverlap = true;
		LapCount++;
	}

	if (LapCount == 8)
	{
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("YOU WIN!!")));
	}

	UWorld* TheWorld = GetWorld();

	FString CurrentLevel = TheWorld->GetMapName();
	CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if (LapCount == 8)
	{
		UE_LOG(LogTemp, Warning, TEXT("change level"))
		if (CurrentLevel == Levels[0])
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Level2");
			UE_LOG(LogTemp, Warning, TEXT("Level 1"))
		}
		if (CurrentLevel == Levels[1])
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Level1");
			UE_LOG(LogTemp, Warning, TEXT("Level 2"))
		}

		
	}
	
}

void AGoalTriggerActor::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bGoalOverlap = false;
	if (OtherActor->IsA(AVehiclePawn::StaticClass()) && LapCount < 9)
	{
		
		switch (LapCount)
		{
			case 2:
			{
				CurrentLap = 1;
				break;
			}
			case 4:
			{
				CurrentLap = 2;
				break;
			}
			case 6:
			{
				CurrentLap = 3;
				break;
			}
		}

		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("LAP  %d "), CurrentLap));
	}
	
}

