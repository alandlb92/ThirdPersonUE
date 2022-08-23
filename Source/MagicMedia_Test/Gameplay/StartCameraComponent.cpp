// Fill out your copyright notice in the Description page of Project Settings.


#include "StartCameraComponent.h"

// Sets default values for this component's properties
UStartCameraComponent::UStartCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStartCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->SetViewTarget(GetOwner());
	// ...
	
}


// Called every frame
void UStartCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

