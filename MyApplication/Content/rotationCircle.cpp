#include "rotationCircle.hpp"

RotarionCircle::RotarionCircle(BlocksGenData gendata) {
    this->bgd = gendata;
    this->i = 0;
    this->fastRm = false;
}

RotarionCircle::~RotarionCircle() {
    this->phantoms.clear();
}

void RotarionCircle::update(const float& delta_time) {
    // push on front 
    this->phantoms.push_front(this->shape);
    // itteration on massive and change Alpha channel
    for (auto& it : this->phantoms) {
        sf::Color color = it.getFillColor();
        color.a = color.a * sin((255 / bgd.countPhantomBlocks) * 180 * M_PI);
        it.setFillColor(color);

    }
    // move on XY >> pos
    this->bgd.pos.x += 1.0f * delta_time;
    this->bgd.pos.y += 1.0f * delta_time;

    // rotarion
    this->shape.setPosition(sf::Vector2f(
        this->bgd.offset.x + cos(bgd.pos.x * bgd.frequency) * this->bgd.amplifire,
        this->bgd.offset.y + sin(bgd.pos.y * bgd.frequency) * this->bgd.amplifire));


    // if counter owersided that limit
    // remove last element
    if (this->phantoms.size() != 0 && this->phantoms.size() > 0)
        if (this->phantoms.size() == bgd.countPhantomBlocks)
            this->phantoms.pop_back();
}

void RotarionCircle::setShape(sf::CircleShape shape) {
    this->shape = shape;
}

void RotarionCircle::render(sf::RenderTarget& target) {
    for (auto it : this->phantoms)
        target.draw(it);
    target.draw(this->shape);
}