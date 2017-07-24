// App

#include "Section_03_BE.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("GRAB"))
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("RELEASE"))
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();

	/// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a Physics Handle Component attached"), *(GetOwner()->GetName()));
	}

	/// Look for attached Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent attached"), *(GetOwner()->GetName()));
		/// Bind the input actions to the method
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a Input Component attached"), *(GetOwner()->GetName()));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PlayerController->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // Get location and rotation of the player
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach; // Calculates the end of the line

	/// Draw a red line in the world to visualize
	DrawDebugLine(
		GetWorld(), 
		PlayerViewPointLocation, 
		LineTraceEnd, 
		FColor::Red, 
		false,
		0.f,
		0,
		10.f
		);

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner()); // We don't worry about the tag (first arg), we DON'T WANT to collide with the complex mesh (2nd) and we ignore ourselves (3rd)

	/// Ray-cast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,															// Hit: the variable holding the response on what we hit
		PlayerViewPointLocation,											// Beginning of the line
		LineTraceEnd,														// End of the line
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),	// Object Type the line will collide with
		TraceParameters														// Query parameters
	);

	/// See what we hit, if we hit something log it
	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Object hit: %s"), *(HitActor->GetName()))
	}
}

