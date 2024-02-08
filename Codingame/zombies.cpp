#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>
#include <cassert>

using namespace std;


/*
 * TODO :
 * - compute the date of death of humans and when threatened, ensure to save on
 */

const int LARG = 15999;
const int HAUT = 8999;
const unsigned MCT_DEPTH = 5;
const int SPEED = 1000;
const int GUN_RANGE = 2000;
const int GUN_RANGE_SQUARED = 4000000;
const int ZOMBIE_SPEED = 400;
const int GAMEOVER = -10000;
// slightly less than the side of the inscribed square (in the gun range) 
const int GRANULARITY_X = 2800; 
const int GRANULARITY_Y = 2800;

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

int compute_score(unsigned kills, unsigned human_count, bool print = false) {
    int score = 10 * pow(human_count, 2);
    score *= fibonacciSum(kills);
    if (print) {
        cerr << "score after killing zombies" << score << "\n";
    }
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

void print_score(const vector<float> &v, bool end_of_line = true) {
    cerr << "[ ";
    for (auto i = v.begin(); i != v.end(); i++) {
        cerr << "(" << *i;
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

bool compare_first(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

bool compare_second(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

class Playground {
    private:
    /* Among all zombies and humans (that are not Ash) */
        int min_x{};
        int min_y{};
        int max_x{};
        int max_y{};

    public:
        list<pair<int, int>> human_pos{};
        vector<pair<int, int>> zombie_pos{};
        vector<pair<int, int>> next_moves{};
        vector<float> score{};
        pair<int, int> pos{};
        unsigned human_count{};
        unsigned zombie_count{};

    void clear() {
        human_pos.clear();
        zombie_pos.clear();
        next_moves.clear();
        score.clear();
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

    void find_zombies_and_humans() {
        int human_min_x = min_element(human_pos.begin(), human_pos.end(), compare_first)->first;
        int human_min_y = min_element(human_pos.begin(), human_pos.end(), compare_second)->second;
        int human_max_x = max_element(human_pos.begin(), human_pos.end(), compare_first)->first;
        int human_max_y = max_element(human_pos.begin(), human_pos.end(), compare_second)->second;

        int zombie_min_x = min_element(zombie_pos.begin(), zombie_pos.end(), compare_first)->first;
        int zombie_min_y = min_element(zombie_pos.begin(), zombie_pos.end(), compare_second)->second;
        int zombie_max_x = max_element(zombie_pos.begin(), zombie_pos.end(), compare_first)->first;
        int zombie_max_y = max_element(zombie_pos.begin(), zombie_pos.end(), compare_second)->second;

        min_x = min(human_min_x, zombie_min_x);
        min_y = min(human_min_y, zombie_min_y);
        max_x = max(human_max_x, zombie_max_x);
        max_y = max(human_max_y, zombie_max_y);

    }

    void compute_possible_moves() {
        assert(next_moves.size() == 0);
        find_zombies_and_humans();
        if (max_x - min_x < GRANULARITY_X) {
            if (max_y - min_y < GRANULARITY_Y) {
                pair<int, int> next_pos = pos;
                move_towards(&next_pos, pair<int, int>((min_x + max_x) / 2, (min_y + max_y) / 2), SPEED);
                next_moves.push_back(next_pos);
            } else {
                pair<int, int> next_pos = pos;
                move_towards(&next_pos, pair<int, int>((min_x + max_x) / 2, min_y), SPEED);
                next_moves.push_back(next_pos);
                next_pos = pos;
                move_towards(&next_pos, pair<int, int>((min_x + max_x) / 2, max_y), SPEED);
                next_moves.push_back(next_pos);
            }
        } else {
            if (max_y - min_y < GRANULARITY_Y) {
                pair<int, int> next_pos = pos;
                move_towards(&next_pos, pair<int, int>(min_x, (min_y + max_y) / 2), SPEED);
                next_moves.push_back(next_pos);
                next_pos = pos;
                move_towards(&next_pos, pair<int, int>(max_x, (min_y + max_y) / 2), SPEED);
                next_moves.push_back(next_pos);
            } else {
                pair<int, int> next_pos = pos;
                move_towards(&next_pos, pair<int, int>(min_x, min_y), SPEED);
                next_moves.push_back(next_pos);
                next_pos = pos;
                move_towards(&next_pos, pair<int, int>(min_x, max_y), SPEED);
                next_moves.push_back(next_pos);
                next_pos = pos;
                move_towards(&next_pos, pair<int, int>(max_x, min_y), SPEED);
                next_moves.push_back(next_pos);
                next_pos = pos;
                move_towards(&next_pos, pair<int, int>(max_x, max_y), SPEED);
                next_moves.push_back(next_pos);
            }
        }
        assert(next_moves.size() != 0);
        cerr << "possible moves ";
        print(next_moves);
    }

    pair<unsigned, float> compute_most_rewarding_move(unsigned depth) {
        compute_possible_moves();
        for (unsigned i = 0; i < next_moves.size(); i++) {
            Playground next_pg;
            cerr << "\ndepth " << depth << " move " << i;
            
            next_pg.pos = next_moves[i];
            cerr << " (pos " << next_pg.pos.first << " " << next_pg.pos.second << ") ";

            score.push_back(compute_score(next_pg.attack_zombies(zombie_pos),
                                          human_count, depth==MCT_DEPTH));

            if (!next_pg.zombies_eat(human_pos)) {
                score[i] = GAMEOVER;
                continue;
            } else if (!next_pg.zombie_count) {
                if (depth > 3) {
                    cerr << "\nscore " << i << " at depth " << depth << " : " << score[i];
                }
                continue;
            }

            next_pg.move_zombies();

            if (depth > 0) {
                float child_score = (float)(next_pg.compute_most_rewarding_move(depth - 1).second);
                score[i] += child_score * 2 / 3;
                if (depth > 3) {
                    cerr << "\nchild score " << child_score;
                    cerr << "score " << i << " at depth " << depth << " : " << score[i];
                }
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
        zombie_count = old_zombie_pos.size() - zombies_killed;
        return zombies_killed;
    }

    bool zombies_eat(list<pair<int, int>> &old_human_pos) {
        cerr << "OHP";
        print(old_human_pos, false);
        for (auto h = old_human_pos.begin(); h != old_human_pos.end(); h++) {
            bool still_alive = true;
            for (auto z = zombie_pos.begin(); z != zombie_pos.end(); z++) {
                if (z->first == h->first && z->second == h->second) {
                    still_alive = false;
                }
            }
            if (still_alive) {
                human_pos.emplace_back(h->first, h->second);
                human_count += 1;
            }
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
            int distance = pow(z->first - pos.first, 2) + pow(z->second - pos.second, 2);
            if (distance < min_distance) {
                closest_human = pos;
                min_distance = distance;
            }
            move_towards(&*z, closest_human, ZOMBIE_SPEED);
        }
    }

    /* Move `moving` towards `target` or on `target` if `speed` >= distance */
    void move_towards(pair<int, int> *moving, pair<int, int> target, int speed) {
        pair<int, int> vector = pair<int, int>(target.first - moving->first, target.second - moving->second);
        float distance_squared = pow(vector.first, 2) + pow(vector.second, 2);
        float ratio = sqrt(pow(speed, 2) / distance_squared);
        if (ratio < 1) {
            moving->first += (int)(vector.first * ratio);
            moving->second += (int)(vector.second * ratio);
        } else {
            moving->first = target.first;
            moving->second = target.second;
        }
    }

    pair<unsigned, float> get_max_score() const {
        auto i = max_element(score.begin(), score.end());
        return pair<unsigned, float>(distance(score.begin(), i), *i);
    }
};

int main()
{
    Playground pg;

    // game loop
    for (int _ = 0; _ < 10; _++) {
    // while (true) {
        pg.clear();
        cin >> pg.pos.first >> pg.pos.second; cin.ignore();
        cin >> pg.human_count; cin.ignore();
        for (unsigned i = 0; i < pg.human_count; i++) {
            int human_id;
            int human_x;
            int human_y;
            cin >> human_id >> human_x >> human_y; cin.ignore();
            cerr << "human at " << human_x << " " << human_y << "\n";
            pg.human_pos.emplace_back(human_x, human_y);
        }

        cin >> pg.zombie_count; cin.ignore();
        for (unsigned i = 0; i < pg.zombie_count; i++) {
            int zombie_id;
            int zombie_x;
            int zombie_y;
            int zombie_xnext;
            int zombie_ynext;
            cin >> zombie_id >> zombie_x >> zombie_y >> zombie_xnext >> zombie_ynext; cin.ignore();
            cerr << "zombie at " << zombie_xnext << " " << zombie_ynext << "\n";
            pg.zombie_pos.emplace_back(zombie_xnext, zombie_ynext);
        }

        pg.move();

        cout << pg.pos.first << " " << pg.pos.second << endl; // Your destination coordinates
    }
}