#include "LSystem.hpp"

bool LSystem::compareByGreen(const sf::RectangleShape &a,
                             const sf::RectangleShape &b) {
  sf::Color colorA = a.getFillColor();
  sf::Color colorB = b.getFillColor();
  return colorA.g < colorB.g; // Меньший зелёный оттенок будет впереди
}

LSystem::LSystem() {
  this->line.resize(20, sf::RectangleShape(sf::Vector2f(1, 1)));
}

LSystem::~LSystem() {
  // очистка стека
  while (!this->stack.empty())
    this->stack.pop();

  // очистка вектора
  this->line.clear();

  // очистка правил
  this->rules.clear();

  // очистка строки
  this->sentence.clear();
}

void LSystem::generate() {
  if (!this->line.empty())
    for (auto it : line)
      it = sf::RectangleShape({1, 1});

  this->data.pos = sf::Vector2f(0, 0);
  this->data.angle = 15;
  this->data.currentAngle = 0;
  this->data.width = 15;
  this->data.length = 25;
  this->data.half_length = -this->data.width / 2;
  this->data.steps = 10;
  this->data.alpha = 255;
  this->data.chanceSkip = 50;
  this->data.seed = 0;
  this->axiom = "qqqqqs";
  this->sentence = axiom;
  for (int i = 0; i < this->data.steps; i++) {
    this->generateSentence();
  }
  this->applyRules();
}

void LSystem::generateSentence() {
  std::string nextSentence;
  for (int i = 0; i < this->sentence.length(); i++) {
    char current = this->sentence[i];
    if (this->rules.find(current) != this->rules.end()) {
      nextSentence += this->rules[current];
    } else {
      nextSentence += current;
    }
  }
  this->sentence = nextSentence;
}

sf::Vector2f LSystem::rotate(sf::Vector2f v, float angle) {
  float rad = angle * M_PI / 180;
  float x = v.x * cos(rad) - v.y * sin(rad);
  float y = v.x * sin(rad) + v.y * cos(rad);
  return sf::Vector2f(x, y);
}

void LSystem::applyRules() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 100);
  std::uniform_int_distribution<> dis_angle(0, 35);
  std::uniform_int_distribution<> dis_color(80, 255);

  sf::RectangleShape bufferShape;
  this->debug_dots =
      sf::VertexArray(sf::PrimitiveType::Points, this->sentence.size());
  sf::Vertex p;
  data.nextPos = {0, 0};

  for (char current : this->sentence) {
    // Перебираем каждый символ текущего предложения
    // (строки команды L-системы)
    // Генерируем случайное число для вероятностных операций
    int chance = dis(gen);
    switch (current) { // Обрабатываем символ в зависимости от его значения
    case 'd':
    case 'q': // Дерево — элемент ствола (лог)
      if (chance < this->data.chanceSkip)
        break; // Пропускаем текущий элемент с заданной вероятностью

      // Задаём размеры и параметры формы, представляющей элемент ствола
      bufferShape.setSize(sf::Vector2f(this->data.width, this->data.length));
      // Устанавливаем точку вращения в центр
      bufferShape.setOrigin(sf::Vector2f(data.width / 2, data.length));
      bufferShape.setPosition(
          data.nextPos + data.offsetPos); // Смещаем позицию с учётом оффсета
      bufferShape.setRotation(
          sf::degrees(data.currentAngle +
                      dis_angle(gen) * 0.05)); // Устанавливаем угол вращения
      bufferShape.setFillColor(sf::Color(
          80, 35, 25, this->data.alpha)); // Устанавливаем цвет (цвет дерева)

      ////DEBUG

      p.position = sf::Vector2f(data.nextPos + data.offsetPos);
      p.color = sf::Color::White;

      debug_dots.append(p);

      // Рассчитываем следующую позицию для элементов ствола
      data.nextPos = this->data.pos +
                     this->rotate(sf::Vector2f(0, -this->data.length),
                                  data.currentAngle + dis_angle(gen) * 0.1);
      this->data.pos = data.nextPos; // Обновляем текущую позицию

      this->line.push_back(
          bufferShape); // Добавляем форму в линию (список элементов дерева)
      break;

    case 's': { // Дерево — элемент листвы
      // Рассчитываем следующую позицию для элемента листвы

      // Настраиваем параметры формы для листвы
      bufferShape.setSize(sf::Vector2f(
          this->data.length + dis_angle(gen) % 3 + 1,
          this->data.width * 2.25)); // Генерируем случайный размер листа
      bufferShape.setOrigin(sf::Vector2f(
          data.width / 2, data.length)); // Устанавливаем точку вращения
      bufferShape.setPosition(this->data.pos +
                              data.offsetPos); // Смещаем позицию с учётом

      bufferShape.setRotation(
          sf::degrees(this->data.currentAngle +
                      dis_angle(gen))); // Устанавливаем угол вращения

      // Генерируем случайный оттенок зелёного цвета для листвы
      int randcolor = dis_color(gen);
      bufferShape.setFillColor(sf::Color(0, randcolor, 0));

      this->line.push_back(bufferShape); // Добавляем форму в линию
      data.nextPos =
          this->data.pos +
          this->rotate(sf::Vector2f(0, -this->data.width),
                       this->data.currentAngle + dis_angle(gen) * 0.01);
      this->data.pos = data.nextPos; // Обновляем текущую позицию
      break;
    }
    case '+': // Вращение направо
      this->data.currentAngle += 25 + dis_angle(gen);
      break;
    case '-': // Вращение налево
      this->data.currentAngle -= 25 + dis_angle(gen);
      break;
    case '[': // Сохраняем текущее состояние в стек
      if (data.length > 2.f)
        this->data.length *= 0.80; // Уменьшаем длину элементов
      if (data.width > 1.f)
        this->data.width *= 0.70;
      this->data.alpha *= 0.95; // Уменьшаем прозрачность
      // this->data.half_length = -this->data.width / 2;
      this->stack.push(this->data); // Сохраняем состояние
      break;
    case ']': // Восстанавливаем состояние из стека
      this->data = this->stack.top(); // Восстанавливаем данные
      this->stack.pop(); // Удаляем верхний элемент стека
      break;
    default:
      break;
    };
  }

  std::sort(this->line.begin(), this->line.end(), this->compareByGreen);
}

void LSystem::update(const float &delta_time) {
  this->line[1].rotate(sf::degrees(delta_time));
}

void LSystem::render(sf::RenderTarget &target) { // render shapes
  for (auto &shape : this->line)
    target.draw(shape);

  // target.draw(debug_dots);
}