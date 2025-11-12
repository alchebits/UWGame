#pragma once

#include "GameFramework/Pawn.h"
#include "UWSheep.generated.h"

UCLASS()
class AUWSheep : public APawn
{
	GENERATED_BODY()
public:
	//~ AActor
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	//~ ---

private:
	uint32 BoidID = 0;
};
