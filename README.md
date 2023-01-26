# CLEAN++

CLEAN++ is an extension of OCLint, a static code analysis tool, to be able to detect 35 code smells in C++ code.

## List of Code Smells

CLEAN++ implements 35 code smells derived from the smells in DesigniteJava and Organic tools.
You can find the full details about each smell in [smells.md](data/smells.md)

| | | | | |
|--------------------------|-----------------------------------------|---------------------|------------------------------|------------------------|
| ImperativeAbstraction    | InsufficientModularization              | Long Method         | Data Class                   | Speculative Generality |
| MultifacetedAbstraction  | HubLikeModularization                   | Long Parameter List | Complex Class                | Brain Class            |
| UnnecessaryAbstraction   | Abstract Function Call From Constructor | Long Statement      | Refused Bequest              | Brain Method           |
| UnutilizedAbstraction    | Complex Conditional                     | Magic Number        | Spaghetti Code               | Dispersed Coupling     |
| DeficientEncapsulation   | Complex Method                          | Missing default     | Large Class                  | Intensive Coupling     |
| UnexploitedEncapsulation | Empty catch clause                      | Lazy Class          | Class Data Should Be Private | Message Chain          |
| BrokenModularization     | Long Identifier                         | Swiss Army Knife    | God Class                    | Shotgun Surgery        |


## Install

## Reproduce Test Cases
### List of Test Cases
We evaluated CLEAN++ smells' implementations by writing 35 test cases, each targeting a specific test.
We include the written tests in the [test directory](tests/), for both [C++](tests/cpp) and [Java](tests/java).

In [test_case_results.tsv](data/test_case_results.tsv), we list the results for each test case from the execution of CLEAN++ for C++ and both tools [DesigniteJava](https://www.designite-tools.com/) and [Organic](https://github.com/opus-research/organic).

In the following figure we show the comparison between the number of smells from the execution of CLEAN++ with the other two Java tools on the test cases for Java.

![test case results alt](fig/test_case_results.png)

## Reproduce Execution in Projects
### List of Projects
We evaluated CLEAN++ on the 44 projects we list below.
You can find more information about them in [projects.tsv](data/projects.tsv)

|           |                    |             |               |                     |                  |           |
|-----------|--------------------|-------------|---------------|---------------------|------------------|-----------|
| WebServer | hnswlib            | FTXUI       | duckdb        | design-patterns-cpp | gperftools       | BlingFire |
| libco     | rpi-rgb-led-matrix | enkiTS      | re2           | zopfli              | ChaiScript       | PEGTL     |
| xlearn    | coost              | json        | git-crypt     | pugixml             | hardware-effects |           |
| mergerfs  | rpclib             | flatbuffers | yoga          | Dobby               | 2048             |           |
| OpenCC    | magic              | C-Plus-Plus | sentencepiece | PacVim              | kfr              |           |
| libfm     | matrix             | spdlog      | LeetCode      | SEAL                | marl             |           |
| cxxopts   | UDPspeeder         | muduo       | handy         | backward-cpp        | openal-soft      |           |

