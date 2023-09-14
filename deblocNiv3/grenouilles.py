# handling init inputs
NB_RUNNERS = int(input())
NB_ROUNDS = int(input())

# runners are numbered from 1 to NB_RUNNERS

# runner 0 is an abstract runner that has 2 roles
# position 0 always contains the position of the previous top
PREVIOUS_TOP = 0
# runner 0 is top runner when there's no strict top
# runner 0 must never win
ABSTRACT_RUNNER = 0

position = [0]*(NB_RUNNERS + 1)
nb_rounds_as_top = [0]*(NB_RUNNERS + 1)
top_runner = 0
max_nb_rounds_as_top = 0

# in each round
for tour in range(NB_ROUNDS):
    # update count of rounds for the top runner
    nb_rounds_as_top[top_runner] += 1
    #print("nb rounds as top : ", nb_rounds_as_top)

    # read the infos about the jump and update the positions accordingly
    runner, jump = map(int, input().split())
    position[runner] += jump

    # update the info about the top runner
    if position[runner] > position[PREVIOUS_TOP]:
        top_runner = runner
        position[PREVIOUS_TOP] = position[top_runner]
    elif position[runner] == position[PREVIOUS_TOP]:
        top_runner = ABSTRACT_RUNNER

    #print("positions : ", position)
    #print("top runner : ", top_runner)

for runner in range(NB_RUNNERS, 0, -1):
    if nb_rounds_as_top[runner] >= max_nb_rounds_as_top:
        winner = runner
        max_nb_rounds_as_top = nb_rounds_as_top[runner]

#print("winner : ", winner)
print(winner)
