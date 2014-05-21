#include "GameView.h"
#include "GameModel.h"
#include "Const.h"
#include "Langage.h"
#include "Editeur.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


using namespace std;
using namespace sf;

/************************************************************
 * Nom: GameView                                            *
 ************************************************************
 * Type: Constructeur                                       *
 ************************************************************/
GameView::GameView(int h, int w, int bpp){
    m_window = new RenderWindow(sf::VideoMode(h, w, bpp), "Puru Puru", sf::Style::Close);
    _font.LoadFromFile("arial.ttf");

    loadNamePicture();

    sound.SetBuffer(Buffer);
    sound.SetPitch(1.5f);
    sound.SetVolume(25.f);
    sound.SetLoop(true);

    bonusSound.SetBuffer(bonus);
    bonusSound.SetPitch(1.5f);
    bonusSound.SetVolume(50.f);

    // Aide pour démarrer le chrono au bon moment
    isEnable = false;
    afficherScore = true;

    //Chargement de la langue par défaut
    m_langue = new Langage();
    m_l = m_langue->getlangues();

    //Initialisation de l'éditeur
    m_editeur = new Editeur();

}
/************************************************************
 * Nom: ~GameView                                           *
 ************************************************************
 * Type: Desstructeur                                       *
 ************************************************************/
GameView::~GameView()
{
    if(m_window != NULL)
        delete m_window;
    if(m_langue != NULL)
        delete m_langue;

}

bool GameView::loadPicture(const std::string name, sf::Image &picture){
    return picture.LoadFromFile(name);
}

bool GameView::loadSprite(const std::string name, sf::Image &picture, sf::Sprite &sprite){
    if(loadPicture(name, picture)){
        sprite = sf::Sprite(picture);
        return true;
    }
    std::cout << "loadPicture "<<name <<" was failed" << std::endl;
    return false;
}

bool GameView::loadSprite(const std::string name, sf::Image &picture, sf::Sprite &sprite, const int rx, const int ry){
    if(loadPicture(name, picture)){
        sprite = sf::Sprite(picture);
        sprite.Resize(rx, ry);
        return true;
    }
    std::cout << "loadPicture "<<name <<" was failed" << std::endl;
    return false;
}

void GameView::loadNamePicture(){
    _namePictureBackground = "background.png";
    _namePictureDigger = "digger_face.png";
    _namePictureBomb = "tuile_bombe.png";
    _namePictureBonus = "tuile_bonus.png";
    _namePictureCase = "tuile.png";
    _namePictureExitButton = "exitButton.png";
    _namePicturePlayButton = "startButton.png";
    _namePictureCaseVide = "vide.png";
    _namePictureOptionButton = "optionButton.png";
    _namePictureMenu = "menu.png";
    _namePictureBestscore = "bestScore.png";
    _namePictureFrancais = "francais.png";
    _namePictureAnglais = "anglais.png";
    _namePictureJouer = "jouer.png";
    _namePictureQuitter = "quitter.png";
    _namePictureSound = "son.png";
    _namePictureNotSound = "notSon.png";
}

bool GameView::initSprite(){
    if(loadSprite(_namePictureBackground, _background_image, _background_sprite, 38, 38) &&
       loadSprite(_namePictureDigger, _digger_image, _digger_sprite, 38, 38) &&
       loadSprite(_namePictureBomb, _bombe_image, _bombe_sprite, 38, 38) &&
       loadSprite(_namePictureBonus, _bonus_image, _bonus_sprite, 38, 38) &&
       loadSprite(_namePictureCase, _tuile_image, _tuile_sprite, 38, 38) &&
       loadSprite(_namePictureExitButton, _exit_image, _exit_sprite) &&
       loadSprite(_namePicturePlayButton, _start_image, _start_sprite) &&
       loadSprite(_namePictureCaseVide, _vide_image, _vide_sprite, 38, 38) &&
       loadSprite(_namePictureOptionButton, _option_image, _option_sprite) &&
       loadSprite(_namePictureMenu, _menu_image, _menu_sprite) &&
       loadSprite(_namePictureBestscore, _bestScore_image, _bestScore_sprite, 500, 600) &&
       loadSprite(_namePictureFrancais, _francais_image, _francais_sprite) &&
       loadSprite(_namePictureAnglais, _anglais_image, _anglais_sprite) &&
       loadSprite(_namePictureJouer, _jouer_image, _jouer_sprite) &&
       loadSprite(_namePictureQuitter, _quitter_image, _quitter_sprite) &&
       loadSprite(_namePictureSound, _son_image, _son_sprite) &&
       loadSprite(_namePictureNotSound, _notSon_image, _notSon_sprite)){
        return true;
    }
    return false;
}

void GameView::loadText(sf::String &s, const int x, const int y, const float size, const std::string text)
{
    s = sf::String(text);
    s.SetPosition(x, y);
    s.SetSize(size);
}

void GameView::loadText(sf::String &s, const int x, const int y, const float size, const std::string text, const sf::Font &f)
{
    s = sf::String(text);
    s.SetPosition(x, y);
    s.SetSize(size);
    s.SetFont(_font);
}


void GameView::loadText(sf::String &s, const int x, const int y, const float size, const std::string text, const int r, const int g, const int b)
{
    s = sf::String(text);
    s.SetPosition(x, y);
    s.SetSize(size);
    s.SetColor(sf::Color(r, g, b));
}


void GameView::loadText(sf::String &s, const int x, const int y, const float size, const std::string text, const sf::Font &f, const int r, const int g, const int b)
{
    s = sf::String(text);
    s.SetPosition(x, y);
    s.SetSize(size);
    s.SetColor(sf::Color(r, g, b));
    s.SetFont(_font);
}


void GameView::loadText(sf::String &s, const int x, const int y, const std::string text)
{
    s = sf::String(text);
    s.SetPosition(x, y);
}

void GameView::changeSprite(sf::Sprite &s, const float x, const float y){
    s.SetPosition(x, y);
}

void GameView::changeSprite(sf::Sprite &s, const float x, const float y, const int r, const int g, const int b, const int alpha){
    s.SetPosition(x, y);
    s.SetColor(sf::Color(r, g, b, alpha));
}

void GameView::changeSprite(sf::Sprite &s, const float x, const float y, const int r, const int g, const int b, const int alpha, const float mx, const float my){
    s.SetPosition(x, y);
    s.SetColor(sf::Color(r, g, b, alpha));
    s.Move(mx, my);
}

void GameView::changeSpriteResize(sf::Sprite &s, const float x, const float y, const int r, const int g, const int b, const int alpha, const float rx, const float ry){
    s.SetPosition(x, y);
    s.SetColor(sf::Color(r, g, b, alpha));
    s.Resize(rx, ry);
}

// Focus

bool GameView::onTheSprite(const sf::Sprite &s, const int x, const int y) const{
    return (x < (s.GetPosition().x + s.GetSize().x ) && x > s.GetPosition().x )&& (y > s.GetPosition().y && y < s.GetPosition().y + s.GetSize().y );
}

bool GameView::onTheText(const sf::String &s, const int x, const int y) const{
    sf::FloatRect sizeText = s.GetRect();
    return (x < (s.GetPosition().x + sizeText.GetWidth() ) && x > s.GetPosition().x )&& (y > s.GetPosition().y && y < s.GetPosition().y + sizeText.GetHeight());
}

/************************************************************
 * Nom: setModel                                            *
 ************************************************************
 * Type: Constructeur                                       *
 ************************************************************
 * Paramètres: model de type GameModel                      *
 ************************************************************
 * Rôle: Affecte un model à un autre model                  *
 ************************************************************/
void GameView::setModel(GameModel *model)
{
    m_model = model;
}

void GameView::s_afficheBonus()
{
    ostringstream out;
    out << m_l[3] << m_model->getLvl().get_score_bonus() << m_l[4] << m_model->getLvl().get_b_temps() <<  m_l[5] << m_model->getLvl().get_b_vie()  <<  m_l[6] << m_model->getLvl().getLevel();

    loadText(affiche_Bonus, WIDTH-250, 100, 25.0F, out.str());
    m_window->Draw(affiche_Bonus);
}

void GameView::s_afficheScore()
{
    ostringstream out;
    out<<  m_l[7] << m_model->getScore().getDeplacement() <<  m_l[8] << m_model->getScore().getCible() << m_l[17] << m_model->getScore().getScoreTotal() << m_l[9] << m_model->getLvl().getTemps() << endl;

    loadText(affiche_Score, WIDTH-250, 200, 25.0F, out.str());

    m_window->Draw(affiche_Score);
}

void GameView::s_viePlayer()
{
    ostringstream out;
    out<< m_l[10] << m_model->getPlayer().getVie();

    loadText(_vie_player, WIDTH-250, 275, 25.0F, out.str());

    m_window->Draw(_vie_player);
}
/************************************************************
 * Nom: affiche                                             *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle: Fonction qui affiche la matrice à l'écran et       *
 *     l'affichage des scores                               *
 ************************************************************/
void GameView::draw(Case*** matrice)
{
    angle = 180.0f;
    // Image background
    _background_sprite.Resize(WIDTH, HEIGHT);
    _background_sprite.SetPosition(0,0);
    _background_sprite.SetColor(sf::Color(126,126,126,128));
    m_window->Draw(_background_sprite);


    if(images.size() != 0) {
        for(std::vector<sf::Sprite*>::iterator it = images.begin(); it != images.end(); ++it) {
            *it = NULL;
            delete *it;
        }
    }
    images.clear();
    images.resize(0);

    for(int i=0; i<18; i++){
        for(int j=0; j<18; j++){
            if(dynamic_cast<Bomb*>(matrice[i][j])){
                _bombe_sprite.SetPosition((j*WIDTH_PIECE)+50,(i*WIDTH_PIECE)+30);
                _bombe_sprite.SetColor(sf::Color(255,255,255,128));

                Sprite *bomb = &_bombe_sprite;
                images.push_back(bomb);
                m_window->Draw(*bomb);
            }
            else if(dynamic_cast<BonusCase*>(matrice[i][j])){
                ostringstream out;
                out << matrice[i][j]->getObj();
                String s = String(out.str());
                s.SetPosition((j*WIDTH_PIECE)+50, (i*WIDTH_PIECE)+30);

                _bonus_sprite.SetPosition((j*WIDTH_PIECE)+50,(i*WIDTH_PIECE)+30);
                _bonus_sprite.SetColor(sf::Color(77,77,77,128));
                Sprite *bonus = &_bonus_sprite;
                images.push_back(bonus);
                m_window->Draw(*bonus);
                m_window->Draw(s);
            }
            else if(dynamic_cast<Croix*>(matrice[i][j]))
            {
                _vide_sprite.SetPosition((j*WIDTH_PIECE)+50, (i*WIDTH_PIECE)+30);
                _vide_sprite.SetColor(sf::Color(246,246,246,128));
                Sprite *vide = &_vide_sprite;
                images.push_back(vide);
                m_window->Draw(*vide);
            }
            else
            {
                ostringstream out;
                out << matrice[i][j]->getObj();
                String s = String(out.str());
                s.SetPosition(j*WIDTH_PIECE + 60, (i*WIDTH_PIECE)+30);
                _tuile_sprite.SetPosition((j*WIDTH_PIECE) + 50,(i*WIDTH_PIECE)+30);
                _tuile_sprite.SetColor(sf::Color(192,192,192,128));
                Sprite *tuile = &_tuile_sprite;
                images.push_back(tuile);
                m_window->Draw(*tuile);
                m_window->Draw(s);
            }
        }

    }
    if(m_model->getEcranJeu() == true && m_model->getGoToView() == 1 && isInLevelEditing == false){
        Sprite *dig = &_digger_sprite;
        if(m_model->getPlayer().get_y()*WIDTH_PIECE < 18*WIDTH_PIECE && m_model->getPlayer().get_x()*WIDTH_PIECE < 18*WIDTH_PIECE){
            images.push_back(dig);
            sf::Image image;
            image.LoadFromFile("tuile_bonus.png");
            sf::Sprite sprite = Sprite(image);
            sprite.Resize(38, 38);
            sprite.SetPosition((m_model->getPlayer().get_x()*WIDTH_PIECE)+50, (m_model->getPlayer().get_y()*WIDTH_PIECE)+30);
            m_window->Draw(sprite);
            _digger_sprite.SetPosition(((m_model->getPlayer().get_x()*WIDTH_PIECE) +50), (m_model->getPlayer().get_y()*WIDTH_PIECE)+30);
                m_window->Draw(*dig);
            }
        s_afficheBonus();
        s_afficheScore();
        s_viePlayer();
    }
}
/************************************************************
 * Nom: presentation                                        *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle: Affiche l'en tête de début de jeu                  *
 ************************************************************/

void GameView::s_Presentation()
{
    loadText(titre, 50, 50, 80.0F, m_l[11], _font, 200, 200, 200);
    loadText(meilleursScore, WIDTH/2 + 80, 225, 45.0F, m_l[20]);

    if(m_langue->getNom() == "anglais"){
        _start_sprite.SetPosition(100, 250);
        _exit_sprite.SetPosition(100, 550);
        m_window->Draw(_start_sprite);
        m_window->Draw(_exit_sprite);
    }
    _option_sprite.SetPosition(100, 400);
    _bestScore_sprite.SetPosition(WIDTH/2 -20, 150);

    if(m_langue->getNom() == "francais"){
        _jouer_sprite.SetPosition(100, 250);
        _quitter_sprite.SetPosition(100, 550);
        m_window->Draw(_jouer_sprite);
        m_window->Draw(_quitter_sprite);
    }

    m_window->Draw(_bestScore_sprite);
    m_window->Draw(_option_sprite);
    m_window->Draw(meilleursScore);
    m_window->Draw(titre);

}
/************************************************************
 * Nom: rejouer                                             *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle: Affiche la question                                *
 ************************************************************/
void GameView::s_rejouer()
{
    ostringstream out;
    out << m_l[12];
    loadText(_abandon, WIDTH/2, HEIGHT/2-200, 80.0F, out.str());


    _start_sprite.SetPosition(WIDTH/2 -300, HEIGHT/2);
    _exit_sprite.SetPosition(WIDTH/2 +100, HEIGHT/2);


    m_window->Draw(_exit_sprite);
    m_window->Draw(_start_sprite);
    m_window->Draw(_abandon);
}
/************************************************************
 * Nom: retourMenu                                          *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle: Affiche une question et un choix menu              *
 ************************************************************/
void GameView::s_perteVie()
{

    loadText(jouer, WIDTH/2-300, HEIGHT/2+50, 40.0F, m_l[0], 125, 205, 128);
    loadText(quitter, WIDTH/2+100, HEIGHT/2+50, 40, m_l[2], 125, 205, 128);

    sf::String perte;
    sf::String suite;
    loadText(suite, WIDTH/2-250, HEIGHT/2-30, 40.0F, m_l[13]);
    loadText(perte, WIDTH/2-300, HEIGHT/2-150, 40.0F, m_l[14]);

    m_window->Clear(sf::Color(20,20,20));

    m_window->Draw(suite);
    m_window->Draw(perte);
    m_window->Draw(jouer);
    m_window->Draw(quitter);
}

void GameView::s_changeLvl()
{
    loadText(jouer, WIDTH/2-300, HEIGHT/2+50, 40.0F, m_l[0], 125, 205, 128);
    loadText(quitter, WIDTH/2+100, HEIGHT/2+50, 40, m_l[2], 125, 205, 128);

    sf::String text = String(m_l[15]);
    text.SetSize(50.0f);


    if(m_langue->getNom() == "anglais"){
        loadText(text, WIDTH/2-300, HEIGHT/2-50, 50.0F, m_l[15]);
    }
    else
        loadText(text, WIDTH/2-350, HEIGHT/2-50, 50.0F, m_l[15]);

    m_window->Draw(text);
    m_window->Draw(jouer);
    m_window->Draw(quitter);
}

void GameView::s_plusDeVie()
{
    ostringstream out;
    out << m_l[18];
    String text;


    nom.SetPosition(WIDTH/2-150, HEIGHT/2);
    nom.SetSize(40);

    loadText(text, WIDTH/2-400, HEIGHT/2-100, 40.0F, m_l[18]);

    m_window->Draw(text);
}

void GameView::s_perteParTemps()
{
    sf::String perte;
    sf::String suite;

    loadText(jouer, WIDTH/2-300, HEIGHT/2+50,40.0F, m_l[0], 125, 205, 128);
    loadText(quitter, WIDTH/2+100, HEIGHT/2+50, 40, m_l[2], 125, 205, 128);
    loadText(perte, WIDTH/2-250, HEIGHT/2-30, 40.0F, m_l[16]);
    loadText(suite, WIDTH/2-300, HEIGHT/2-150, 40.0F, m_l[14]);

    m_window->Clear(sf::Color(20,20,20));

    m_window->Draw(suite);
    m_window->Draw(perte);
    m_window->Draw(jouer);
    m_window->Draw(quitter);
}

void GameView::s_option()
{
    String e;

    loadText(e, WIDTH/2-150, 100, 80.0F, m_l[1], _font, 200, 200, 200);

    _menu_sprite.SetPosition(WIDTH/2-100, HEIGHT/2 + 250);
    m_window->Draw(_menu_sprite);

    m_window->Draw(e);
}

void GameView::s_chargementScore()
{
    fstream f;
    f.open("meilleursScores.txt", ios::in);

    if( f.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        afficherScore = false;
        f.close();
    }
    else
    {
        int valeur = 0;
        string phrase; // Nom du joueur
        string sauv;

        f >> phrase;

        while(!f.eof()){
            if(valeur%2 == 0){
                sauv = phrase;
            }
            else {
                m_e[atoi(phrase.c_str())] = sauv;
            }
            valeur++;
            f >> phrase;
        }

        f.close(); // fermeture du fichier
    }
}
/**************************************************************
 * Nom: affichageScore                                        *
 **************************************************************
 * Type: void                                                 *
 **************************************************************
 * Rôle: Affiche les scores(ouverture et fermeture de fichier)*
 **************************************************************/
void GameView::affichageScore()
{
    if(afficherScore)
        s_chargementScore();

    int numero = 0;
    int distance = 0;
    for(map<int, std::string>::reverse_iterator it=m_e.rbegin(); it != m_e.rend(); ++it)
    {
        if(numero < 5){
            string e = it->second;
            e += " ";
            stringstream ss;
            ss << it->first;
            e += ss.str();
            score = String(e);
            score.SetSize(35);
            score.SetPosition(WIDTH/2 +70, (HEIGHT/2)-60 +distance);
            distance+=70;
            m_window->Draw(score);
        }
        numero++;
    }
    afficherScore = false;

}

void GameView::s_affichageLangue()
{
    langue = String(m_l[19]);
    langue.SetPosition(100, HEIGHT/2 - 150);
    langue.SetSize(50);

    _anglais_sprite.SetPosition(WIDTH/2 - 200, HEIGHT/2 - 200);
    _francais_sprite.SetPosition(WIDTH/2 - 50, HEIGHT/2 - 200);
    m_window->Draw(_anglais_sprite);
    m_window->Draw(_francais_sprite);
    m_window->Draw(langue);
}
/**************************************************************
 * Nom: s_sauvegarde_Score                                    *
 **************************************************************
 * Type: void                                                 *
 **************************************************************
 * Rôle: Sauvegarde des scores                                *
 **************************************************************/
void GameView::s_sauvegarde_score() {
    fstream f;
    f.open( "meilleursScores.txt", ios::out | ios::app ); // ouverture du fichier en ecriture
    if( f.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        f.close();
    }
    f << s_nom << endl;
    f << m_model->getScore().getScoreTotal() << endl;
    f.close();
}

void GameView::s_quitte_inGame()
{
    if(m_langue->getNom() == "anglais")
        _quitte_inGame = Sprite(_exit_image);
    else
        _quitte_inGame = Sprite(_quitter_image);

    _quitte_inGame.SetPosition(800, HEIGHT-100);
    m_window->Draw(_quitte_inGame);
}

void GameView::s_boutton_son()
{
    _son_sprite.SetPosition(900, 50);
    _notSon_sprite.SetPosition(840, 50);
    status = sound.GetStatus();

    if(status == sf::Music::Playing){
        m_window->Draw(_son_sprite);
    }
    else
    {
        m_window->Draw(_notSon_sprite);
    }
}

bool GameView::answer_move(string answer) {
    if(m_model->check_answer(answer)){
        return true;
    }
    else
        return false;
}
void GameView::s_boutonEditeur() {
    _editer = String("Editer");
    _editer.SetPosition(WIDTH -200, 50);
    _editer.SetSize(40);
    _editer.SetColor(sf::Color(200,200,200));


    m_window->Draw(_editer);
}
void GameView::s_verifiationSelectionBomb(const sf::Sprite *s, int x, int y){
    if((x < (s->GetPosition().x + s->GetSize().x ) && x > s->GetPosition().x && (y > s->GetPosition().y) && y < s->GetPosition().y + s->GetSize().y )){
        isBombSelecting = true;
        isBonusSelecting = false;
    }
}
void GameView::s_verifiationSelectionBonus(const sf::Sprite *s, int x, int y){
    if((x < (s->GetPosition().x + s->GetSize().x ) && x > s->GetPosition().x && (y > s->GetPosition().y) && y < s->GetPosition().y + s->GetSize().y )){
        isBombSelecting = false;
        isBonusSelecting = true;
    }
}

void GameView::s_affiche_choix()
{
    _digger_sprite.SetPosition(WIDTH -230, 200);
    _bombe_sprite.SetPosition(WIDTH -230, 300);
    _bonus_sprite.SetPosition(WIDTH -230, 400);

    _prendre_Bomb = String("Bombes");
    _prendre_Bonus = String("Bonus");
    _selectionner = String("Selectionner et placer");

    _prendre_Bomb.SetPosition(WIDTH-170, 300);
    _prendre_Bonus.SetPosition(WIDTH-170, 400);
    _selectionner.SetPosition(WIDTH-250, 100);

    _prendre_Bomb.SetSize(30);
    _prendre_Bonus.SetSize(30);
    _selectionner.SetSize(25);

    m_window->Draw(_prendre_Bomb);
    m_window->Draw(_prendre_Bonus);
    m_window->Draw(_selectionner);
    m_window->Draw(_bombe_sprite);
    m_window->Draw(_bonus_sprite);

}
void GameView::s_bouton_save()
{
    _enregistrer = String("Enregistrer");
    _enregistrer.SetPosition(WIDTH-200, 600);
    _enregistrer.SetSize(30);
    m_window->Draw(_enregistrer);
}
void GameView::s_buttonInEdit() {
    _nouveau = String("Nouveau");
    _chargerNiveau = String("Charger Niveau");
    _fichierExistant = String("Fichier Recent");

    _fichierExistant.SetSize(45.0f);
    _fichierExistant.SetPosition(WIDTH/2 + 80, 225);

    _nouveau.SetPosition(100, 250);
    _chargerNiveau.SetPosition(100, 550);
    _nouveau.SetSize(50.0f);
    _chargerNiveau.SetSize(50.0f);

    m_window->Draw(_bestScore_sprite);
    m_window->Draw(_fichierExistant);
    m_window->Draw(_nouveau);
    m_window->Draw(_chargerNiveau);
}
void GameView::s_afficheFichierRecent() {
    m_editeur->chargementListeFichier();
    m_fichierRecent = m_editeur->getFichierRecent();
    int numero = 0;
    int distance = 0;
    for(vector<string>::reverse_iterator it=m_fichierRecent.rbegin(); it!=m_fichierRecent.rend(); ++it){
        if(numero < 5){
            score = String(*it);
            score.SetSize(35);
            score.SetPosition(WIDTH/2 +70, (HEIGHT/2)-60 +distance);
            distance+=70;
            m_window->Draw(score);
        }
        numero++;

    }
}
void GameView::s_inscrireNomFichier(){
    String text = String("Entrez un nom de fichier");
    text.SetPosition(WIDTH/2-400, HEIGHT/2- 100);
    nom.SetPosition(WIDTH/2-150, HEIGHT/2);
    nom.SetSize(40);
    text.SetSize(40);

    m_window->Draw(text);
}
bool GameView::treatEvents()
{
    if(initSprite()){
        while (m_window->IsOpened())
        {
            if(isEnable)
                m_model->calculDuTemps();
            // Process events
            sf::Event e;
            while (m_window->GetEvent(e))
            {
                // Close window : exit
                if (e.Type == sf::Event::Closed)
                    m_window->Close();

                switch (m_model->getGoToView())
                {
                    case 0:
                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() == false){

                            if(m_langue->getNom() == "anglais"){
                                if(onTheSprite(_start_sprite, e.MouseButton.X, e.MouseButton.Y)){
                                    m_model->setEcranJeu(true);
                                    m_model->setGoToView(1);
                                    isEnable = true;
                                }

                                if( onTheSprite(_exit_sprite, e.MouseButton.X, e.MouseButton.Y)&& m_model->getEcranJeu() == false){
                                    m_window->Close();
                                }
                            }
                            if(m_langue->getNom() == "francais"){
                                if(onTheSprite(_jouer_sprite, e.MouseButton.X, e.MouseButton.Y)){
                                    m_model->setEcranJeu(true);
                                    m_model->setGoToView(1);
                                    isEnable = true;
                                }
                                if(onTheSprite(_quitter_sprite, e.MouseButton.X, e.MouseButton.Y) && m_model->getEcranJeu() == false){
                                    m_window->Close();
                                }
                            }
                            if(onTheSprite(_option_sprite, e.MouseButton.X, e.MouseButton.Y) && m_model->getEcranJeu() == false){
                                s_option();
                                m_model->setGoToView(5);
                            }
                            if(onTheText(_editer, e.MouseButton.X, e.MouseButton.Y) && m_model->getEcranJeu() == false){
                                m_model->setGoToView(7);
                            }
                        }
                    case 1:

                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() ){

                            if((e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x ) && e.MouseButton.X > _digger_sprite.GetPosition().x ) && (e.MouseButton.Y < _digger_sprite.GetPosition().y && e.MouseButton.Y > _digger_sprite.GetPosition().y - 40)){
                                if(answer_move("N"))
                                    m_model->direction("N");
                            }
                            if((e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x ) && e.MouseButton.X > _digger_sprite.GetPosition().x ) && (e.MouseButton.Y > (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y) && e.MouseButton.Y < (_digger_sprite.GetPosition().y) + _digger_sprite.GetSize().y + 40)){
                                if(answer_move("S"))
                                    m_model->direction("S");

                            }
                            if((e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x + 40) && e.MouseButton.X > (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x)) && (e.MouseButton.Y > _digger_sprite.GetPosition().y && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y))){
                                if(answer_move("E"))
                                    m_model->direction("E");

                            }

                            if((e.MouseButton.X > (_digger_sprite.GetPosition().x + -40) && e.MouseButton.X < _digger_sprite.GetPosition().x && e.MouseButton.Y > _digger_sprite.GetPosition().y && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y))){
                                if(answer_move("O"))
                                    m_model->direction("O");

                            }

                            if(e.MouseButton.X > (_digger_sprite.GetPosition().x + -40) && e.MouseButton.X < _digger_sprite.GetPosition().x && e.MouseButton.Y < _digger_sprite.GetPosition().y && e.MouseButton.Y > (_digger_sprite.GetPosition().y - 40)){
                                if(answer_move("NO"))
                                    m_model->direction("NO");

                            }

                            if(e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x + 40) && e.MouseButton.X > (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x) && e.MouseButton.Y < _digger_sprite.GetPosition().y && e.MouseButton.Y > (_digger_sprite.GetPosition().y - 40)){
                                if(answer_move("NE"))
                                    m_model->direction("NE");
                            }

                            if(e.MouseButton.X > (_digger_sprite.GetPosition().x + -40) && e.MouseButton.X < _digger_sprite.GetPosition().x && e.MouseButton.Y > (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y) && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y + 40)){
                                if(answer_move("SO"))
                                    m_model->direction("SO");

                            }
                            if(e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x + 40) && e.MouseButton.X > (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x) && e.MouseButton.Y > (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y) && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y + 40)){
                                if(answer_move("SE"))
                                    m_model->direction("SE");

                            }
                            if(onTheSprite(_quitte_inGame, e.MouseButton.X, e.MouseButton.Y)){
                                m_model->setEcranJeu(false);
                                m_model->rejouerPartie();
                                isEnable = false;
                                m_model->setGoToView(0);
                            }
                            if(onTheSprite(_son_sprite, e.MouseButton.X, e.MouseButton.Y)){
                                sound.Pause();
                            }
                            if(onTheSprite(_notSon_sprite, e.MouseButton.X, e.MouseButton.Y)){
                                sound.Play();
                            }


                        }
                        break;
                    case 2:
                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() == false){
                            if(onTheText(jouer, e.MouseButton.X, e.MouseButton.Y)){
                                m_model->genereMatrice();
                                m_model->setGoToView(1);
                                m_model->setEcranJeu(true);
                                isEnable = true;
                            }
                            if(onTheText(quitter, e.MouseButton.X, e.MouseButton.Y)){
                                m_window->Close();
                            }

                        }
                        break;
                    case 3:

                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() == false){
                            if(onTheText(jouer, e.MouseButton.X, e.MouseButton.Y)){
                                m_model->genereMatrice();
                                m_model->setGoToView(1);
                                m_model->setEcranJeu(true);
                                isEnable = true;
                            }

                            if(onTheText(quitter, e.MouseButton.X, e.MouseButton.Y)){
                                m_window->Close();
                            }

                        }
                        break;
                    case 4:
                        if(e.Type == sf::Event::TextEntered){
                            if(s_nom_player.length() <= 10)
                            {
                                s_nom_player += static_cast<char>(e.Text.Unicode);
                                nom.SetText(s_nom_player);
                            }
                        }
                        if ((e.Type == sf::Event::KeyPressed) && (e.Key.Code == sf::Key::Back)) {
                            if(s_nom_player.length() > 0){
                                s_nom_player.erase(s_nom_player.length()-1,1);
                                nom.SetText(s_nom_player);
                                if(s_nom_player.length() >= 1)
                                    s_nom_player.resize(s_nom_player.length()-1);
                            }
                        }
                        if(e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::Return)) {
                            s_nom = s_nom_player;
                            afficherScore = true;
                            s_sauvegarde_score();
                            s_nom_player.resize(0);
                            m_model->setEcranJeu(false);
                            m_model->rejouerPartie();
                            m_model->setGoToView(0);
                        }
                        break;

                    case 5:
                        // Menu dans l'écran Option
                        if(onTheSprite(_menu_sprite, e.MouseButton.X, e.MouseButton.Y)){
                            m_model->setGoToView(0);
                        }
                        if (e.Type == sf::Event::Closed)
                            m_window->Close();

                        if(onTheSprite(_anglais_sprite, e.MouseButton.X, e.MouseButton.Y)){
                            m_langue->setNom("anglais");
                            m_l = m_langue->getlangues();
                        }

                        if(onTheSprite(_francais_sprite, e.MouseButton.X, e.MouseButton.Y)){
                            m_langue->setNom("francais");
                            m_l = m_langue->getlangues();
                        }
                        break;
                    case 6:
                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() == false){
                            if(onTheText(jouer, e.MouseButton.X, e.MouseButton.Y)){
                                m_model->genereMatrice();
                                m_model->setGoToView(1);
                                m_model->setEcranJeu(true);
                                isEnable = true;
                            }
                            if(onTheText(quitter, e.MouseButton.X, e.MouseButton.Y)){
                                m_window->Close();
                            }

                        }
                        break;
                    case 7: // Vue avant editeur
                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() == false){

                             if(onTheText(_nouveau, e.MouseButton.X, e.MouseButton.Y)){
                                m_editeur->genereMatriceEditeur();
                                m_model->setGoToView(8);
                            }

                             if(onTheText(_chargerNiveau, e.MouseButton.X, e.MouseButton.Y)){
                                m_model->setGoToView(10);
                            }
                        }
                        break;
                    case 8:
                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() == false){
                            s_verifiationSelectionBomb(&_bombe_sprite, e.MouseButton.X, e.MouseButton.Y);
                            s_verifiationSelectionBonus(&_bonus_sprite, e.MouseButton.X, e.MouseButton.Y);
                            m_editeur->ajouterBomb(e.MouseButton.X, e.MouseButton.Y, isBombSelecting);
                            m_editeur->ajouterBonus(e.MouseButton.X, e.MouseButton.Y, isBonusSelecting);

                           if(onTheText(_enregistrer, e.MouseButton.X, e.MouseButton.Y)){
                                m_model->setGoToView(9);
                            }

                        }
                        break;
                    case 9:
                        if(e.Type == sf::Event::TextEntered){
                            if(_nomDuFichier.length() <= 15)
                            {
                                _nomDuFichier += static_cast<char>(e.Text.Unicode);
                                nom.SetText(_nomDuFichier);
                            }
                        }
                        if ((e.Type == sf::Event::KeyPressed) && (e.Key.Code == sf::Key::Back)) {
                            if(_nomDuFichier.length() > 0){
                                _nomDuFichier.erase(_nomDuFichier.length()-1,1);
                                nom.SetText(_nomDuFichier);
                            }
                            if(_nomDuFichier.length() >= 1)
                                _nomDuFichier.resize(_nomDuFichier.length()-1);
                        }
                        if(e.Type == sf::Event::KeyPressed  && (e.Key.Code == sf::Key::Return)) {
                            m_editeur->sauvegardeFichier(_nomDuFichier);
                            s_nom_player.resize(0);
                            m_model->setGoToView(7);
                        }
                        break;

                    case 10:
                        if(e.Type == sf::Event::TextEntered){
                            if(_nomDuFichier.length() <= 15)
                            {
                                _nomDuFichier += static_cast<char>(e.Text.Unicode);
                                nom.SetText(_nomDuFichier);
                            }
                        }
                        if ((e.Type == sf::Event::KeyPressed) && (e.Key.Code == sf::Key::Back)) {
                            if(_nomDuFichier.length() > 0){
                                _nomDuFichier.erase(_nomDuFichier.length()-1,1);
                                nom.SetText(_nomDuFichier);
                                if(_nomDuFichier.length() >= 1)
                                    _nomDuFichier.resize(_nomDuFichier.length()-1);
                            }
                        }
                        if(e.Type == sf::Event::KeyPressed  && (e.Key.Code == sf::Key::Return)) {
                            m_editeur->chargerNiveau(_nomDuFichier);
                            _nomDuFichier = " ";
                            nom.SetText(_nomDuFichier);
                            isEnable = true;
                            s_nom_player.resize(0);
                            m_model->setGoToView(11);
                        }
                        break;
                    default:
                        break;

            }
        }

            m_window->Clear();
        if(m_model->getGoToView() == 0){
            sound.Pause();
            s_Presentation();
            s_boutonEditeur();
            affichageScore();
        }
        else if(m_model->getGoToView() == 1) {
            status = sound.GetStatus();
            s_boutton_son();
            if(isInLevelEditing)
                draw(m_editeur->getMatriceEditeur());
            else
                draw(m_model->getMatrice());
            s_quitte_inGame();
        }
        else if(m_model->getGoToView() == 2) {
            isInLevelEditing = false;
            isEnable = false;
            s_perteVie();
        }
        else if(m_model->getGoToView() == 3) {
            isInLevelEditing = false;
            isEnable = false;
             s_changeLvl();
        }
        else if(m_model->getGoToView() == 4) {
            isEnable = false;
             s_plusDeVie();
            m_window->Draw(nom);
        }
        else if(m_model->getGoToView() == 5) {
            isEnable = false;
            s_option();
            s_affichageLangue();
        }
        else if(m_model->getGoToView() == 6) {
            isInLevelEditing = false;
            isEnable = false;
            s_perteParTemps();
        }
        else if(m_model->getGoToView() == 7){
            isInLevelEditing = false;
            s_buttonInEdit();
            s_afficheFichierRecent();
        }
        else if(m_model->getGoToView() == 8){
            isInLevelEditing = true;
            draw(m_editeur->getMatriceEditeur());
            s_affiche_choix();
            s_bouton_save();
        }
        else if(m_model->getGoToView() == 9){
            s_inscrireNomFichier();
            m_window->Draw(nom);
        }
        else if(m_model->getGoToView() == 10){
            s_inscrireNomFichier();
            m_window->Draw(nom);
        }
        else if(m_model->getGoToView() == 11){
            isInLevelEditing = false;
            m_model->setMatrice(m_editeur->getMatriceEditeur());
            m_model->setEcranJeu(true);
            m_model->setGoToView(1);
        }
        m_window->Display();
    }
    return true;
}

}







// BAC À SABLE BALBLABLABLABLABLABALBALABALLLALALL

// MAIN TREAT MAIN TREAT MAIN TREAT MAIN TREAT MAIN TREAT MAIN TREAT MAIN TREAT MAIN TREAT
void GameView::Test(){
    if(initSprite()){
        _screen = 0;
        _refresh = true;
        while(m_window->IsOpened()){
            while(m_window->GetEvent(_event)){
                if(_event.Type == sf::Event::Closed || _screen == -1)
                    m_window->Close();

                switch (_screen) {
                    case 1:
                        //std::cout << "1" << std::endl; // ingame
                        eventGame();
                        initGame();
                        displayGame();
                        break;
                    case 2:
                        //std::cout << "2" << std::endl; // option
                        eventOption();
                        displayOption();
                        break;
                    default:
                        //std::cout << "0" << std::endl; // menu
                        eventMenu();
                        initMenu();
                        displayMenu();
                        break;
                }
                m_window->Display();
            }
        }
    }
    else{
        std::cout << "Erreur de chargement des images" << std::endl;
    }
}

// MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU MENU
void GameView::initMenu(){
    changeSprite(_start_sprite, WIDTH/2-_start_sprite.GetSize().x/2, HEIGHT/4);
    changeSprite(_exit_sprite, WIDTH/2-_exit_sprite.GetSize().x/2, HEIGHT/3);
}
void GameView::displayMenu(){
    m_window->Clear(sf::Color(255,255,255));
    m_window->Draw(_start_sprite);
    m_window->Draw(_exit_sprite);
}

void GameView::eventMenu(){
    if(onTheSprite(_start_sprite, _event.MouseButton.X, _event.MouseButton.Y)){
        _screen = 1;
    }
    else if(onTheSprite(_exit_sprite, _event.MouseButton.X, _event.MouseButton.Y)){
        _screen = -1;
    }
    else if((_event.Type == sf::Event::KeyPressed) && (_event.Key.Code == sf::Key::Escape)){
        _previousScreen = _screen;
        _screen = 2;
    }
}

// GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME GAME

void GameView::initGame(){
    changeSprite(_quitter_sprite, WIDTH-_quitter_sprite.GetSize().x/2-_quitter_sprite.GetSize().x, HEIGHT-_quitter_sprite.GetSize().y-_quitter_sprite.GetSize().y/2);
}



void GameView::displayGame(){
    m_window->Clear(sf::Color(0,0,0));
    m_window->Draw(_quitter_sprite);
    displayPlateau();
}

void GameView::eventGame(){
    if(onTheSprite(_quitter_sprite, _event.MouseButton.X, _event.MouseButton.Y)){
        _screen = 0;
    }
    else if((_event.Type == sf::Event::KeyPressed) && (_event.Key.Code == sf::Key::Escape)){
        _previousScreen = _screen;
        _screen = 2;
    }
    if(_event.Type == sf::Event::MouseButtonPressed && _event.MouseButton.Button == Mouse::Left){
        if(diggerEvent()){
            std::cout << "in-game" << std::endl;
        }
        else{
            m_model->genereMatrice();
            std::cout << "partie perdu" << std::endl;
        }
    }
}

void GameView::displayPlateau(){
    Case ***matrice = m_model->getMatrice();
    for(int li = 0; li < 18; li++){
        for(int col = 0; col < 18; col++){
            if(col == m_model->getPlayer().get_x() && li == m_model->getPlayer().get_y()){
                changeSprite(_digger_sprite, col*_digger_sprite.GetSize().x, li*_digger_sprite.GetSize().y);
                m_window->Draw(_digger_sprite);
            }
            else if(dynamic_cast<Bomb*>(matrice[li][col])){
                changeSprite(_bombe_sprite, col*_bombe_sprite.GetSize().x, li*_bombe_sprite.GetSize().y);
                m_window->Draw(_bombe_sprite);
            }
            else if(dynamic_cast<Croix*>(matrice[li][col])){
                changeSprite(_vide_sprite, col*_vide_sprite.GetSize().x, li*_vide_sprite.GetSize().y);
                m_window->Draw(_vide_sprite);
            }
            else if(dynamic_cast<BonusCase*>(matrice[li][col])){
                changeSprite(_bonus_sprite, col*_bonus_sprite.GetSize().x, li*_bonus_sprite.GetSize().y);
                m_window->Draw(_bonus_sprite);
            }
            else{
                changeSprite(_tuile_sprite, col*_tuile_sprite.GetSize().x, li*_tuile_sprite.GetSize().y);
                m_window->Draw(_tuile_sprite);
            }
        }
    }
}

bool GameView::diggerEvent(){
    if(onTheDiggerEAST()){
        if(m_model->datMove(1, 0)){
            std::cout << "EAST" << std::endl;
            return true;
        }
    }
    else if(onTheDiggerNORTH()){
        if(m_model->datMove(0, -1)){
            std::cout << "NORTH" << std::endl;
            return true;
        }
    }
    else if(onTheDiggerSOUTH()){
        if(m_model->datMove(0, 1)){
            std::cout << "SOUTH" << std::endl;
            return true;
        }
    }
    else if(onTheDiggerWEST()){
        if(m_model->datMove(-1, 0)){
            std::cout << "WEST" << std::endl;
            return true;
        }
    }
    else if(onTheDiggerDIAG_NORTH_WEST()){
        if(m_model->datMove(-1, -1)){
            std::cout << "NORTH_WEST" << std::endl;
            return true;
        }
    }
    else if(onTheDiggerDIAG_NORTH_EAST()){
        if(m_model->datMove(-1, 1)){
            std::cout << "NORTH_EAST" << std::endl;
            return true;
        }
    }
    else if(onTheDiggerDIAG_SOUTH_EAST()){
        if(m_model->datMove(1, 1)){
            std::cout << "SOUTH_EAST" << std::endl;
            return true;
        }
    }
    else if(onTheDiggerDIAG_SOUTH_WEST()){
        if(m_model->datMove(-1, 1)){
            std::cout << "SOUTH_WEST" << std::endl;
            return true;
        }
    }
    std::cout << "return false" << std::endl;
    return false;
}

bool GameView::onTheDiggerSOUTH(){
    return(_event.MouseButton.X >= _digger_sprite.GetPosition().x &&
           _event.MouseButton.X <= _digger_sprite.GetPosition().x + _digger_sprite.GetSize().x &&
           _event.MouseButton.Y >= _digger_sprite.GetPosition().y + _digger_sprite.GetSize().y &&
           _event.MouseButton.Y <= _digger_sprite.GetPosition().y + 2*_digger_sprite.GetSize().y);
}

bool GameView::onTheDiggerNORTH(){
    return(_event.MouseButton.X >= _digger_sprite.GetPosition().x &&
           _event.MouseButton.X <= _digger_sprite.GetPosition().x + _digger_sprite.GetSize().x &&
           _event.MouseButton.Y >= _digger_sprite.GetPosition().y - _digger_sprite.GetSize().y &&
           _event.MouseButton.Y <= _digger_sprite.GetPosition().y);
}

bool GameView::onTheDiggerWEST(){
    return(_event.MouseButton.X <= _digger_sprite.GetPosition().x &&
           _event.MouseButton.X >= _digger_sprite.GetPosition().x - _digger_sprite.GetSize().x &&
           _event.MouseButton.Y >= _digger_sprite.GetPosition().y &&
           _event.MouseButton.Y <= _digger_sprite.GetPosition().y + _digger_sprite.GetSize().y);
}

bool GameView::onTheDiggerEAST(){
    return(_event.MouseButton.X >= _digger_sprite.GetPosition().x + _digger_sprite.GetSize().x &&
           _event.MouseButton.X <= _digger_sprite.GetPosition().x + 2*_digger_sprite.GetSize().x &&
           _event.MouseButton.Y >= _digger_sprite.GetPosition().y &&
           _event.MouseButton.Y <= _digger_sprite.GetPosition().y + _digger_sprite.GetSize().y);
}

bool GameView::onTheDiggerDIAG_SOUTH_EAST(){
    return(_event.MouseButton.X <= _digger_sprite.GetPosition().x + 2*_digger_sprite.GetSize().x &&
           _event.MouseButton.X >= _digger_sprite.GetPosition().x + _digger_sprite.GetSize().x &&
           _event.MouseButton.Y >= _digger_sprite.GetPosition().y + _digger_sprite.GetSize().y &&
           _event.MouseButton.Y <= _digger_sprite.GetPosition().y + 2*_digger_sprite.GetSize().y);
}

bool GameView::onTheDiggerDIAG_SOUTH_WEST(){
    return(_event.MouseButton.X >= _digger_sprite.GetPosition().x - _digger_sprite.GetSize().x &&
           _event.MouseButton.X <= _digger_sprite.GetPosition().x &&
           _event.MouseButton.Y >= _digger_sprite.GetPosition().y + _digger_sprite.GetSize().y &&
           _event.MouseButton.Y <= _digger_sprite.GetPosition().y + 2*_digger_sprite.GetSize().y);
}

bool GameView::onTheDiggerDIAG_NORTH_WEST(){
    return(_event.MouseButton.X <= _digger_sprite.GetPosition().x &&
           _event.MouseButton.X >= _digger_sprite.GetPosition().x - _digger_sprite.GetSize().x &&
           _event.MouseButton.Y >= _digger_sprite.GetPosition().y-_digger_sprite.GetSize().y &&
           _event.MouseButton.Y <= _digger_sprite.GetPosition().y);
}

bool GameView::onTheDiggerDIAG_NORTH_EAST(){
    return(_event.MouseButton.X >= _digger_sprite.GetPosition().x + _digger_sprite.GetSize().x &&
           _event.MouseButton.X <= _digger_sprite.GetPosition().x + 2*_digger_sprite.GetSize().x &&
           _event.MouseButton.Y >= _digger_sprite.GetPosition().y - _digger_sprite.GetSize().y &&
           _event.MouseButton.Y <= _digger_sprite.GetPosition().y);
}


// OPTION OPTION OPTION OPTION OPTION OPTION OPTION OPTION OPTION OPTION OPTION OPTION OPTION OPTION

//void GameView::initOption(){
//}

void GameView::displayOption(){
    m_window->Clear(sf::Color(0,0,0));
    s_affichageLangue();
    s_option();
}

void GameView::eventOption(){
    if((_event.Type == sf::Event::KeyPressed) && (_event.Key.Code == sf::Key::Escape)){
        _screen = _previousScreen;
        _refresh = true;
    }
    else if(onTheSprite(_francais_sprite, _event.MouseButton.X, _event.MouseButton.Y)){
        m_langue->setNom("francais");
        m_l = m_langue->getlangues();
    }
    else if(onTheSprite(_anglais_sprite, _event.MouseButton.X, _event.MouseButton.Y)){
        m_langue->setNom("anglais");
        m_l = m_langue->getlangues();
    }
}




