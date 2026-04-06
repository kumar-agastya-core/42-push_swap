*This project has been created as part of the 42 curriculum.*

---

## Description

**push_swap** is a sorting algorithm project from the 42 school curriculum. The challenge is deceptively simple: sort a list of unique integers using only two stacks and a limited set of stack operations, while producing the **smallest possible number of instructions**.

You are given:
- **Stack a** — pre-loaded with a random set of unique integers (unsorted)
- **Stack b** — starts completely empty

Your goal is to sort stack a in **ascending order** (smallest on top, largest at bottom) with stack b empty at the end, using the fewest operations possible. The program reads integers as arguments and prints the sequence of instructions to stdout.

This project is fundamentally about understanding algorithm complexity, choosing the right strategy for different input sizes, and optimising every decision.

---

## The Operations

There are 11 valid operations. Every operation printed must be one of these exact strings:

| Operation | What it does |
|-----------|-------------|
| `sa` | Swap the first two elements at the top of stack a. Does nothing if fewer than 2 elements. |
| `sb` | Same as `sa` but for stack b. |
| `ss` | Performs `sa` and `sb` simultaneously — counts as 1 instruction. |
| `pa` | Takes the top element of stack b and places it on top of stack a. Does nothing if b is empty. |
| `pb` | Takes the top element of stack a and places it on top of stack b. Does nothing if a is empty. |
| `ra` | Rotates stack a upward — the top element becomes the last. |
| `rb` | Same as `ra` but for stack b. |
| `rr` | Performs `ra` and `rb` simultaneously — counts as 1 instruction. |
| `rra` | Reverse rotates stack a — the last element becomes the first (top). |
| `rrb` | Same as `rra` but for stack b. |
| `rrr` | Performs `rra` and `rrb` simultaneously — counts as 1 instruction. |

The combined operations (`ss`, `rr`, `rrr`) are key to efficiency — whenever both stacks need to move in the same direction at the same time, using the combined op saves one instruction per pair of moves.

---

## Project Requirements

- Written in **C**, compiled with `cc -Wall -Wextra -Werror`
- No global variables
- All heap memory must be freed — no leaks
- Must follow the **42 Norm** (max 25 lines per function, no `for` loops, etc.)
- If no arguments are given, the program outputs nothing and exits cleanly
- On any error (invalid integer, duplicate, overflow), print `Error` to **stderr** and exit

### Benchmark targets for full marks

| Input size | Must stay under |
|-----------|----------------|
| 100 numbers | 700 operations |
| 500 numbers | 5500 operations |

---

## How the Algorithm Works

The sorting strategy is not one-size-fits-all. Different input sizes call for completely different approaches. Here is how each case is handled:

### n = 1
Nothing to do. A single element is already sorted.

### n = 2
At most one `sa`. If the top is greater than the bottom, swap. Done in 0 or 1 operations.

### n = 3
There are exactly 6 possible permutations of 3 elements. Each one is handled with a hardcoded optimal sequence — never more than 2 operations. The 6 cases and their fixes:

| State | Fix |
|-------|-----|
| `[1, 2, 3]` | already sorted — nothing |
| `[2, 1, 3]` | `sa` |
| `[3, 1, 2]` | `ra` |
| `[1, 3, 2]` | `rra` → `sa` |
| `[2, 3, 1]` | `rra` |
| `[3, 2, 1]` | `ra` → `sa` |

### n = 4 and n = 5
The strategy here is to reduce to the 3-element case:
1. Find the minimum value in a and rotate it to the top (using `ra` or `rra` depending on which direction costs fewer moves)
2. Push it to b with `pb`
3. For n = 5, repeat to push the second smallest
4. Sort the remaining 3 elements in a using the hardcoded sort above
5. Pull back from b with `pa` — since we pushed smallest first, the order is restored correctly

This gives optimal results for small inputs without the overhead of the full large-sort algorithm.

### n > 5 — Chunk-based push + greedy insertion

This is where the main algorithm lives. It runs in four phases:

#### Phase 1 — Assign compressed indices

Before anything else, each element in stack a is assigned a **rank** from `0` to `n-1`, where `0` is the smallest value and `n-1` is the largest. This compression lets us reason about relative order without caring about actual values or gaps between them. The rank is computed by counting how many other elements in a are smaller than the current one — O(n²) but only done once.

#### Phase 2 — Push to b in chunks

Rather than pushing elements to b randomly, we push them in **index-ordered batches (chunks)**. This pre-sorts b in a way that makes the later greedy phase much cheaper.

- For **n ≤ 100**: chunk size = 30 (roughly 3–4 passes)
- For **n > 100**: chunk size = 100 (roughly 5 passes for 500 elements)

For each chunk, we scan all remaining elements in a. If the element at the top has an index in the current chunk's range, we push it to b. Otherwise, we `ra` it to the bottom and continue. After a full scan, we move to the next chunk.

**The rb optimisation:** Immediately after pushing an element to b, if that element's index is in the **lower half** of the current chunk (i.e. it's a relatively smaller element within the batch), we do `rb` to sink it deeper in b. This means within each chunk, larger elements float to the top of b and smaller elements settle lower. The result is that b ends up in a rough descending order, which dramatically reduces rotation costs in the greedy phase.

We continue until only 3 elements remain in a.

#### Phase 3 — Sort the 3 remaining in a

The 3 elements left in a are sorted using the hardcoded 3-element sort described above.

#### Phase 4 — Greedy insertion from b to a

This is the core of the algorithm. Stack a is now a sorted (or rotating-sorted) sequence and we need to insert all elements from b one by one into their correct position in a.

For **each candidate element in b** (at position `pos_b` from the top), we calculate:

- **cb_fwd** = cost to bring it to the top of b using forward rotations (`rb`) = `pos_b`
- **cb_bwd** = cost to bring it to the top of b using reverse rotations (`rrb`) = `b.size - pos_b` (or 0 if already at top)
- **target_a** = the position in a where this element should be inserted (found by scanning a for the smallest element larger than the candidate — if candidate is the new max, it goes just after the current max)
- **ca_fwd** = `target_a`
- **ca_bwd** = `a.size - target_a` (or 0 if already at the right position)

Four possible strategies exist for each candidate:

| Strategy | Cost |
|----------|------|
| Both rotate forward (`rr`) | `max(ca_fwd, cb_fwd)` |
| Both rotate backward (`rrr`) | `max(ca_bwd, cb_bwd)` |
| a forward, b backward | `ca_fwd + cb_bwd` |
| a backward, b forward | `ca_bwd + cb_fwd` |

The minimum of these four is the **insertion cost** for that candidate. We scan every element in b, compute its cost, and pick the one with the **lowest total cost**. Then we execute the rotations (using `rr` / `rrr` for the overlapping portion when both stacks go the same direction) and finish with `pa`.

This repeats until b is empty.

#### Phase 5 — Final rotate

After all elements are back in a, the stack is a sorted sequence but may be rotated (minimum might not be at the top). We find the position of the minimum and rotate a the shortest way — either forward with `ra` or backward with `rra` — to bring it to the top.

---

## File Structure

| File | Responsibility |
|------|---------------|
| `push_swap.h` | Defines `t_node` and `t_stack` structs. Contains all function prototypes used across files. |
| `main.c` | Entry point. Handles the argc < 2 early exit, calls `parse_args`, initialises stack b, calls `sort`, then frees both stacks. |
| `parse.c` | Iterates over all arguments, splits quoted strings into tokens, validates each token as a legal integer (no non-digit chars, no overflow beyond INT range, no duplicates), and builds stack a. Exits with `Error` on any failure. |
| `ft_utils.c` | Low-level utilities: `ft_putstr_fd` (write string to fd), `ft_isdigit`, `ft_isspace`, and `ft_atoi_safe` which parses a string to `long` with overflow detection and returns a success flag. |
| `ft_split.c` | Splits a string on any whitespace into a null-terminated array of strings. Handles leading/trailing spaces and multiple spaces between tokens. Used so that `./push_swap "1 2 3"` works the same as `./push_swap 1 2 3`. |
| `stack.c` | Stack lifecycle and utility functions: `stack_new`, `stack_free`, `stack_push_bottom` (used during initial population), `stack_min_pos`, `stack_max_pos`, `is_sorted`, and `assign_indices` (computes rank for each node). |
| `operations.c` | Implements all 11 stack operations. Each function modifies the stack(s) and immediately prints the operation name followed by `\n`. Swap operates on node values in place. Push moves the actual node pointer between stacks. Rotate and reverse-rotate rewire the linked list pointers. |
| `sort.c` | Contains the `sort` dispatcher (routes to the right strategy based on `a->size`), the `sort_3` function (6-case hardcoded sort), and `sort_4` / `sort_5` (push-min + sort_3 + pull-back). Also contains the `rotate_min_to_top` helper. |
| `sort_large.c` | The full large-input algorithm: `push_chunks_to_b` (chunk push with rb optimisation), `get_insert_pos` (finds target position in a for a given value), `get_best_pos` (scans all b elements and returns index of cheapest to insert), `exec_insertion` (performs the actual rotation + pa using rr/rrr when possible), and `sort_large` which orchestrates all phases. |

---

## Instructions

### Compilation

```bash
make        # compiles push_swap
make clean  # removes .o files
make fclean # removes .o files and the binary
make re     # fclean then rebuild from scratch
```

### Running the program

```bash
# Multiple arguments
./push_swap 4 67 3 87 23

# Single quoted string — both work
./push_swap "4 67 3 87 23"

# Negative numbers
./push_swap -5 3 -1 2 0
```

### Verifying output with the checker

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker_OS $ARG
# prints: OK
```

If the checker prints `KO`, the instruction sequence doesn't correctly sort the stack.

### Error cases (all print `Error` to stderr)

```bash
./push_swap 1 two 3       # non-integer argument
./push_swap 1 2 2         # duplicate value
./push_swap 2147483648    # exceeds INT_MAX
./push_swap -2147483649   # below INT_MIN
./push_swap ""            # empty string argument
```

---

## Benchmark Results

Tested across 1000+ randomly generated inputs using an automated Python checker that simulates every operation and verifies the final state:

| Input size | Typical max ops | Hard limit | Status |
|-----------|----------------|-----------|--------|
| 100 numbers | ~650–673 | 700 | ✓ Pass |
| 500 numbers | ~5000–5200 | 5500 | ✓ Pass |

---

## Resources

- [Push_swap — finding the most efficient sort with two stacks](https://medium.com/@jamierobertdawson/push-swap-the-least-number-of-moves-with-two-stacks-d1e76a71789a)
- [Sorting algorithm visualizer](https://visualgo.net/en/sorting)
- [42 Norm documentation](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)

### AI usage

Claude AI (Anthropic) was used as a learning resource throughout this project. It helped me understand concepts like greedy algorithms, cost-based decision making, and how to reason about stack rotations mathematically. I used it to work through the logic of the chunk-based push strategy, debug edge cases in the argument parser, and understand trade-offs between different chunk sizes through discussion and guided experimentation. The goal was always to understand *why* each design choice works, not just to get output.
