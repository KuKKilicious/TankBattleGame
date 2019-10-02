// //KuKKi ©2019


#include "WheelSpawn.h"
#include "SprungWheel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWheelSpawn::UWheelSpawn()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWheelSpawn::BeginPlay()
{
	Super::BeginPlay();

	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(m_SpawnWheel,GetComponentTransform());
	
	if(!SpawnedActor) {return;}
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor,GetComponentTransform());

}

void UWheelSpawn::setWheel(UClass* SpawnWheel)
{
	if (!ensure(SpawnWheel)) { return; }
	m_SpawnWheel = SpawnWheel;
}


// Called every frame
void UWheelSpawn::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UWheelSpawn::getSpawnedActor() const
{
	return SpawnedActor;
}

