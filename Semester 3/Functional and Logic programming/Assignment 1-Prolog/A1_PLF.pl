% Ex 5 - a
/*
removeOccurences(l1,l2,..,ln,E,[])=0 if the list=[]
                                  remove(l2,l3,...E,ln,[l1]),l1<>E
                                  remove(l2,l3,..,E,[]) l1=E */
% removeOccurences(L - list, E - number, R - result list)
% flow model (i, i, o)

removeOccurences([], _, []).

removeOccurences([H|T], E, [H|R]):-
    H =\= E,
    removeOccurences(T, E, R).

removeOccurences([H|T], E, R):-
    H =:= E,
    removeOccurences(T, E, R).
/*Write a predicate to compute the union of two sets
 * union(l1,l2,...,ln, L1,L2,...,Ln,[])=[] if the list1=[] and list2=[]
                      union(l2,..,ln,L1,L2,..,Ln,[]),list1<>[]
                      union([],L2,..Ln,[l1,..ln,L1]),list=[] and list2<>[]*/
% Union(L1 - list, L2 - list, R - result list)
% flow model (i, i, o)

union([], [], []).
union([H|T], B, [H|R]):-
    removeOccurences([H|T], H, R1),
    removeOccurences(B, H, R2),
    union(R1, R2, R).
union([], B, R):-
    union(B, [], R).
%union([1, 2, 3], [3, 4, 5], Result)
% Ex 5 - b
/*generateSets(l1,l2,..ln,K,[])=[] if k=0
                              [l1]+generatesets(l2,..ln,k-1),k<>0
                              generatesets(l2,..ln,k)*/
% generateSets(L - list, K - number, R - result list)
% flow model (i i o)

generateSets(_, 0, []):-
    !.
generateSets([H|T], K, [H|R]):-
    K1 is K - 1,
    generateSets(T, K1, R).
generateSets([_|T], K, R):-
    generateSets(T, K, R).

generateAllSets(L, R):-
    findall(R1, generateSets(L, 3, R1), R).
%generateAllSets([1, 2, 3, 4], Result)





