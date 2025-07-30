// Copyright Epic Games, Inc. All Rights Reserved.


#include "GMTKPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "GMTKCameraManager.h"

AGMTKPlayerController::AGMTKPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AGMTKCameraManager::StaticClass();
}

void AGMTKPlayerController::SetupInputComponent()
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
