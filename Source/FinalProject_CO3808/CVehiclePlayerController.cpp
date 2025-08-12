// Fill out your copyright notice in the Description page of Project Settings.


#include "CVehiclePlayerController.h"


void ACVehiclePlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    // Check if WidgetClass is set
    if (WidgetSelect)
    {
        // Create the widget instance
        WidgetInstance = CreateWidget<UUserWidget>(this, WidgetSelect);

        if (WidgetInstance)
        {
            // Add the widget to the viewport
            WidgetInstance->AddToViewport();
        }
        GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ACVehiclePlayerController::TimerFunction, 180.0f, false);
        GetWorldTimerManager().PauseTimer(MyTimerHandle);
        GamePaused = true;
    }
}

//add a pasenger, blue = 1, red = 2, green = 3
void ACVehiclePlayerController::AddPassenger(int floor, int colour)
{
    /*
    if (floor == 1)
    {
        if (colour == 1)
        {
            F1BluePass += 1;
        }
        else if (colour == 2)
        {
            F1RedPass += 1;
        }
        else if (colour == 3)
        {
            F1GreenPass += 1;
        }
    }
    else if (floor == 2)
    {
        if (colour == 1)
        {
            F2BluePass += 1;
        }
        else if (colour == 2)
        {
            F2RedPass += 1;
        }
        else if (colour == 3)
        {
            F2GreenPass += 1;
        }
    }
    else if (floor == 3)
    {
        if (colour == 1)
        {
            F3BluePass += 1;
        }
        else if (colour == 2)
        {
            F3RedPass += 1;
        }
        else if (colour == 3)
        {
            F3GreenPass += 1;
        }
    }
    */

	//add a new passenger to the list
    APassenger* someItem = GetWorld()->SpawnActor<APassenger>(APassenger::StaticClass());
    Passengers.Add(someItem);
	Passengers[(Passengers.Num()) - 1]->setDeafaultValues(floor, colour, APassenger::passengerTypeList::Normal);
    Passengers[(Passengers.Num()) - 1]->Pickup();

}

void ACVehiclePlayerController::RemovePassenger(int floor, int colour)
{
    /*
    if (floor == 1)
    {
        if (colour == 1)
        {
            F1BluePass -= 1;
        }
        else if (colour == 2)
        {
            F1RedPass -= 1;
        }
        else if (colour == 3)
        {
            F1GreenPass -= 1;
        }
    }
    else if (floor == 2)
    {
        if (colour == 1)
        {
            F2BluePass -= 1;
        }
        else if (colour == 2)
        {
            F2RedPass -= 1;
        }
        else if (colour == 3)
        {
            F2GreenPass -= 1;
        }
    }
    else if (floor == 3)
    {
        if (colour == 1)
        {
            F3BluePass -= 1;
        }
        else if (colour == 2)
        {
            F3RedPass -= 1;
        }
        else if (colour == 3)
        {
            F3GreenPass -= 1;
        }
    }
    */

	//go through all passengers and remove any that matches the floor and colour
    for (int i = 0; i < Passengers.Num(); i++)
    {
        if (Passengers[i]->floorDestination == floor && Passengers[i]->colourDestination == colour)
        {
			Passengers[i]->Dropoff();
			Passengers[i]->Destroy();
			Passengers[i] = nullptr;  
			Passengers.RemoveAt(i);

			VMoney += 100;
			addTime(10.0f);

        }
    }
}

void ACVehiclePlayerController::LoadHud()
{
    // Check if WidgetClass is set
    if (HudWiddget)
    {
        // Create the widget instance
        HudWidgetInstance = CreateWidget<UUserWidget>(this, HudWiddget);

        //remove possibly active UI
        if (ShopWidgetInstance)
        {
            ShopWidgetInstance->RemoveFromParent();
        }
        if (WidgetInstance)
        {
            WidgetInstance->RemoveFromParent();
        }

		//make shure the game is not paused
        if (GamePaused == true)
        {
            GamePaused = false;
            PauseGame();
        }

        if (HudWidgetInstance)
        {
            // Add the widget to the viewport
            HudWidgetInstance->AddToViewport();
        }
    }
}

void ACVehiclePlayerController::TimerFunction()
{
	//load game over level depending on the carbon
    if (VCarbon == 0.0f)
    {
        UGameplayStatics::OpenLevel(GetWorld(), "EndGood");
    }
    else if (VCarbon <= 0.25f)
    {
		UGameplayStatics::OpenLevel(GetWorld(), "EndOK");
	}
	else if (VCarbon <= 0.5f)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "EndNeutral");
	}
    else if (VCarbon <= 0.75f)
    {
        UGameplayStatics::OpenLevel(GetWorld(), "EndBad");
    }
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), "EndHorrable");
    }
}

//add time to timer handel
void ACVehiclePlayerController::addTime(float time)
{
	float timerOldVallue = GetWorldTimerManager().GetTimerRemaining(MyTimerHandle);
	GetWorldTimerManager().ClearTimer(MyTimerHandle);
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ACVehiclePlayerController::TimerFunction, timerOldVallue + time, false);
}

void ACVehiclePlayerController::LoadShop()
{
	// Check if WidgetClass is set
	if (ShopWiddget)
	{
        //pause the game
        GamePaused = true;
        PauseGame();

		
        if (HudWidgetInstance)
        {
            //hide and delete old HudWiddgetInatance
            HudWidgetInstance->RemoveFromParent();
        }

		// Create the widget instance
		ShopWidgetInstance = CreateWidget<UUserWidget>(this, ShopWiddget);
        //unlock mouse
		bShowMouseCursor = true;


		if (ShopWidgetInstance)
		{
			// Add the widget to the viewport
			ShopWidgetInstance->AddToViewport();
		}
	}
}

void ACVehiclePlayerController::PauseGame()
{
	if (GamePaused == true)
	{
        GetWorldTimerManager().PauseTimer(MyTimerHandle);
	}
	else
	{
        GetWorldTimerManager().UnPauseTimer(MyTimerHandle);
	}
}
