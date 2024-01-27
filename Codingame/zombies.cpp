#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;

const int LARG = 15999;
const int HAUT = 8999;
const unsigned MCT_DEPTH = 2;
const int SPEED = 1000;
const int GUN_RANGE_SQUARED = 4000000;
const int ZOMBIE_SPEED = 400;
const int GAMEOVER = -10000;

unsigned fibonacci(unsigned n) {
    if (n <= 1)  {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

unsigned fibonacciSum(unsigned n) {
    if (n <= 0) {
        return 0;
    } else {
        return fibonacciSum(n - 1) + fibonacci(n);
    }
}

int compute_score(unsigned kills, unsigned human_count) {
    int score = 10 * pow(human_count, 2);
    score *= fibonacciSum(kills);
    cerr << "score after killing zombies" << score << " ";
    return score;
}

void print(pair<int, int> p, bool end_of_line = true) {
    cerr << "x : " << p.first << " y : " << p.second;
    if (end_of_line) {
        cerr << "\n";
    }
}

void print(vector<pair<int, int>> &v, bool end_of_line = true) {
    cerr << "[ ";
    for (auto i = v.begin(); i != v.end(); i++) {
        cerr << "(";
        print(*i, false);
        cerr << "), ";
    }
    cerr << " ]";
    if (end_of_line) {
        cerr << "\n";
    }
}

void print(list<pair<int, int>> &v, bool end_of_line = true) {
    cerr << "[ ";
    for (auto i = v.begin(); i != v.end(); i++) {
        cerr << "(";
        print(*i, false);
        cerr << ")";
    }
    cerr << " ]";
    if (end_of_line) {
        cerr << "\n";
    }
}

class Playground {
    public:
        list<pair<int, int>> human_pos{};
        vector<pair<int, int>> zombie_pos{};
        vector<pair<int, int>> next_moves{};
        vector<int> score{};
        pair<int, int> pos{};
        unsigned human_count{};

    void clear() {
        human_pos.clear();
        zombie_pos.clear();
        next_moves.clear();
    }

    void move() {
        if (human_count > 0) {
            unsigned i = compute_most_rewarding_move(MCT_DEPTH).first;
            pos = next_moves[i];
            cerr << "\n\nMOVED TO ";
            print(pos);
        } else {
            pos = *human_pos.begin();
            /* pair<int, int> human_mean = pair(0, 0);
            pair<int, int> zombie_mean = pair(0, 0);
            unsigned count = 0;
            for (auto h = human_pos.begin(); h != human_pos.end(); h++) {
                human_mean.first += h->first;
                human_mean.second += h->second;
                count++;
            }
            pos.first = human_mean.first / count * 0.5;
            pos.second = human_mean.second / count * 0.5;
            count = 0;
            for (auto h = zombie_pos.begin(); h != zombie_pos.end(); h++) {
                zombie_mean.first += h->first;
                zombie_mean.second += h->second;
                count++;
            }
            pos.first += zombie_mean.first / count * 0.5;
            pos.second += zombie_mean.second / count * 0.5; */
        }
    }

    void compute_possible_moves() {
        if (pos.first + 1000 <= LARG) {
            next_moves.emplace_back(min(LARG, pos.first + 1000), pos.second);
        }
        if (pos.second - 1000 >= 0) {
            next_moves.emplace_back(pos.first, max(0, pos.second - 1000));
        }
        if (pos.first - 1000 >= 0) {
            next_moves.emplace_back(max(0, pos.first - 1000), pos.second);
        }
        if (pos.second + 1000 <= HAUT) {
            next_moves.emplace_back(pos.first, min(HAUT, pos.second + 1000));
        }
    }

    pair<unsigned, unsigned> compute_most_rewarding_move(unsigned depth) {
        compute_possible_moves();
        for (unsigned i = 0; i < next_moves.size(); i++) {
            Playground *next_pg = new Playground();
            cerr << "\ndepth " << depth << " move " << i;
            
            next_pg->pos = next_moves[i];
            cerr << " (pos " << next_pg->pos.first << " " << next_pg->pos.second << ") ";

            score.push_back(compute_score(next_pg->attack_zombies(zombie_pos),
                                          human_count));

            if (!next_pg->zombies_eat(human_pos)) {
                score[i] = GAMEOVER;
                continue;
            }

            next_pg->move_zombies();

            if (depth > 0) {
                score[i] += next_pg->compute_most_rewarding_move(depth - 1).second;
                cerr << "\nscore " << i << " at depth " << depth << " : " << score[i];
            }
        }

        return get_max_score();
    }

    unsigned attack_zombies(vector<pair<int, int>> &old_zombie_pos) {
        unsigned zombies_killed = 0;
        for (auto z = old_zombie_pos.begin(); z != old_zombie_pos.end(); z++) {
            if (pow(z->first - pos.first, 2) +
                pow(z->second - pos.second, 2) >= GUN_RANGE_SQUARED) {
                    zombie_pos.emplace_back(z->first, z->second);
            } else {
                zombies_killed += 1;
            }
        }
        cerr << "Z alive after Ash attacks : ";
        print(zombie_pos, false);
        return zombies_killed;
    }

    bool zombies_eat(list<pair<int, int>> &old_human_pos) {
        cerr << "OHP";
        print(old_human_pos, false);
        for (auto z = zombie_pos.begin(); z != zombie_pos.end(); z++) {
            for (auto h = old_human_pos.begin(); h != old_human_pos.end();) {
                if (z->first == h->first && z->second == h->second) {
                    h = old_human_pos.erase(h);
                } else {
                    h++;
                }
            }
        }
        for (auto h = old_human_pos.begin(); h != old_human_pos.end(); h++) {
            human_pos.emplace_back(h->first, h->second);
            human_count += 1;
        }
        cerr << "H alive after zombies eat : ";
        print(human_pos); 
        return (human_count != 0);
    }

    void move_zombies() {
        // TODO : compute distance only once and store it
        for (auto z = zombie_pos.begin(); z != zombie_pos.end(); z++) {
            int min_distance = pow(HAUT + 1, 2) + pow(LARG + 1, 2);
            auto closest_human = *human_pos.begin();
            for (auto h = human_pos.begin(); h != human_pos.end(); h++) {
                int distance = pow(z->first - h->first, 2) + pow(z->second - h->second, 2);
                if (distance < min_distance) {
                    closest_human = *h;
                    min_distance = distance;
                }
            }
            move_towards(&*z, closest_human, min_distance);
        }
    }

    void move_towards(pair<int, int> *zombie, pair<int, int> target, int distance) {
        pair<int, int> vector = pair<int, int>(target.first - zombie->first, target.second - zombie->second);
        float ratio = sqrt(pow(ZOMBIE_SPEED, 2) / (float)distance);
        if (ratio < 1) {
            zombie->first += (int)(vector.first * ratio);
            zombie->second += (int)(vector.second * ratio);
        } else {
            zombie->first = target.first;
            zombie->second = target.second;
        }
    }

    pair<unsigned, unsigned> get_max_score() const {
        auto i = max_element(score.begin(), score.end());
        return pair<int, int>(distance(score.begin(), i), *i);
    }
};

int main()
{
    Playground *pg = new Playground();

    // game loop
    while (1) {
        pg->clear();
        cin >> pg->pos.first >> pg->pos.second; cin.ignore();
        cin >> pg->human_count; cin.ignore();
        for (unsigned i = 0; i < pg->human_count; i++) {
            int human_id;
            int human_x;
            int human_y;
            cin >> human_id >> human_x >> human_y; cin.ignore();
            cerr << "human at " << human_x << " " << human_y << "\n";
            pg->human_pos.emplace_back(human_x, human_y);
        }

        int zombie_count;
        cin >> zombie_count; cin.ignore();
        for (int i = 0; i < zombie_count; i++) {
            int zombie_id;
            int zombie_x;
            int zombie_y;
            int zombie_xnext;
            int zombie_ynext;
            cin >> zombie_id >> zombie_x >> zombie_y >> zombie_xnext >> zombie_ynext; cin.ignore();
            cerr << "zombie at " << zombie_xnext << " " << zombie_ynext << "\n";
            pg->zombie_pos.emplace_back(zombie_xnext, zombie_ynext);
        }

        pg->move();

        cout << pg->pos.first << " " << pg->pos.second << endl; // Your destination coordinates
    }
}