#include "Inventory.hpp"

Inventory::Inventory(sf::Vector2f screen_size, float cell_size, sf::Font& font, unsigned int character_size):m_font(font)
{
    this->m_BackShape.setSize(sf::Vector2f(screen_size / 2.f));
    this->m_BackShape.setPosition(sf::Vector2f(screen_size / 4.f));
    this->m_BackShape.setFillColor(sf::Color(40, 40, 40, 225));

    float size = mmath::p2pX(10, this->m_BackShape.getSize().x);

    this->m_Text.setCharacterSize(character_size);
    this->m_Text.setFont(font);
    this->m_Text.setFillColor(sf::Color::White);
    this->m_Text.setOutlineColor(sf::Color::Black);
    this->m_Text.setOutlineThickness(2.0f);
    this->m_CellInvTex.loadFromFile(texture_CellInventory_path);
    this->m_StringStream.str("");
    this->m_Text.setPosition(m_BackShape.getPosition().x + character_size,
        m_BackShape.getPosition().y + m_BackShape.getSize().y - mmath::p2pX(5, this->m_BackShape.getSize().y) - character_size);


    for (int x = 0;x < 10;x++)
        for (int y = 0;y < 4;y++)
            this->CellsInventory.push_back(
                Cell(sf::Vector2f(
                this->m_BackShape.getPosition().x + size * x,
                this->m_BackShape.getPosition().y + size * y),
                size, this->m_CellInvTex, x + y * 10));

    this->m_Coins = new Coins(sf::Vector2f(
        m_BackShape.getPosition().x,
        m_BackShape.getPosition().y + m_BackShape.getSize().y - size / 2), //pos
        sf::Vector2f(this->m_BackShape.getSize().x, size),
        sf::Vector2f(size / 2, size / 2), this->m_font, character_size);
}

Inventory::~Inventory() {
    delete this->m_Coins;
    CellsInventory.clear();

}
void Inventory::update(sf::Vector2i& mouse_pos) {
    if (!this->CellsInventory.empty())
        for (auto& i : this->CellsInventory)
            i.update(mouse_pos);

    this->m_StringStream <<
        this->m_Coins->get_GoldCointCount() << "\t\t" <<
        this->m_Coins->get_SilverCointCount() << "\t\t" <<
        this->m_Coins->get_CopperCointCount();
    this->m_Text.setString(this->m_StringStream.str());
    this->m_StringStream.str("");

    this->m_Coins->getText();
}

void Inventory::render(sf::RenderTarget& target) {
    target.draw(this->m_BackShape);

    if (!this->CellsInventory.empty())
        for (auto& i : this->CellsInventory)
            target.draw(i);

    target.draw(*this->m_Coins);
}