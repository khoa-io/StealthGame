// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"

#include "FPSPlayerController.h"

void AFPSGameState::MultiCastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	// Iterate over all the player controller that are available (on all clients)
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		auto PC = Cast<AFPSPlayerController>(It->Get());
		if (PC && PC->IsLocalController())	  // Only when the controller is from this client
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			// Disable Input
			auto MyPawn = PC->GetPawn();
			if (MyPawn)
			{
				MyPawn->DisableInput(PC);
			}
		}
	}
}
