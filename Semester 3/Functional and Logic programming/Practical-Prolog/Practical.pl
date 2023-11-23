
%minimul dintre 2 elemente
min(E,R,R):-
    R < E.
min(E,R,E):-
    E =< R.
%gaseste minimul
min_list([H],H).
min_list([H|T],R1):-
    min_list(T,R),
    min(H,R,R1).
%remove la orice obiect
removeOc([],_,[]).
removeOc([H|T],E,[H|R]):-
    H=\=E,
    removeOc(T,E,R).
removeOc([H|T],E,R):-
    H=:=E,
    removeOc(T,E,R).
%remove la minim
remove_min([],[]).
remove_min(L,R):-
    min_list(L,R1),
    removeOc(L,R1,R).
gcd(A, B, Result) :-
    A >= B,
    R is A mod B,
    gcd(B, R, Result).
gcd(A, B, Result) :-
    A < B,
    gcd(B, A, Result).

% Predicate to calculate the least common multiple (LCM)
lcm(A, B, Result) :-
    gcd(A, B, GCD),
    Result is abs(A * B) // GCD.

%ex4 a
%exist_in(l1,..,ln,E,0)=0 if L=[]
%                       1 if l1=E
%                       exist_in(l2,..ln,E,0) if l1<>E
%exist_in(L-list,E-element,f-flag)
%flow model (i,i,o)
exist_in([],_,0).
exist_in([H|_],E,1):-
    H=:=E.
exist_in([H|T],E,R):-
    H=\=E,
    exist_in(T,E,R).
%diff_set(L1,L2,R)=[] if L1,L2=[]
%                  l1 U diff_set(l2,..ln,L2,R) if exist_In(L2,l1,R)=0
%                  diff_set(l2,..ln,L2,R) if exist_In(L2,l1,R)=1
diff_set([],[],[]).
diff_set([],_,[]).
diff_set([H|T],[],[H|R]):-
    diff_set(T,[],R).
diff_set([H|T],L2,R):-
    \+ exist_in(L2,H,0),
    diff_set(T,L2,R).
diff_set([H|T],L2,[H|R]):-
    \+ exist_in(L2,H,1),
    diff_set(T,L2,R).
%add1(l1,l2,..ln,R)=[] if L=[]
%                   l1,1 U add1(l2,..,ln,R)if l1 mod 2 =0
%                   l1 U add1(l2,..,ln) if l1 mod 2=1
%flow model:(i,i),(i,o)
add1([],[]).
add1([H|T],[H,1|R]):-
    H mod 2 =:= 0,
    add1(T,R).
add1([H|T],[H|R]):-
    H mod 2 =:= 1,
    add1(T,R).

substitute([],_,_,[]).
substitute([H|T],E,L,[L|R]):-
    H=:=E,
    substitute(T,E,L,R).
substitute([H|T],E,L,[H|R]):-
    H=\=E,
    substitute(T,E,L,R).

%p2 ex2 a
%sort(l1,l2..,ln,R)=[],n=0
%                   l1,l2 U sort(l3,..,ln) if l1<l2
%                   l2,l1 U sort(l3,..,ln) if l1>l2
my_sort([], []).
my_sort([H|T], Sorted) :-
    my_sort(T, SortedTail),
    insert(H, SortedTail, Sorted).
insert(X, [], [X]).
insert(X, [Y | Rest], [X, Y | Rest]) :-
    X =< Y.
insert(X, [Y | Rest], [Y | SortedRest]) :-
    X > Y,
    insert(X, Rest, SortedRest).
%p2 ex2 b
iss_list([]).
iss_list([_|_]).

sort_homogeneous([],[]).
sort_homogeneous([H|T],[H|R]):-
    \+ iss_list(H),
    sort_homogeneous(T,R).
sort_homogeneous([H|T],[R1|R]):-
    iss_list(H),
    my_sort(H,R1),
    sort_homogeneous(T,R).
%pb2 ex3a
merge_sets([],[],[]).
merge_sets([H|T],L,[H|R]):-
    removeOc(L,H,R1),
    merge_sets(T,R1,R).
merge_sets([],[H|T],[H|R]):-
    merge_sets([],T,R).
%p2 ex3b
merge_homogeneous([],[]).
merge_homogeneous([H|T],[H|R]):-
    \+ iss_list(H),
    merge_homogeneous(T,R).
merge_homogeneous([H|T],R):-
    iss_list(H),
    merge_sets(H,R,R1),
    merge_homogeneous(T,R1).
%p2 ex11 a
replace_elem([],_,_,[]).
replace_elem([H|T],E,V,[H|R]):-
    H=\=E,
    replace_elem(T,E,V,R).
replace_elem([H|T],E,V,[V|R]):-
    H=:=E,
    replace_elem(T,E,V,R).
%p2 ex11 b
max_list([],R):- R = 0.
max_list([H|T],R):-
    \+ iss_list(H),
    H >= R,
    max_list(T,H).
max_list([H|T],R):-
    \+ iss_list(H),
    H < R,
    max_list(T,R).
max_list([H|T], R) :-
    iss_list(H),
    max_list(T, R).















