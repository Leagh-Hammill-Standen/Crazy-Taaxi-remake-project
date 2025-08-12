// Fill out your copyright notice in the Description page of Project Settings.


#include "CVehicle.h"

// Sets default values
ACVehicle::ACVehicle()
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(NRootComponent);

	// Create Camera Component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(NRootComponent);
}

// Called when the game starts or when spawned
void ACVehicle::BeginPlay()
{
	Super::BeginPlay();
	

	// Add Input Mapping Context to Subsystem
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(playerMappingContext, 0);
	}
}

// Called every frame
void ACVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (VIsDriving != true && VSpeed <= 0)
	{
		VSpeed -= VdecelerationSpeed;
	}

	//move forward constatly acording to "VSpeed"
	// get direction to face
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//move forward
	AddMovementInput(Direction, VSpeed);
}

// Called to bind functionality to input
void ACVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EIC->BindAction(MoveXAcation, ETriggerEvent::Triggered, this, &ACVehicle::FMoveX);
	EIC->BindAction(MoveXAcation, ETriggerEvent::Triggered, this, &ACVehicle::FMoveY);
	EIC->BindAction(RotateAcation, ETriggerEvent::Triggered, this, &ACVehicle::FRotate);
	
}

//move forward
void ACVehicle::FMoveX(const FInputActionValue& Value)
{
	VIsDriving = true;
	VSpeed = 100;
	if (VSpeed > VMaxSpeed)
	{
		VSpeed += VAccelerationSpeed;
	}
}

void ACVehicle::FMoveY(const FInputActionValue& Value)
{
}

void ACVehicle::FRotate(const FInputActionValue& Value)
{
}

