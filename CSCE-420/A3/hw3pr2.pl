% Raymond Zhu
% 923008555
% CSCE 420
% Due: March 26, 2018
% hw3pr2.pl

% base case
adjacent(a,s).
adjacent(a,z).
adjacent(a,t).
adjacent(z,o).
adjacent(s,f).
adjacent(s,r).
adjacent(s,o).
adjacent(t,l).
adjacent(f,b).
adjacent(r,p).
adjacent(r,c).
adjacent(l,m).
adjacent(b,p).
adjacent(b,g).
adjacent(b,u).
adjacent(p,c).
adjacent(c,d).
adjacent(m,d).
adjacent(u,v).
adjacent(u,h).
adjacent(v,i).
adjacent(h,e).
adjacent(i,n).

% http://www.swi-prolog.org/pldoc/man?predicate=member/2
% checks if path is a set of distinct cities
alldiff([]).
alldiff([Head|Tail]) :- \+ member(Head,Tail), alldiff(Tail).

% to account for both directions
valid_move(X,Y) :- adjacent(X,Y).
valid_move(X,Y) :- adjacent(Y,X).

% keeps track of visited nodes to limit the search and checks if the next move is valid
valid_path([Goal],Moves,Goal,Goal).
valid_path([X,Y],Moves,X,Y):-valid_move(X,Y).
valid_path([Start|[Head|Tail]],Moves,Start,Goal):- \+member(Start,Moves),append(Moves, [Start], M),valid_move(Start,Head),valid_path([Head|Tail],M,Head,Goal).

% path(P,Start,Goal) means P is a path from Start to Goal and included alldiff check 
path(P, Start, End) :- valid_path(P,[],Start,End), alldiff(P).
