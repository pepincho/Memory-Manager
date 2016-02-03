# Memory-Manager

Course project for the Data-Structures-and-Algorithms course in FMI

В рамките на този проект трябва да се разработи собствен memory allocator.

За целта трябва да реализирате следните функции:

* MyMalloc, която получава като вход брой байтове, които трябва да се заделят и връща указател към заделения от нея блок. При неуспех функцията да връща NULL;
* MyFree, която освобождава паметта заделена с MyMalloc.

Сами можете да изберете типа на функциите и на техните параметри, например:

```
char* MyMalloc(size_t Size);
void MyFree(char* pBlock);
```

Също така сами трябва да изберете какво да бъде тяхното поведение при възникване на грешка (например ако MyAlloc не може да задели памет или когато на MyFree бъде подаден адрес, който не е бил заделен с MyAlloc и т.н.).

Началният адрес на блока, който връща MyMalloc трябва да бъде подравнен на 8 байта.
Можете сами да изберете какъв да бъде алгоритъмът, който да реализирате. Той трябва да бъде такъв, че да позволява операциите да протичат бързо и да се намали фрагментацията.

При реализацията на двете функции не е необходимо да използвате примитиви на операционната система. За работата на двете функции е достатъчно да заделите и поддържате достатъчно голям обем памет, от който да заделяте и в който да освобождавате необходимите на потребителя блокове.

Ето пример за това как трябва да може да работят двете функции:

```
int *pArr1 = (int*) MyMalloc(100 * sizeof(int));
int *pArr2 = (int*) MyMalloc(100 * sizeof(int));
pArr1[0] = pArr2[0] = 10;
MyFree(pArr1);
MyFree(pArr2);
```

При работата върху проекта, полезни могат да ви бъдат следните външни източници:

* Data alignment: Straighten up and fly right. http://www.ibm.com/developerworks/library/pa-dalign/
* Memory, Part 2: Implementing a Memory Allocator. https://github.com/angrave/SystemProgramming/wiki/Memory,-Part-2%3A-Implementing-a-Memory-Allocator
* Dynamic Memory Allocation: Basic Concepts. http://www.cs.cmu.edu/afs/cs/academic/class/15213-f10/www/lectures/17-allocation-basic.pptx
* Dynamic Memory Allocation: Advanced Concepts. http://www.cs.cmu.edu/afs/cs/academic/class/15213-f10/www/lectures/18-allocation-advanced.pptx
