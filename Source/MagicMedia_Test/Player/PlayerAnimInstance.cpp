// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

bool UPlayerAnimInstance::IsMovingFoward()
{
	return _directionY >= 0;
}