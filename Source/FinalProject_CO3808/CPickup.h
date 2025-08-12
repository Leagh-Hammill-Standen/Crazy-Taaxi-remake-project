// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCheckpoint.h"
#include "CPickup.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_CO3808_API ACPickup : public ACCheckpoint
{
	GENERATED_BODY()

	void FPickupTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//create a timer when a passenger is picked up to re enable the trigger
	FTimerHandle PickupTimer;

	void MyTimerHandle();
	
};
