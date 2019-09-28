// //KuKKi ©2019


#include "Projectile.h"
#include "TankProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileCollisionMesh"));
	SetRootComponent(ProjectileCollisionMesh);
	ProjectileCollisionMesh->SetNotifyRigidBodyCollision(true);
	ProjectileCollisionMesh->SetVisibility(false);


	ProjectileLaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ProjectileLaunchBlast"));
	ProjectileLaunchBlast->bAutoActivate = true;
	
	ProjectileImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ProjectileImpactBlast"));
	ProjectileImpactBlast->bAutoActivate = false;
	

	ProjectileMovementComponent = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	auto attachrule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	ProjectileLaunchBlast->AttachToComponent(RootComponent, attachrule);
	ProjectileImpactBlast->AttachToComponent(RootComponent, attachrule);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector *speed);
	ProjectileMovementComponent->Activate(true);
}



