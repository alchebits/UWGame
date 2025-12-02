#pragma once

#include "GameFramework/Pawn.h"
#include "UWSheep.generated.h"

UCLASS()
class AUWSheep : public APawn
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnSheepAloneStateChange(bool bInIsAlone);

	//~ AActor
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	//~ ---

	void SetIsSheepAlone(bool bInIsAlone);
	bool CanBeEaten() const;
	
private:
	uint32 BoidID = 0;

	UPROPERTY()
	bool bIsAlone = false;
};
