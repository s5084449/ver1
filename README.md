# Report
The individual cpp file named "ConsoleApplication1.cpp" is the first development of code.
The second and third are in the files ver2 and ver3.

## Designs
The grammar logical design was inspired by reference:https://en.wikipedia.org/wiki/L-system.

The refernce source codes and part of program designing was from:https://blog.csdn.net/Mahabharata_/article/details/66967837?utm_medium=distribute.pc_relevant_download.none-task-blog-2~default~BlogCommendFromBaidu~default-3.nonecase&depth_1-utm_source=distribute.pc_relevant_download.none-task-blog-2~default~BlogCommendFromBaidu~default-3.nonecas

As Wikipidia introduced, L-system was generated by symbols, which were rewrited in specific production rules. Generally a L-system fractal contains elements: variable - the set of symbols containing elements and it could be replaced as well; constants mean the actions that variables should follow up. Here is a short production example for me to understanding the rule of L-system:
![Image text](https://github.com/s5084449/ver1/blob/main/readmeImage/1.png)

The "F" and "X" in my grammar means variables; and F is the point to start. "[]" mean the start and end of each action; "+""-" mean rotation in X axis,"*""/"mean rotation in Y axis, and"&""%" mean rotation in Z axis.
