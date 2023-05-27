#include "Inventory.hpp"

const unsigned int Cell::getID(sf::Vector2i mouse_pos) {
    return this->m_ID;
}

Inventory::Inventory(sf::Vector2f screen_size, float cell_size, sf::Font& font, unsigned int character_size) :m_font(font)
{
    this->isOpened = false;

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

    //init GUI inventory
    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 4; y++)
            this->CellsInventory.push_back(
                Cell(sf::Vector2f(
                this->m_BackShape.getPosition().x + size * x,
                this->m_BackShape.getPosition().y + size * y),
                size, this->m_CellInvTex, x + (y * 10)));

    //init Coins GUI
    this->m_Coins = new Coins(sf::Vector2f(
        m_BackShape.getPosition().x,
        m_BackShape.getPosition().y + m_BackShape.getSize().y - size / 2), //pos
        sf::Vector2f(this->m_BackShape.getSize().x, size),
        sf::Vector2f(size / 2, size / 2), this->m_font, character_size);


    //inttialisation inventory with 40 stone inside
    for (int x = 0; x < 40; x++)
    {
        this->m_InventoryMap[x] = new Stone(sf::Vector2f(
            this->m_BackShape.getPosition().x + size * x,
            this->m_BackShape.getPosition().y + size * x),
            sf::Vector2f(size, size), item_img_someore, false, 1, 1, false);

    }
}

Inventory::~Inventory() {
    //clearing the inventory
    for (auto& i : this->m_InventoryMap)
        delete i.second;
    //clearing the GUI inventory
    this->CellsInventory.clear();
    //clearing the GUI coins
    delete this->m_Coins;
}

void Inventory::addItem(Item* item) {
    //made a check if the item is already in the inventory
    if (item != nullptr)
        for (auto& i : this->m_InventoryMap) {
            //if current item slot is not null and the item is the same as the one we want to add
            if (i.second != nullptr && i.second == item) {
                if (i.second->getStackable()) {
                    i.second->addQuantity(item->getQuantity());
                    return;
                }
                else
                    continue;
            } // if current item slot is null and the item is the same as the one we want to add
            else if (i.second == nullptr) {
                i.second = item;
                return;
            }
            else
                return;
        }
}
void Inventory::removeItem(Item* item) {
    if (item != nullptr)
        for (auto& i : this->m_InventoryMap) {
            if (i.second == item)
            {
                delete i.second;
                i.second = nullptr;
                return;
            }

        }
}
void Inventory::removeItem(unsigned int ID) {
    //find item by using ID, if found delete it and set it to nullptr
    for (auto& i : this->m_InventoryMap) {
        if (i.second->getUnicID() == ID)
        {
            delete i.second;
            i.second = nullptr;
            return;
        }
    }
}
void Inventory::clear() {
    //clearing the inventory
    for (auto& i : this->m_InventoryMap)
        delete i.second;
}
void Inventory::openInventory() {
    this->isOpened = true;
}
void Inventory::closeInventory() {
    this->isOpened = false;
}

const unsigned int Inventory::getCurrentCellID(sf::Vector2i mousePos) {
    if (!this->CellsInventory.empty())
        for (auto& i : this->CellsInventory)
            if (i.getGlobalBounds(mousePos))
                return i.getID(mousePos);
    return 0;
}

//get item from the inventory by using ID item
Item* Inventory::getItem(unsigned int ID) {
    //get the item by using ID, else not found return nullptr
    for (auto& i : this->m_InventoryMap)
        if (i.second->getUnicID() == ID)
            return i.second;
    return nullptr;

}

Item* Inventory::getItemFromNumSlot(unsigned int num_slot) {
    //return the item from the num slot, else return nullptr
    if (this->m_InventoryMap[num_slot] != nullptr)
        return this->m_InventoryMap[num_slot];
    return nullptr;
}

void Inventory::update(sf::Vector2i mouse_pos) {
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
    //rendering the inventory

    //draw background layout
    target.draw(this->m_BackShape);

    //draw cells inventory
    if (!this->CellsInventory.empty())
        for (auto& i : this->CellsInventory)
            target.draw(i);

    //draw items in inventory, if not empty and not null draw it, else continue
    if (!this->m_InventoryMap.empty())
        for (auto& i : this->m_InventoryMap)
            if (i.second != nullptr)
                i.second->render(target);

    //draw coins
    target.draw(*this->m_Coins);
}