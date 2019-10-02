// //KuKKi ©2019


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxleConstraint"));
	SetRootComponent(m_MassAxleConstraint);

	m_WheelAxle = CreateDefaultSubobject<USphereComponent>(FName("AxleWheel"));
	m_WheelAxle->SetupAttachment(m_MassAxleConstraint);

	m_Wheel = CreateDefaultSubobject<USphereComponent>(FName("WheeEel"));
	m_Wheel->SetupAttachment(m_WheelAxle);

	m_AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelAxleConstraint"));
	m_AxleWheelConstraint->SetupAttachment(m_WheelAxle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (GetAttachParentActor())
	{
		auto* bodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		m_MassAxleConstraint->SetConstrainedComponents(bodyRoot, FName(NAME_None), m_WheelAxle, FName(NAME_None));

		m_AxleWheelConstraint->SetConstrainedComponents(m_WheelAxle, FName(NAME_None), m_Wheel, FName(NAME_None));
	}

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDrivingForce(float ForceToApply)
{

	m_Wheel->AddForce(m_WheelAxle->GetForwardVector() * ForceToApply);
}

