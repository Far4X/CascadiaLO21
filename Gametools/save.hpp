#include "../Scoring/scoringcards/scoringcarda.hpp"
#include <vector>

void computeScore(Wildlife& type) {
	switch (type) {
	case Bear:
		/* "bears" est une liste de listes contenant tous les ours du jeu. Les listes a l'interieur contiennent
		* les ours adjacents. Elles sont construites au fil de la partie. Avant le placement de
		* chaque ours, on verifie s'il est adjacent a un ours (en verifiant ses voisins). Si c'est le cas,
		* on le rajoute dans la sous-liste contenant l'ours adjacent deja place. Sinon, on le place dans une
		* nouvelle sous-liste de la liste "bears".
		* bears : std::vector<std::vector<Wildlife>>
		* n est un entier qui definit la taille du groupe d'ours rapportant des points
		* Cette methode permet de couvrir les 3 types de marquage A, B et C
		* Envisager un attribut "isScoring" pour aider dans l'affichage final du tableau montrant les WildLife Token comptabilises dans le score
		*/
		for (int i = 0; i < bears.size(); i++) {
			if (bears[i].size() == n) {
				points += 4;
			}
		}
		break;
	case Salmon:
		break;
	case Hawk:
		break;
	case Elk:
		break;
	case Fox:
		break;
	default:
		throw "impossible";
	}
}
