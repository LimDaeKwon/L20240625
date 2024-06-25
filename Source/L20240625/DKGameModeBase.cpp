// Fill out your copyright notice in the Description page of Project Settings.


#include "DKGameModeBase.h"
#include "DKPlayerController.h"
#include "DKPawn.h"
ADKGameModeBase::ADKGameModeBase()
{
	DefaultPawnClass = ADKPawn::StaticClass();
	PlayerControllerClass = ADKPlayerController::StaticClass();
}
