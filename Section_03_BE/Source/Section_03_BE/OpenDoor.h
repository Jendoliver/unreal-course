// App||ElBotna Solutions ©

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION_03_BE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

	private:
		// Door's aperture angle fam
		UPROPERTY(EditAnywhere)
		float OpenAngle = -60.0f;

		// PressurePlate that triggers the door
		UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

		UPROPERTY(EditAnywhere)
		float TriggerMassTreshold = 100.f;

		UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 3.0f;

		float LastDoorOpenTime;
		FRotator InitialRotation;

		// Actors that are on the pressure plate

		float CalculateTotalMassOnPressurePlate();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	public:	
		// Sets default values for this component's properties
		UOpenDoor();
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		void OpenDoor();
		void CloseDoor();
};
