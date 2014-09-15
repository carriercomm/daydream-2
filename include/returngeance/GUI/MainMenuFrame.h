/*
	This file is part of Daydream Engine.
	Copyright 2014 Adam Byléhn, Tobias Dahl, Simon Holmberg, Viktor Ljung
	
	Daydream Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Daydream Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Daydream Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GUI_MainMenuFrame_h__
#define GUI_MainMenuFrame_h__

#include "GUI/Frame.h"
#include "GUI/HealthOverlay.h"

#include "Events/GameStart.h"
#include "Events/PlayBGM.h"

namespace GUI
{

class MainMenuFrame : public Frame
{
public:
	MainMenuFrame(Frame* parent, std::string name)
		: Frame(parent, name)
	{
		m_CurrentSelection = 0;

		//Hide();
		m_Background = new TextureFrame(this, "Background");
		m_Background->SetTexture("Textures/GUI/MainMenu/BackGround.png");

		m_Buttons = new TextureFrame(this, "Message");
		m_Buttons->SetTexture("Textures/GUI/MainMenu/Buttons.png");
		m_CurrentCoordinate = -m_SelectionCoordinates[0] * Scale();
		m_TargetCoordinate = m_CurrentCoordinate;
		m_Buttons->X = m_CurrentCoordinate.x;
		m_Buttons->Y = m_CurrentCoordinate.y;

		Events::PlayBGM e;
		e.Resource = "Sounds/BGM/DiesIrae.mp3";
		EventBroker->Publish(e);
	}

	void Update(double dt) override
	{
		if (Hidden())
			return;

		glm::vec2 posDiff = m_TargetCoordinate - m_CurrentCoordinate;
		m_CurrentCoordinate += posDiff * 4.f * (float)dt;

		m_Buttons->X = m_CurrentCoordinate.x;
		m_Buttons->Y = m_CurrentCoordinate.y;
	}

protected:
	bool m_Victory;
	TextureFrame* m_Background;
	TextureFrame* m_Buttons;

	int m_CurrentSelection;
	static glm::vec2 m_SelectionCoordinates[2];
	glm::vec2 m_CurrentCoordinate;
	glm::vec2 m_TargetCoordinate;

	bool OnCommand(const Events::InputCommand &event) override
	{
		if (Hidden())
			return false;

		const float deadzone = 0.5f;

		if (event.Command == "interface_horizontal")
		{
			if (event.Value > deadzone)
				m_CurrentSelection++;
			else if (event.Value < -deadzone)
				m_CurrentSelection--;
		}
		m_CurrentSelection = (m_CurrentSelection < 0) ? 0 : ((m_CurrentSelection > 1) ? 1 : m_CurrentSelection);
		m_TargetCoordinate = -m_SelectionCoordinates[m_CurrentSelection] * Scale();

		if (event.Command == "interface_confirm" && event.Value > 0)
		{
			// Play
			if (m_CurrentSelection == 0)
			{
				Hide();
				Events::GameStart e1;
				EventBroker->Publish(e1);
				Events::PlayBGM e2;
				e2.Resource = "Sounds/BGM/FlightOfTheBumblebee.mp3";
				EventBroker->Publish(e2);
			}
			// Quit
			else if (m_CurrentSelection == 1)
			{
				exit(EXIT_SUCCESS);
			}
		}

		return false;
	}

	
};

glm::vec2 MainMenuFrame::m_SelectionCoordinates[2] = {
	glm::vec2(0, 0),
	glm::vec2(193, 0),
};

}

#endif // GUI_MainMenuFrame_h__
