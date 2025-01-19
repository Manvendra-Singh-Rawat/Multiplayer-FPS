#include "PlayableCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "Weapon.h"

APlayableCharacter::APlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FPSCamera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bUsePawnControlRotation = true;
	FPSCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Overhead Widget"));
	OverheadWidget->SetupAttachment(RootComponent);
}

void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayableCharacter::MoveForward(float Axis)
{
	if (Controller == nullptr && Axis == 0.0f)
	{
		return;
	}

	FRotator ControlRotation = FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
	FVector Direction = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction, Axis);
}

void APlayableCharacter::MoveRight(float Axis)
{
	if (Controller == nullptr && Axis == 0.0f)
	{
		return;
	}

	FRotator ControlRotation = FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
	FVector Direction = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction, Axis);
}

void APlayableCharacter::Turn(float Axis)
{
	AddControllerYawInput(Axis);
}

void APlayableCharacter::LookUp(float Axis)
{
	AddControllerPitchInput(Axis);
}

void APlayableCharacter::OnRep_OverlappingWeapon(AWeapon* LastWeapon)
{
	if (OverlappingWeapon != nullptr)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}
	else if (LastWeapon != nullptr)
	{
		LastWeapon->ShowPickupWidget(false);
	}
}

void APlayableCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(APlayableCharacter, OverlappingWeapon);
	DOREPLIFETIME_CONDITION(APlayableCharacter, OverlappingWeapon, COND_OwnerOnly);
}

void APlayableCharacter::SetOverlappingWeapon(AWeapon* Weapon)
{
	if (OverlappingWeapon != nullptr)
	{
		OverlappingWeapon->ShowPickupWidget(false);
	}
	OverlappingWeapon = Weapon;
	if (IsLocallyControlled())
	{
		if (OverlappingWeapon != nullptr)
		{
			OverlappingWeapon->ShowPickupWidget(true);
		}
	}
}

void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ThisClass::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}
