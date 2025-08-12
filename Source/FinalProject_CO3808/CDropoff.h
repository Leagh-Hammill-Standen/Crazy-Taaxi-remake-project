// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCheckpoint.h"
#include "CDropoff.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_CO3808_API ACDropoff : public ACCheckpoint
{
	GENERATED_BODY()

	void FPickupTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//the floor the its on
	UPROPERTY(EditAnywhere)
	int floor;

	//blue = 1, red = 2, green = 3
	UPROPERTY(EditAnywhere)
	int colour;


	

};
