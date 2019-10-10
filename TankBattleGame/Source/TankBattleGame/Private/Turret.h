// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class ATurret : public ATank
{
	GENERATED_BODY()
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
