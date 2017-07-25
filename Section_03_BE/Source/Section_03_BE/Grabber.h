// App

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_03_BE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

	private:	
		APlayerController* PlayerController;
		FRotator PlayerViewPointRotation;
		struct FReachLine
		{
			FVector Begin;
			FVector End;
		} ReachLine;

		UPROPERTY(EditAnywhere)
			float Reach = 100.f;

		UPhysicsHandleComponent* PhysicsHandle = nullptr;
		UInputComponent* InputComponent = nullptr;

		/// Called-by-input functions
		void Grab();
		FHitResult GetFirstPhysicsBodyInReach();
		void Release();

		/// Component search
		void FindPhysicsHandleComponent();
		void FindInputComponent(); // Calls BindInputActions if it finds an InputComponent
		void BindInputActions();

		/// Debug tools
		void DrawGrabReachLine();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	public:

		UGrabber();
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		inline FReachLine GetLineTrace() const { return ReachLine; }
		inline FVector GetReachLineBegin() const { return ReachLine.Begin; }
		inline FVector GetReachLineEnd() const { return ReachLine.End; }
		void RefreshReachLine();
};
