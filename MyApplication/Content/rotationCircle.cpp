#include "rotationCircle.hpp"

RotarionCircle::RotarionCircle(BlocksGenData gendata)
{
    this->bgd = gendata;
    this->i = 0;
    this->fastRm = false;
    if (bgd.offsetAngle == 0)
        bgd.offsetAngle = 0;
    else if (bgd.offsetAngle == 1)
        bgd.offsetAngle = M_PI / (3.f / 2.f);
    else if (bgd.offsetAngle == 2)
        bgd.offsetAngle = M_PI * (4.f / 3.f);
    else {
    }
}

RotarionCircle::~RotarionCircle()
{
    this->phantoms.clear();
}

void RotarionCircle::update(const float& delta_time)
{

    // push on front
    this->phantoms.push_back(this->shape);
    // itteration on massive and change Alpha channel
    // alpha channel depends on index of element and count of elements
    // using logarithm for alpha
    for (int i = 0; i < this->phantoms.size(); i++) {
        this->phantoms[i].setFillColor(sf::Color(
            this->phantoms[i].getFillColor().r,
            this->phantoms[i].getFillColor().g,
            this->phantoms[i].getFillColor().b,
            // 255 * sin(((i * M_PI_2) / this->phantoms.size()) + (M_PI * 3 / 2)) + this->phantoms.size()));
            255 * (log(this->phantoms.size() - i) / -log(this->phantoms.size())) + 255));
    }
    // use same loop for size
    for (int i = 0; i < this->phantoms.size(); i++)
        this->phantoms[i].setRadius(20 * sin(i * M_PI_2 / this->phantoms.size()));

    // move on XY >> pos
    this->bgd.pos.x += 0.005;
    this->bgd.pos.y += 0.005;

    // rotarion
    this->shape.setPosition(sf::Vector2f(
        this->bgd.offset.x + cos(bgd.pos.x * bgd.frequency + bgd.offsetAngle) * this->bgd.amplifire,
        this->bgd.offset.y + sin(bgd.pos.y * bgd.frequency + bgd.offsetAngle) * this->bgd.amplifire));

    // check for fast remove
    if (this->phantoms.size() > this->bgd.countPhantomBlocks) {
        this->phantoms.erase(this->phantoms.begin());
    }
}

void RotarionCircle::setShape(sf::CircleShape shape)
{
    this->shape = shape;
}

void RotarionCircle::render(sf::RenderTarget& target)
{
    for (auto it : this->phantoms)
        target.draw(it);
    target.draw(this->shape);
}