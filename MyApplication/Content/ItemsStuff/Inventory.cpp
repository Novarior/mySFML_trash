#include "Inventory.hpp"

Inventory::Inventory(sf::Vector2f screen_size, float gridSize_cell, sf::Font& font, unsigned int character_size)
    : m_font(font)
{
    // init all variables who use in this class operator new like nullptr
    this->m_Coins = nullptr;

    // init flag for inventory
    this->isOpened = false;

    // init background layout
    sf::Vector2f screen_2to3(mmath::p2pX(66, screen_size.x), mmath::p2pX(66, screen_size.y));
    sf::Vector2f screen_1to6(mmath::p2pX(16, screen_size.x), mmath::p2pX(16, screen_size.y));
    sf::Vector2f screen_1t10(mmath::p2pX(10, screen_size.x), mmath::p2pX(10, screen_size.y));

    this->m_background_inventory.setSize(screen_2to3);
    this->m_background_inventory.setPosition(screen_1to6);
    this->m_background_inventory.setFillColor(sf::Color(40, 40, 40, 225));

    // // init text layout
    // this->m_Text.setCharacterSize(character_size);
    // this->m_Text.setFont(font);
    // this->m_Text.setFillColor(sf::Color::White);
    // this->m_Text.setOutlineColor(sf::Color::Black);
    // this->m_Text.setOutlineThickness(2.0f);
    // this->m_CellInvTex.loadFromFile(myConst::texture_CellInventory_path);
    // this->m_StringStream.str("");
    // this->m_Text.setPosition(m_BackShape.getPosition().x + character_size,
    //     m_BackShape.getPosition().y + m_BackShape.getSize().y - mmath::p2pX(5, this->m_BackShape.getSize().y) - character_size);

    // init cells inventory layout
    // Initialize the CellsInventory with rows and columns
    unsigned int rows = 30; // for example
    unsigned int cols = 4; // for example
    float cell_size = gridSize_cell;
    for (unsigned int row = 0; row < rows; ++row) {
        std::vector<Cell> rowCells;
        for (unsigned int col = 0; col < cols; ++col) {
            sf::Vector2f cellPos(
                this->m_background_inventory.getPosition().x + (screen_2to3.x / 30) * row,
                this->m_background_inventory.getPosition().y + (screen_2to3.x / 30) * col);

            rowCells.emplace_back(cellPos, screen_2to3.x / rows, this->m_CellInvTex, row * cols + col);
        }
        CellsInventory.push_back(rowCells);
    }

    // init Coins GUI
    this->m_Coins = new Coins(
        sf::Vector2f(
            m_background_inventory.getPosition().x,
            m_background_inventory.getPosition().y + this->m_background_inventory.getSize().y - screen_1t10.y * 2 / 3),
        sf::Vector2f(screen_2to3.x, screen_1t10.y * 2 / 3),
        sf::Vector2f(gridSize_cell, gridSize_cell), this->m_font, character_size);

    // initializing the inventory map (empty)
    this->InventoryArray.resize(rows, std::vector<std::map<unsigned int, Item*>>(cols));
}

Inventory::~Inventory()
{
    // clearing the inventory
    for (std::vector<std::map<unsigned int, Item*>>& row : this->InventoryArray) {
        for (std::map<unsigned int, Item*>& slotMap : row) {
            for (auto& entry : slotMap) {
                delete entry.second;
                entry.second = nullptr;
            }
            slotMap.clear();
        }
    }
    this->InventoryArray.clear();

    // Очистка вектора CellsInventory
    for (auto& rowCells : this->CellsInventory)
        rowCells.clear();

    this->CellsInventory.clear();

    // clearing the GUI coins
    if (this->m_Coins != nullptr)
        delete this->m_Coins;
}

bool Inventory::addItem(Item* item)
{
    // Made a check if the item is already in the inventory
    if (item != nullptr) {
        // Try to stack the item in existing slots
        for (std::vector<std::map<unsigned int, Item*>>& row : InventoryArray) {
            for (std::map<unsigned int, Item*>& slotMap : row) {
                for (auto& entry : slotMap) {
                    if (entry.second != nullptr && entry.second == item) {
                        if (entry.second->getStackable()) {
                            entry.second->addQuantity(item->getQuantity());
                            return true;
                        } else {
                            continue;
                        }
                    }
                }
            }
        }

        // If stacking is not possible, find an empty slot and add the item
        for (std::vector<std::map<unsigned int, Item*>>& row : InventoryArray) {
            for (std::map<unsigned int, Item*>& slotMap : row) {
                for (auto& entry : slotMap) {
                    if (entry.second == nullptr) {
                        entry.second = item;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Inventory::removeItem(Item* item)
{
    if (item != nullptr) {
        for (std::vector<std::map<unsigned int, Item*>>& row : InventoryArray) {
            for (std::map<unsigned int, Item*>& slotMap : row) {
                for (auto& entry : slotMap) {
                    if (entry.second == item) {
                        delete entry.second;
                        entry.second = nullptr;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool Inventory::removeItem(unsigned int ID)
{
    // find item by using ID, if found delete it and set it to nullptr
    for (std::vector<std::map<unsigned int, Item*>>& row : InventoryArray) {
        for (std::map<unsigned int, Item*>& slotMap : row) {
            for (auto& entry : slotMap) {
                if (entry.second != nullptr && entry.second->getID() == ID) {
                    delete entry.second;
                    entry.second = nullptr;
                    return true;
                }
            }
        }
    }
    return false;
}
void Inventory::clear()
{
    // Clearing the inventory
    for (std::vector<std::map<unsigned int, Item*>>& row : InventoryArray) {
        for (std::map<unsigned int, Item*>& slotMap : row) {
            for (auto& entry : slotMap) {
                delete entry.second;
                entry.second = nullptr;
            }
        }
    }
}

void Inventory::openInventory()
{
    this->isOpened = true;
}
void Inventory::closeInventory()
{
    this->isOpened = false;
}

const unsigned int Inventory::getCurrentCellID(sf::Vector2i mousePos)
{
    if (!this->CellsInventory.empty())
        for (auto& rowCells : CellsInventory)
            for (auto& cell : rowCells) {
                if (cell.getGlobalBounds(mousePos))
                    return cell.getID(mousePos);
            }
    return 0;
}

Coins* Inventory::getCoins()
{
    if (this->m_Coins != nullptr)
        return this->m_Coins;
    return nullptr;
}
// get item from the inventory by using ID item
Item* Inventory::getItem(unsigned int ID)
{
    Item* foundItem = nullptr;

    for (auto& x : this->InventoryArray)
        for (auto y : x)
            for (auto& item : y)
                if (item.second->getID() == ID)
                    foundItem = item.second;

    return foundItem;
}

Item* Inventory::getItemFromNumSlot(unsigned int num_slot)
{
    // Check if the slot is within the valid range
    if (num_slot < this->InventoryArray.size()) {
        // Get the row of the slot
        std::vector<std::map<unsigned int, Item*>>& row = this->InventoryArray[num_slot];

        // Loop through each column in the row
        for (std::map<unsigned int, Item*>& slotMap : row) {
            // Check if the slot contains an item with the given ID
            if (slotMap.find(num_slot) != slotMap.end() && slotMap[num_slot] != nullptr) {
                return slotMap[num_slot];
            }
        }
    }

    return nullptr; // Item not found
}

void Inventory::update(sf::Vector2i mouse_pos)
{
    if (!this->CellsInventory.empty())
        for (auto& rowCells : CellsInventory)
            for (auto& cell : rowCells)
                cell.update(mouse_pos);

    this->m_StringStream << this->m_Coins->get_GoldCointCount() << "\t\t" << this->m_Coins->get_SilverCointCount() << "\t\t" << this->m_Coins->get_CopperCointCount();
    this->m_Text.setString(this->m_StringStream.str());
    this->m_StringStream.str("");

    this->m_Coins->getText();
}

void Inventory::render(sf::RenderTarget& target)
{
    // rendering the inventory

    // draw background layout
    target.draw(this->m_background_inventory);

    // draw cells inventory
    if (!this->CellsInventory.empty())
        for (auto& rowCells : CellsInventory)
            for (auto& cell : rowCells)
                target.draw(cell);

    // // draw items in inventory, if not empty and not null draw it, else continue
    for (const auto& row : InventoryArray) {
        for (const auto& column : row) {
            for (const auto& entry : column) {
                Item* item = entry.second;
                if (item != nullptr) {
                    item->render(target);
                }
            }
        }
    }

    // draw coins
    target.draw(*this->m_Coins);
}