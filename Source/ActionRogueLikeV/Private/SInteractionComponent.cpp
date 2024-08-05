// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGamePlayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);


	//FHitResult Hit;
    //bool bBlockingIt = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End,ObjectQueryParams);

	TArray<FHitResult> Hits;
	float Radius = 30.0f;
	FCollisionShape Shape;
 	Shape.SetSphere(Radius);
    bool bBlockingIt =	GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams,Shape);
	FColor LineColor = bBlockingIt ? FColor::Green : FColor::Red;

	//to get the whole array
	for (const FHitResult &Hit:Hits)
	{
		AActor* HitActor = nullptr;
	    HitActor = Hit.GetActor();
		//IF HITACTOR IS NOT NULL
		if (HitActor)
		{
			if (HitActor->Implements<USGamePlayInterface>())
			{
				
				//casting variable ExeCute_Interact needs a pawn param
				APawn* MyPawn = Cast<APawn>(GetOwner());
				if (MyPawn)
				{
					ISGamePlayInterface::Execute_Interact(HitActor, MyPawn);

					FHitResult DebugTemp = Hit;
					//FVector2D DebugMsgPosition(DebugTemp.ImpactPoint.X, DebugTemp.ImpactPoint.Y);

					break;
				}
				
			}
			
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32,LineColor, false, 2.0f);
	}
	
	
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 2.0f);
}

