// Fill out your copyright notice in the Description page of Project Settings.


#include "MeowMeow.h"

// Sets default values
AMeowMeow::AMeowMeow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	CatMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMeowMeow::BeginPlay()
{
	Super::BeginPlay();
	CatMesh->OnComponentBeginOverlap.AddDynamic(this, &AMeowMeow::OnOverlap);
}

// Called every frame
void AMeowMeow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();

	SetActorRotation(MoveDirection.Rotation());

	if (RootComponent)
	{
		RootComponent->AddRelativeLocation(GetActorForwardVector() * Speed);
	}

}

void AMeowMeow::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	if (OtherActor->IsA(AVehiclePawn::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Health dropped to %d"), Health)
		Health = Health - 5;
	}
}
