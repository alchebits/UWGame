#include "UWGameInstance.h"

void UUWGameInstance::Init()
{
	Super::Init();
}

float UUWGameInstance::GetScoreSum() const
{
	return ScoreSum;
}

float UUWGameInstance::GetHighestScore() const
{
	return HighestScore;
}

void UUWGameInstance::SetScoreSum(float NewScoreSum)
{
	ScoreSum = NewScoreSum;
}

void UUWGameInstance::SetHighestScore(float NewHighestScore)
{
	HighestScore = NewHighestScore;
}
