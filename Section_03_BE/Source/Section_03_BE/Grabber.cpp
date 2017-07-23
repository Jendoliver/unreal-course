// App

#include "Section_03_BE.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	UE_LOG(LogTemp, Warning, TEXT("Viewpoint position: %s , Viewpoint rotation: %s"), 
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	);

	/*UE_LOG(LogTemp, Warning, 
		TEXT("Player is looking at position (%f, %f, %f) and with a rotation of (%f, %f, %f)", 
			*PlayerViewPointLocation.X, *PlayerViewPointLocation.Y, *PlayerViewPointLocation.Z, *PlayerViewPointRotation.Pitch, *PlayerViewPointRotation.Yaw, *PlayerViewPointRotation.Roll));*/

	// Ray-cast out to reach distance

	// See what we hit
}

