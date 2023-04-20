#include "Inventory.hpp"

Inventory::Inventory(sf::Vector2f screen_size, float cell_size)
{
    this->m_BackShape.setSize(sf::Vector2f(screen_size / 2.f));
    this->m_BackShape.setPosition(sf::Vector2f(screen_size / 4.f));
    this->m_BackShape.setFillColor(sf::Color(40, 40, 40, 225));

    this->m_CellInvTex.loadFromFile(tex_CellInventory_path);

    float size = mmath::p2pX(10, this->m_BackShape.getSize().x);
    float offsetX = mmath::p2pX(1, this->m_BackShape.getSize().x);

    for (int x = 0;x < 10;x++)
        for (int y = 0;y < 4;y++)
            this->CellsInventory.push_back(Cell(sf::Vector2f(
                this->m_BackShape.getPosition().x + size * x,
                this->m_BackShape.getPosition().y + size * y),
                size, this->m_CellInvTex));
}

Inventory::~Inventory()
{
    CellsInventory.clear();
}
void Inventory::update(const float& delta_time)
{

}

void Inventory::render(sf::RenderTarget* target)
{
    target->draw(this->m_BackShape);
    for (auto& i : this->CellsInventory)
        target->draw(i);
}