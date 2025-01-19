#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class MULTIPLAYERFPS_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayableCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FPSCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	class AWeapon* OverlappingWeapon;

protected:
	UFUNCTION()
	void MoveForward(float Axis);
	UFUNCTION()
	void MoveRight(float Axis);
	UFUNCTION()
	void Turn(float Axis);
	UFUNCTION()
	void LookUp(float Axis);

	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void SetOverlappingWeapon(AWeapon* Weapon);
};
