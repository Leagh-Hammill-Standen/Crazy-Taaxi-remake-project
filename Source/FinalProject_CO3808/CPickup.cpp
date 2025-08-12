// Fill out your copyright notice in the Description page of Project Settings.


#include "CPickup.h"

void ACPickup::FPickupTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//get player and call a function
	if (OtherActor)
	{
		// Check if the overlapping actor is the player
		ACVehiclePlayer* Player = Cast<ACVehiclePlayer>(OtherActor); // Replace AYourPlayerClass with your actual player class name

		if (Player)
		{
			//get randmon floor and colour
			int floor = FMath::RandRange(1, 3);

			int colour = FMath::RandRange(1, 3);

			Player->FPickupPasenger(floor, colour);

			//disable the trigger
			this->SetActorEnableCollision(false);
			//create a timer when a passenger is picked up to re enable the trigger
			GetWorldTimerManager().SetTimer(PickupTimer, this, &ACPickup::MyTimerHandle, 5.0f, false);
			//make this actorm disappear
			this->SetActorHiddenInGame(true);
		}
	}
}

void ACPickup::MyTimerHandle()
{
	//re enable the trigger
	this->SetActorEnableCollision(true);
	this->SetActorHiddenInGame(false);
}
