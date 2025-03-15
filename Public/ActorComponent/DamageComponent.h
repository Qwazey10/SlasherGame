// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"
#include "Components/ActorComponent.h"
#include "Interfaces/BPI_DamageInterface.h"
#include "DamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASHER_API UDamageComponent : public UActorComponent, public IBPI_DamageInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GetDefenseVarsFromOwner(); //Gets Owner and casts to type depending on owner tag and then pulls defensive vars. 
	void CallDeathOfOwnerInterface(); // Function to call the interface event on Owner.

	//Interface Functions to call cosmetic effect for status on owners. 
	void CallDmgInterfaceApplyEffectCosmeticBurning();
	void CallDmgInterfaceApplyEffectCosmeticPoison();
	void CallDmgInterfaceApplyEffectCosmeticBleed();
	void CallDmgInterfaceApplyEffectCosmeticFrost();

	void EndDmgInterfaceApplyEffectCosmeticBurning();
	void EndDmgInterfaceApplyEffectCosmeticPoison();
	void EndDmgInterfaceApplyEffectCosmeticBleed();
	void EndDmgInterfaceApplyEffectCosmeticFrost();

	//Meat and bones of the damage function. 
	void ApplyDamage(AActor* InstigatingActor, float BaseWeaponDamage, EDamageType DamageType, float StatusAmt);
	//Function that we will call when the relevant actor triggers a damage event. 
	void DealDamage(AActor* InstigatingActor, float BaseWeaponDamage,
	EDamageType PrimaryDamageType, float PrimaryStatusAmt, EDamageType SecondaryDamageType, float SecondaryStatusAmt);

	static float CalculateStatusDamage(const float StatusAmt, const float StatusDefense);
	static float CalculateBaseDamage(const float BaseDamage, const float DamageTypeResist);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float CurrentHealth = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float MaxHealth = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float DmgComponentCurrentMana = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float DmgComponentCurrentGuard = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float DmgComponentMaxGuard = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float DmgComponentArmor = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float DmgComponentResist_Fire = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float DmgComponentResist_Cold = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float DmgComponentResist_Detrimental = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float DmgComponentResist_Divine = 0.0f;
	
	//Status Effects
	FTimerHandle BurningEffectTimerHandle;
	float BurnDamageBase;
	int BurningEffectTimerCount;
	int BurningEffectTimerCountMax = 10;
	float BurningTimerTickRate = 2;
	void StartBurningEffect();
	void ApplyBurningDamage();
	void StopBurningEffect();

	FTimerHandle PoisonEffectTimerHandle;
	float PoisonDamageBase = 0.0f;
	int PoisonEffectTimerCount=0;
	int PoisonEffectTimerCountMax = 5;
	float PoisonTimerTickRate = 6;
	void StartPoisonEffect();
	void ApplyPoisonDamage();
	void StopPoisonEffect();

	FTimerHandle FrostEffectTimerHandle;
	float FrostDamageBase = 0.0f;
	int FrostEffectTimerCount = 0;
	int FrostEffectTimerCountMax = 2;
	float FrostTimerTickRate = 6;
	void StartFrostEffect();
	void ApplyFrostDamage();
	void StopFrostEffect();

	FTimerHandle BleedingEffectTimerHandle;
	float BleedingDamageBase = 1;
	int BleedingEffectTimerCount;
	int BleedingEffectTimerCountMax = 10;
	float BleedingTimerTickRate = 2;
	void StartBleedingEffect();
	void ApplyBleedingDamage();
	void StopBleedingEffect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float BasePoisonBuildup = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float BaseBleedBuildup = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float BaseBurnBuildup = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	float BaseFrostBuildup = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	bool bIsImmunePoison = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	bool bIsImmuneBleed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	bool bIsImmuneBurn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Status")
	bool bIsImmuneFrost = false;

	
};
