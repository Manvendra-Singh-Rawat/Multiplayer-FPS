// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText != nullptr)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString Role;
	
	switch(LocalRole)
	{
	case ENetRole::ROLE_Authority:
		Role = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		Role = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		Role = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		Role = FString("None");
		break;
	}

	FString LocalRoleString = FString::Printf(TEXT("Local role: %s"), *Role);
	SetDisplayText(LocalRoleString);
}

void UOverheadWidget::ShowPlayerName(APawn* InPawn)
{
	FString PlayerName;
	PlayerName = InPawn->GetPlayerState()->GetPlayerName();
	FString PlayerNameString = FString::Printf(TEXT("Player name: %s"), *PlayerName);
	SetDisplayText(PlayerNameString);
}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
}
