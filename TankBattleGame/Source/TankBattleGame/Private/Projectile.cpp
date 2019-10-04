// //KuKKi ©2019


#include "Projectile.h"
#include "TankProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"


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

	ProjectileExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ProjectileExplosionForce"));

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
	ProjectileExplosionForce->AttachToComponent(RootComponent,attachrule);
	
	ProjectileCollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
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

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	
	
	
	
	ProjectileLaunchBlast->Deactivate();
	ProjectileImpactBlast->Activate();
	ProjectileExplosionForce->FireImpulse();
	SetRootComponent(ProjectileImpactBlast);
	ProjectileCollisionMesh->DestroyComponent();
	FTimerHandle timerHandle;
	

	UGameplayStatics::ApplyRadialDamage(this,m_ProjectileDamage,GetActorLocation(),ProjectileExplosionForce->Radius,UDamageType::StaticClass(),TArray<AActor*>());

	GetWorld()->GetTimerManager().SetTimer(timerHandle,this,&AProjectile::OnTimerExpire,m_DestroyDelay);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}
