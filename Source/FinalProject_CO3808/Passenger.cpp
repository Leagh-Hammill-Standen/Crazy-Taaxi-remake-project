// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Passenger.h"

// Sets default values
APassenger::APassenger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APassenger::Pickup()
{
	//play audio depending on passenger type
	UGameplayStatics::PlaySoundAtLocation(this, PickupSound, UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation());
}

void APassenger::Dropoff()
{
	//play audio depending on passenger type
	UGameplayStatics::PlaySoundAtLocation(this, DropoffSound, UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation());
}

void APassenger::setDeafaultValues(int floor, int colour, passengerTypeList Type)
{
	floorDestination = floor;
	colourDestination = colour;
	passengerType = Type;
}

APassenger::~APassenger()
{
}

// Called when the game starts or when spawned
void APassenger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APassenger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

