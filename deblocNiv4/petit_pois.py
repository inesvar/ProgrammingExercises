nb_units = int(input())

# UTILS
def factorial_subceiling(index: int=1, factorial: int=1) -> (int, int):
    if factorial > nb_units:
        return index - 1, factorial / index
    else:
        index += 1
        factorial *= index
        return factorial_subceiling(index, factorial)

N, higher_factorial = factorial_subceiling()
higher_index = N
decomposition = [0] * higher_index

for decomposition_index in range(higher_index - 1, -1, -1):
    decomposition[decomposition_index] = int(nb_units // higher_factorial)
    nb_units = nb_units % higher_factorial
    higher_factorial /= higher_index
    higher_index -= 1

print(N)
print(" ".join(map(str, decomposition)))