#ifndef GTOKENMENU_HPP
#define GTOKENMENU_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include "../../GameActors/GraphicalComponents/GraphX/gdecktile.hpp"

#include "gmenu.hpp"
//#include "../../../Gametools/Tiling/gametile.hpp"
#include "../../../Gametools/Abstract/decktile.hpp"
#include "../../player.hpp"

class GTokenMenu final : public GMenu<unsigned short int>{
    Q_OBJECT
    QGridLayout* m_main_layout = nullptr;
    QPushButton* m_btn_validate = nullptr;
    QPushButton* m_btn_clear_tokens = nullptr;
    QPushButton* m_btn_no_token = nullptr;
    QPushButton* m_btn_multichoice = nullptr;
    QLabel* m_label = nullptr;
    QLabel* m_label_token = nullptr;
    QLabel* m_label_tile = nullptr;

    QSpinBox* m_spin_tile = nullptr;
    QSpinBox* m_spin_token = nullptr;
    DeckTile* m_decktile = nullptr;
    Player* m_caller = nullptr;
    GDeckTile* gdecktile = nullptr;

private slots:
    void onTileClicked(int index);

public:
    GTokenMenu(NotifiableInterface* tar, DeckTile* decktile, Player* caller);
    ~GTokenMenu();
    void selectTile();
    void clearTokens();
    void chooseMultiple();
    void pushResults();
    void show();
};

#endif // GTOKENMENU_HPP
