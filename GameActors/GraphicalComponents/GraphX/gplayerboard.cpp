#include "gplayerboard.hpp"
#include <iostream>
#include <QMouseEvent>
#include <cstdlib>
#include <ctime>
#include "graphxvue.hpp"
#include "gtile.hpp"

GPlayerBoard::GPlayerBoard(NotifiableInterface* tar, QWidget *parent,int size) : PlayerBoard(tar), QWidget{parent}, max_size(size) {
    construct();
}

GPlayerBoard::GPlayerBoard(NotifiableInterface *tar, const std::string& def, QWidget *parent, int size) : PlayerBoard(tar), QWidget{parent}, max_size(size){
    reinterpretString(def);
    construct();
}

void GPlayerBoard::construct(){
    tiles.resize(max_size); // On init le tableau pour acceder a tiles[1] par exemple

    m_layout = new QVBoxLayout(this);

    setLayout(m_layout);  // Applique le layout (mais ne sera pas utilisé pour les tuiles, c'était pour le score)
    initHexTiles();
    setGeometry(0, 0, 33*tileWidth,42*tileHeight);  // Fixe la taille du widget

    m_manager = GraphXVue::instance();
    m_manager->addPlayerBoard(this);

    connect(m_manager, &GraphXVue::rightClickOnBoard, this, [this](GPlayerBoard* board, const QPointF& pos){
        if (board == this) {
            // Traiter clic droit ici avec pos
            qDebug() << "Clic droit sur ce GPlayerBoard à " << pos;
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
            tileLabel->setFixedSize(tileWidth*1.03, tileHeight*1.16); // il faut zoom car ce sont des carrés les valeurs sont choisie pour un bon rendu
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
            if(getTile(hex.getQ(),hex.getR()) != nullptr)posed.push_back(getTile(hex.getQ(),hex.getR())); // stockage des tuiles posée
            if(GameTile* tile = getTile(hex.getQ(),hex.getR())){
                int rot = tile->getRotation();
                if(rot == 1 || rot == 2 || rot == 4 || rot == 5)
                {
                    int newW = tileWidth * 1.38; // 1.03*1.41 car une tuile c'est 116px ansi la diag = sqrt(2)*116, // on a du ajuster la valeurs car c'est pas exactement le bon calculs
                    int newH = tileHeight * 1.58; // enfin on veut retrouver 116 donc sqrt(2)*116* x = 116, on obtient x = 1.41 // ''
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

                int x = (off.getCol()) * xOffset;    // on doit remettre à sa position la tuile pour prevenir le cas ou on annulerai un action, en effet sinon
                int y = (off.getRow()) * tileHeight; // une tuile qui aurait été tourné puis enlevé produirait un déclage sur le highlight
                if (off.getCol() % 2 == 1) {
                    y += yOffset;
                }
                tiles[off.getCol()][off.getRow()]->move(x,y);
            }
        }
    }

}

void GPlayerBoard::scoreScree(std::vector<double>& ti_scores,std::vector<double>& to_scores,int nb_nature_tokens,std::vector<unsigned short int> m_bonuses){
    QLabel* score = new QLabel(this);
    QPixmap scoreimg(":/Assets/Assets/Scoring/full-scoring-table.jpg");
    QPainter painter(&scoreimg);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QColorConstants::Svg::brown); // Couleur du texte
    painter.setFont(QFont("Arial", 30, QFont::Bold)); // Police, taille, style
    QPoint position(95, 45);
    painter.drawText(position,QString::number(nb_nature_tokens));
    int i = 1;
    double to_score_L[5]{to_scores[0],to_scores[1],to_scores[3],to_scores[2],to_scores[4]}; // inversion en code par rapport aux visuels sur le site
    double ti_score_L[5]{ti_scores[3],ti_scores[0],ti_scores[4],ti_scores[1],ti_scores[2]};
    for(auto &e : to_score_L){
        int pos = (i++)*60;
        QPoint position(95, pos+45);
        painter.drawText(position,QString::number(e));
    }
    double totto = to_score_L[0]+to_score_L[1]+to_score_L[2]+to_score_L[3]+to_score_L[4]+nb_nature_tokens;
    painter.drawText(QPoint(95, 405),QString::number(totto));

    i = 1;
    for(auto &e : ti_score_L){
        int pos = (i++)*60;
        QPoint position(245, pos+45);
        painter.drawText(position,QString::number(e));
    }
    double titti = ti_score_L[0]+ti_score_L[1]+ti_score_L[2]+ti_score_L[3]+ti_score_L[4];
    painter.drawText(QPoint(245, 405),QString::number(titti));

    i=1;
    for(auto &e : m_bonuses){
        int pos = (i++)*60;
        QPoint position(310, pos+45);
        painter.drawText(position,QString::number(e));
    }

    double bobbo = static_cast<double>(m_bonuses[0]+m_bonuses[1]+m_bonuses[2]+m_bonuses[3]+m_bonuses[4]);
    painter.drawText(QPoint(310, 405),QString::number(bobbo));

    painter.setPen(QColorConstants::Svg::green); // Couleur du texte
    painter.drawText(QPoint(95, 470),QString::number(bobbo+totto+titti));

    score->setPixmap(scoreimg);
    m_layout->addWidget(score);


    //this->adjustSize();

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
    return QSize(33*tileWidth,42*tileHeight);
}










