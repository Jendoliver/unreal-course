// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_03_BE.h"
#include "PositionReporter.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	FVector ObjectPos = GetOwner()->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s is at pos (%d, %d, %d)"), *ObjectName, ObjectPos.X, ObjectPos.Y, ObjectPos.Z);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

