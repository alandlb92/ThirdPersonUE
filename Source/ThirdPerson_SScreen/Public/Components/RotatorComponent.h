// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSON_SSCREEN_API URotatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotatorComponent();
	
	UPROPERTY(EditAnywhere)
	float _speed = 200;
	UPROPERTY(EditAnywhere)
	class USceneComponent* _pivot;

	FRotator _startRotation;
	FRotator _endRotation;

	void SetScenePivotRotate(class USceneComponent* pivot);
	void Rotate();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	bool _isOpening;
};
