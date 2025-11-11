#include "UWBoidSubsystem.h"


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
	}

	// Update boids data in next frame
	Boids = CopyBoids;
}

TStatId UUWBoidSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UUWBoidSubsystem, STATGROUP_Tickables);
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

