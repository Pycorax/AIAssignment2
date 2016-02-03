#pragma once

// STL Includes
#include <sstream>
#include <string>

// Other Includes
#include "Character.h"
#include "TextObject.h"

// Using Directives
using std::ostringstream;
using std::string;

struct CharacterBundle
{
	enum E_CHAR_TEXT_DETAIL
	{
		CTD_NAME,
		CTD_HEALTH,
		CTD_STATE,
		CTD_SUBSTATE,
		CTD_TOTAL
	};

	Character* character;
	TextObject* charDetail[CTD_TOTAL];

	CharacterBundle(Character* charToShow, Mesh* font, Vector2 textPos)
	{
		if (charToShow)
		{
			Init(charToShow, font, textPos);
		}
	}

	~CharacterBundle()
	{
		delete character;
		character = nullptr;

		for (size_t i = 0; i < CTD_TOTAL; ++i)
		{
			delete charDetail[i];
			charDetail[i] = nullptr;
 		}
	}

	void Init(Character* charToShow, Mesh* font, Vector2 textPos)
	{
		character = charToShow;

		// Init Text
		for (size_t i = 0; i < CTD_TOTAL; ++i)
		{
			charDetail[i] = new TextObject(font, "", Color(0.0f, 0.0f, 0.0f));
			charDetail[i]->SetPos(Vector2(textPos.x, textPos.y + (CTD_TOTAL - i) * 3));
			charDetail[i]->SetScale(Vector2(3.0f));
		}
	}

	void Update(double dt)
	{
		// Update the Character
		character->Update(dt);

		// Update the Text
		ostringstream oss;

		// Set Character Name
		static string charNames[GameCharacter::NUM_GC] =
		{
			"Warrior",
			"Ranger",
			"Tank",
			"Healer"
		};

		GameCharacter* gc = dynamic_cast<GameCharacter*>(character);
		if (gc)
		{
			charDetail[CTD_NAME]->SetText(charNames[gc->GetType()]);
		}
		else
		{
			charDetail[CTD_NAME]->SetText("Enemy");
		}
		// -- HP
		oss << "HP: " << character->GetHealth() << "/" << character->GetMaxHealth();
		charDetail[CTD_HEALTH]->SetText(oss.str());
		oss.str("");
		// -- State
		charDetail[CTD_STATE]->SetText(character->GetThisStateName());
		// -- Substate
		charDetail[CTD_SUBSTATE]->SetText(character->GetChildStateName());
	}
};