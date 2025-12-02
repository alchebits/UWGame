#include "UWSheep.h"

#include "UWBoidSubsystem.h"

void AUWSheep::BeginPlay()
{
	Super::BeginPlay();

	UUWBoidSubsystem* BoidSubsystem = GetWorld()->GetSubsystem<UUWBoidSubsystem>();
	if ( ! BoidSubsystem)
	{
		return;
	}

	BoidSubsystem->RegisterActor(this, BoidID);
	OnSheepAloneStateChange(bIsAlone);
}

void AUWSheep::Destroyed()
{
	Super::Destroyed();
	
	UUWBoidSubsystem* BoidSubsystem = GetWorld()->GetSubsystem<UUWBoidSubsystem>();
	if ( ! BoidSubsystem)
	{
		return;
	}
	
	BoidSubsystem->UnregisterActor(BoidID);
}

void AUWSheep::SetIsSheepAlone(bool bInIsAlone)
{
	if (bIsAlone != bInIsAlone)
	{
		bIsAlone = bInIsAlone;
		OnSheepAloneStateChange(bIsAlone);
	}
}

bool AUWSheep::CanBeEaten() const
{
	return bIsAlone;
}
