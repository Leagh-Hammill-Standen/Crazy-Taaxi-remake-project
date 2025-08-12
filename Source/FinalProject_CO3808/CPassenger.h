// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */
class FINALPROJECT_CO3808_API CPassenger : public UObject
{
public:
	enum passengerTypeList { Hippie, Ritch, Normal, Criminal};
	passengerTypeList passengerType;

	int floorDestination;
	int colourDestination;

	//called when this passenger is picked up
	void Pickup();

	//called when this passenger is dropped off
	void Dropoff();


	CPassenger(int floor, int colour, passengerTypeList Type);
	~CPassenger();
};
