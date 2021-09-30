/*
 * A simulation of game picks, proving the average is the average.
 *
 * Do what you wish with this, no rights reserved.
 */


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

#define GAMES_PER_WEEK (16)
#define MAX_SCORE (136)

void swap(int& in1, int& in2)
{
    int temp = in1;
    in1 = in2;
    in2 = temp;
}

int get_score(const int winning_games[GAMES_PER_WEEK])
{
    int picked_games[GAMES_PER_WEEK];
    for (int & picked_game : picked_games)
        picked_game = rand() % 2;

    int games_scores[GAMES_PER_WEEK];
    for (int i = 0; i < GAMES_PER_WEEK; i++)
        games_scores[i] = i + 1;

    for (int i = 0; i < 100; i++)
        swap(games_scores[rand() % GAMES_PER_WEEK], games_scores[rand() % GAMES_PER_WEEK]);

    int this_score = 0;
    for (int i = 0; i < GAMES_PER_WEEK; i++)
    {
        if (picked_games[i] == winning_games[i])
            this_score += games_scores[i];
    }
    return this_score;
}

void print_results(const int game_score_ending_count[MAX_SCORE])
{
    bool continue_drawing = true;
    int row = 99;

    std::vector<std::string> strings;

    while (continue_drawing)
    {
        continue_drawing = false;
        std::string this_row;
        for (int i = 0; i < MAX_SCORE; i++)
        {
            if (game_score_ending_count[i] > row)
            {
                this_row += " $";
                continue_drawing = true;
            }
            else
            {
                this_row += "  ";
            }
        }

        row += 100;
        strings.push_back(this_row);
    }
    while (!strings.empty())
    {
        std::cout << strings.back() << std::endl;
        strings.pop_back();
    }
}

int main()
{
    srand (time(NULL));

    int total_picks = 0;
    int score = 0;
    int score_dist[MAX_SCORE] = {};

    for (int week = 0; week < 100; week++)
    {
        int winning_games[GAMES_PER_WEEK];
        for (int & winning_game : winning_games)
            winning_game = rand() % 2;

        for (int pick = 0; pick < 10000; pick++)
        {
            int this_score = get_score(winning_games);
            score += this_score;
            score_dist[this_score]++;
            total_picks++;
        }
        std::cout << "Week Complete: " << week << std::endl;
    }

    printf("Across [%d] weeks, the total score is [%d], with an average of [%f.4]\n", total_picks, score, float(score) / (float) total_picks);

    print_results(score_dist);
    return 0;
}
