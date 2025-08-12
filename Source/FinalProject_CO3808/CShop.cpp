// Fill out your copyright notice in the Description page of Project Settings.


#include "CShop.h"

void ACShop::FPickupTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	//get player and call a function
	if (OtherActor)
	{
		// Check if the overlapping actor is the player
		ACVehiclePlayer* Player = Cast<ACVehiclePlayer>(OtherActor); // Replace AYourPlayerClass with your actual player class name
		ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(Player->GetController());

		if (Player)
		{
			if (PlayerController->VMoney >= 100)
			{
				PlayerController->VMoney -= 100;
				Player->VAccelerationSpeed += VIncreseAccelerationVallue;
				Player->VdecelerationSpeed += VIncreseDecelerationVallue;

				this->Destroy();
			}
		}
	}
	
}
