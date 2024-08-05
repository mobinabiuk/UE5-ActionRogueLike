// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"


void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	GEngine->AddOnScreenDebugMessage((uint64)-1, 5.f, FColor::Blue, TEXT("SItemChest called"));
	FRotator CurrentRotation = PivotPoint->GetRelativeRotation();
	UE_LOG(LogTemp, Warning, TEXT("Current Pitch: %f"), CurrentRotation.Pitch);
	PivotPoint->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
}

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	PivotPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PivotPoint"));
	PivotPoint->SetupAttachment(BaseMesh);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(PivotPoint);

	
}


// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

