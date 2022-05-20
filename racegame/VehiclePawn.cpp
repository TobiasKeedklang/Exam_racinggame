// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiclePawn.h"

#include "BoostPad.h"
#include "AmmoCache.h"
#include "SplineActor.h"
#include "Blockade.h"

#include <rpcnterr.h>

#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/PlayerInput.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/InputComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVehiclePawn::AVehiclePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	SetRootComponent(Hitbox);

	VehicleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VehicleMeshComponent->SetupAttachment(GetRootComponent());

	

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->SetUsingAbsoluteRotation(false);
	SpringArmComponent->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = 800.f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 10.f;
	SpringArmComponent->SetupAttachment(VehicleMeshComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	AmmoWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("AmmoBar"));
	AmmoWidgetComp->AttachToComponent(VehicleMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	

}

// Called when the game starts or when spawned
void AVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
	
	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &AVehiclePawn::OnOverlap);
}

// Called every frame
void AVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	BoostLength += DeltaTime;

	if (bBoost == true)
	{
		MoveSpeed = 60.f;
		if (SpringArmComponent->TargetArmLength < 1400.f)
		{
			SpringArmComponent->TargetArmLength = SpringArmComponent->TargetArmLength + 20;
		}
	}
	if (bBoost==true && BoostLength > BoostDuration)
	{
		UE_LOG(LogTemp, Warning, TEXT("Boost end"))
		MoveSpeed = 30.f;
		
		bBoost = false;
	}
	if (bBoost==false && SpringArmComponent->TargetArmLength > 800)
	{
		SpringArmComponent->TargetArmLength = SpringArmComponent->TargetArmLength - 20;
	}

	if (bStop == true)
	{
		if (bStop == true && MoveSpeed > 29.f)
		{
			MoveSpeed = 2.f;
		}

		if (bStop==true && MoveSpeed < 30.f)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Engine starting %d"), MoveSpeed)
			MoveSpeed = MoveSpeed+1.f;

			if (MoveSpeed == 30)
			{
				UE_LOG(LogTemp, Warning, TEXT("Engine resume"))
					bStop = false;
			}
		}
	
		
	}

	if (bEnableInput == true)
	{
		AddActorLocalOffset(FVector(ForwardForce, YValue, ZValue) * MoveSpeed, true);
	}
}

static void InitialiseDefaultPawnInputBinding()
{
	static bool BindingsAdded = false;

	if (BindingsAdded == false)
	{
		BindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveZ", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveZ", EKeys::S, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveY", EKeys::D, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveY", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("HorisontalRot", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Shoot", EKeys::SpaceBar));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Roll", EKeys::Q));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("CameraSwap", EKeys::R));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Pause", EKeys::Tab));

	}
}
// Called to bind functionality to input
void AVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InitialiseDefaultPawnInputBinding();

	PlayerInputComponent->BindAxis("MoveZ", this, &AVehiclePawn::MoveZAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AVehiclePawn::MoveYAxis);
	PlayerInputComponent->BindAxis("HorisontalRot", this, &AVehiclePawn::RotateCam);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &AVehiclePawn::Shoot);
	PlayerInputComponent->BindAction("CameraSwap", EInputEvent::IE_Pressed, this, &AVehiclePawn::CameraSwap);
	PlayerInputComponent->BindAction("CameraSwap", EInputEvent::IE_Released, this, &AVehiclePawn::CameraSwap);
	PlayerInputComponent->BindAction("Pause", EInputEvent::IE_Pressed, this, &AVehiclePawn::OnPause);
}

void AVehiclePawn::Shoot()
{
	if (bShooting == true)
	{
		if (Ammo > 0)
		{
			Ammo--;
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, FString::Printf(TEXT("Ammo :  %d "), Ammo));
			UWorld* World = GetWorld();
			if (World)
			{
				FVector Location = GetActorLocation();
				World->SpawnActor<AActor>(ActorToSpawn, Location, GetActorRotation());
				UGameplayStatics::PlaySound2D(World, ShootingSound, 1.f, 1.f, 0.f, 0);
			}
			if (Ammo == 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("Ammo Empty Please find a cache"), Ammo));
			}
		}
	}
}
void AVehiclePawn::Reload()
{
	Ammo = 30.f;
	const UWorld* NewWorld = GetWorld();
	UGameplayStatics::PlaySound2D(NewWorld, ReloadingSound, 1.f, 1.f, 0.f, 0);
	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("Ammo :  %d "), Ammo));
}
int AVehiclePawn::GetAmmo()
{
	return Ammo;
}
int AVehiclePawn::GetMaxAmmo()
{
	return MaxAmmo;
}

void AVehiclePawn::MoveZAxis(float Value)
{
	if (bEnableInput)
	{
		ZValue = Value;
	}
}
void AVehiclePawn::MoveYAxis(float Value)
{
	if (bEnableInput)
	{
		YValue = Value;
	}
}
void AVehiclePawn::RotateCam(float value)
{
	if (value && bRotation == true && bEnableInput==true)
	{
		FRotator PlayerRot(FRotator(0, value, 0));
		AddActorLocalRotation(PlayerRot);
	}
}
void AVehiclePawn::CameraSwap()
{
	if (bEnableInput == true)
	{
		bSwap = !bSwap;

		switch (bSwap)
		{
		case true:
		{
			SpringArmComponent->SetRelativeRotation(FRotator(-15.f, 180.f, 0.f));
			break;
		}
		case false:
		{
			SpringArmComponent->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
			break;
		}
		}
	}
}
void AVehiclePawn::OnPause()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	UUserWidget* PauseWidget = CreateWidget(GetWorld(), PauseWidgetClass);
	if (PauseWidget)
	{
		PauseWidget->AddToViewport();
	}
}

void AVehiclePawn::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
		if (OtherActor->IsA(AAmmoCache::StaticClass()))
		{
				//Activates self destruction of cache
				Cast<AAmmoCache>(OtherActor)->ImHit();
			AVehiclePawn::Reload();
			OtherActor->Destroy();
		}
		else if (OtherActor->IsA(ABoostPad::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Boost initiated"))
				BoostLength = 0.f;
			bBoost = true;
		}
		else if (OtherActor->IsA(ABlockade::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("stop initiated"))
			bStop = true;
			Cast<ABlockade>(OtherActor)->ImHit();

		}
		else if (OtherActor->IsA(ASplineActor::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("YOU LOSE!!")));
			UGameplayStatics::OpenLevel(GetWorld(), "Menu");
		}
}
