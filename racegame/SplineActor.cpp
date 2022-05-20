// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineActor.h"

#include "Components/WidgetComponent.h"
#include "MeowMeow.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
ASplineActor::ASplineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineComponent->SetupAttachment(GetRootComponent());

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(SplineComponent);

	Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(MeshComponent);

	//HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	//HealthWidgetComp->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

    if (SplineComponent)
    {
	    SetRootComponent(SplineComponent);
    	
    }
	Seconds = 3;
	Levels.Add("Level1");
	Levels.Add("Level2");
}

void ASplineActor::OnConstruction(const FTransform& Transform)
{
	
}

// Called when the game starts or when spawned
void ASplineActor::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, TEXT("ProcessMovementTimeline"));
	MovementTimeline.AddInterpFloat(MovementCurve, ProgressFunction);

	FOnTimelineEvent OnTimelineFinishedFunction;
	OnTimelineFinishedFunction.BindUFunction(this,  TEXT("OnEndMovementTimeline"));
	MovementTimeline.SetTimelineFinishedFunc(OnTimelineFinishedFunction);

	MovementTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
	MovementTimeline.Play();

	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &ASplineActor::TimerTick, 1.0f, true);
	
	MovementTimeline.SetLooping(true);

	UWorld* TheWorld = GetWorld();
	FString CurrentWorld = TheWorld->GetMapName();
	CurrentWorld.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if (CurrentWorld == Levels[0])
	{
		UE_LOG(LogTemp, Warning, TEXT("reverse"))
		MovementTimeline.ReverseFromEnd();
	}
	if (CurrentWorld == Levels[1])
	{
		UE_LOG(LogTemp, Warning, TEXT("propper"))
		MovementTimeline.Play();
	}
	
	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &ASplineActor::OnOverlap);
}

// Called every frame
void ASplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStart == true)
	{
		if (MovementTimeline.IsPlaying())
		{
			MovementTimeline.TickTimeline(DeltaTime);
		}
	}

	

}


void ASplineActor::TimerTick()
{
	if (Seconds < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Start"))
		TimerFinish();
	}
	if (Seconds < 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Start2"))
		
	}
	Seconds--;
}

void ASplineActor::TimerFinish()
{
	UE_LOG(LogTemp, Warning, TEXT("Start3"))
		bStart = true;
}

void ASplineActor::ProcessMovementTimeline(float Value)
{
	const float SplineLength = SplineComponent->GetSplineLength();

	FVector CurrentSplineLocation = SplineComponent->GetLocationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);
	FRotator CurrentSplineRotation = SplineComponent->GetRotationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);

	MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, CurrentSplineRotation);
}

void ASplineActor::OnEndMovementTimeline()
{
	
}


void ASplineActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision on enemy"))
		if (OtherActor->IsA(ABulletActor::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("DAMAGE"))
			this->Health = Health -50.f;
			if (Health == 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("YOU Win!!")));
				UGameplayStatics::OpenLevel(GetWorld(), "Menu");
			}
		}
}

int ASplineActor::GetHealth()
{
	return Health;
}
	