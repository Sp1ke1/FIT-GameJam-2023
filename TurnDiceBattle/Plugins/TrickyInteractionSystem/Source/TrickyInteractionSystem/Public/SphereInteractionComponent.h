// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "InteractionLibrary.h"
#include "Components/SphereComponent.h"
#include "SphereInteractionComponent.generated.h"

class AActor;

/**
 * A simple sphere interaction component which adds the owner to the interaction queue. 
 */
UCLASS(ClassGroup=(TrickyInteraction), meta=(BlueprintSpawnableComponent))
class TRICKYINTERACTIONSYSTEM_API USphereInteractionComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	USphereInteractionComponent();

	/** Called when the owner was added to the interaction queue. */
	UPROPERTY(BlueprintAssignable, Category="TrickyInteractionSystem")
	FOnQueueChangedSignature OnActorAdded;

	/** Called when the owner was removed from the interaction queue. */
	UPROPERTY(BlueprintAssignable, Category="TrickyInteractionSystem")
	FOnQueueChangedSignature OnActorRemoved;

	UFUNCTION(BlueprintSetter, Category="TrickyInteractionSystem")
	void SetInteractionData(const FInteractionData& Value);

	UFUNCTION(BlueprintCallable, Category="TrickyInteractionSystem")
	void SetInteractionMessage(AActor* Actor, const FString& Message);

	UFUNCTION(BlueprintGetter, Category="TrickyInteractionSystem")
	FInteractionData GetInteractionData() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly,
		BlueprintGetter=GetInteractionData,
		BlueprintSetter=SetInteractionData,
		Category="Interaction",
		meta=(AllowPrivateAccess))
	FInteractionData InteractionData;

	UFUNCTION()
	virtual void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                AActor* OtherActor,
	                                UPrimitiveComponent* OtherComp,
	                                int32 OtherBodyIndex,
	                                bool bFromSweep,
	                                const FHitResult& SweepResult);

	UFUNCTION()
	virtual void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent,
	                              AActor* OtherActor,
	                              UPrimitiveComponent* OtherComp,
	                              int32 OtherBodyIndex);
};
