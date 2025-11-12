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
