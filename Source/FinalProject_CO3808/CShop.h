// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCheckpoint.h"
#include "CShop.generated.h"


UCLASS()
class FINALPROJECT_CO3808_API ACShop : public ACCheckpoint
{
	GENERATED_BODY()

	void FPickupTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere)
	float VIncreseAccelerationVallue;

	UPROPERTY(EditAnywhere)
	float VIncreseDecelerationVallue;
};
