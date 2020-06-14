#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

enum TypeOfNetwork { Global, Local };

class User {

public:
    User(string name, TypeOfNetwork id) {
        NetworkID = id;
        this->name = name;
    }

    TypeOfNetwork getNetworkID() {
        return NetworkID;
    }
    string getName() {
        return name;
    }

    void checkAccess() {
        if (NetworkID == Global) {
            cout << "Пользователь " << getName() << " находится во внешней сети. Доступ только к списку журналов.\n";
        }
        else {
            cout << "Пользователь " << getName() << " находится во внутренней сети. Доступ к списку журналов, списку статей"
                << " и скачиванию статей\n";
        }
    }
private:
        TypeOfNetwork NetworkID;
        string name;
};



class RealHseLibrary {
private:
    vector<string> articles = { "article1", "article2", "article3" };
    vector<string> magazines = { "magazine1", "magazine2", "magazine3" };
public:
    void showArticles() {
        cout << "Cписок статей:\n";
        for (int i = 0; i < articles.size(); i++) {
            cout << articles[i] << "\n";
        }
    }

    void showMagazines() {
        cout << "Cписок журналов:\n";
        for (int i = 0; i < magazines.size(); i++) {
            cout << magazines[i] << "\n";
        }
    }

    void downloadArticle(string article) {
        
        auto found = std::find(std::begin(articles), std::end(articles),article);
        if (found != end(articles)) {
            cout << "Статья: " << article <<  " скачивается\n";
        }
        else {
            cout << "Такой статьи нет\n";
        }
    }

};

class ProxyLibrary {
    RealHseLibrary realLibrary;
public:
    void showArticles(User& user) {
        if (user.getNetworkID() == Global) {
            cout << "Пользователь " << user.getName() << " находится во внешней сети. Доступ к списку статей запрещен.\n";
        }
        else {
            cout << "Пользователь " << user.getName() << " находится во внутренней сети. Доступ к списку статей разрешен.\n";
            realLibrary.showArticles();
        }
    }
    void showMagazines(User& user) {
        if (user.getNetworkID() == Global) {
            cout << "Пользователь " << user.getName() << " находится во внешней сети. Доступ к списку журналов разрешен.\n";
            realLibrary.showMagazines();
        }
        else {
            cout << "Пользователь " << user.getName() << " находится во внутренней сети. Доступ к списку журналов разрешен.\n";
            realLibrary.showMagazines();
        }
    }

    void downloadArticle(User & user, string article) {
        if (user.getNetworkID() == Global) {
            cout << "Пользователь " << user.getName() << " находится во внешней сети. Доступ к скачиванию статей запрещен.\n";
        }
        else {
            cout << "Пользователь " << user.getName() << " находится во внутренней сети. Доступ к скачиванию разрешен.\n";
            realLibrary.downloadArticle(article);
        }
        
    }
};

int main()
{
    ProxyLibrary Hselib;
    setlocale(LC_ALL, "Russian");
    User Ivan("Иван", Global);
    User Petr("Петр", Local);
    Hselib.showMagazines(Ivan);
    Hselib.showArticles(Ivan);
    Hselib.downloadArticle(Ivan, "article1");
    Ivan.checkAccess();
    cout << "--------------------------------------------------------------------------\n--------------------------------------------------------------------------\n";
    Hselib.showMagazines(Petr);
    Hselib.showArticles(Petr);
    Hselib.downloadArticle(Petr, "article2");
    Petr.checkAccess();
    
    
}
