#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Player {
    int id;
    string name;
    int score;
};

vector<Player> players;

void loadData() {
    ifstream file("players.txt");
    Player p;
    while (file >> p.id >> p.name >> p.score) {
        players.push_back(p);
    }
    file.close();
}

void saveData() {
    ofstream file("players.txt");
    for (auto p : players) {
        file << p.id << " " << p.name << " " << p.score << endl;
    }
    file.close();
}

void addPlayer() {
    Player p;
    cout << "Nhap ID: ";
    cin >> p.id;
    cout << "Nhap ten: ";
    cin >> p.name;
    p.score = 0;

    players.push_back(p);
    saveData();
    cout << "Them thanh cong!\n";
}

void showPlayers() {
    cout << "\nDanh sach nguoi choi:\n";
    for (auto p : players) {
        cout << p.id << " - " << p.name << " - Score: " << p.score << endl;
    }
}

void playGame() {
    if (players.empty()) {
        cout << "Chua co nguoi choi!\n";
        return;
    }

    int id;
    cout << "Nhap ID nguoi choi: ";
    cin >> id;

    Player *p = nullptr;
    for (auto &player : players) {
        if (player.id == id) {
            p = &player;
        }
    }

    if (p == nullptr) {
        cout << "Khong tim thay nguoi choi!\n";
        return;
    }

    srand(time(0));
    int number = rand() % 100 + 1;
    int guess;

    cout << "\nGame Doan So (1 - 100)\n";

    do {
        cout << "Nhap so ban doan: ";
        cin >> guess;

        if (guess > number)
            cout << "Lon hon!\n";
        else if (guess < number)
            cout << "Nho hon!\n";
        else
            cout << "Chinh xac!\n";

    } while (guess != number);

    p->score += 10;
    saveData();
}

void menu() {
    int choice;

    do {
        cout << "\n===== GAME DOAN SO =====\n";
        cout << "1. Them nguoi choi\n";
        cout << "2. Xem danh sach\n";
        cout << "3. Choi game\n";
        cout << "0. Thoat\n";

        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
            case 1: addPlayer(); break;
            case 2: showPlayers(); break;
            case 3: playGame(); break;
        }

    } while (choice != 0);
}

int main() {
    loadData();
    menu();
    return 0;
}