*This project has been created as part of the 42 curriculum.*

## Description

**push_swap** is a sorting algorithm project from the 42 curriculum. The goal is to sort a stack of unique integers using two stacks (`a` and `b`) and a limited set of operations, producing the **smallest possible number of instructions**.

### Available operations

| Operation | Effect |
|-----------|--------|
| `sa` / `sb` | Swap the top 2 elements of stack a / b |
| `ss` | `sa` and `sb` simultaneously |
| `pa` / `pb` | Push top of b to a / top of a to b |
| `ra` / `rb` | Rotate stack a / b (first → last) |
| `rr` | `ra` and `rb` simultaneously |
| `rra` / `rrb` | Reverse rotate a / b (last → first) |
| `rrr` | `rra` and `rrb` simultaneously |

### Algorithm

- **n ≤ 3**: Hardcoded optimal sequences (0–2 operations).
- **n = 4–5**: Push smallest elements to b, sort 3 in a, pull back.
- **n > 5**: Chunk-based push to b + greedy cost insertion:
  1. Assign compressed indices (0..n-1) to all elements.
  2. Push elements to stack b in sorted chunks, using `rb` to pre-sort each chunk (larger elements stay on top).
  3. Sort the remaining 3 elements in a.
  4. Greedily pull each element from b into its correct position in a, choosing the element with the lowest combined rotation cost (using `rr`/`rrr` when rotations in both stacks share direction).
  5. Rotate a to bring the minimum to the top.

### Benchmark results

| Input size | Operations | Limit |
|-----------|-----------|-------|
| 100 random numbers | ≤ 673 | 700 |
| 500 random numbers | ≤ 5202 | 5500 |

## Instructions

### Compilation

```bash
make        # builds push_swap
make clean  # removes object files
make fclean # removes objects and binary
make re     # full rebuild
```

### Usage

```bash
./push_swap 4 67 3 87 23
# Outputs sorted sequence of instructions to stdout

./push_swap "4 67 3 87 23"
# Also accepts a single quoted string

./push_swap 0 one 2 3
# Outputs: Error (to stderr)
```

### Verifying correctness

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker_OS $ARG
# Outputs: OK
```

## Resources

- [Sorting algorithm visualizer](https://visualgo.net/en/sorting)
- [Push_swap — A journey to find most efficient sorting algorithm](https://medium.com/@jamierobertdawson/push-swap-the-least-number-of-moves-with-two-stacks-d1e76a71789a)
- [Greedy cost-based algorithm explanation](https://github.com/anyaschukin/Push_Swap)


