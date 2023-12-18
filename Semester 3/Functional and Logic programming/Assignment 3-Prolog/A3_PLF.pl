% Prolog3:Problem3 :Write a predicate to determine all decomposition of
% n (n given, positive) as sum of consecutive natural numbers.

% This predicate generates a number between the given parameters N and
% M.
% my_between(N - integer, M - integer, K - integer)
% my_between(i,i,o)
% my_between(N,M) = { N, N < M
%                   { my_between(N+1,M)
my_between(N, M, K) :- N < M, K = N.
my_between(N, M, K) :- N == M, !, K = N.
my_between(N, M, K) :- N < M, N1 is N+1, my_between(N1, M, K).

% This predicate generates a pair of integers such that their sum is
% equal with the given parameter N.
% generatePair(N - integer, X - integer, Y - integer)
% generatePair(i,o,o)
% generatePair(N) = { (X,Y), X<Y && X+Y=N
generatePair(N, X, Y) :-
    my_between(1, N, Y),
    my_between(1, N, X),
    X < Y,
    N =:= X + Y.

% This predicate decomposes the given number N into a list of integers
% such that their sum is equal to N.
% decomposeNumber(N - integer, L - list)
% decomposeNumber(i,o)
% decomposeNumber(N) = { [X|L]
decomposeNumber(N, [N]).
decomposeNumber(N, [X|L]) :- generatePair(N, X, Y), decomposeNumber(Y, L).

% This predicate checks it the that elements in the given list have
% consecutive value.
% isConsecutive(L - list)
% isConsecutive(i)
% isConsecutive([l1,l2,..,ln]) = { true, L=[l1,l2] && l1+1=l2
%                                { isConsecutive(l2..ln), l1+1=l2 && n>2
%                                { false, otherwise
isConsecutive([X,Y]):-X+1=:=Y.
isConsecutive([H1,H2|T]):-H2=:=H1+1, isConsecutive([H2|T]).

nAsSumOfConsecutives(N,L):-decomposeNumber(N,X), isConsecutive(X), L=X.

main(N,L):-findall(R,nAsSumOfConsecutives(N,R),L).
