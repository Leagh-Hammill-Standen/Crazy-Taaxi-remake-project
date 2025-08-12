// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "CVehicle.generated.h"

UCLASS()
class FINALPROJECT_CO3808_API ACVehicle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* playerMappingContext;

	//imput actions
	UPROPERTY(EditAnywhere)
	UInputAction* MoveXAcation;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveYAcation;

	UPROPERTY(EditAnywhere)
	UInputAction* RotateAcation;

	//car componets
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USceneComponent* NRootComponent;

	//speed and driving stats
	bool VIsDriving = false;

	UPROPERTY(EditAnywhere)
	float VMaxSpeed = 100;

	UPROPERTY(EditAnywhere)
	float VAccelerationSpeed = 1;

	UPROPERTY(EditAnywhere)
	float VdecelerationSpeed = 1;

	UPROPERTY(VisibleAnywhere)
	float VSpeed = 0;

	UPROPERTY(VisibleAnywhere)
	float VTurnSpeed = 10;

	

private:
	//called to move forwards and backwards
	UFUNCTION()
	void FMoveX(const FInputActionValue& Value);

	//called to move left and right
	UFUNCTION()
	void FMoveY(const FInputActionValue& Value);

	//called to rotate
	UFUNCTION()
	void FRotate(const FInputActionValue& Value);

};
