// Fill out your copyright notice in the Description page of Project Settings.


#include "CDropoff.h"
#include "CCheckpoint.h"
#include "Passenger.h"

void ACDropoff::FPickupTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//get player and call a function
	if (OtherActor)
	{
		// Check if the overlapping actor is the player
		ACVehiclePlayer* Player = Cast<ACVehiclePlayer>(OtherActor);

		if (Player)
		{
			//see if the player has any passengers
			ACVehiclePlayerController* PlayerController = Cast<ACVehiclePlayerController>(Player->GetController());
			if (PlayerController->Passengers.IsEmpty() == false)
			{
				for (int i = 0; i < PlayerController->Passengers.Num(); i++)
				{
					if (PlayerController->Passengers[i]->floorDestination == floor && PlayerController->Passengers[i]->colourDestination == colour)
					{
						Player->FDropoffPasenger(floor, colour);
					}
				}
			}
		}
	}
}

