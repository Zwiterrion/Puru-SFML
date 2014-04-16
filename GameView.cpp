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
    
    if(!_background_image.LoadFromFile("background.png") || !_digger_image.LoadFromFile("digger_face.png") || !_bombe_image.LoadFromFile("tuile_bombe.png") || !_bonus_image.LoadFromFile("tuile_bonus.png") || !_tuile_image.LoadFromFile("tuile.png") || !_exit_image.LoadFromFile("exitButton.png") || !_start_image.LoadFromFile("startButton.png") || !_vide_image.LoadFromFile("vide.png")) {
        
        cerr << "ERROR";
    }
    else {
        _background_sprite = Sprite (_background_image);
        _background_sprite.Resize(1024, 768);
        _background_sprite.SetPosition(0,0);
        
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
string GameView::afficheBonus() const
{
    ostringstream out;
    out << "Score Bonus :" << m_model->getLvl().get_score_bonus() << "\t\t\t\tBonus Temps: " << m_model->getLvl().get_b_temps() << "\t\t\t\tBonus Vie: " << m_model->getLvl().get_b_vie()  << "\nLevel : " << m_model->getLvl().getLevel();
    string s = out.str();
    return s;
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
string GameView::afficheScore() const
{
    ostringstream out;
     out<< "Les Scores  \n\nLe score déplacement: " << m_model->getScore().getDeplacement() << "\t\t\tLe score cible: " << m_model->getScore().getCible() << "\t\t\tLe score total: " << m_model->getScore().getScoreTotal() << endl;
    string s = out.str();
    return s;
}
void GameView::s_afficheScore()
{
    ostringstream out;
    out<< "Le score deplacement: " << m_model->getScore().getDeplacement() << "\nLe score cible: " << m_model->getScore().getCible() << "\t\t\nLe score total: " << m_model->getScore().getScoreTotal() << endl;
    affiche_Score = String(out.str());
    affiche_Score.SetPosition(WIDTH - 300, 200);
    
    affiche_Score.SetSize(25.0F);
    m_window->Draw(affiche_Score);
}

string GameView::viePlayer() const
{
    ostringstream out;
    out<< "\t\tVie du joueur: " << m_model->getPlayer().getVie();
    
    string s= out.str();
    return s;
}
void GameView::s_viePlayer()
{
    ostringstream out;
    out<< "Vie du joueur: " << m_model->getPlayer().getVie();
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
   
    Case ***matrice = m_model->getMatrice();
    /* Affichage */
    for(int i=0; i<18; i++){
        cout << ("\t\t\t\t|---");
        for(int k=0; k<17; k++)
            cout << "|---";
        cout <<"|" << endl << "\t\t\t\t";
        for(int j=0; j<18; j++){
            if(dynamic_cast<Bomb*>(matrice[i][j]))
                cout << "|" << "@@@";
            else if(m_model->getPlayer().get_x() == j && m_model->getPlayer().get_y() == i)
                cout << "|$$$";
            else if(dynamic_cast<BonusCase*>(matrice[i][j]))
                cout << "|" << matrice[i][j]->getObj();
            else
                cout << "| " << matrice[i][j]->getObj() << " ";
        }
        cout << "|" <<endl ;
    }
    cout << "\t\t\t\t|---";
    for(int k=0; k<17; k++)
        cout << "|---";
    cout << "|" <<endl ;
    
    for(int i=0; i<18; i++){
        for(int j=0; j<18; j++){
            if(dynamic_cast<Bomb*>(matrice[i][j])){
                _bombe_sprite.SetPosition(j*40,i*40);
                _bombe_sprite.SetColor(sf::Color(255,255,255,128));
                m_window->Draw(_bombe_sprite);
            }
            else if(m_model->getPlayer().get_x() == j && m_model->getPlayer().get_y() == i){
                _digger_sprite.SetPosition(j*40, i*40);
                m_window->Draw(_digger_sprite);
            }
            else if(dynamic_cast<BonusCase*>(matrice[i][j])){
                ostringstream out;
                out << matrice[i][j]->getObj();
                String s = String(out.str());
                s.SetPosition(j*40, i*40);
                _bonus_sprite.SetPosition(j*40,i*40);
                _bonus_sprite.SetColor(sf::Color(77,77,77,128));
                m_window->Draw(_bonus_sprite);
                m_window->Draw(s);
            }
            else if(dynamic_cast<Croix*>(matrice[i][j]))
            {
                _vide_sprite.SetPosition(j*40, i*40);
                _vide_sprite.SetColor(sf::Color(246,246,246,128));
                m_window->Draw(_vide_sprite);
            }
            else{
                ostringstream out;
                out << matrice[i][j]->getObj();
                String s = String(out.str());
                s.SetPosition(j*40 + 10, i*40);
                _tuile_sprite.SetPosition(j*40,i*40);
                _tuile_sprite.SetColor(sf::Color(192,192,192,128));
                m_window->Draw(_tuile_sprite);
                m_window->Draw(s);
            }
        }
   
    }
    s_afficheBonus();
    s_afficheScore();
    s_viePlayer();
    m_window->Display();

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
    titre.SetPosition(1024/2 - 325 ,768/2 - 200);
    m_window->Draw(titre);
    
    /*jouer = String("Jouer");
    jouer.SetColor(sf::Color(200,200,200));
    jouer.SetFont(_font);
    jouer.SetSize(40.0f);
    jouer.SetPosition(1024/2 - 200, 768/2);
    m_window->Draw(jouer);
    
    quitter = String("Quitter");
    quitter.SetColor(sf::Color(200,200,200));
    quitter.SetFont(_font);
    quitter.SetSize(40.0f);
    quitter.SetPosition(1024/2 + 100, 768/2);
    m_window->Draw(quitter);
    */
    
    _start_sprite.SetPosition(1024/2 -300, 768/2);
    m_window->Draw(_start_sprite);
    
    _exit_sprite.SetPosition(1024/2 +100, 768/2);
    m_window->Draw(_exit_sprite);
    
    
    m_window->Display();
}
/************************************************************
 * Nom: rejouer                                             *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle: Affiche la question                                *
 ************************************************************/
 void GameView::rejouer()
{
    cout << "Vous avez perdu ou décider d'abandonner" << endl;
    cout << " Voulez rejouer ? " << endl;
    cout << " Quitter: 1 " << "\t" << "Rejouer: 0" << endl;
}
void GameView::s_rejouer()
{
    ostringstream out;
    out << "Vous avez perdu ou décider d'abandonner !" << "\nVoulez rejouer ? ";
    _start_sprite.SetPosition(1024/2 -300, 768/2);
    m_window->Draw(_start_sprite);
    
    _exit_sprite.SetPosition(1024/2 +100, 768/2);
    m_window->Draw(_exit_sprite);
    
    string s = out.str();
    _abandon = String(s);
    
    _abandon.SetPosition(1024/2, 768/2 - 200);
    _abandon.SetSize(80.0f);
    
    m_window->Draw(_abandon);    
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
    fstream f;
    f.open("scores.txt", ios::in); // ouverture du fichier en ecriture ficNb
    if( f.fail() )
    {// Si probleme afficher une erreur
        cerr << "ouverture en lecture impossible" << endl;
        f.close();
    }
    string phrase;
    f >> phrase;
    while(!f.eof()){
        cout << phrase << endl;
        f >> phrase;
    }
    cout << endl;

    f.close(); // fermeture du fichier
}
/************************************************************
 * Nom: retourMenu                                          *
 ************************************************************
 * Type: void                                               *
 ************************************************************
 * Rôle: Affiche une question et un choix menu              *
 ************************************************************/
void GameView::retourMenu()
{
    cout << "\n\nVoulez-vous quitter ou jouer ?" << endl;
    cout  << "Jouer: 0" << "\tQuitter: 1 " << endl;
}

void GameView::perteVie()
{
    cout << " \nVous venez de perdre une vie !" << endl;
    cout << " Voulez-vous continuer ?" << endl;
    cout << " Continuer: 0 \t\t\t Quitter: 1" << endl;
}
void GameView::s_perteVie()
{
    m_window->Clear(sf::Color(20,20,20));
    sf::String perte = String(" \nVous venez de perdre une vie !\n\n Voulez-vous continuer ?");
    perte.SetPosition(WIDTH/2, HEIGHT/2);
    m_window->Draw(perte);
    m_window->Display();
}
void GameView::changementLevel()
{
    cout << "\nVous avez changé de niveau " << endl;
    cout << "Continuer :0 \t\t\t Quitter: 1" << endl;
}
void GameView::s_changeLvl()
{
    sf::String text = String("Vous avez change de niveau ! ");
    text.SetSize(50.0f);
    text.SetPosition(WIDTH/2 -350, HEIGHT/2 -50);
    m_window->Draw(text);
    m_window->Display();
}
void GameView::plusDeVie()
{
    cout << "\n Vous n'avez plus de vies. Fin de Jeu." << endl;
    cout << "\nVeuillez rentrez votre nom" << endl;
}
bool GameView::treatEvents()
{
    while (m_window->IsOpened())
    {
        // Process events
        sf::Event e;
        while (m_window->GetEvent(e))
        {
            // Close window : exit
            if (e.Type == sf::Event::Closed)
                m_window->Close();
            
            if(e.Type == sf::Event::MouseButtonPressed){
                if(e.MouseButton.Button == Mouse::Left){
                    if((e.MouseButton.X < (_start_sprite.GetPosition().x +_start_sprite.GetSize().x ) && e.MouseButton.X > _start_sprite.GetPosition().x )&& (e.MouseButton.Y > _start_sprite.GetPosition().y && e.MouseButton.Y < _start_sprite.GetPosition().y + _start_sprite.GetSize().y)){
                        m_window->Clear(sf::Color(40,40,38));
                        draw();
                    }
                    if(m_model->getEndGame()){
                    if((e.MouseButton.X < (_exit_sprite.GetPosition().x +_exit_sprite.GetSize().x ) && e.MouseButton.X > _exit_sprite.GetPosition().x )&& (e.MouseButton.Y > _exit_sprite.GetPosition().y && e.MouseButton.Y < _exit_sprite.GetPosition().y + _exit_sprite.GetSize().y )){
                        m_window->Close();
                    }

                        if((e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x ) && e.MouseButton.X > _digger_sprite.GetPosition().x ) && (e.MouseButton.Y < _digger_sprite.GetPosition().y && e.MouseButton.Y > _digger_sprite.GetPosition().y - 40)){
                            m_model->direction("N");
                            m_window->Clear(sf::Color(40,40,38));
                            draw();

                        }
                        if((e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x ) && e.MouseButton.X > _digger_sprite.GetPosition().x ) && (e.MouseButton.Y > (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y) && e.MouseButton.Y < (_digger_sprite.GetPosition().y) + _digger_sprite.GetSize().y + 40)){
                            m_model->direction("S");
                            m_window->Clear(sf::Color(40,40,38));
                            draw();

                        }
                        if((e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x + 40) && e.MouseButton.X > (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x)) && (e.MouseButton.Y > _digger_sprite.GetPosition().y && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y))){
                            m_model->direction("E");
                            m_window->Clear(sf::Color(40,40,38));
                            draw();

                        }
                    
                        if((e.MouseButton.X > (_digger_sprite.GetPosition().x + -40) && e.MouseButton.X < _digger_sprite.GetPosition().x  && e.MouseButton.Y > _digger_sprite.GetPosition().y && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y))){
                            m_model->direction("O");
                            m_window->Clear(sf::Color(40,40,38));
                            draw();
                            
                        }
                    
                        if(e.MouseButton.X > (_digger_sprite.GetPosition().x + -40) && e.MouseButton.X < _digger_sprite.GetPosition().x  && e.MouseButton.Y < _digger_sprite.GetPosition().y && e.MouseButton.Y > (_digger_sprite.GetPosition().y - 40)){
                            m_model->direction("NO");
                            m_window->Clear(sf::Color(40,40,38));
                            draw();
                            
                        }
                    
                        if(e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x + 40) && e.MouseButton.X > (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x)  && e.MouseButton.Y < _digger_sprite.GetPosition().y && e.MouseButton.Y > (_digger_sprite.GetPosition().y - 40)){
                            m_model->direction("NE");
                            m_window->Clear(sf::Color(40,40,38));
                            draw();

                        }
                    
                        if(e.MouseButton.X > (_digger_sprite.GetPosition().x + -40) && e.MouseButton.X < _digger_sprite.GetPosition().x  && e.MouseButton.Y > (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y) && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y + 40)){
                            m_model->direction("SO");
                            m_window->Clear(sf::Color(40,40,38));
                            draw();

                        }
                        if(e.MouseButton.X < (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x + 40) && e.MouseButton.X > (_digger_sprite.GetPosition().x +_digger_sprite.GetSize().x) && e.MouseButton.Y > (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y) && e.MouseButton.Y < (_digger_sprite.GetPosition().y + _digger_sprite.GetSize().y + 40)){
                            m_model->direction("SE");
                            m_window->Clear(sf::Color(40,40,38));
                            draw();
                            
                        }
                    }
                }
            }
        }
    }
    return true;
}





