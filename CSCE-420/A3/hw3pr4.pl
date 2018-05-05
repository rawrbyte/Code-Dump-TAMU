% Raymond Zhu
% 923008555
% CSCE 420
% Due: March 26, 2018
% hw3pr4.pl

my_sorted([]).
my_sorted([X]).
my_sorted([First,Second]) :- Second >= First.
% checks to see if second elem is larger than head, and recursively does tail until []
my_sorted([Start|[Head|Tail]]) :-   Head >= Start, 
                                    my_sorted([Head|Tail]).

% http://www.learnprolognow.org/lpnpage.php?pagetype=html&pageid=lpn-htmlse24
% Using the append predicate, we can gain deduction of X and [Head|Y] given M 
% By doing so, Head can be eliminated from the M list so that we can recursively call my_perm(Tail, Z)
% This works because each time we are removing the same elem from both my_perm arguments
% Similar but different when compared to using member predicate since member doesn't account for multiples
my_perm([], []).
my_perm([Head|Tail], M) :-  member(Head, M), 
                            append(X, [Head|Y], M), 
                            append(X, Y, Z), 
                            my_perm(Tail, Z).

my_sort([], []).
% deducts all the possibilities of L permutations and picks the one that is sorted
my_sort(L, M) :-    my_perm(M, L), 
                    my_sorted(M).