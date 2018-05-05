% Raymond Zhu
% 923008555
% CSCE 420
% Due: March 26, 2018
% hw3pr3.pl

% rules for males
male(king_george).
male(spencer).
male(philip).
male(charles).
male(mark).
male(timothy).
male(andrew).
male(edward).
male(william).
male(peter).
male(mike).
male(harry).
male(prince_george).
male(james).
% rules for females
female(mum).
female(kydd).
female(elizabeth).
female(margaret).
female(diana).
female(camilla).
female(anne).
female(sarah).
female(sophie).
female(kate).
female(autumn).
female(zara).
female(charlotte).
female(beatrice).
female(eugenie).
female(louise).
female(mia).
female(isla).
female(savannah).
% rules for marriages
married(king_george, mum).
married(spencer, kydd).
married(philip, elizabeth).
married(charles, diana).
married(charles, camilla).
married(mark, anne).
married(timothy, anne).
married(andrew, sarah).
married(edward, sophie).
married(william, kate).
married(peter, autumn).
married(mike, zara).
% rules for parents
parents(married(king_george, mum), margaret).
parents(married(king_george, mum), elizabeth).
parents(married(spencer, kydd), diana).
parents(married(philip, elizabeth), charles).
parents(married(philip, elizabeth), anne).
parents(married(philip, elizabeth), andrew).
parents(married(philip, elizabeth), edward).
parents(married(charles, diana), william).
parents(married(charles, diana), harry).
parents(married(mark, anne), peter).
parents(married(mark, anne), zara).
parents(married(andrew, sarah), beatrice).
parents(married(andrew, sarah), eugenie).
parents(married(edward, sophie), louise).
parents(married(edward, sophie), james).
parents(married(william, kate), prince_george).
parents(married(william, kate), charlotte).
parents(married(peter, autumn), savannah).
parents(married(peter, autumn), isla).
parents(married(mike, zara), mia).
% Given C and given facts, M and F can be deducted
mother(M, C)                :-  parents(married(F,M), C).
father(F, C)                :-  parents(married(F,M), C).
% Deducts the parents of GC, and deducts GF/GM by the GC's parents
grandfather(GF, GC)         :-  (father(X, GC);mother(X, GC)), parents(married(GF, S), X).
grandmother(GM, GC)         :-  (father(X, GC);mother(X, GC)), parents(married(S, GM), X).
% Checks whether GF or GM, and deducts GF/GM's children and, depending on father/mother, deducts the GC(s)
grandchild(GC, GP)          :-  (grandfather(GP, GC), parents(married(GP, S), C), (father(C, GC);mother(C, GC)));
                                (grandmother(GP, GC), parents(married(S, GP), C), (father(C, GC);mother(C, GC))).    
% Checks whether X and Y have the same parents where X != Y
sibling(X, Y)               :-  parents(married(M, F), Y), parents(married(M, F), X), \+ X == Y. 
% Deducts by checking whether spouce is male/female, and deducts spouce's siblings that are male/female
% Or, deducts X's siblings and where X and X's sibling's spouce are not siblings and are male/female
brother_in_law(S, X)        :-  ((married(X, Y);married(Y, X)), sibling(Y, S), male(S));
                                (sibling(X, Y), (married(S, Y);married(Y, S)), \+sibling(S, X), male(S)).
sister_in_law(S, X)         :-  ((married(X, Y);married(Y, X)), sibling(Y, S), female(S));
                                (sibling(X, Y), (married(S, Y);married(Y, S)), \+sibling(S, X), female(S)).
% Deducts the parents of GGC, and deducts the GF/GM by the GGC's parents, and deducts GGP from their child GF/GM
great_grandparent(GGP, GGC) :-  (father(X, GGC); mother(X, GGC)), (father(Y, X); mother(Y, X)), 
                                (parents(married(GGP, S), Y);parents(married(S, GGP), Y)).
% Deducts the parents of given child, and deducts the children of the parent's siblings
first_cousin(X, Y)          :-  parents(married(M, F), Y), (sibling(M, Z);sibling(F, Z)), 
                                (parents(married(Z, S), X);parents(married(S, Z), X)).
% Deducts the parents of given individual, and deducts the siblings that are male/female
aunt(X, Y)                  :-  parents(married(M, F), Y), (sibling(M, X);sibling(F, X)), female(X).
uncle(X, Y)                 :-  parents(married(M, F), Y), (sibling(M, X);sibling(F, X)), male(X).               
% Deducts siblings that are male/female
brother(X, Y)               :-  sibling(X, Y), male(X).
sister(X, Y)                :-  sibling(X, Y), female(X).
% Checks whether parent is male/female and deducts their children who are male/female
daughter(C, P)              :-  (parents(married(S, P), C);parents(married(P, S), C)), female(C).
son(C, P)                   :-  (parents(married(S, P), C);parents(married(P, S), C)), male(C).
% First one is a base case to end recursion
% Rescursively calls ancestor for all ancestors depending on blood-line based on child's mother/father
ancestor(X, Y)              :-  mother(X, Y);father(X, Y).
ancestor(X, Y)              :-  (mother(M, Y), ancestor(X, M));(father(F, Y), ancestor(X, F)).