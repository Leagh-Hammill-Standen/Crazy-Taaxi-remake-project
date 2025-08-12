// Fill out your copyright notice in the Description page of Project Settings.


#include "CPassenger.h"

void CPassenger::Pickup()
{
}

void CPassenger::Dropoff()
{
}

CPassenger::CPassenger(int floor, int colour, passengerTypeList Type)
{
	floorDestination = floor;
	colourDestination = colour;
	passengerType = Type;
}

CPassenger::~CPassenger()
{
}
