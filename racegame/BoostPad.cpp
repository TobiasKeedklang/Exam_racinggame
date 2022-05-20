// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostPad.h"

// Sets default values
ABoostPad::ABoostPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PadMesh->SetupAttachment(GetRootComponent());

	Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABoostPad::BeginPlay()
{
	Super::BeginPlay();
	
	//Hitbox->OnComponentBeginOverlap.AddDynamic(this, &ABoostPad::OnOverlap);
}

// Called every frame
void ABoostPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ABoostPad::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
//	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Collision but not enemy"))
//		if (OtherActor->IsA(AVehiclePawn::StaticClass()))
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Collision happening in Vehicle"))
//				//Activates self destruction of cache
//				Cast<AVehiclePawn>(OtherActor)->bBoost=true;
//		}
//
//}
