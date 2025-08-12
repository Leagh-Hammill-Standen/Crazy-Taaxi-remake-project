// Fill out your copyright notice in the Description page of Project Settings.


#include "CCheckpoint.h"

// Sets default values
ACCheckpoint::ACCheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	APickupVisual = CreateDefaultSubobject<UStaticMeshComponent>("Trigger Visual");
	APickupVisual->SetupAttachment(GetRootComponent());

	APickupTrigger = CreateDefaultSubobject<UBoxComponent>("Trigger zone");
	APickupTrigger->SetupAttachment(APickupVisual);

	APickupTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACCheckpoint::FPickupTriggerOverlap);
}

// Called when the game starts or when spawned
void ACCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	APickupTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	APickupTrigger->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	APickupTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	APickupTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
}

// Called every frame
void ACCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCheckpoint::FPickupTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//get player and call a function
	if (OtherActor)
	{
		
	}
}

