// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCache.h"

// Sets default values
AAmmoCache::AAmmoCache()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CacheMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CacheMesh"));
	CacheMesh->SetupAttachment(GetRootComponent());
	CacheMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AAmmoCache::BeginPlay()
{
	Super::BeginPlay();
	//CacheMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoCache::OnOverlap);
}

// Called every frame
void AAmmoCache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoCache::ImHit()
{
	this->Destroy();
}

//void AAmmoCache::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
//	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Collision but not enemy"))
//		if (OtherActor->IsA(AAmmoCache::StaticClass()))
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Collision happening in Vehicle"))
//				//Activates self destruction of cache
//				Cast<AVehiclePawn>(OtherActor)->Reload();
//			AAmmoCache::ImHit();
//			this->Destroy();
//		}
//
//}
