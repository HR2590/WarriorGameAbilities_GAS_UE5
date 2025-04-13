// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tarea3GASGameMode.h"
#include "Tarea3GASPlayerController.h"
#include "Tarea3GASCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATarea3GASGameMode::ATarea3GASGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATarea3GASPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}