#include "PlayableCharacterAnimInstance.h"
#include "PlayableCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayableCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayableCharacter = Cast<APlayableCharacter>(TryGetPawnOwner());
	if (PlayableCharacter != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("PlayableCharacter is not null"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("PlayableCharacter is null"));
	}
}

void UPlayableCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (PlayableCharacter == nullptr)
	{
		PlayableCharacter = Cast<APlayableCharacter>(TryGetPawnOwner());
	}
	if (PlayableCharacter == nullptr)
	{
		return;
	}

	FVector PlayerVelocity = PlayableCharacter->GetVelocity();
	PlayerVelocity.Z = 0.0f;
	Speed = PlayerVelocity.Length();

	const UCharacterMovementComponent* CharacterMovement = PlayableCharacter->GetCharacterMovement();
	bIsInAir = CharacterMovement->IsFalling();
	bIsAccelerating = CharacterMovement->GetCurrentAcceleration().Length() > 0 ? true : false;
}
