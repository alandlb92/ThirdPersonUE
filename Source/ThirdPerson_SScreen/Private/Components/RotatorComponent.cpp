// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RotatorComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

URotatorComponent::URotatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(false);
	SetComponentTickEnabled(true);
}

void URotatorComponent::SetScenePivotRotate(USceneComponent* pivot)
{
	_pivot = pivot;
	_startRotation = _pivot->GetRelativeRotation();
	_endRotation = _startRotation + FRotator(0, 120, 0);
}


void URotatorComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.SetTickFunctionEnable(false);
	if (GetWorld()->IsServer())
	{
		SetComponentTickEnabled(true);
		PrimaryComponentTick.SetTickFunctionEnable(true);
	}
}


void URotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	_pivot->AddLocalRotation(FQuat::MakeFromRotator(FRotator3d(0, _speed * DeltaTime * (_isOpening ? 1 : -1), 0)));
	if (_pivot->GetComponentRotation().Yaw <= _startRotation.Yaw) {
		PrimaryComponentTick.SetTickFunctionEnable(false);
		_pivot->SetRelativeRotation(_startRotation);
	}
	else if (_pivot->GetComponentRotation().Yaw >= _endRotation.Yaw) {

		PrimaryComponentTick.SetTickFunctionEnable(false);
		_pivot->SetRelativeRotation(_endRotation);
	}
}


void URotatorComponent::Rotate()
{
	UE_LOG(LogTemp, Warning, TEXT("Server_Rotate_Implementation"));

	if (!PrimaryComponentTick.IsTickFunctionEnabled())
		PrimaryComponentTick.SetTickFunctionEnable(true);

	if (_pivot->GetRelativeRotation().Yaw <= _startRotation.Yaw)
		_isOpening = true;
	else if (_pivot->GetRelativeRotation().Yaw >= _endRotation.Yaw)
		_isOpening = false;
	else
		_isOpening = !_isOpening;
}