// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);

	PlayerCountInSession = GameState.Get()->PlayerArray.Num();
	if (PlayerCountInSession >= 10)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel(FString("/Game/MyStuff/Map/GameLevel?listen"));
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
}
