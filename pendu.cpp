#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <random>
#include <stdlib.h>

using namespace std;

const int pendu_length=17;
const int number_of_pendu=7;
const int number_of_words=23;
string pendu_list[number_of_pendu*pendu_length];
string dictionnary[number_of_words];

// Lire le fichier contenant les différentes représentations du pendu
void create_pendu_list()
{
    ifstream pendu;
    pendu.open("pendu.txt");

    if(!pendu.fail())
    {
        for (int i=0; i<number_of_pendu*pendu_length; i++)
        {
            getline(pendu,pendu_list[i]);
        }

    }
    pendu.close();
}

// Lire le fichier contenant le dictionnaire
void create_dictionnary()
{
    ifstream dic;
    dic.open("dictionnaire.txt");

    if(!dic.fail())
    {
        for (int i=0; i<number_of_words; i++)
        {
            dic >> dictionnary[i];
        }

    }
    dic.close();
}

// Afficher l'une des représentations du pendu
void display_pendu(int number)
{
    for (int i=number*pendu_length; i<number*pendu_length+pendu_length; i++)
    {
        cout << pendu_list[i] << endl;
    }
    cout << endl;
}

// Formatter le mot à deviner pour une meilleur lisibilité
string format_word(string mot)
{
    string txt="";
    for (int i=0; i<mot.length(); i++)
    {
        txt+=toupper(mot[i]);
        txt+=' ';
    }

    return txt;
}

// Cacher les lettres du mots à deviner
string hide_word(string mot)
{
    string txt="";
    for (int i=0; i<mot.length(); i++)
    {
        txt+='_';
    }

    return txt;
}

// Ajouter les lettres trouvées dans le mot
string add_letters(char letter, string word, string hidden_word)
{
    for (int i=0; i<word.length(); i++)
    {
        if (toupper(letter)==word[i])
        {
            hidden_word[i] = word[i];
        }
    }

    return hidden_word;
}

int main()
{

    // Ouvrir et lire fichiers dictionnaire et pendu
    create_pendu_list();
    create_dictionnary();
    // Initialisation
    int errors = 5;
    char letter;

    // Message de bienvenue
    cout << "Bienvenue dans le Jeu du Pendu!" << endl << endl;
    cout << "Tu as droit a 6 erreurs maximum par mot. On t'aide un peu avec un theme: \"MAISON\"!" << endl;
    cout << "A toi de jouer et bonne chance!" << endl << endl;

    char ans='y';

    while (toupper(ans)=='Y')
    {
        // Initialisation
        errors = 5;
        srand (time(NULL));
        int i = rand()%number_of_words;

        string word_to_guess = format_word(dictionnary[i]);
        string word_hidden = format_word(hide_word(dictionnary[i]));

        while (errors>-1)
        {
            // Affichage du pendu
            display_pendu(errors+1);
            cout << word_hidden << endl << endl;

            // L'utilisateur entre une lettre et on compare
            cout << "Entrer une lettre : ";
            cin >> letter;
            string word = add_letters(letter, word_to_guess, word_hidden);

            // Si le mot à trouver est inchangé, alors la lettre entrée n'a pas été trouvée
            if (word_hidden==word)
            {
                errors--;
                cout << "\'" << letter << "\' ne fait pas partie de ce mot." << endl;
            }
            // Sinon, alors on modifie le mot à trouver
            else
            {
                cout << "\'" << letter << "\' fait bien partie de ce mot." << endl;
                word_hidden = word;

                if (word_hidden==word_to_guess)
                    break;
            }

            cout << "Vous n'avez plus droit qu'a " << errors << " erreurs.\n" << endl;
        }

        // Gagné ou perdu?
        if (errors>=0)
            cout << "Felicitations, vous avez devine juste! Le mot etait bien: " << word_to_guess << endl;
        else
            display_pendu(0);;

        // Recommencer la partie
        cout << "La partie est terminee! Voulez-vous tenter votre chance une nouvelle fois (y/n)?";
        cin >> ans;
    }

    return 0;
}
