#include "GameView.h"
#include "GameModel.h"
#include "Const.h"
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

    m_window->Clear(sf::Color(20,20,20));
    
    if(!_background_image.LoadFromFile("background.png") || !_digger_image.LoadFromFile("digger_face.png") || !_bombe_image.LoadFromFile("tuile_bombe.png") || !_bonus_image.LoadFromFile("tuile_bonus.png") || !_tuile_image.LoadFromFile("tuile.png") || !_exit_image.LoadFromFile("exitButton.png") || !_start_image.LoadFromFile("startButton.png") || !_vide_image.LoadFromFile("vide.png") || !_option_image.LoadFromFile("optionButton.png") || !_menu_image.LoadFromFile("menu.png") || !Buffer.LoadFromFile("music.wav") || !bonus.LoadFromFile("bonus.wav") || !_bestScore_image.LoadFromFile("bestScore.png")) {
        
        cerr << "ERROR";
    }
    else {
        _background_sprite = Sprite (_background_image);
        _bestScore_sprite = Sprite(_bestScore_image);
        _option_sprite = Sprite(_option_image);
        _menu_sprite = Sprite(_menu_image);
        _digger_sprite = Sprite(_digger_image);
        _bombe_sprite = Sprite(_bombe_image);
        _tuile_sprite = Sprite(_tuile_image);
        _bonus_sprite = Sprite(_bonus_image);
        _exit_sprite = Sprite(_exit_image);
        _start_sprite = Sprite(_start_image);
        _vide_sprite = Sprite(_vide_image);
    }

    _background_sprite.Resize(38, 38);
    _digger_sprite.Resize(38, 38);
    _bombe_sprite.Resize(38, 38);
    _tuile_sprite.Resize(38, 38);
    _bonus_sprite.Resize(38, 38);
    _vide_sprite.Resize(38, 38);
    
    
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
    out << "Score Bonus :" << m_model->getLvl().get_score_bonus() << "\nBonus Temps: " << m_model->getLvl().get_b_temps() << "\nBonus Vie: " << m_model->getLvl().get_b_vie()  << "\nLevel : " << m_model->getLvl().getLevel();
    affiche_Bonus = String(out.str());
    affiche_Bonus.SetPosition(WIDTH - 300, 100);
    
    affiche_Bonus.SetSize(25.0F);
    m_window->Draw(affiche_Bonus);
}
void GameView::s_afficheScore()
{
    ostringstream out;
    out<< "Le score deplacement: " << m_model->getScore().getDeplacement() << "\nLe score cible: " << m_model->getScore().getCible() << "\t\t\nLe score total: " << m_model->getScore().getScoreTotal() << "\nTemps restant : " << m_model->getLvl().getTemps() << endl;
    affiche_Score = String(out.str());
    affiche_Score.SetPosition(WIDTH - 300, 200);
    
    affiche_Score.SetSize(25.0F);
    m_window->Draw(affiche_Score);
}
void GameView::s_viePlayer()
{
    ostringstream out;
    out<< "\nVie du joueur: " << m_model->getPlayer().getVie();
    _vie_player = String(out.str());
    _vie_player.SetPosition(WIDTH - 300, 275);
    
    _vie_player.SetSize(25.0F);
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
void GameView::draw()
{
   
    // Image background
    _background_sprite.Resize(WIDTH, HEIGHT);
    _background_sprite.SetPosition(0,0);
    _background_sprite.SetColor(sf::Color(126,126,126,128));
    m_window->Draw(_background_sprite);
    
    Case ***matrice = m_model->getMatrice();
    
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
                _bombe_sprite.SetPosition(j*WIDTH_PIECE,i*WIDTH_PIECE);
                _bombe_sprite.SetColor(sf::Color(255,255,255,128));
                
                Sprite *bomb = &_bombe_sprite;
                images.push_back(bomb);
                m_window->Draw(*bomb);
            }
            else if(dynamic_cast<BonusCase*>(matrice[i][j])){
                ostringstream out;
                out << matrice[i][j]->getObj();
                String s = String(out.str());
                s.SetPosition(j*WIDTH_PIECE, i*WIDTH_PIECE);
                
                _bonus_sprite.SetPosition(j*WIDTH_PIECE,i*WIDTH_PIECE);
                _bonus_sprite.SetColor(sf::Color(77,77,77,128));
                Sprite *bonus = &_bonus_sprite;
                images.push_back(bonus);
                m_window->Draw(*bonus);
                m_window->Draw(s);
            }
            else if(dynamic_cast<Croix*>(matrice[i][j]))
            {
                _vide_sprite.SetPosition(j*WIDTH_PIECE, i*WIDTH_PIECE);
                if(m_window->GetInput().IsMouseButtonDown(sf::Mouse::Left)){
                    _vide_sprite.Move(0, 3);
                }
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
                s.SetPosition(j*WIDTH_PIECE + 10, i*WIDTH_PIECE);
                _tuile_sprite.SetPosition(j*WIDTH_PIECE,i*WIDTH_PIECE);
                _tuile_sprite.SetColor(sf::Color(192,192,192,128));
                Sprite *tuile = &_tuile_sprite;
                images.push_back(tuile);
                m_window->Draw(*tuile);
                m_window->Draw(s);
            }
        }
   
    }
    if(m_model->getPlayer().get_y()*WIDTH_PIECE < 18*WIDTH_PIECE && m_model->getPlayer().get_x()*WIDTH_PIECE < 18*WIDTH_PIECE){
        sf::Image image;
        image.LoadFromFile("tuile_bonus.png");
        sf::Sprite sprite = Sprite(image);
        sprite.Resize(38, 38);
        sprite.SetPosition(m_model->getPlayer().get_x()*WIDTH_PIECE, m_model->getPlayer().get_y()*WIDTH_PIECE);
         m_window->Draw(sprite);
        _digger_sprite.SetPosition(((m_model->getPlayer().get_x()*WIDTH_PIECE)), (m_model->getPlayer().get_y()*WIDTH_PIECE));
    }
    
    Sprite *dig = &_digger_sprite;
    images.push_back(dig);
    m_window->Draw(*dig);
    
    s_afficheBonus();
    s_afficheScore();
    s_viePlayer();
    
   // m_window->Display();

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
    titre = String("Puru Puru Digger");
    titre.SetColor(sf::Color(200,200,200));
    titre.SetFont(_font);
    titre.SetSize(80.0f);
    
    
    titre.SetPosition(50 , 50);
    _option_sprite.SetPosition(100, 400);
    _start_sprite.SetPosition(100, 250);
    _exit_sprite.SetPosition(100, 550);
    _bestScore_sprite.SetPosition(WIDTH/2, 200);
    
    m_window->Draw(_option_sprite);
    m_window->Draw(_start_sprite);
    m_window->Draw(_exit_sprite);
    m_window->Draw(titre);
    m_window->Draw(_bestScore_sprite);
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
    out << "Vous avez perdu ou décider d'abandonner !" << "\nVoulez rejouer ? ";
    _start_sprite.SetPosition(WIDTH/2 -300, HEIGHT/2);
    m_window->Draw(_start_sprite);
    
    _exit_sprite.SetPosition(WIDTH/2 +100, HEIGHT/2);
    m_window->Draw(_exit_sprite);
    
    string s = out.str();
    _abandon = String(s);
    
    _abandon.SetPosition(WIDTH/2, HEIGHT/2 - 200);
    _abandon.SetSize(80.0f);
    
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
    
    jouer = String("Jouer");
    jouer.SetSize(40);
    jouer.SetPosition((WIDTH/2)-300, HEIGHT/2+50);
    jouer.SetColor(sf::Color(125, 205, 128));
    
    quitter = String("Quitter");
    quitter.SetSize(40);
    quitter.SetPosition((WIDTH/2)+100, HEIGHT/2+50);
    quitter.SetColor(sf::Color(125, 205, 128));
    
    m_window->Clear(sf::Color(20,20,20));
    sf::String perte = String(" \nVous venez de perdre une vie !");
    sf::String suite = String("Voulez-vous continuer ?");
    suite.SetPosition(WIDTH/2 - 250, HEIGHT/2-30);
    perte.SetPosition(WIDTH/2 - 300, HEIGHT/2-150);
    perte.SetSize(40);
    suite.SetSize(40);

    m_window->Draw(suite);
    m_window->Draw(perte);
    m_window->Draw(jouer);
    m_window->Draw(quitter);
}
void GameView::s_changeLvl()
{
    jouer = String("Jouer");
    jouer.SetSize(40);
    jouer.SetPosition((WIDTH/2)-300, HEIGHT/2+50);
    
    
    quitter = String("Quitter");
    quitter.SetSize(40);
    quitter.SetPosition((WIDTH/2)+100, HEIGHT/2+50);
    
    sf::String text = String("Vous avez change de niveau ! ");
    text.SetSize(50.0f);
    text.SetPosition(WIDTH/2 -350, HEIGHT/2 -50);
    m_window->Draw(text);
    m_window->Draw(jouer);
    m_window->Draw(quitter);
}
void GameView::s_plusDeVie()
{
    ostringstream out;
    out << "Vous n'avez plus de vies. Entrez Votre nom :";
    String text = String(out.str());
    text.SetPosition(WIDTH/2-400, HEIGHT/2- 100);
    nom.SetPosition(WIDTH/2-150, HEIGHT/2);
    nom.SetSize(40);
    text.SetSize(40);
    
    m_window->Draw(text);
}
void GameView::s_perteParTemps()
{
    
    jouer = String("Jouer");
    jouer.SetSize(40);
    jouer.SetPosition((WIDTH/2)-300, HEIGHT/2+50);
    jouer.SetColor(sf::Color(125, 205, 128));
    
    quitter = String("Quitter");
    quitter.SetSize(40);
    quitter.SetPosition((WIDTH/2)+100, HEIGHT/2+50);
    quitter.SetColor(sf::Color(125, 205, 128));
    
    m_window->Clear(sf::Color(20,20,20));
    sf::String perte = String(" \nPlus de Temps. Perte de Vie!");
    sf::String suite = String("Voulez-vous continuer ?");
    suite.SetPosition(WIDTH/2 - 250, HEIGHT/2-30);
    perte.SetPosition(WIDTH/2 - 300, HEIGHT/2-150);
    perte.SetSize(40);
    suite.SetSize(40);
    
    m_window->Draw(suite);
    m_window->Draw(perte);
    m_window->Draw(jouer);
    m_window->Draw(quitter);
}
void GameView::s_option()
{
    String e = String("Option");
    e.SetColor(sf::Color(200,200,200));
    e.SetFont(_font);
    e.SetSize(80.0f);
    e.SetPosition(WIDTH/2-150,HEIGHT/2 - 200);
    
    _menu_sprite.SetPosition(WIDTH/2-100, HEIGHT/2 + 250);
    m_window->Draw(_menu_sprite);
    
    m_window->Draw(e);
}
void GameView::s_chargementScore()
{
    fstream f;
    f.open("/Users/Etienne/Desktop/Puru-SFML/meilleursScores.txt", ios::in);
    
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
               // cout << "ICI";
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
            distance+=50;
            m_window->Draw(score);
        }
        numero++;
    }
    afficherScore = false;

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
    f.open( "/Users/Etienne/Desktop/Puru-SFML/meilleursScores.txt", ios::out | ios::app ); // ouverture du fichier en ecriture ficNb
    if( f.fail() )
    {
        cerr << "ouverture en lecture impossible" << endl;
        f.close();
    }
    f << s_nom << endl;
    f << m_model->getScore().getScoreTotal() << endl;
    f.close();
}
bool GameView::treatEvents()
{
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
                            
                            if((e.MouseButton.X < (_start_sprite.GetPosition().x +_start_sprite.GetSize().x ) && e.MouseButton.X > _start_sprite.GetPosition().x )&& (e.MouseButton.Y > _start_sprite.GetPosition().y && e.MouseButton.Y < _start_sprite.GetPosition().y + _start_sprite.GetSize().y)){
                                m_model->setEcranJeu(true);
                                m_model->setGoToView(1);
                                isEnable = true;
                            }
                            
                            if((e.MouseButton.X < (_exit_sprite.GetPosition().x +_exit_sprite.GetSize().x ) && e.MouseButton.X > _exit_sprite.GetPosition().x )&& (e.MouseButton.Y > _exit_sprite.GetPosition().y && e.MouseButton.Y < _exit_sprite.GetPosition().y + _exit_sprite.GetSize().y )  && m_model->getEcranJeu() == false){
                                m_window->Close();
                            }
                            if((e.MouseButton.X < (_option_sprite.GetPosition().x + _option_sprite.GetSize().x ) && e.MouseButton.X >  _option_sprite.GetPosition().x )&& (e.MouseButton.Y >  _option_sprite.GetPosition().y && e.MouseButton.Y <  _option_sprite.GetPosition().y + _option_sprite.GetSize().y )  && m_model->getEcranJeu() == false){
                                s_option();
                                m_model->setGoToView(5);
                            }
                        }
                    case 1:

                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() ){
                            
                            if((e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x ) && e.MouseButton.X > _digger_sprite.GetPosition().x ) && (e.MouseButton.Y < _digger_sprite.GetPosition().y && e.MouseButton.Y > _digger_sprite.GetPosition().y - 40)){
                                m_model->direction("N");
                            }
                            if((e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x ) && e.MouseButton.X > _digger_sprite.GetPosition().x ) && (e.MouseButton.Y > (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y) && e.MouseButton.Y < (_digger_sprite.GetPosition().y) + _digger_sprite.GetSize().y + 40)){
                                m_model->direction("S");

                            }
                            if((e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x + 40) && e.MouseButton.X > (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x)) && (e.MouseButton.Y > _digger_sprite.GetPosition().y && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y))){
                                m_model->direction("E");
                
                            }
                            
                            if((e.MouseButton.X > (_digger_sprite.GetPosition().x + -40) && e.MouseButton.X < _digger_sprite.GetPosition().x  && e.MouseButton.Y > _digger_sprite.GetPosition().y && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y))){
                                m_model->direction("O");
                     
                            }
                            
                            if(e.MouseButton.X > (_digger_sprite.GetPosition().x + -40) && e.MouseButton.X < _digger_sprite.GetPosition().x  && e.MouseButton.Y < _digger_sprite.GetPosition().y && e.MouseButton.Y > (_digger_sprite.GetPosition().y - 40)){
                                m_model->direction("NO");
                       
                            }
                            
                            if(e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x + 40) && e.MouseButton.X > (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x)  && e.MouseButton.Y < _digger_sprite.GetPosition().y && e.MouseButton.Y > (_digger_sprite.GetPosition().y - 40)){
                                m_model->direction("NE");
                            
                            }
                            
                            if(e.MouseButton.X > (_digger_sprite.GetPosition().x + -40) && e.MouseButton.X < _digger_sprite.GetPosition().x  && e.MouseButton.Y > (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y) && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y + 40)){
                                m_model->direction("SO");
                          
                            }
                            if(e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x + 40) && e.MouseButton.X > (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x) && e.MouseButton.Y > (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y) && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y + 40)){
                                m_model->direction("SE");
                          
                            }
                        }
                        break;
                    case 2:
                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() == false){
                            if((e.MouseButton.X < (jouer.GetPosition().x + jouer.GetRect().GetWidth() ) && e.MouseButton.X > jouer.GetPosition().x )&& (e.MouseButton.Y > jouer.GetPosition().y && e.MouseButton.Y < jouer.GetPosition().y + jouer.GetRect().GetHeight())){
                                m_model->genereMatrice();
                                m_model->setGoToView(1);
                                m_model->setEcranJeu(true);
                                isEnable = true;
                            }
                            
                            if((e.MouseButton.X < (quitter.GetPosition().x + 150) && e.MouseButton.X > quitter.GetPosition().x )&& (e.MouseButton.Y > quitter.GetPosition().y && e.MouseButton.Y < 50 + quitter.GetPosition().y)  && m_model->getEcranJeu() == false){
                                m_window->Close();
                            }
                            
                        }
                        break;
                    case 3:
                    
                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() == false){
                            if((e.MouseButton.X < (jouer.GetPosition().x + 150 ) && e.MouseButton.X > jouer.GetPosition().x )&& (e.MouseButton.Y > jouer.GetPosition().y && e.MouseButton.Y < jouer.GetPosition().y + 50)){
                                m_model->genereMatrice();
                                m_model->setGoToView(1);
                                m_model->setEcranJeu(true);
                                isEnable = true;
                            }
                            
                            
                            if((e.MouseButton.X < (quitter.GetPosition().x + 150) && e.MouseButton.X > quitter.GetPosition().x )&& (e.MouseButton.Y > quitter.GetPosition().y && e.MouseButton.Y < quitter.GetPosition().y + 50)  && m_model->getEcranJeu() == false){
                                m_window->Close();
                            }
                            
                        }
                        break;
                    case 4:
                        if(e.Type == sf::Event::TextEntered){
                            if(s_nom.length() <= 9)
                            {
                                s_nom += static_cast<char>(e.Text.Unicode);
                                nom.SetText(s_nom);
                            }
                        }
                        if ((e.Type == sf::Event::KeyPressed) && (e.Key.Code == sf::Key::Back)) {
                            if(s_nom.length() > 0){
                                s_nom.erase(s_nom.length()-1,1);
                                nom.SetText(s_nom);
                                if(s_nom.length() >= 1)
                                    s_nom.resize(s_nom.length()-1);
                            }
                        }
                        if(e.Type == sf::Event::KeyPressed  && (e.Key.Code == sf::Key::Return)) {
                            s_nom.clear();
                            afficherScore = true;
                            s_sauvegarde_score();
                            m_model->setEcranJeu(false);
                            m_model->rejouerPartie();
                            m_model->setGoToView(0);
                        }
                        break;
                   
                    case 5:
                        // Menu dans l'écran Option
                        if((e.MouseButton.X < (_menu_sprite.GetPosition().x +_menu_sprite.GetSize().x ) && e.MouseButton.X > _menu_sprite.GetPosition().x )&& (e.MouseButton.Y > _menu_sprite.GetPosition().y && e.MouseButton.Y < _menu_sprite.GetPosition().y + _menu_sprite.GetSize().y )){
                            m_model->setGoToView(0);
                        }
                        if (e.Type == sf::Event::Closed)
                            m_window->Close();
                        break;
                    case 6:
                        if(e.Type == sf::Event::MouseButtonPressed && e.MouseButton.Button == Mouse::Left && m_model->getEcranJeu() == false){
                            if((e.MouseButton.X < (jouer.GetPosition().x + jouer.GetRect().GetWidth() ) && e.MouseButton.X > jouer.GetPosition().x )&& (e.MouseButton.Y > jouer.GetPosition().y && e.MouseButton.Y < jouer.GetPosition().y + jouer.GetRect().GetHeight())){
                                m_model->genereMatrice();
                                m_model->setGoToView(1);
                                m_model->setEcranJeu(true);
                                isEnable = true;
                            }
                            
                            if((e.MouseButton.X < (quitter.GetPosition().x + 150) && e.MouseButton.X > quitter.GetPosition().x )&& (e.MouseButton.Y > quitter.GetPosition().y && e.MouseButton.Y < 50 + quitter.GetPosition().y)  && m_model->getEcranJeu() == false){
                                m_window->Close();
                            }
                            
                        }
                        break;
                    default:
                        break;
                
            }
        }
        
        m_window->Clear();
        if(m_model->getGoToView() == 0){
            s_Presentation();
            affichageScore();
        }
        else if(m_model->getGoToView() == 1) {
            status = sound.GetStatus();
            if(status != sf::Music::Playing)
                sound.Play();
            draw();
        }
        else if(m_model->getGoToView() == 2) {
            isEnable = false;
            s_perteVie();
        }
        else if(m_model->getGoToView() == 3) {
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
        }
        else if(m_model->getGoToView() == 6) {
            isEnable = false;
            s_perteParTemps();
        }
        m_window->Display();
    }
    return true;
}








