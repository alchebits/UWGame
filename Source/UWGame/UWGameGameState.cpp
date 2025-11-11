#include "UWGameGameState.h"

AUWGameGameState::AUWGameGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AUWGameGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TimeLeftInSession <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameEnd"));
		return;
	}

	TimeLeftInSession -= DeltaSeconds;
	UE_LOG(LogTemp, Warning, TEXT("Time Left: %f"), TimeLeftInSession);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(TimeLeftInSession));
}
