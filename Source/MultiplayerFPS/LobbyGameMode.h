// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERFPS_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:
	int PlayerCountInSession{ 0 };

protected:
	virtual void PostLogin(APlayerController* NewPlayerController) override;
	virtual void Logout(AController* Exiting) override;
};
