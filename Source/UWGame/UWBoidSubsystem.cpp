#include "UWBoidSubsystem.h"
#include "UWGameLog.h"

UUWBoidSubsystem::UUWBoidSubsystem()
{
	 NeighborRadius = 300.f;
	 SeparationWeight = 1.f;
	 AlignmentWeight = 1.2f;
	 CohesionWeight = 1.2f;
	 MaxSpeed = 400.f;
	 MaxForce = 100.f;
}

void UUWBoidSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

void UUWBoidSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogUwGame, Warning, TEXT("Boid World Tick"));
	
	TArray<FBoid> CopyBoids= Boids;
	
	for (int32 i = 0; i < CopyBoids.Num(); ++i)
	{
		FBoid& Boid = CopyBoids[i];
		
		FVector SeparationForce = ApplySeparation(Boid) * SeparationWeight;
		FVector AlignmentForce = ApplyAlignment(Boid) * AlignmentWeight;
		FVector CohesionForce = ApplyCohesion(Boid) * CohesionWeight;
		
		FVector Acceleration = SeparationForce + AlignmentForce + CohesionForce;
		Acceleration = LimitVectorLength(Acceleration, MaxForce);
		
		Boid.Velocity += Acceleration * DeltaTime;
		Boid.Velocity = LimitVectorLength(Boid.Velocity, MaxSpeed);
		
		Boid.Position += Boid.Velocity * DeltaTime;
		
		if (AActor** BoidActor = BoidActors.Find(Boid.ID))
		{
			(*BoidActor)->SetActorLocation(Boid.Position);
			(*BoidActor)->SetActorRotation(Boid.Velocity.Rotation());
		}
	}

	// Update boids data in next frame
	Boids = CopyBoids;
}

TStatId UUWBoidSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UUWBoidSubsystem, STATGROUP_Tickables);
}

bool UUWBoidSubsystem::RegisterActor(AActor* AuwSheep, uint32& RetID)
{
	if (AuwSheep == nullptr)
	{
		return false;
	}
	
	FBoid NewBoid;
	NewBoid.ID = ++NextID;
	NewBoid.Position = AuwSheep->GetActorLocation();
	NewBoid.Velocity = FVector(FMath::RandRange(-100, 100), FMath::RandRange(-100, 100), 0.f);

	Boids.Add(NewBoid);
	BoidActors.Add(NextID, AuwSheep);

	RetID = NextID;
	return true;
}

bool UUWBoidSubsystem::UnregisterActor(uint32 ID)
{
	BoidActors.Remove(ID);
	int32 IndexToRemove = Boids.IndexOfByPredicate([ID](const FBoid& Value)
	{
		return Value.ID == ID;
	});

	if (IndexToRemove != INDEX_NONE)
	{
		Boids.RemoveAtSwap(IndexToRemove);
		return true;
	}
	
	return false;
}

FVector UUWBoidSubsystem::ApplySeparation(const FBoid& Boid)
{
	FVector SteeringForce = FVector::ZeroVector;
	int32 NeighborCount = 0;
    
	for (const FBoid& OtherBoid : Boids)
	{
		if (OtherBoid.ID == Boid.ID)
		{
			continue;
		}
        
		float Distance = FVector::Distance(Boid.Position, OtherBoid.Position);
        
		if (Distance < NeighborRadius)
		{
			// repulsion force is stronger if closer to another boid
			FVector RepulsionDirection = Boid.Position - OtherBoid.Position;
            
			if (!RepulsionDirection.IsNearlyZero())
			{
				RepulsionDirection.Normalize();

				RepulsionDirection *= (NeighborRadius / FMath::Max(Distance, 1.0f));
				SteeringForce += RepulsionDirection;
			}
            
			NeighborCount++;
		}
	}
    
	if (NeighborCount > 0)
	{
		SteeringForce /= NeighborCount;
        
		if (!SteeringForce.IsNearlyZero())
		{
			SteeringForce.Normalize();
			SteeringForce *= MaxSpeed;
			SteeringForce -= Boid.Velocity;
			SteeringForce = LimitVectorLength(SteeringForce, MaxForce);
		}
	}
    
	return SteeringForce;

}

FVector UUWBoidSubsystem::ApplyAlignment(const FBoid& Boid)
{
	FVector AverageVelocity = FVector::ZeroVector;
	int32 NeighborCount = 0;
    
	for (const FBoid& OtherBoid : Boids)
	{
		if (OtherBoid.ID == Boid.ID)
		{
			continue;
		}
        
		float Distance = FVector::Distance(Boid.Position, OtherBoid.Position);
        
		if (Distance < NeighborRadius)
		{
			AverageVelocity += OtherBoid.Velocity;
			NeighborCount++;
		}
	}
    
	if (NeighborCount > 0)
	{
		AverageVelocity /= NeighborCount;
        
		if (!AverageVelocity.IsNearlyZero())
		{
			AverageVelocity.Normalize();
			AverageVelocity *= MaxSpeed;
            
			FVector SteeringForce = AverageVelocity - Boid.Velocity;
			SteeringForce = LimitVectorLength(SteeringForce, MaxForce);
			return SteeringForce;
		}
	}
    
	return FVector::ZeroVector;
}

FVector UUWBoidSubsystem::ApplyCohesion(const FBoid& Boid)
{
	FVector CenterOfMass = FVector::ZeroVector;
	int32 NeighborCount = 0;
    
	for (const FBoid& OtherBoid : Boids)
	{
		if (OtherBoid.ID == Boid.ID)
		{
			continue;
		}
        
		float Distance = FVector::Distance(Boid.Position, OtherBoid.Position);
        
		if (Distance < NeighborRadius)
		{
			CenterOfMass += OtherBoid.Position;
			NeighborCount++;
		}
	}
    
	if (NeighborCount > 0)
	{
		CenterOfMass /= NeighborCount;
        
		FVector DesiredVelocity = CenterOfMass - Boid.Position;
        
		if (!DesiredVelocity.IsNearlyZero())
		{
			DesiredVelocity.Normalize();
			DesiredVelocity *= MaxSpeed;
            
			FVector SteeringForce = DesiredVelocity - Boid.Velocity;
			SteeringForce = LimitVectorLength(SteeringForce, MaxForce);
			return SteeringForce;
		}
	}
    
	return FVector::ZeroVector;
}

FVector UUWBoidSubsystem::LimitVectorLength(const FVector& Vector, float MaxSize)
{
	if (Vector.SizeSquared() > FMath::Square(MaxSize))
	{
		return Vector.GetSafeNormal() * MaxSize;
	}
    
	return Vector;
}
