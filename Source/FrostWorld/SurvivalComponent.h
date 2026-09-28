#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivalComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FROSTWORLD_API USurvivalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USurvivalComponent();

protected:
	virtual void BeginPlay() override;

public:
	// Вызывается каждый кадр (аналог Update() в Unity)
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// --- ТЕКУЩИЕ ПАРАМЕТРЫ (доступны для чтения из UI в Blueprints) ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival|Stats")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival|Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival|Stats")
	float Warmth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival|Stats")
	float MaxWarmth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival|Stats")
	float Hunger = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Survival|Stats")
	float MaxHunger = 100.0f;

	// --- СКОРОСТИ ИЗМЕНЕНИЯ (в секунду) ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival|Balance")
	float WarmthDrainRate = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival|Balance")
	float HungerDrainRate = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival|Balance")
	float FreezingDamageRate = 2.0f;

	// Флаг: находится ли игрок сейчас возле источника тепла (костра)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Survival|State")
	bool bIsWarmingUp = false;

	// --- МЕТОДЫ ИНТЕРАКЦИИ (сможем вызывать при поедании еды или у костра) ---
	UFUNCTION(BlueprintCallable, Category = "Survival|Actions")
	void AddWarmth(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Survival|Actions")
	void AddHunger(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Survival|Actions")
	void SetWarmingUp(bool bWarming) { bIsWarmingUp = bWarming; }
};