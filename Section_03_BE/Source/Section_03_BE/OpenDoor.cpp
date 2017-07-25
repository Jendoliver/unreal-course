// App||ElBotna Solutions ©

#include "Section_03_BE.h"
#include "OpenDoor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = GetOwner()->GetActorRotation();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger volume
	if (CalculateTotalMassOnPressurePlate() > TriggerMassTreshold)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

float UOpenDoor::CalculateTotalMassOnPressurePlate()
{
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// Iterate through them adding their masses
	for (const AActor* Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is on the plate"), *(Actor->GetName()));
		TotalMass += Actor->GetRootPrimitiveComponent()->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("Total mass: %f"), TotalMass);
	return TotalMass;
}

void UOpenDoor::OpenDoor()
{
	GetOwner()->SetActorRotation(InitialRotation + FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	GetOwner()->SetActorRotation(InitialRotation);
}

