// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPGPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "RPGCameraManager.h"

ARPGPlayerController::ARPGPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ARPGCameraManager::StaticClass();
}

void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
