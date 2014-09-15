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

#ifndef GUI_GameOverFrame_h__
#define GUI_GameOverFrame_h__

#include "GUI/Frame.h"
#include "GUI/HealthOverlay.h"

namespace GUI
{

	class GameOverFrame : public Frame
	{
	public:
		GameOverFrame(Frame* parent, std::string name)
			: Frame(parent, name)
		{
			//Hide();
			m_Background = new TextureFrame(this, "Background");
			m_Background->SetTexture("Textures/GUI/black.png");
			m_Background->SetColor(glm::vec4(1.f, 1.f, 1.f, 0.6f));
			m_Text = new TextureFrame(this, "Message");
			m_Text->SetTexture("Textures/GUI/GloriousVictory.png");
		}

		void Show(bool victory)
		{
			if (victory)
				m_Text->SetTexture("Textures/GUI/GloriousVictory.png");
			else
				m_Text->SetTexture("Textures/GUI/ShamefulDefeat.png");

			Frame::Show();
		}

	protected:
		bool m_Victory;
		TextureFrame* m_Background;
		TextureFrame* m_Text;
	};
}

#endif // GUI_GameOverFrame_h__
