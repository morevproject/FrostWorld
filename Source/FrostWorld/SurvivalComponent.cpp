#include "SurvivalComponent.h"

USurvivalComponent::USurvivalComponent()
{
	// Разрешаем компоненту тикать каждый кадр (как включение Update() в Unity)
	PrimaryComponentTick.bCanEverTick = true;
}

void USurvivalComponent::BeginPlay()
{
	Super::BeginPlay();

	// На старте выравниваем статы до максимума
	Health = MaxHealth;
	Warmth = MaxWarmth;
	Hunger = MaxHunger;
}

void USurvivalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 1. Считаем Голод
	Hunger = FMath::Clamp(Hunger - (HungerDrainRate * DeltaTime), 0.0f, MaxHunger);

	// 2. Считаем Тепло
	if (bIsWarmingUp)
	{
		// Если греемся у костра — тепло быстро восстанавливается (+10 в сек)
		Warmth = FMath::Clamp(Warmth + (10.0f * DeltaTime), 0.0f, MaxWarmth);
	}
	else
	{
		// Если на морозе — мерзнем. Если игрок еще и голодает (Hunger < 20), мерзнет в 2 раза быстрее!
		float DrainMultiplier = (Hunger < 20.0f) ? 2.0f : 1.0f;
		Warmth = FMath::Clamp(Warmth - (WarmthDrainRate * DrainMultiplier * DeltaTime), 0.0f, MaxWarmth);
	}

	// 3. Здоровье: если Тепло упало до нуля — получаем урон от обморожения
	if (Warmth <= 0.0f)
	{
		Health = FMath::Clamp(Health - (FreezingDamageRate * DeltaTime), 0.0f, MaxHealth);

		if (Health <= 0.0f)
		{
			// Персонаж погиб (позже прикрутим экран смерти)
		}
	}

	// 4. Отладочный вывод прямо на экран (чтобы сразу видеть цифры без готового UI!)
	if (GEngine)
	{
		FString DebugMsg = FString::Printf(
			TEXT("Warmth: %d%% | Hunger: %d%% | HP: %d%%"),
			FMath::RoundToInt(Warmth),
			FMath::RoundToInt(Hunger),
			FMath::RoundToInt(Health)
		);
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Cyan, DebugMsg);
	}
}

void USurvivalComponent::AddWarmth(float Amount)
{
	Warmth = FMath::Clamp(Warmth + Amount, 0.0f, MaxWarmth);
}

void USurvivalComponent::AddHunger(float Amount)
{
	Hunger = FMath::Clamp(Hunger + Amount, 0.0f, MaxHunger);
}