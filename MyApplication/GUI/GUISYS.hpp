#ifndef GUI_H
#define GUI_H
#include "../header.h"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	class Button
	{
		private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Text text;
		sf::Font& b_font;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

		public:
		/**
		 * @brief Construct a new Button object
		 *
		 * @param position - position of button
		 * @param size - size of button
		 * @param font - font of button
		 * @param text - text of button
		 * @param character_size - size of text
		 * @param text_idle_color - color of text when idle
		 * @param text_hover_color - color of text when hover
		 * @param text_active_color - color of text when active
		 * @param idle_color - color of button when idle
		 * @param hover_color	- color of button when hover
		 * @param active_color	- color of button when active
		 * @param outline_idle_color - color of outline when idle
		 * @param outline_hover_color	- color of outline when hover
		 * @param outline_active_color - color of outline when active
		 * @param id - id of button
		 */
		Button(sf::Vector2f position, sf::Vector2f size,
			sf::Font& font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent,
			sf::Color outline_hover_color = sf::Color::Transparent,
			sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};

	class DropDownList
	{
		private:
		float keytime;
		float keytimeMax;

		sf::Font font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

		public:
		DropDownList(float x, float y, float width, float height,
			sf::Font& font, std::string list[],
			unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const unsigned short& getActiveElementId() const;

		//Functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
		private:
		float keytime;
		const float keytimeMax;
		float gridSize;
		bool active;
		bool hidden;
		gui::Button* hide_btn;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

		public:
		TextureSelector(float x, float y, float width, float height,
			float gridSize, const sf::Texture* texture_sheet,
			sf::Font& font, std::string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		//Functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class ProgressBar
	{
		private:
		std::string barString;
		sf::Text text;
		float maxWidth;
		sf::RectangleShape back;
		sf::RectangleShape inner;

		public:
		ProgressBar(sf::Vector2f pos, sf::Vector2f size,
			sf::Color inner_color, unsigned character_size,
			sf::Vector2f resolution, sf::Font& font);
		~ProgressBar();

		//Accessors

		//Modifiers

		//Functions
		void update(const int current_value, const int max_value);
		void render(sf::RenderTarget& target);
	};
}

#endif