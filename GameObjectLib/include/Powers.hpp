#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"


class Power {
	PlayObject& _obj;
	sf::View cameraView;

	sf::Sprite& character;

public:


	Power(PlayObject& obj) : _obj(obj), character(_obj.globalSprt[GlobalS::HFISH]){
	}
	~Power() = default;


};