// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/LeverInteractable.h"
#include "Components/SceneComponent.h"
#include "Components/RotatorComponent.h"
#include "SingleAnimationPlayData.h"



ALeverInteractable::ALeverInteractable() : AInteractableBase()
{
	_sMeshLever = CreateAbstractDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Lever"));
	_sMeshLever->SetupAttachment(_sceneComponent);
	_sMeshLever->AddWorldRotation(FRotator(0, 0, 0));
	_sMeshLever->SetRelativeLocation(FVector(0, 0, 0));

	_rotatorPivot = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Rotator Pivot"));
	_rotatorPivot->SetupAttachment(_sceneComponent);

	_meshToRotate = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("<Mesh To Rotate"));
	_meshToRotate->SetupAttachment(_rotatorPivot);

	_rotator = CreateAbstractDefaultSubobject<URotatorComponent>(TEXT("Rotator"));

}
void ALeverInteractable::BeginPlay()
{
	Super::BeginPlay();
	_word = GetWorld();
	if (_word) {
		if (_word->IsServer()) {
			_rotator->SetScenePivotRotate(_rotatorPivot);
			SetActorTickEnabled(false);
		}
	}
}

void ALeverInteractable::Tick(float DeltaTime)
{
	if (!_sMeshLever->IsPlaying())
		OnAnimationEnd();

}


void ALeverInteractable::Interact(APlayerPawn* player)
{
	if (!_sMeshLever->IsPlaying()) {
		Multicast_PlayAnimation();
	}
}

void ALeverInteractable::Multicast_PlayAnimation_Implementation()
{
	_sMeshLever->Play(false);
	SetActorTickEnabled(true);
}



void ALeverInteractable::Desinteract(APlayerPawn* player)
{
}

void ALeverInteractable::OnAnimationEnd()
{
	SetActorTickEnabled(false);
	_sMeshLever->InitAnim(true);
	_sMeshLever->Stop();
	if (_rotator && _word->IsServer())
		_rotator->Rotate();
}
