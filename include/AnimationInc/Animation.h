#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(const sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

    void update(int row, int totalImages, float deltaTime, bool isFaceRight);
    const sf::IntRect& getUvRect() const;

private:
    sf::Vector2u m_imageCount;     // عدد الإطارات (أعمدة، صفوف)
    sf::Vector2u m_currentImage;   // الإطار الحالي (x: العمود، y: الصف)

    float m_totalTime;             // الوقت التراكمي بين الإطارات
    float m_switchTime;            // الوقت بين كل إطار
    int m_totalImages;             // عدد الإطارات الفعلي للحركة الحالية
    int m_displayed;               // كم إطار تم عرضه حتى الآن

    sf::IntRect m_uvRect;          // المنطقة الحالية من الـ texture
};
