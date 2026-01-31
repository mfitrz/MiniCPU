# Sample SAL Test Files

This directory contains 12 sample .sal test files for my SAL (Simple Assembly Language) interpreter project.

## Test Files Overview

### Basic Arithmetic Tests

#### test1_simple_add.sal
**Purpose**: Tests basic arithmetic addition with variable storage  
**Instructions**: 12 lines  
**Expected execution steps**: ~12  

**What it does**:
- Declares three variables: x, y, sum
- Sets x = 5, y = 10
- Adds x + y and stores result in sum

**Expected Final State**:
- sum = 15
- Register A = 15
- Register B = 10
- Overflow bit = 0
- Zero bit = 0

---

#### test2_overflow.sal
**Purpose**: Tests overflow bit detection  
**Instructions**: 12 lines  
**Expected execution steps**: ~12  

**What it does**:
- Sets large1 = 2,000,000,000
- Sets large2 = 2,000,000,000
- Adds them together (exceeds 32-bit signed max)

**Expected Final State**:
- Overflow bit = 1 
- Register A = 2,000,000,000 (preserved, not overflowed)
- Addition correctly detected as overflow

---

#### test3_zero_flag.sal
**Purpose**: Tests zero flag detection  
**Instructions**: 12 lines  
**Expected execution steps**: ~12  

**What it does**:
- Sets num1 = 100
- Sets num2 = -100
- Adds them together (result = 0)

**Expected Final State**:
- result = 0
- Register A = 0
- Zero bit = 1 

---

### Register Operations

#### test4_exchange.sal
**Purpose**: Tests the XCH (exchange) instruction
**Instructions**: 11 lines
**Expected execution steps**: ~11

**What it does**:
- Sets val1 = 42, val2 = 99
- Loads them into registers A and B
- Exchanges register contents using XCH
- Stores swapped values back

**Expected Final State**:
- val1 = 99 (originally 42)
- val2 = 42 (originally 99)
- Registers correctly swapped

---

### Jump and Control Flow Tests

#### test5_simple_jump.sal
**Purpose**: Tests unconditional JMP instruction  
**Instructions**: 8 lines  
**Expected execution steps**: ~6  

**What it does**:
- Sets x = 10
- Jumps to PC 6 (skipping 2 instructions)
- The skipped instructions would have set x = 999

**Expected Final State**:
- x = 10 (not 999) 
- Register A = 10
- Jump successfully skipped instructions

---

#### test6_jzs.sal
**Purpose**: Tests JZS (Jump if Zero Set) conditional branch  
**Instructions**: 17 lines  
**Expected execution steps**: ~14  

**What it does**:
- Sets a = 50, b = -50
- Adds them (result = 0, sets zero flag)
- If zero flag set: jumps to PC 14, sets result = 0
- If zero flag not set: sets result = 1

**Expected Final State**:
- result = 0  (zero branch taken)
- Zero bit = 1
- Conditional jump worked correctly

---

#### test7_jvs.sal
**Purpose**: Tests JVS (Jump if oVerflow Set) conditional branch  
**Instructions**: 17 lines  
**Expected execution steps**: ~16  

**What it does**:
- Sets big1 = 2,000,000,000, big2 = 2,000,000,000
- Adds them (causes overflow)
- If overflow flag set: jumps to PC 14, sets overflow_flag = 1
- If overflow flag not set: sets overflow_flag = 0

**Expected Final State**:
- overflow_flag = 1  (overflow branch taken)
- Overflow bit = 1
- Conditional jump worked correctly

---

### Loop Tests (1000+ Execution Steps)

#### test8_loop_100.sal
**Purpose**: Tests loop functionality with 100 iterations  
**Instructions**: 18 lines  

**What it does**:
- Counts from 0 to 100 using a loop
- Uses negative limit (-100) to detect termination
- When counter = 100, (counter + limit = 0), zero flag sets, loop exits

**Loop Structure**:
```
counter = 0, limit = -100, one = 1
LOOP:
  counter = counter + 1
  if (limit + counter == 0): exit
  else: jump to LOOP
```

**Expected Final State**:
- counter = 100 
- Zero bit = 1 (exit condition)
- ~1,100 instruction executions

---

#### test9_loop_500.sal
**Purpose**: Tests loop with 500 iterations  
**Instructions**: 18 lines  
**Expected execution steps**: ~5,500+  

**What it does**:
- Same structure as test8 but counts to 500
- Will trigger 1000-step warning during execution

**Expected Final State**:
- counter = 500 
- Zero bit = 1
- ~5,500 instruction executions
- 1000-step warning triggered 

**Note**: When prompted after 1000 steps, enter any key except 'n' to continue.

---

#### test10_nested_loop.sal
**Purpose**: Tests nested loop functionality  
**Instructions**: 34 lines  
**Expected execution steps**: ~24,000+  

**What it does**:
- Outer loop: counts from 0 to 20
- Inner loop: counts from 0 to 100 (resets each outer iteration)
- Total loop iterations: 20 × 100 = 2,000

**Loop Structure**:
```
outer_counter = 0, outer_limit = -20
inner_counter = 0, inner_limit = -100

OUTER_LOOP:
  inner_counter = 0
  INNER_LOOP:
    inner_counter = inner_counter + 1
    if (inner_limit + inner_counter == 0): exit inner loop
    else: repeat inner loop
  outer_counter = outer_counter + 1
  if (outer_limit + outer_counter == 0): exit program
  else: repeat outer loop
```

**Expected Final State**:
- outer_counter = 20 
- inner_counter = 100 
- ~24,000 instruction executions
- Multiple 1000-step warnings 

**Note**: Multiple prompts will appear. Keep confirming to continue until completion.

---

#### test11_fibonacci.sal
**Purpose**: Tests accumulation pattern (Fibonacci sequence)  
**Instructions**: 34 lines  
**Expected execution steps**: ~1,200+  

**What it does**:
- Generates first 30 Fibonacci numbers
- Uses three variables: prev, curr, next
- Each iteration: next = prev + curr, then shifts values

**Algorithm**:
```
prev = 0, curr = 1, counter = 0, limit = -30

LOOP:
  next = prev + curr
  prev = curr
  curr = next
  counter = counter + 1
  if (limit + counter == 0): exit
  else: repeat loop
```

**Expected Final State**:
- counter = 30 
- prev = 832,040 (29th Fibonacci number)
- curr = 1,346,269 (30th Fibonacci number)
- ~1,200 instruction executions

**Fibonacci Sequence Generated**:  
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269

---

#### test12_loop_1000.sal
**Purpose**: Tests very long loop with 1000 iterations  
**Instructions**: 18 lines  
**Expected execution steps**: ~11,000+  

**What it does**:
- Same structure as test8/test9 but counts to 1000
- Will trigger multiple 1000-step warnings

**Expected Final State**:
- counter = 1000 
- Zero bit = 1
- ~11,000 instruction executions
- Multiple 1000-step warnings 

**Note**: Multiple prompts will appear. Keep confirming until completion.



