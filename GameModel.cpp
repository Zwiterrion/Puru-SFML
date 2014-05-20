#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "GameModel.h"
#include "GameView.h"
#include "Const.h"

using namespace std;

/************************************************************
 * Nom: GameModel                                           *
 ************************************************************
 * Type: Constructeur                                       *
 ************************************************************
 * Rôle: Initialise les pointeurs contenus et créé les cases*
 *      contenues matrice et toutes les cases avec les      *
 *      différents objets. Initialise le tableau de bombes, *
 *      le tableau de bonusCase également et place le joueur*
 *      dans la matrice.                                    *
 ************************************************************/
GameModel::GameModel()
{
    m_n = new Lvl();                        // Appel du constructeur de Level
    m_s = new Score();                      // Appel du constructeur de Score
    fin = true;

    m_b = new Bomb*[30];
    for(int i=0; i<m_n->getNb(); i++)
    {
        m_b[i] = new Bomb();
    }

    /*Allocation dynamique des pointeurs qui vont contenir des cases */
    matrice = new Case** [18];
    for (int i=0; i < 18 ; i++)
        matrice[i] = new Case*[18];

    /* Allocation des cases */
    for(int i=0; i<18; i++){
        for(int j=0; j<18; j++)
            matrice[i][j] = new Case();
    }

    /* Allocation dynamique des 10 bombes*/
    for (int i=0; i < m_n->getNb() ; i++){
        int x = m_b[i]->get_x();
        int y = m_b[i]->get_y();
        delete matrice[m_b[i]->get_x()][m_b[i]->get_y()];                   // Désallocation de la case pour mettre la bombe
        matrice[x][y] = m_b[i];                                             // Appel du construteur de Bomb pour remplir la case
    }


     for (int i=0; i < m_n->getBonus() ; i++){
        int x = rand()%(WIDTH_GAME);            // Affectation aléatoire d'un entier
        int y = rand()%(HEIGHT_GAME);           // Affectation aléatoire d'un entier
        delete matrice[x][y];                   // Désallocation de la case pour mettre le bonus
        matrice[x][y] = new BonusCase();             // Appel du construteur de Bonus pour remplir la case
    }

    m_p = new Player();                     // Appel du constructeur du player
   // delete matrice[m_p->get_x()][m_p->get_y()];
    
    // Pour le début du jeu.
    goToView = 0;
}
/**************************************************************
 * Nom: ~GameModel                                            *
 **************************************************************
 * Type: Destructeur                                          *
 **************************************************************
 * Rôle: Permet de désallouer tous les pointeurs contenus dans*
 *     contenus dans la matrice, et de désallouer les cases   *
 *      de la matrice. Désalloue également le joueur.         *
 **************************************************************/
GameModel::~GameModel()
{
    /* Allocation dynamique des cases */
    for (int i=0; i < 18; i++){
        for(int j=0; j < 18; j++)
            delete matrice[i][j];
        delete[] matrice[i];
    }
    delete[] matrice;                           // Désallocation de la matrice

    delete [] m_b;

    /* Désallocation du score */
    if(m_s != NULL)
        delete m_s;
    if(m_p != NULL)
        delete m_p;
    if(m_n != NULL)
        delete m_n;
}
/*************************************************************
 * Nom: direction                                            *
 *************************************************************
 * Type: void                                                *
 *************************************************************
 * Paramètres: answer de type string                         *
 *************************************************************
 * Rôle:  Fonction qui appelle la fonction move avec des     *
 *       paramètres différents qui changent en fonction de la*
 *       direction entrée par l'utilisateur.                 *
 *************************************************************/
void GameModel::direction(string answer){
    if(answer=="N")
        move(0,-1);
    if(answer=="S")
        move(0, 1);
    if(answer=="E")
        move(1,0);
    if(answer=="O")
        move(-1, 0);
    if(answer=="SE")
        move(1, 1);
    if(answer=="SO")
        move(-1, 1);
    if(answer=="NO")
        move(-1, -1);
    if(answer=="NE")
        move(1,-1);
}
/************************************************************
 * Nom: set_answer_move                                     *
 ************************************************************
 * Type: void  (setter)                                     *
 ************************************************************
 * @param string                                            *
 ************************************************************
 * Rôle: Affecte une chaine de caractère                    *
 ************************************************************/
void GameModel::set_answer_move(std::string a){
    m_answer_move=a;
}
/************************************************************
 * Nom: get_answer_move                                     *
 ************************************************************
 * Type: string (getter)                                    *
 ************************************************************
 * Rôle: Retourne la valeur de la varaible m_answer_move    *
 ************************************************************/
std::string GameModel::get_answer_move(){
    return m_answer_move;
}

void GameModel::tabScore()
{
    setGoToView(4);
}
/**************************************************************
 * Nom: initLevel                                             *
 **************************************************************
 * Type: void                                                 *
 **************************************************************
 * Rôle:  Fonction appelée lorsque l'on commence un niveau    *
 *       Elle appelle les fonctionsdes classes Score, Lvl et  *
 *       Player et affecte des valeurs de début de parties au *
 *       différents attributs (bonus à 0, level à 1).         *
 **************************************************************/
void GameModel::initLevel()
{
    m_n->setLevel(1);
    m_n->initBonus();
    m_s->setCible(10);
    m_s->setScoreTotal(0);
    m_p->setVie(3);
}
/************************************************************
 * Nom: perteVie                                            *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle:  Fonction appelée lors de la perte d'une vie. Elle *
 *       décrémente la vie et gère le cas où le joueur veut *
 *       continuer et celui ou celui-ci veut s'arrêter      *
 ************************************************************/
void GameModel::perteVie()
{
    m_p->setVie(m_p->getVie() - 1); // On décremente la vie
    m_s->setDeplacement(0); // On remet le score déplacement à O

    if(m_p->getVie() > 0 && m_n->getTemps() <= 0) {
        setEcranJeu(false);
        m_n->initBonus();
        setGoToView(6);
    }
    else if(m_p->getVie() > 0){
       setEcranJeu(false);
        m_n->initBonus();
        setGoToView(2);
    }
    else
        setGoToView(4); // Si plus de vie on passe à l'écran 4
}
/************************************************************
 * Nom: move                                                *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Paramètres: variable pos_x,pos_y de type integer         *
 ************************************************************
 * Rôle:  Focntion principale du déplacement. Elle permet de*
 *       déplacer le joueur, vérifier que le joueur ne      *
 *       rencontre pas une bombe ou ne sorte de la matrice  *
 ************************************************************/
void GameModel::move(int pos_x, int pos_y)
{
    int x = m_p->get_x();
    int y = m_p->get_y();
    if(x != -1 && y != -1) {
        delete matrice[m_p->get_y()][m_p->get_x()];
        matrice[m_p->get_y()][m_p->get_x()] = new Croix();
        m_p->deplacement(pos_x,pos_y);
    }
    nb_cases = deplacement();
    
    if(x != -1 && y != -1) {
        string obj = matrice[m_p->get_y()][m_p->get_x()]->getObj();  // Test si la case suivante, la premiere, est une bombe
        if(obj == "@@@" || obj == " "){
            nb_cases = 0;
        }
    }
    if(nb_cases == 0)                                          // Si c'est une bombe on recule
    {
        m_p->set_pos(x, y);
    }
    else if(nb_cases != -1 ){
        
        m_s->setDeplacement(m_s->getDeplacement()+nb_cases);    // Incrémentation du nombre de déplacement
        m_s->setScoreTotal(m_s->getScoreTotal()+nb_cases*10);   // Incrémentation du score total
        
        i = 1;                                                  // Initialisation de i à 1
        
        while(i < nb_cases && deplacement() != -1)
        {
            delete matrice[m_p->get_y()][m_p->get_x()];         // On libére la case du joueur
            matrice[m_p->get_y()][m_p->get_x()] = new Croix();
            m_p->deplacement(pos_x, pos_y);
            i++;                                                // On incrémente i
        }
        if(deplacement() != -1){                                // Si le joueur a atteint le nb_case alors on supprime et on met une croix
            delete matrice[m_p->get_y()][m_p->get_x()];
            matrice[m_p->get_y()][m_p->get_x()] = new Croix();
            if(!plusDeTemps())
                objectifAtteint();
        }
        else
        {
            m_s->setScoreTotal(m_s->getScoreTotal()-nb_cases*10);
            perteVie();
        }
    }
    
    else
    {
        perteVie();
    }
    
}
/**************************************************************
 * Nom: objectifAtteint                                       *
 **************************************************************
 * Type: void                                                 *
 **************************************************************
 * Rôle:  Fonction qui vérifie si l'objectif n'est pas atteint*
 * par le joueur.                                             *
 **************************************************************/
void GameModel::objectifAtteint()
{
    if(m_s->getDeplacement() >= m_s->getCible())
            changeLevel();
}
/************************************************************
 * Nom: changeLevel                                         *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle:  Fonction qui permet de changer de niveau, de      *
 *       demander si l'on veut continuer. Elle permet aussi *
 *       d'augmenter la valeur de l'objectif et de quitter  *
 *       si voulu.                                          *
 ************************************************************/
void GameModel::changeLevel()
{
    if(!plusDeTemps()){
        m_n->setLevel(m_n->getLevel() + 1); // Incrémentation du level grâce à la surcharge
        m_s->setCible(m_s->getCible() + 5);
        m_n->initBonus();
        
        if(m_n->getLevel()%2 == 0){
            m_n->setBomb(m_n->getNb() +1);
            m_n->setBonus(m_n->getBonus() +1);
        }
        m_s->setDeplacement(0); // On remet le score déplacement à O
        setEcranJeu(false);
        setGoToView(3);
    }

}
/************************************************************
 * Nom: check_answer                                        *
 ************************************************************
 * Type: bool                                               *
 ************************************************************
 * @param string                                            *
 ************************************************************
 * Rôle:  Retourne vrai ou faux en fonction de la saisie de *
 *     l'utilisateur au clavier lors de la demande de       *
 *     la direction voulue.                                 *
 ************************************************************/
bool GameModel::check_answer(std::string a){
    
    if ((a == "N" || a == "NE" || a == "NO") && m_p->get_y() == 0){
        return false;
    }
    else if ((a == "S" || a == "SO" || a == "SE") && m_p->get_y() == HEIGHT_GAME-1){
        return false;
    }
    else if ((a == "O" || a == "NO" || a == "SO") && m_p->get_x() == 0){
        return false;
    }
    else if ((a == "E" || a == "NE" || a == "SE") && m_p->get_x() == WIDTH_GAME-1){
        return false;
    }
    else
        return true;
}
/************************************************************
 * Nom: deplacement                                         *
 ************************************************************
 * Type: int                                                *
 ************************************************************
 * Rôle:  Renvoie la valeur de la case où va aller le joueur*
 *      au prochain déplacement. Renvoie un integer positif *
 *      et négatif si la case suivante est occupée par une  *
 *      bombe où n'est pas contenue dans la matrice.        *
 ************************************************************/
int GameModel::deplacement(){

    string obj;
    if(m_p->get_x() >= 0 && m_p->get_x() < WIDTH_GAME && m_p->get_y() >= 0 && m_p->get_y() < HEIGHT_GAME){
         obj = matrice[m_p->get_y()][m_p->get_x()]->getObj();
    }
    else{
        return -1;
    }
    if(obj != " " && obj != "@@@" && obj != m_p->getObj() && obj != "-1-" && obj != "-2-" &&
       obj != "-3-" && obj != "-4-" && obj != "-5-" && obj != "-6-")
    {
        istringstream iss(obj);
        int nombre_cases;
        iss >> nombre_cases;
        return nombre_cases;
    }
    else if(obj == "-1-" || obj == "-2-" || obj == "-3-" ||
            obj == "-4-" || obj == "-5-" || obj == "-6-"){
        randomBonus();
        if(obj == "-1-")
            return 1;
        else if(obj == "-2-")
            return 2;
        else if(obj == "-3-")
            return 3;
        else if(obj == "-4-")
            return 4;
        else if(obj == "-5-")
            return 5;
        else
            return 6;
    }
    else{
        std::cout << "deplacement impossible" << std::endl;
        return -1;
    }
}
/************************************************************
 * Nom: randomBonus                                         *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle:  Fonction qui produit un chiffre aléatoire entre   *
 *      1 et 3, et affecte un type de bonus en fonction du  *
 *      chiffre tiré.                                       *
 ************************************************************/
void GameModel::randomBonus()
{
    int x = rand()%(3);

    switch(x)
    {
        case 0:
            if(m_p->getVie() < 4){
                m_n->set_bonusVie(m_n->get_b_vie() +1);
                m_p->setVie(m_p->getVie() +1);
            }
            break;
        case 1:
            m_n->set_bonusTemps(m_n->get_b_temps() +5);
            m_n->setTemps(m_n->getTemps() + m_n->get_b_temps());
            if(m_n->getTemps() > 60)
                m_n->setTemps(60);
            break;
        case 2:
            m_n->set_score_bonus(m_n->get_score_bonus() +20);
            m_s->setScoreTotal(m_s->getScoreTotal()+ 20);
            break;
    }
}
/************************************************************
 * Nom: getPlayer                                           *
 ************************************************************
 * Type: const Player&  (getter)                            *
 ************************************************************
 * Rôle:  Fonction qui retourne un pointeur sur le joueur   *
 ************************************************************/
const Player& GameModel::getPlayer() const
{
    return *m_p;
}
/************************************************************
 * Nom: getScore                                            *
 ************************************************************
 * Type: const Score&  (getter)                             *
 ************************************************************
 * Rôle:  Fonction qui retourne un pointeur sur le score    *
 ************************************************************/
const Score& GameModel::getScore() const
{
    return *m_s;
}
/************************************************************
 * Nom: getLvl                                              *
 ************************************************************
 * Type: const Lvl&  (getter)                               *
 ************************************************************
 * Rôle:  Fonction qui retourne un pointeur sur le level    *
 ************************************************************/
Lvl& GameModel::getLvl() const
{
    return *m_n;
}
/************************************************************
 * Nom: getMatrice                                          *
 ************************************************************
 * Type: Case***  (getter)                                  *
 ************************************************************
 * Rôle:  Fonction qui retourne la matrice                  *
 ************************************************************/
Case*** GameModel::getMatrice() const{

    return matrice;
}
/************************************************************
 * Nom: setMatrice                                          *
 ************************************************************
 * Type: void (setter)                                      *
 ************************************************************
 * @Param Case*** matriceBis                                *
 ************************************************************
 * Rôle:  Fonction qui retourne un pointeur sur le level    *
 ************************************************************/
void GameModel::setMatrice(Case*** matriceBis)
{
    matrice = matriceBis;
}
/************************************************************
 * Nom: genereMatrice                                       *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle:  Fonction qui génère une nouvelle matrice et       *
 *       affecte des nouvelles cases à la matrice principale*
 ************************************************************/
void GameModel::genereMatrice(){

    for (int i=0; i < 18; i++){
        for(int j=0; j < 18; j++)
            delete matrice[i][j];
    }

     for(int i=0; i<18; i++){
        for(int j=0; j<18; j++)
            matrice[i][j] = new Case();
    }

    for(int i=0; i<m_n->getNb(); i++)
    {
        m_b[i] = new Bomb();
    }

      /* Allocation dynamique des 10 bombes*/
    for (int i=0; i < m_n->getNb() ; i++){
        int x = m_b[i]->get_x();
        int y = m_b[i]->get_y();
        delete matrice[m_b[i]->get_x()][m_b[i]->get_y()];                   // Désallocation de la case pour mettre la bombe
        matrice[x][y] = m_b[i];                                             // Appel du construteur de Bomb pour remplir la case
    }

    for (int i=0; i < m_n->getBonus() ; i++){
        int x = rand()%(WIDTH_GAME);            // Affectation aléatoire d'un entier
        int y = rand()%(HEIGHT_GAME);           // Affectation aléatoire d'un entier
        delete matrice[x][y];                   // Désallocation de la case pour mettre le bonus
        matrice[x][y] = new BonusCase();             // Appel du construteur de Bonus pour remplir la case
    }

    setMatrice(matrice);
    
    m_p->set_position(rand()%WIDTH_GAME,rand()%HEIGHT_GAME);
}

void GameModel::rejouerPartie()
{
    /*if(get_answer_move() != "1"){ // On affiche les scores seulement si on a pas abandonné
        GameView::affichageScore();
    }*/
    initLevel();
    genereMatrice();

}

void GameModel::setGoToView(int t){
    goToView = t;
}
int GameModel::getGoToView(){
    return goToView;
}
void GameModel::setEcranJeu(bool e) {
    ecranJeu = e;
}
bool GameModel::getEcranJeu() const {
    return ecranJeu;
}
bool GameModel::plusDeTemps() {
    
    if(m_n->getTemps() <= 0){
        perteVie();
        return true;
    }
    
    return false;
}
void GameModel::calculDuTemps()
{
     time_t sec;
    if(m_n->getFirstTime() == 0){
        m_n->setFirstTime(1);
        time(&sec);
        m_n->setInstant(*localtime(&sec));
        m_n->setFin(m_n->getInstant().tm_sec);
        m_n->setMinutes(m_n->getInstant().tm_min);
        m_n->setCompteur(m_n->getMinutes() * 60+ m_n->getFin());
    }
    else
    {
        sec = m_n->getSecondes();
        time(&sec);
        m_n->setInstant(*localtime(&sec));
        m_n->setFin(m_n->getInstant().tm_sec); // Temps à l'instant en secondes
        m_n->setMinutes(m_n->getInstant().tm_min); // Temps à l'instant en minutes
        m_n->setDifference(((m_n->getMinutes() * 60) + m_n->getFin()) - m_n->getCompteur()); // Convertion du tout en secondes
        m_n->setTemps(m_n->getTemps() - m_n->getDifference()); // Puis affectation du temps - la difference
        m_n->setCompteur((m_n->getMinutes() * 60 )+  m_n->getFin()); // Récupération du temps précédent
        
        if(m_n->getTemps() <= 0){
            m_n->setTemps(0);
            plusDeTemps();
        }
    }
    
}

// J'etais en train de le faire tkt
/*
bool GameModel::verification_niveau()
{
    string tab[8] = {"N","O","S","E","NE","NO","SE","SO"};
    string directionPrecedente;
    for(int i=0; i< 8; i++){
        while(directionBis(tab[i])){
            int x = m_p->get_x();
            int y = m_p->get_y();
            directionPrecedente = tab[i];
        }
        if(directionBis(tab[i]) != true){
            
        }
    }
    return false;
}
bool GameModel::directionBis(string answer)
{
    if(answer=="N")
        return moveBis(0,-1);
    else if(answer=="S")
        return moveBis(0, 1);
    else if(answer=="E")
        return moveBis(1,0);
    else if(answer=="O")
        return moveBis(-1, 0);
    else if(answer=="SE")
        return moveBis(1, 1);
    else if(answer=="SO")
        return moveBis(-1, 1);
    else if(answer=="NO")
        return moveBis(-1, -1);
    else if(answer=="NE")
        return moveBis(1,-1);
    else
        return false;
}
bool GameModel::moveBis(int pos_x, int pos_y)
{
    int x = m_p->get_x();
    int y = m_p->get_y();
    if(x != -1 && y != -1) {
        delete matrice[m_p->get_y()][m_p->get_x()];
        matrice[m_p->get_y()][m_p->get_x()] = new Croix();
        m_p->deplacement(pos_x,pos_y);
    }
    nb_cases = deplacement();
    
    if(x != -1 && y != -1) {
        string obj = matrice[m_p->get_y()][m_p->get_x()]->getObj();  // Test si la case suivante, la premiere, est une bombe
        if(obj == "@@@" || obj == " "){
            nb_cases = 0;
        }
    }
    if(nb_cases == 0)                                          // Si c'est une bombe on recule
    {
        m_p->set_pos(x, y);
        return false;
    }
    else if(nb_cases != -1 ){
        
        m_s->setDeplacement(m_s->getDeplacement()+nb_cases);    // Incrémentation du nombre de déplacement
        m_s->setScoreTotal(m_s->getScoreTotal()+nb_cases*10);   // Incrémentation du score total
        
        i = 1;                                                  // Initialisation de i à 1
        
        while(i < nb_cases && deplacement() != -1)
        {
            delete matrice[m_p->get_y()][m_p->get_x()];         // On libére la case du joueur
            matrice[m_p->get_y()][m_p->get_x()] = new Croix();
            m_p->deplacement(pos_x, pos_y);
            i++;                                                // On incrémente i
        }
        if(deplacement() != -1){                                // Si le joueur a atteint le nb_case alors on supprime et on met une croix
            delete matrice[m_p->get_y()][m_p->get_x()];
            matrice[m_p->get_y()][m_p->get_x()] = new Croix();
            objectifAtteint();
            return true;
        }
        else
        {
            m_s->setScoreTotal(m_s->getScoreTotal()-nb_cases*10);
            perteVie();
            return false;
        }
    }
    
    else
    {
        perteVie();
        return false;
    }
    
}
*/

// BAC À SABLE DU GAME MODEL


bool GameModel::testCase(const int x, const int y) const{
    //std::cout << "x : " << x << " y : " << y << std::endl;
    std::cout << "matrice[" << y << "][" << x << "] : " << matrice[y][x]->getMov() << std::endl;
    if(matrice[y][x]->getMov() == -1 || matrice[y][x]->getMov()){
        std::cout << "LA CASE SUIVANTE N'EST PAS ACCESSIBLE" << std::endl;
        return false;
    }
    else
        std::cout << "LA CASE SUIVANTE EST DISPONIBLE" << std::endl;
        return true;
}

bool GameModel::datMove(const int x, const int y){
    std::cout << "x : " << x << " y : " << y << std::endl;
    if(testCase(m_p->get_x()+x, m_p->get_y()+y)){
        int nbCase = matrice[m_p->get_y()+y][m_p->get_x()+x]->getMov();
        std::cout << "nbCase : " << nbCase << std::endl;
        int dep=0;
        while(dep < nbCase && testCase(m_p->get_x()+x, m_p->get_y()+y)){
            matrice[m_p->get_y()][m_p->get_x()] = new Croix();
            m_p->set_position(m_p->get_x() + x, m_p->get_y()+ y);
            ++dep;
        }
        if(dep == nbCase)
            return true;
        
        return false;
    }
    else
        return false;
}




