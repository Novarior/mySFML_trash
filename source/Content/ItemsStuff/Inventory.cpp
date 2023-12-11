#include "Inventory.hpp"

void Inventory::clearInventory()
{
    // Clearing the inventory
    for (std::vector<Item*>& row : InventoryArray) {
        for (Item* slotMap : row) {
            delete slotMap;
            slotMap = nullptr;
        }
    }
}

Inventory::Inventory(sf::Vector2f screen_size, float gridSize_cell, sf::Font& font, unsigned int character_size)
    : m_font(font)
{
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
    unsigned int rows = 20; // for example
    unsigned int cols = 10; // for example
    float cell_size = gridSize_cell;
    for (unsigned int row = 0; row < rows; ++row) {
        std::vector<Cell> rowCells;
        for (unsigned int col = 0; col < cols; ++col) {
            sf::Vector2f cellPos(
                this->m_background_inventory.getPosition().x + (screen_2to3.x / 20) * row,
                this->m_background_inventory.getPosition().y + (screen_2to3.x / 20) * col);

            rowCells.emplace_back(cellPos, screen_2to3.x / rows, this->m_CellInvTex, row * cols + col);
        }
        CellsInventory.push_back(rowCells);
    }

    // init Coins GUI
    this->m_Coins = { 0, 0, 0 };

    // initializing the inventory map with nullptr 30 rows and 4 columns
    // array std::vector<std::vector<Item*>> InventoryArray;
    this->clearInventory();
    // resize 30x4
    this->InventoryArray.resize(rows, std::vector<Item*>());
    for (int i = 0; i < rows; i++)
        this->InventoryArray[i].resize(cols, nullptr);
}

Inventory::~Inventory()
{
    // clearing the inventory
    for (std::vector<Item*>& row : this->InventoryArray) {
        for (Item* it : row) {
            delete it;
            it = nullptr;
        }
        row.clear();
    }
    this->InventoryArray.clear();

    // Очистка вектора CellsInventory
    for (auto& rowCells : this->CellsInventory)
        rowCells.clear();

    this->CellsInventory.clear();
}

bool Inventory::addItem(Item* item)
{ // check if item is not null
    if (item != nullptr) { // check if item is not nullptr
        //  check if the item is stackable
        if (item->isStackable()) { // if stackable
            // find empty slot and add item to it
            for (size_t row = 0; row < this->InventoryArray.size(); row++)
                for (size_t col = 0; col < this->InventoryArray[row].size(); col++)
                    // if slot is not empty
                    if (this->InventoryArray[row][col] != nullptr) {

                        // check if the amount of item is less than max amount
                        if (this->InventoryArray[row][col]->getAmount() < this->InventoryArray[row][col]->getMaxAmount()) {
                            this->InventoryArray[row][col]->addAmount(item->getAmount());
                            return true;
                        }
                    } else if (this->InventoryArray[row][col] == nullptr) {
                        // if slot is empty

                        this->InventoryArray[row][col] = item;
                        this->InventoryArray[row][col]->setPosistion(this->CellsInventory[row][col].getPosition());
                        this->InventoryArray[row][col]->setSize(this->CellsInventory[row][col].getSize());
                        return true;
                    }

        } else { // if not stackable
            // find empty slot and add item to it
            for (auto& row : this->InventoryArray)
                for (auto& it : row)
                    if (it == nullptr) {
                        it = item;
                        return true;
                    }
        }
    }
    return false;
}

bool Inventory::removeItem(Item* item)
{
    if (item != nullptr) {
        for (std::vector<Item*>& row : InventoryArray) {
            for (Item* slotMap : row) {
                if (slotMap != nullptr && slotMap->getID() == item->getID()) {
                    delete slotMap;
                    slotMap = nullptr;
                    return true;
                }
            }
        }
    }
    return false;
}
bool Inventory::removeItem(unsigned int ID)
{
    // find item by using ID, if found delete it and set it to nullptr
    for (std::vector<Item*>& row : InventoryArray) {
        for (Item* slotMap : row) {
            if (slotMap != nullptr && slotMap->getID() == ID) {
                delete slotMap;
                slotMap = nullptr;
                return true;
            }
        }
    }
    return false;
}

void Inventory::clear()
{
    // Clearing the inventory
    for (std::vector<Item*>& row : InventoryArray) {
        for (Item* slotMap : row) {
            delete slotMap;
            slotMap = nullptr;
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

const int Inventory::getNumSlot(Item* item)
{
    if (item != nullptr)
        for (int x = 0; x < this->InventoryArray.size(); x++)
            for (int y = 0; y < this->InventoryArray[x].size(); y++)
                if (this->InventoryArray[x][y] != nullptr && this->InventoryArray[x][y]->getID() == item->getID())
                    return x * this->InventoryArray.size() + y;

    return -1;
}

Coins& Inventory::getCoins()
{
    return this->m_Coins;
}
// get item from the inventory by using ID item
Item* Inventory::getItem(unsigned int ID)
{
    Item* foundItem = nullptr;

    for (std::vector<Item*>& row : this->InventoryArray)
        for (Item* item : row)
            if (item != nullptr && item->getID() == ID)
                return item;

    return foundItem;
}

Item* Inventory::getItemFromNumSlot(unsigned int num_slot)
{ // Check if the slot is within the valid range
    if (0 <= num_slot < this->InventoryArray.size()) {
        // Get the row of the slot
        // Loop through each column in the row
        for (int i = 0; i < this->InventoryArray.size(); ++i)
            if (this->InventoryArray[i][i % 4] != nullptr)
                return this->InventoryArray[num_slot][i];
    }
    return nullptr; // Item not found
}

void Inventory::update(sf::Vector2i mouse_pos)
{
    if (!this->CellsInventory.empty())
        for (auto& rowCells : CellsInventory)
            for (auto& cell : rowCells)
                cell.update(mouse_pos);

    this->m_StringStream << this->m_Coins.get_GoldCointCount() << "\t\t" << this->m_Coins.get_SilverCointCount() << "\t\t" << this->m_Coins.get_CopperCointCount();
    this->m_Text.setString(this->m_StringStream.str());
    this->m_StringStream.str("");
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
    for (std::vector<Item*>& row : this->InventoryArray)
        for (Item* item : row)
            if (item != nullptr)
                item->render(target);
            else
                continue;
}