#include "UWGameGameMode.h"
#include "UWGameGameState.h"
#include "UWGameInstance.h"
#include "UWGameSettings.h"

AUWGameGameMode::AUWGameGameMode()
{
	GameStateClass = AUWGameGameState::StaticClass();
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AUWGameGameMode::InitGameState()
{
	Super::InitGameState();

	UUWGameInstance* UWGameInstance = Cast<UUWGameInstance>(GetGameInstance());
	AUWGameGameState* UWGameState = Cast<AUWGameGameState>(GameState);
	if (UWGameInstance && UWGameState)
	{
		UWGameState->TimeLeftInSession = GameSessionTimeSeconds;
		UWGameState->CurrentScore = UWGameInstance->GetScoreSum();
	}
}

void AUWGameGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AUWGameGameState* UWGameState = Cast<AUWGameGameState>(GameState))
	{
		if (UWGameState->TimeLeftInSession <= 0)
		{
			EndGame();
			return;
		}

		UWGameState->TimeLeftInSession -= DeltaSeconds;
	}
}

void AUWGameGameMode::IncreaseScore(float ScoreToSum)
{
	if (AUWGameGameState* UWGameState = Cast<AUWGameGameState>(GameState))
	{
		UWGameState->CurrentScore += ScoreToSum;

		const UUWGameSettings* Settings = GetDefault<UUWGameSettings>();
		if (Settings->bDrawDebugs)
		{
			const FString Message = FString::Printf(TEXT("Score = %f"), UWGameState->CurrentScore);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);	
		}

		OnScoreChanged(UWGameState->CurrentScore);
		
		if (UWGameState->CurrentScore >= ScoreToNextLevel)
		{
			OpenNextLevel(UWGameState->CurrentLevel + 1);
		}
	}
}
