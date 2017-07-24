// App

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_03_BE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

	private:	
		// Sets default values for this component's properties
		APlayerController* PlayerController;
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		UPROPERTY(EditAnywhere) // How far the player can reach
			float Reach = 100.f;

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	public:	
		UGrabber();
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
