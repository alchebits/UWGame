#include "UWGameGameMode.h"
#include "UWGameGameState.h"

AUWGameGameMode::AUWGameGameMode()
{
	GameStateClass = AUWGameGameState::StaticClass();
}

void AUWGameGameMode::InitGameState()
{
	Super::InitGameState();

	if (AUWGameGameState* UWGameState = Cast<AUWGameGameState>(GameState))
	{
		UWGameState->TimeLeftInSession = GameSessionTimeSeconds;
	}
}
