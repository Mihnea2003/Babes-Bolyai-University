%eliminate_duplicate(l1,...,ln,R)=[] if n=0,
%                              l1 U eliminate(l2,..ln,R) if
%                              is_member(l1,l2,...,ln) is false
%                              eliminate_duplicate otherwise
%flow model(i,o)
eliminate_duplicates([], []).
eliminate_duplicates([Head | Tail], Result) :-
    is_member(Head, Tail),
    eliminate_duplicates(Tail, Result).
eliminate_duplicates([Head | Tail], [Head | Result]) :-
    \+ is_member(Head, Tail),
    eliminate_duplicates(Tail, Result).


%is_member(E,l1..ln)=true if E=l1,
%                    false U is_member(l2,..ln) if E<>l1
%flow model(i,i)
is_member(Element, [Element | _]).
is_member(Element, [_ | Tail]) :-
    is_member(Element, Tail).
%sort(l1,l2..,ln,R)=[],n=0
%                   l1,l2 U sort(l3,..,ln) if l1<l2
%                   l2,l1 U sort(l3,..,ln) if l1>l2
%flow model(i,o)
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
wrapper(L,R):-
    my_sort(L,R1),
    eliminate_duplicates(R1,R).

