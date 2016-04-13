/**
*  PlayerInputComponent.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
InputComponent represents the abstreact base class from which all other
imput Components are derived.

Only the local player GameObject should have this component.

*/
#pragma once

#ifndef PLAYERINPUTCOMPONENT_H_INCLUDED
#define PLAYERINPUTCOMPONENT_H_INCLUDED

#include "InputComponent.h"
#include "PlayerComponentIncludes.h"

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent(GameObject* player, float _playerSpeed, float _featherSpeed);
	~PlayerInputComponent();

	void Update();

	InputManager* input;

private:
	/// True if player currently charging a feather
	bool isChargingAttack = false;
	/// True if the player attack is not on cooldown
	bool canFire = true;
	/// the top bound for feather timer
	float maxCharge = 1300;
	float playerSpeed;
	float featherSpeed;
};

#endif