// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Passenger.h"
#include "Blueprint/UserWidget.h"
#include "CVehiclePlayerController.generated.h"

UCLASS()
class FINALPROJECT_CO3808_API ACVehiclePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	//Called when the `AMyPlayerController` is created.
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool GamePaused = false;

	UFUNCTION()
	void PauseGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VCarbon = 1.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int VMoney = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)	
	TArray<APassenger*> Passengers;

	/*
	//floor 3 pasenger stops
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int F3GreenPass = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int F3RedPass = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int F3BluePass = 0;

	//floor 2 pasenger stops
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int F2GreenPass = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int F2RedPass = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int F2BluePass = 0;

	//floor 1 pasenger stops
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int F1GreenPass = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int F1RedPass = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int F1BluePass = 0;
	*/

	UFUNCTION()
	void AddPassenger(int floor, int colour);

	UFUNCTION()
	void RemovePassenger(int floor, int colour);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetSelect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HudWiddget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ShopWiddget;

	UFUNCTION(BlueprintCallable)
	void LoadHud();

	UPROPERTY()
	UUserWidget* WidgetInstance;

	UPROPERTY()
	UUserWidget* HudWidgetInstance;

	UPROPERTY()
	UUserWidget* ShopWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle MyTimerHandle;

	UFUNCTION(BlueprintCallable)
	void TimerFunction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timerVallue;

	UFUNCTION(BlueprintCallable)
	void addTime(float time);

	UFUNCTION()
	void LoadShop();

private:


};
