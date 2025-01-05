#include "Inventory.hpp"

// Очистка инвентаря
void Inventory::clearInventory()
{
    for (auto& row : InventoryArray)
        for (auto& item : row) {
            item.reset(); // Умное указание освободит память
        }
}

void Inventory::initializeCells(unsigned int rows, unsigned int cols, float cell_size)
{
    // Резервируем память для двух векторов: ячеек и инвентаря
    CellsInventory.resize(rows, std::vector<Cell>(cols, Cell(sf::Vector2f(0, 0), cell_size, m_CellInvTex)));
    InventoryArray.resize(rows, std::vector<std::shared_ptr<Item>>(cols, nullptr));

    // Загружаем текстуру для ячеек
    if (!m_CellInvTex.loadFromFile("path_to_texture.png")) {
        // Обработка ошибки загрузки текстуры
        std::cerr << "Ошибка загрузки текстуры для ячеек инвентаря!" << std::endl;
        return;
    }

    // Инициализация каждой ячейки
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            // Позиция ячейки на экране
            sf::Vector2f cellPosition(
                m_background_inventory.getPosition().x + col * cell_size,
                m_background_inventory.getPosition().y + row * cell_size);

            // Создание ячейки
            CellsInventory[row][col] = Cell(cellPosition, cell_size, this->m_CellInvTex);
        }
    }
}

// Конструктор инвентаря
Inventory::Inventory(sf::Vector2f screen_size, unsigned int rows, unsigned int cols, sf::Font& font, float cell_size)
    : m_font(font)
    , isOpened(false)
    , m_Coins(0, 0, 0)
{
    // Фон инвентаря
    sf::Vector2f inventorySize(screen_size.x * 0.5f, screen_size.y * 0.5f);
    sf::Vector2f inventoryPosition(screen_size.x * 0.25f, screen_size.y * 0.25f);

    m_background_inventory.setSize(inventorySize);
    m_background_inventory.setPosition(inventoryPosition);
    m_background_inventory.setFillColor(sf::Color(40, 40, 40, 225));

    // Инициализация ячеек
    initializeCells(rows, cols, cell_size);

    // Инициализация текста
    m_Text.setFont(m_font);
    m_Text.setCharacterSize(24);
    m_Text.setFillColor(sf::Color::White);
    m_Text.setString("Inventory");
    updateTextPosition();
}

void Inventory::updateTextPosition()
{
    // Позиционируем текст в верхней части инвентаря (например, чуть выше фона)
    sf::Vector2f textPosition(
        m_background_inventory.getPosition().x + 10.f, // сдвиг от левого края фона
        m_background_inventory.getPosition().y - 30.f // сдвиг от верхнего края фона
    );

    m_Text.setPosition(textPosition);
}

unsigned int Inventory::getCurrentCellID(sf::Vector2i mouse_pos) const
{
    // Получаем размеры ячеек
    float cell_size = CellsInventory[0][0].getSize().x; // Предполагаем, что все ячейки одного размера

    // Проверяем, что позиция мыши находится в пределах инвентаря
    if (mouse_pos.x < m_background_inventory.getPosition().x || mouse_pos.y < m_background_inventory.getPosition().y || mouse_pos.x > m_background_inventory.getPosition().x + m_background_inventory.getSize().x || mouse_pos.y > m_background_inventory.getPosition().y + m_background_inventory.getSize().y) {
        return -1; // Если мышь не внутри инвентаря
    }

    // Рассчитываем индексы строки и столбца в сетке инвентаря
    unsigned int row = (mouse_pos.y - m_background_inventory.getPosition().y) / cell_size;
    unsigned int col = (mouse_pos.x - m_background_inventory.getPosition().x) / cell_size;

    // Проверяем, что индексы находятся в пределах размеров инвентаря
    if (row >= CellsInventory.size() || col >= CellsInventory[0].size()) {
        return -1; // Если координаты вне допустимого диапазона
    }

    // Возвращаем идентификатор ячейки
    return CellsInventory[row][col].getID();
}

// Деструктор инвентаря
Inventory::~Inventory()
{
    clearInventory();
}

bool Inventory::addItem(std::shared_ptr<Item> item)
{
    if (!item)
        return false;

    // Если предмет можно складывать
    if (item->isStackable()) {
        for (auto& row : InventoryArray) {
            for (auto& slot : row) {
                if (slot && slot->getID() == item->getID() && slot->getAmount() < slot->getMaxAmount()) {
                    slot->addAmount(item->getAmount());
                    return true;
                }
            }
        }
    }

    // Если предмет не складывается, ищем пустой слот
    for (size_t row = 0; row < InventoryArray.size(); ++row) {
        for (size_t col = 0; col < InventoryArray[row].size(); ++col) {
            if (!InventoryArray[row][col]) {
                InventoryArray[row][col] = item;

                // Привязка позиции и размера предмета к ячейке
                item->setPosition(CellsInventory[row][col].getPosition());
                item->setSize(CellsInventory[row][col].getSize());
                return true;
            }
        }
    }

    return false; // Инвентарь заполнен
}

bool Inventory::removeItemByID(unsigned int ID)
{
    for (auto& row : InventoryArray) {
        auto it = std::find_if(row.begin(), row.end(), [ID](std::shared_ptr<Item> slot) {
            return slot && slot->getID() == ID;
        });

        if (it != row.end()) {
            *it = nullptr; // Освобождение слота
            return true;
        }
    }
    return false; // Предмет с таким ID не найден
}

std::shared_ptr<Item> Inventory::getItem(unsigned int ID) const
{
    for (const auto& row : InventoryArray) {
        for (const auto& item : row) {
            if (item && item->getID() == ID) {
                return item;
            }
        }
    }
    return nullptr; // Предмет не найден
}

std::shared_ptr<Item> Inventory::getItemFromSlot(unsigned int slot) const
{
    unsigned int rows = InventoryArray.size();
    unsigned int cols = InventoryArray[0].size();

    if (slot >= rows * cols)
        return nullptr;

    return InventoryArray[slot / cols][slot % cols];
}

int Inventory::getTotalSlots() const
{
    return static_cast<int>(InventoryArray.size() * InventoryArray[0].size());
}

Coins& Inventory::getCoins()
{
    return m_Coins;
}

// Обновление инвентаря
void Inventory::update(sf::Vector2i mouse_pos)
{
    for (auto& row : CellsInventory) {
        for (auto& cell : row) {
            cell.update(mouse_pos);
        }
    }

    // Обновление текста с монетами
    m_StringStream.str("");
    m_StringStream.clear();
    m_StringStream << "Gold: " << m_Coins.get_GoldCointCount() << " | "
                   << "Silver: " << m_Coins.get_SilverCointCount() << " | "
                   << "Copper: " << m_Coins.get_CopperCointCount();
    m_Text.setString(m_StringStream.str());
}

void Inventory::render(sf::RenderTarget& target)
{
    if (!isOpened)
        return;

    // Отображение фона и ячеек
    target.draw(m_background_inventory);
    for (const auto& row : CellsInventory) {
        for (const auto& cell : row) {
            target.draw(cell);
        }
    }

    // Отображение текста
    target.draw(m_Text);

    // Отображение предметов
    for (const auto& row : InventoryArray) {
        for (const auto& item : row) {
            if (item) {
                item->render(target);
            }
        }
    }
}