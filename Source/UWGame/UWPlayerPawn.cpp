#include "UWPlayerPawn.h"
#include "UWGameLog.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

void AUWPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if ( ! PlayerController)
	{
		UE_LOG(LogUwGame, Error, TEXT("Player Pawn does not have player controller"));
		return;
	}

	// Adding InputMappingContext asset to EI subsystem (enabling it)
	UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if ( ! EISubsystem)
	{
		UE_LOG(LogUwGame, Error, TEXT("UEnhancedInputLocalPlayerSubsystem is null"));
		return;
	}

	if ( ! WolfInputMappingContext || ! MovementInputAction || ! CameraInputAction)
	{
		UE_LOG(LogUwGame, Error, TEXT("WolfInputMappingContext is null or MovementInputAction is null or CameraInputAction is null"));
		return;
	}
	
	EISubsystem->AddMappingContext(WolfInputMappingContext, 0);
	
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if ( ! EIC)
	{
		UE_LOG(LogUwGame, Error, TEXT("PlayerInputComponent is not UEnhancedInputComponent type. Enable EnhancedInput subsystem in settings."));
		return;
	}
	
	EIC->BindAction(MovementInputAction, ETriggerEvent::Triggered, this, &AUWPlayerPawn::HandleMovementInput);
	EIC->BindAction(CameraInputAction, ETriggerEvent::Triggered, this, &AUWPlayerPawn::HandleCameraInput);
}

void AUWPlayerPawn::HandleMovementInput(const FInputActionValue& InputValue)
{
	const EInputActionValueType InputType = InputValue.GetValueType();

	switch (InputType)
	{
	case EInputActionValueType::Axis2D:
		{
			float DeltaTimeSeconds = GetWorld()->GetDeltaSeconds();
			FInputActionValue::Axis2D XYDelta = InputValue.Get<FInputActionValue::Axis2D>();
			XYDelta = XYDelta * DeltaTimeSeconds * AccelerationPerSecond;

			FVector ForwardVector = UKismetMathLibrary::GetForwardVector(GetController()->GetControlRotation());
			ForwardVector.Normalize();

			FVector RightVector = UKismetMathLibrary::GetRightVector(GetController()->GetControlRotation());
			RightVector.Normalize();

			ForwardVector *= XYDelta.X; // scale forward vector 
			RightVector *= XYDelta.Y; // scale right vector

			AddMovementInput(ForwardVector, 1.f, false);
			AddMovementInput(RightVector, 1.f, false);
			break;
		}
	default:
		break;
	}
}

void AUWPlayerPawn::HandleCameraInput(const FInputActionValue& InputValue)
{
	const EInputActionValueType InputType = InputValue.GetValueType();

	switch (InputType)
	{
	case EInputActionValueType::Axis2D:
		{
			FInputActionValue::Axis2D MouseXYDelta = InputValue.Get<FInputActionValue::Axis2D>();
			AddControllerYawInput(MouseXYDelta.X);
			AddControllerPitchInput(MouseXYDelta.Y);
			break;
		}
	default:
		break;
	}
}

