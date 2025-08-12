// Fill out your copyright notice in the Description page of Project Settings.


#include "CVehiclePlayer.h"

// Sets default values
ACVehiclePlayer::ACVehiclePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//NRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//SetRootComponent(NRootComponent);

	// Create Camera Component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ACVehiclePlayer::BeginPlay()
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
void ACVehiclePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElectricCar();

	FeulCar();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), VSpeed));

	ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(GetController());
	//if game is paised do not move
	if (PlayerController)
	{
		if (PlayerController->GamePaused == false)
		{
			if (VIsDriving == false && VSpeed <= VMaxSpeed)
			{
				VSpeed -= VdecelerationSpeed;
				VIsDriving = false;
			}
			if (VSpeed > VMaxSpeed)
			{
				VSpeed = VMaxSpeed;
			}
			if (VIsDriving == false && VSpeed < 0)
			{
				VSpeed = 0;
				VIsDriving = false;
			}

			//move forward constatly acording to "VSpeed"
			// get direction to face
			FRotator Rotation = Controller->GetControlRotation();
			FRotator YawRotation(0, Rotation.Yaw, 0);
			FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			//move forward
			AddMovementInput(Direction * VSpeed);
		}
	}

}

// Called to bind functionality to input
void ACVehiclePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EIC->BindAction(MoveXAcation, ETriggerEvent::Triggered, this, &ACVehiclePlayer::FMoveX);
	EIC->BindAction(stopMoveXAcation, ETriggerEvent::Triggered, this, &ACVehiclePlayer::FMoveStopX);
	EIC->BindAction(MoveYAcation, ETriggerEvent::Triggered, this, &ACVehiclePlayer::FMoveY);
	EIC->BindAction(RotateAcation, ETriggerEvent::Triggered, this, &ACVehiclePlayer::FRotate);
	EIC->BindAction(StopRotateAcation, ETriggerEvent::Triggered, this, &ACVehiclePlayer::FStopRotate);
	EIC->BindAction(DriftAction, ETriggerEvent::Triggered, this, &ACVehiclePlayer::FDrift);
	EIC->BindAction(ShopAction, ETriggerEvent::Triggered, this, &ACVehiclePlayer::FShop);
	EIC->BindAction(StopShopAction, ETriggerEvent::Triggered, this, &ACVehiclePlayer::FShopRelise);
}

//move forward
void ACVehiclePlayer::FMoveX(const FInputActionValue& Value)
{
	if (VSpeed < VMaxSpeed)
	{
		VIsDriving = true;
		VSpeed += VAccelerationSpeed;
	}
}

//move forward
void ACVehiclePlayer::FMoveStopX(const FInputActionValue& Value)
{
	VIsDriving = false;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("test test stest")));
}

//rotate
void ACVehiclePlayer::FMoveY(const FInputActionValue& Value)
{
	if (VSpeed > 0)
	{
		if (drifting == true)
		{
			drifting = false;
			turning = true;
			AddControllerYawInput(Value.Get<float>() * (VSpeed * 2));
		}
		else
		{
			turning = true;
			AddControllerYawInput(Value.Get<float>() * VSpeed);
		}
	}
}

//move forward
void ACVehiclePlayer::FRotate(const FInputActionValue& Value)
{
}

void ACVehiclePlayer::FPickupPasenger(int floor, int colour)
{
	ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(GetController());
	if (PlayerController)
	{
		//if this passenger will bring the totoal number of passengers to the more than the mazx number of passengers, do not add
		if (PlayerController->Passengers.Num() >= pasengerCount)
		{
			return;
		}
		PlayerController->AddPassenger(floor, colour);
	}

	VSpeed = 0;
}

void ACVehiclePlayer::FDropoffPasenger(int floor, int colour)
{
	ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->RemovePassenger(floor, colour);
		if (PlayerController->VCarbon > 0)
		{
			if (electricCarTrue == true)
			{
				PlayerController->VCarbon -= 0.25f;
			}
			else if (feulCarTrue == true)
			{
				PlayerController->VCarbon += 0.25f;
			}
			else
			{
				PlayerController->VCarbon -= (0.25f / Vefficiency);
			}
			
		}
	}
}

void ACVehiclePlayer::FIncreseMoney(int MoneyVallue)
{
	ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(GetController());
	PlayerController->VMoney += MoneyVallue;
}

void ACVehiclePlayer::ElectricCar()
{
	ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(GetController());
	if (PlayerController)
	{
		if (electricCarTrue == true)
		{
			//incroment carbon
			PlayerController->VCarbon -= (VAccelerationSpeed / 2);

			//if carbon is 0, load end screen
			if (PlayerController->VCarbon <= 0)
			{
				PlayerController->TimerFunction();
			}
		}
	}
}

void ACVehiclePlayer::FeulCar()
{
	ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(GetController());
	if (PlayerController)
	{
		if (feulCarTrue == true)
		{
			//incroment carbon
			PlayerController->VCarbon += (VAccelerationSpeed / 2);

			//if carbon is 0, load end screen
			if (PlayerController->VCarbon >= 1)
			{
				PlayerController->TimerFunction();
			}
		}
	}
}

//called to STOP rotate
void ACVehiclePlayer::FStopRotate(const FInputActionValue& Value)
{
	turning = false;
}

//called to drift
void ACVehiclePlayer::FDrift(const FInputActionValue& Value)
{
	if (turning == true)
	{
		ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(GetController());
		if (PlayerController)
		{
			if (PlayerController->VCarbon > 0)
			{
				PlayerController->VCarbon -= (VAccelerationSpeed / 2);
			}
			
		}
		drifting = true;
	}
}

void ACVehiclePlayer::FShop(const FInputActionValue& Value)
{
	//load shop ui from controller
	ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->LoadShop();
	}
}

void ACVehiclePlayer::FShopRelise(const FInputActionValue& Value)
{
	//close shop ui from controller
	ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->LoadHud();
	}
}
