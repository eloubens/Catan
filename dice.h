#ifndef DICE_H
#define DICE_h

enum class DiceType {
    FAIR,
    LOADED
};


class Dice final {
    DiceType type = DiceType::LOADED;

    int rollLoaded();
    int rollFair();
 public:
    // no ctor needed
    int roll();
    void updateDiceTYpe(DiceType diceType);
};

#endif
