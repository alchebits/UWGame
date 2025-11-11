#include "UWPlayerPawn.h"

void AUWPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &AUWPlayerPawn::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AUWPlayerPawn::MoveRight);
	}
}

void AUWPlayerPawn::MoveForward(float UnUnit)
{
	float DeltaTimeSeconds = GetWorld()->GetDeltaSeconds();
	float FinalDeltaForwardMovement = DeltaTimeSeconds * PlayerSpeedPerSecond * UnUnit;

	FVector DeltaForward = FVector(FinalDeltaForwardMovement, 0.f, 0.f);
	AddActorWorldOffset(DeltaForward);
}

void AUWPlayerPawn::MoveRight(float UnUnit)
{
	float DeltaTimeSeconds = GetWorld()->GetDeltaSeconds();
	float FinalDeltaRightMovement = DeltaTimeSeconds * PlayerSpeedPerSecond * UnUnit;
	
	FVector DeltaRight = FVector(0.f, FinalDeltaRightMovement, 0.f);
	AddActorWorldOffset(DeltaRight);
}
