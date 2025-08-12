// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Passenger.generated.h"

UCLASS()
class FINALPROJECT_CO3808_API APassenger : public AActor
{
	GENERATED_BODY()
	
public:
	APassenger();

	enum passengerTypeList { Hippie, Ritch, Normal, Criminal };
	passengerTypeList passengerType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int floorDestination;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int colourDestination;

	//called when this passenger is picked up
	void Pickup();

	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), NULL, TEXT("SoundWave'/Game/Sounds/PassengerPickup.PassengerPickup'")));

	//called when this passenger is dropped off
	void Dropoff();

	UPROPERTY(EditAnywhere)
	USoundBase*	DropoffSound = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), NULL, TEXT("SoundWave'/Game/Sounds/PassengerPickup.PassengerPickup'")));

	// Sets default values for this actor's properties
	
	void setDeafaultValues(int floor, int colour, passengerTypeList Type);
	~APassenger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
