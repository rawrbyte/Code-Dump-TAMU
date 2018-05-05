% Raymond Zhu
% 923008555
% CSCE 420
% Due: March 26, 2018
% hw3pr1.pl

\+ mortal(X) :- mythical(X).
% p -> (q & r) === p -> q & p -> r
mortal(X) :- \+ mythical(X).
mammal(X) :- \+ mythical(X).
horned(X) :- \+ mortal(X); mammal(X). 
magical(X) :- horned(X).
% http://www.cse.unsw.edu.au/~billw/dictionaries/prolog/dynamic.html
% /1 a.k.a arity 1 because one variable
:-dynamic(mythical/1).