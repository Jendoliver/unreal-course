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
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
	FindPhysicsHandleComponent();
	FindInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
	{
		RefreshReachLine();
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

///***** BeginPlay METHODS *****///
// Sets the PhysicsHandle*
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a PhysicsHandle component attached to it"), *(GetOwner()->GetName()))
	}
}

// Sets the InputComponent* and calls BindInputActions on success
void UGrabber::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		BindInputActions();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a Input Component attached"), *(GetOwner()->GetName()));
	}
}

// Maps the action events
void UGrabber::BindInputActions()
{
	InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
}

///***** TickComponent METHODS *****///
// Refreshes LineTrace begin and end
void UGrabber::RefreshReachLine()
{
	PlayerController->GetPlayerViewPoint(OUT UGrabber::ReachLine.Begin, OUT PlayerViewPointRotation); // Get location and rotation of the player
	UGrabber::ReachLine.End = GetReachLineBegin() + PlayerViewPointRotation.Vector() * Reach; // Calculates the end of the line
}

// Called on F press, calls GetFirstPhysicsBodyInReach
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("GRAB"));

	/// Try and reach any actors with physics body collision channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

	/// If we hit something then attach that to the physics handle
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None, // No bones needed
			HitResult.GetComponent()->GetOwner()->GetActorLocation(),
			HitResult.GetComponent()->GetOwner()->GetActorRotation()
		);
	}
}

// Traces a line searching for the first PhysicsBody in Reach
FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	RefreshReachLine();
	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner()); // We don't worry about the tag (first arg), we DON'T WANT to collide with the complex mesh (2nd) and we ignore ourselves (3rd)

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,															// Hit: the variable holding the response on what we hit
		GetReachLineBegin(),												// Beginning of the line
		GetReachLineEnd(),													// End of the line
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),	// Object Type the line will collide with
		TraceParameters														// Query parameters
	);
	return Hit;
}

// Called on F release
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("RELEASE"));
	PhysicsHandle->ReleaseComponent();
}

///***** DEBUGGING TOOLS *****///
// Draws a red line in the world to visualize grab reach
void UGrabber::DrawGrabReachLine()
{
	DrawDebugLine(
		GetWorld(),
		GetReachLineBegin(),
		GetReachLineEnd(),
		FColor::Red,
		false,
		0.f,
		0,
		10.f
	);
}
