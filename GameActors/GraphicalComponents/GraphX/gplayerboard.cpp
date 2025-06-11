#include "gplayerboard.hpp"
#include <iostream>
#include <QMouseEvent>
#include <cstdlib>
#include <ctime>
#include "graphxvue.hpp"
#include "gtile.hpp"

GPlayerBoard::GPlayerBoard(NotifiableInterface* tar, QWidget *parent,int size) : PlayerBoard(tar), QWidget{parent}, max_size(size) {

    // FOR DEBUG ONLY
    Biome deb_biomes[6] = {River,Mountain,Prairie,Forest,Wetland,Wetland};
    //GameTile* debugT = new GameTile(1,deb_biomes);
    HexCell deb_cell(0,0);
    HexCell::Offset* deb_off = new HexCell::Offset(axialToOffset(deb_cell));

    unsigned int deb_xs = (deb_off->getCol());
    unsigned int* deb_x = & deb_xs;

    unsigned int deb_ys = (deb_off->getRow());
    unsigned int* deb_y = & deb_ys;
    //addTile(*debugT,deb_x,deb_y);
    // FOR DEBUG ONLY

    tiles.resize(max_size); // On init le tableau pour acceder a tiles[1] par exemple

    setAutoFillBackground(true); // Permet de remplir l'arrière-plan

    m_layout = new QVBoxLayout(this);  // Optionnel : peut être utilisé si tu veux gérer des widgets enfants
    setLayout(m_layout);  // Applique le layout (mais ne sera pas utilisé pour les tuiles)

    initHexTiles();
    setGeometry(0, 0, sizeHint().width(), sizeHint().height());  // Fixe la taille du widget

    m_manager = GraphXVue::instance();
    m_manager->addPlayerBoard(this);

    connect(m_manager, &GraphXVue::rightClickOnBoard, this, [this](GPlayerBoard* board, const QPointF& pos){
        if (board == this) {
            // Traiter clic droit ici avec pos
            qDebug() << "Clic droit sur ce GPlayerBoard à " << pos;
            // Ton code ici
        }
    });
}

GPlayerBoard::GPlayerBoard(NotifiableInterface *tar, const std::string& def, QWidget *parent, int size) : PlayerBoard(tar), QWidget{parent}, max_size(size){
    reinterpretString(def);
    // FOR DEBUG ONLY
    Biome deb_biomes[6] = {River,Mountain,Prairie,Forest,Wetland,Wetland};
    //GameTile* debugT = new GameTile(1,deb_biomes);
    HexCell deb_cell(0,0);
    HexCell::Offset* deb_off = new HexCell::Offset(axialToOffset(deb_cell));

    unsigned int deb_xs = (deb_off->getCol());
    unsigned int* deb_x = & deb_xs;

    unsigned int deb_ys = (deb_off->getRow());
    unsigned int* deb_y = & deb_ys;
    //addTile(*debugT,deb_x,deb_y);
    // FOR DEBUG ONLY

    setAutoFillBackground(true); // Permet de remplir l'arrière-plan

    m_layout = new QVBoxLayout(this);  // Optionnel : peut être utilisé si tu veux gérer des widgets enfants
    setLayout(m_layout);  // Applique le layout (mais ne sera pas utilisé pour les tuiles)

    initHexTiles();
    setGeometry(0, 0, sizeHint().width(), sizeHint().height());  // Fixe la taille du widget

    m_manager = GraphXVue::instance();
    m_manager->addPlayerBoard(this);

    connect(m_manager, &GraphXVue::rightClickOnBoard, this, [this](GPlayerBoard* board, const QPointF& pos){
        if (board == this) {
            // Traiter clic droit ici avec pos
            qDebug() << "Clic droit sur ce GPlayerBoard à " << pos;
            // Ton code ici
        }
    });
}



void GPlayerBoard::initHexTiles(){
    for (int col = 0; col < max_size; ++col) {
        for (int row = 0; row < max_size; ++row) {
            QLabel* tileLabel = new QLabel(this);  // Création d'un QLabel pour chaque tuile
            HexCell::Offset off(col, row);
            HexCell hex (PlayerBoard::offsetToAxial(off));
            QPixmap pixmap = PixmapFactory::createTile(getTile(hex.getQ(),hex.getR()));
            if (pixmap.isNull()) {std::cerr << "Erreur : l'image n'a pas pu être chargée !" << std::endl;}
            tileLabel->setPixmap(pixmap);
            tileLabel->setFixedSize(tileWidth*1.03, tileHeight*1.16); // il faut zoom car c'est des carrés les valeurs sont choisie pour un bon rendu
            tileLabel->setScaledContents(true);  // Pour que l'image remplisse le QLabel

            // Calcul des positions x et y pour chaque tuile en utilisant un décalage
            int x = (col) * xOffset;    //Easter egg
            int y = (row) * tileHeight;

            // Décalage pour les lignes impaires
            if (col % 2 == 1) {
                y += yOffset;  // Décalage vertical pour les colonnes impaires
            }

            if(getTile(hex.getQ(),hex.getR()) != nullptr)posed.push_back(getTile(hex.getQ(),hex.getR())); // stockage des tuiles posées

            tileLabel->move(x, y);  // Déplacement relatif au widget
            tileLabel->setAttribute(Qt::WA_TransparentForMouseEvents); // permet de skip les cliques souris
            tiles[col].push_back(tileLabel);
        }
    }

}

void GPlayerBoard::updateHexTiles(){
    posed.clear();
    for (int col = 0; col < max_size; ++col) {
        for (int row = 0; row < max_size; ++row) {
            HexCell::Offset off(col,row);
            HexCell hex (PlayerBoard::offsetToAxial(off));
            tiles[col][row]->setPixmap(PixmapFactory::createTile(getTile(hex.getQ(),hex.getR())));
            if(getTile(hex.getQ(),hex.getR()) != nullptr)posed.push_back(getTile(hex.getQ(),hex.getR())); // stockage des tuiles posées
            if(GameTile* tile = getTile(hex.getQ(),hex.getR())){
                int rot = tile->getRotation();
                std::cout<<"HELLO";
                if(rot == 1 || rot == 2 || rot == 4 || rot == 5)
                {
                    int newW = tileWidth * 1.38; // 1.03*1.41 car une tuile c'est 116px ansi la diag = sqrt(2)*116,
                    int newH = tileHeight * 1.58; // enfin on veut retrouver 116 donc sqrt(2)*116* x = 116, on obtient x = 1.41
                    tiles[col][row]->setFixedSize(newW, newH);

                    int x = col * xOffset;
                    int y = row * tileHeight;
                    if (col % 2 == 1) y += yOffset;

                    // Décalage pour recentrer localement la tuile
                    int dx = (newW - tileWidth * 1.03) / 2;
                    int dy = (newH - tileHeight * 1.16) / 2;
                    tiles[col][row]->move(x - dx, y - dy);
                }

            }
         }
    }
    setHighlight();
}

void GPlayerBoard::setHighlight(){
    for(auto &p : posed){
        for (auto &d : HexCell::directions){
            HexCell neiH((*p+d).getQ(),(*p+d).getR());
            GameTile* neiG = getTile(neiH.getQ(),neiH.getR());
            if ( neiG == nullptr){
                HexCell::Offset off = HexCell::axialToOffset(neiH,max_size);
                tiles[off.getCol()][off.getRow()]->setPixmap(QPixmap(":/Tile/Assets/Tiles/potentialPlacement.png"));
                tiles[off.getCol()][off.getRow()]->setFixedSize(tileWidth*1.03, tileHeight*1.19); // il faut zoom car c'est des carrés
                tiles[off.getCol()][off.getRow()]->setScaledContents(true);  // Pour que l'image remplisse le QLabel
            }
        }
    }

}

void GPlayerBoard::scoreScree(){
    for (int col = 0; col < max_size; ++col) {
        for (int row = 0; row < max_size; ++row) {
            tiles[col][row]->clear();
        }
    }
    QLabel* score = new QLabel(this);
    score->setPixmap(QPixmap(":/Assets/Assets/Scoring/full-scoring-table.jpg"));
    m_layout->addWidget(score);
}


void GPlayerBoard::addGxTile(int col,int row){
    QLabel* tileLabel = new QLabel(this);  // Création d'un QLabel pour chaque tuile
    QPixmap pixmap(":/Assets/Assets/Tiles/desert.png");  // Charge une image de tuile
    if (pixmap.isNull()) {
        std::cerr << "Erreur : l'image n'a pas pu être chargée !" << std::endl;
    }
    tileLabel->setPixmap(pixmap);
    tileLabel->setFixedSize(tileWidth, tileHeight);
    tileLabel->setScaledContents(true);  // Pour que l'image remplisse le QLabel

    // Calcul des positions x et y pour chaque tuile en utilisant un décalage
    int x = (col) * xOffset;
    int y = (row) * tileHeight;

    // Décalage pour les lignes impaires
    if (col % 2 == 1) {
        y += yOffset;  // Décalage vertical pour les colonnes impaires
    }

    tileLabel->move(x, y);  // Déplacement relatif au widget
}


void GPlayerBoard::show(){
    updateHexTiles();
    m_manager->show(-1);
}

QSize GPlayerBoard::sizeHint() const {
    return QSize(41*tileWidth,42*tileHeight);
}










