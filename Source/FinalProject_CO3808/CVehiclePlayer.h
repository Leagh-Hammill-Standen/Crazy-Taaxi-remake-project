// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
//#include "EventLoop/EventLoopTimer.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "CVehiclePlayerController.h"

#include "CVehiclePlayer.generated.h"

UCLASS()
class FINALPROJECT_CO3808_API ACVehiclePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACVehiclePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// === imput settup ===
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* playerMappingContext;

	// === imput actions ===
	UPROPERTY(EditAnywhere)
	UInputAction* MoveXAcation;

	UPROPERTY(EditAnywhere)
	UInputAction* stopMoveXAcation;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveYAcation;

	UPROPERTY(EditAnywhere)
	UInputAction* RotateAcation;

	UPROPERTY(EditAnywhere)
	UInputAction* StopRotateAcation;

	UPROPERTY(EditAnywhere)
	UInputAction* DriftAction;

	UPROPERTY(EditAnywhere)
	UInputAction* ShopAction;
	
	UPROPERTY(EditAnywhere)
	UInputAction* StopShopAction;

	// === car componets ===
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USceneComponent* NRootComponent;

	// === speed and driving stats ===
	bool VIsDriving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VMaxSpeed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VAccelerationSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Vefficiency = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VdecelerationSpeed = 1;

	UPROPERTY(VisibleAnywhere)
	float VSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VTurnSpeed = 10;

	UPROPERTY()
	bool turning = false;

	UPROPERTY()
	bool drifting = false;


	// === pickup/ dropoff passenger data ===

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int pasengerCount = 1;

	bool pasengerActive = false;

	UFUNCTION()
	void FPickupPasenger(int floor, int colour);

	UFUNCTION()
	void FDropoffPasenger(int floor, int colour);

	UFUNCTION()
	void FIncreseMoney(int MoneyVallue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool electricCarTrue = false;

	UFUNCTION()
	void ElectricCar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool feulCarTrue = false;

	UFUNCTION()
	void FeulCar();

private:
	// === movememt functions ===
	//called to acelorate forwards and backwards
	UFUNCTION()
	void FMoveX(const FInputActionValue& Value);

	//called when the player staops accelorating
	UFUNCTION()
	void FMoveStopX(const FInputActionValue& Value);

	//called to move left and right
	UFUNCTION()
	void FMoveY(const FInputActionValue& Value);

	//called to rotate
	UFUNCTION()
	void FRotate(const FInputActionValue& Value);

	//called to STOP rotate
	UFUNCTION()
	void FStopRotate(const FInputActionValue& Value);
	
	//called to drift
	UFUNCTION()
	void FDrift(const FInputActionValue& Value);

	UFUNCTION()
	void FShop(const FInputActionValue& Value);

	UFUNCTION()
	void FShopRelise(const FInputActionValue& Value);
};
